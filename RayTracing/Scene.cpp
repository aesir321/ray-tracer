#include "Scene.h"
#include "Ray.h"
#include "Shape.h"
#include <iostream>
#include <fstream>
#include <string>

#include "EasyBMP.h"
#include "EasyBMP_BMP.h"
#include "EasyBMP_DataStructures.h"
#include "EasyBMP_VariousBMPutilities.h"
#include "EasyBMP.cpp"

Scene::Scene()
{
	//Preserve as a default state as a scene should be constructed and a default state cannot be assumed.
}

Scene::Scene(Viewport viewport, Vector observer, std::vector<LightSource> lightSources, std::vector<Shape*> sceneObjects, RGBColour backgroundColour, double ambientCoefficient)
{
	_viewport = viewport;
	_observer = observer;
	_lightSources = lightSources;
	_sceneObjects = sceneObjects;
	_backgroundColour = backgroundColour;
	_ambientCoefficient = ambientCoefficient;
}

Scene::~Scene()
{

}

void Scene::Populate(LightSource lightSource)
{
	_lightSources.push_back(lightSource);
}

void Scene::Populate(Vector observer)
{
	_observer = observer;
}

void Scene::Populate(Viewport viewport)
{
	_viewport = viewport;
}

void Scene::Populate(Shape* shape)
{
	_sceneObjects.push_back(shape);
}

void Scene::SetAmbientCoefficient(double ambientCoefficient)
{
	_ambientCoefficient = ambientCoefficient;
}

void Scene::TraceRays(const char *filename)
{
	BMP image;
	image.SetSize(_viewport.XPixels(), _viewport.YPixels());
	image.SetBitDepth(32);

	double z = _viewport.Position().Z();

	for (int x = 0; x < _viewport.XPixels(); x++)
	{
		for (int y = 0; y < _viewport.YPixels(); y++)
		{
			double xRay = x / (double)_viewport.XPixels() * _viewport.Width() - _viewport.Width() / 2.0;
			double yRay = y / (double)_viewport.YPixels() * _viewport.Height() - _viewport.Height() / 2.0;
			Vector direction(xRay, yRay, z);

			Ray ray(_observer, direction);

			image.SetPixel(x, y, TraceRay(ray).Normalise());
			
		}
	}

	image.WriteToFile(filename);
}

int Scene::getIndexOfClosestShape(std::vector<double> intersections)
{
	int minimumIntersection = -1;

	if (intersections.size() == 1 && intersections.at(0) > 0)
	{
		minimumIntersection = 0; //Only one object so no need to calculate.
	}
	else
	{
		double max = 0;
		for (unsigned int i = 0; i < intersections.size(); i++)
		{
			if (max < intersections.at(i))
			{
				max = intersections.at(i);
			}
			if (max > 0) // needs to be > -1
			{
				for (unsigned int i = 0; i < intersections.size(); i++)
				{
					if (intersections.at(i) > 0 && intersections.at(i) <= max)
					{
						max = intersections.at(i);
						minimumIntersection = i;
					}
				}
			}
			else
			{
				minimumIntersection = -1; //No positive intersections
			}
		}
	}
	return minimumIntersection;
}

RGBColour Scene::TraceRay(Ray ray)
{
	RGBColour light = _backgroundColour;
	RGBColour ambientLight;

	std::vector<double> intersections;

	for (unsigned int i = 0; i < _sceneObjects.size(); i++)
	{
		intersections.push_back(_sceneObjects[i]->Intersection(ray, _epsilon));
	}
	int indexOfClosestShape = getIndexOfClosestShape(intersections);

	if (indexOfClosestShape != -1 && intersections.at(indexOfClosestShape) > _epsilon)
	{
		Ray incidentRay = ray.RayLine(intersections.at(indexOfClosestShape));
		Shape *closestShape = _sceneObjects[indexOfClosestShape];
		RGBColour shapeColour = closestShape->Colour();
		RGBColour totalReflectedLight;
		ambientLight = shapeColour * _ambientCoefficient;
		
		if (closestShape->ReflectionCoefficient() > 0) //shape is reflective
		{
			totalReflectedLight = reflectRays(closestShape, incidentRay, 0);
		}
		light = ambientLight  + illumination(incidentRay, closestShape, shapeColour, ray) + totalReflectedLight;
	}
	return light;
}

RGBColour Scene::illumination(Ray incidentRay, Shape *closestShape, RGBColour shapeColour, Ray ray)
{
	RGBColour diffuseLight = _backgroundColour;
	RGBColour specularLight = _backgroundColour;
	double projectionNormalToSource = 0.0;

	for (unsigned int i = 0; i < _lightSources.size(); i++)
	{
		Ray sourceRay(incidentRay.Direction(), (_lightSources.at(i).GetPosition() - incidentRay.Direction()).UnitVector());

		Vector surfaceNormal = closestShape->SurfaceNormal(incidentRay);

		//lambertian shading.
		projectionNormalToSource = surfaceNormal.ScalarProduct(sourceRay.Direction());

		if (projectionNormalToSource > 0)
		{
			bool isShadow = false;

			std::vector<double> shadowIntersections;

			Ray temp(incidentRay.Direction(), (_lightSources.at(i).GetPosition() - incidentRay.Direction()));
			for (unsigned int j = 0; j < _sceneObjects.size(); j++)
			{
				shadowIntersections.push_back(_sceneObjects.at(j)->Intersection(temp, _epsilon));
			}

			//Test each point to see if it is in shadow.
			for (unsigned int j = 0; j < shadowIntersections.size(); j++)
			{
				if (shadowIntersections.at(j) != -1)
				{
					Ray shadowRay(ray.Direction(), sourceRay.Direction().UnitVector() * shadowIntersections.at(j));

					if (shadowRay.Direction().Magnitude() > _epsilon && shadowRay.Direction().Magnitude() <= temp.Direction().Magnitude() && closestShape != _sceneObjects.at(j))
					{
						isShadow = true;
						break;
					}
				}
			}

			if (!isShadow)
			{
				diffuseLight = diffuseLight + (closestShape->Colour() * projectionNormalToSource * closestShape->DiffuseCoefficient() * _lightSources.at(i).DiffuseIntensity());
				specularLight = specularLight + specularReflection(_lightSources.at(i), projectionNormalToSource, closestShape, incidentRay, sourceRay, ray);
			}
		}
	}
	return diffuseLight + specularLight;
}

RGBColour Scene::specularReflection(LightSource lightSource, double projectionNormalToSource, Shape *closestShape, Ray incidentRay, Ray rayToSource, Ray ray)
{
	RGBColour specularLight;
	if (closestShape->ReflectionCoefficient() > 0)//Is the shape reflective?
	{
		Vector reflectionSurfaceNormal = closestShape->SurfaceNormal(incidentRay);
		Ray reflectedRay = ray.Reflection(reflectionSurfaceNormal);
		double specularIllumination = reflectedRay.Direction().UnitVector().ScalarProduct(rayToSource.Direction().UnitVector());

		if (specularIllumination > 0)
		{
			specularIllumination = pow(specularIllumination, closestShape->Shininess());
			specularLight = specularLight + lightSource.Colour() * specularIllumination * closestShape->ReflectionCoefficient() * lightSource.SpecularIntensity();

		}
	}
	return specularLight;
}

RGBColour Scene::reflectRays(Shape *shape, Ray incidentRay, int depth)
{
	RGBColour totalReflectedLight;
	Vector reflectionSurfaceNormal = shape->SurfaceNormal(incidentRay);
	Ray reflectedRay = incidentRay.Reflection(reflectionSurfaceNormal);

	std::vector<double> reflectionIntersections;

	for (unsigned int i = 0; i < _sceneObjects.size(); i++)
	{
		reflectionIntersections.push_back(_sceneObjects.at(i)->Intersection(reflectedRay, _epsilon));
	}

	int indexOfClosestReflectedShape = getIndexOfClosestShape(reflectionIntersections);
	if (indexOfClosestReflectedShape != -1 && reflectionIntersections.at(indexOfClosestReflectedShape) > _epsilon)
	{
		Shape *closestReflectedShape = _sceneObjects[indexOfClosestReflectedShape];

		for (unsigned int i = 0; i < reflectionIntersections.size(); i++)
		{
			if (_sceneObjects[indexOfClosestReflectedShape] != shape)
			{
				Vector reflectedIntersectionDirection = reflectedRay.Direction().UnitVector() * reflectionIntersections.at(indexOfClosestReflectedShape);
				Ray intersectedReflectedRay(reflectedRay.Origin(), reflectedIntersectionDirection);

				RGBColour reflectedLight;
				if (depth < _maxDepth)
				{
					reflectedLight = illumination(intersectedReflectedRay, closestReflectedShape, closestReflectedShape->Colour(), reflectedRay);
					reflectedLight = reflectedLight + reflectRays(closestReflectedShape, intersectedReflectedRay, depth + 1);
				}
				totalReflectedLight = totalReflectedLight + reflectedLight;
			}
		}
	}
	return totalReflectedLight;
}
