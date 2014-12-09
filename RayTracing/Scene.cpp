#include "Scene.h"
#include "Ray.h"
#include "Shape.h"
#include <iostream>
#include <fstream>

#include "EasyBMP.h"
#include "EasyBMP_BMP.h"
#include "EasyBMP_DataStructures.h"
#include "EasyBMP_VariousBMPutilities.h"
#include "EasyBMP.cpp"

Scene::Scene()
{
	// Not sure whether to set defaults here or not?
	// In this case probably more useful to be able to have an empty instance.
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

void Scene::TraceRays()
{
	BMP image;
	image.SetSize(_viewport.GetNumberOfPixels(1), _viewport.GetNumberOfPixels(2));
	image.SetBitDepth(32);

	double z = _viewport.GetPosition().Z();

	for (int x = 0; x < _viewport.GetNumberOfPixels(1); x++)
	{
		for (int y = 0; y < _viewport.GetNumberOfPixels(2); y++)
		{
			double xRay = x / (double)_viewport.GetNumberOfPixels(1) * _viewport.GetDimension(1) - _viewport.GetDimension(1) / 2.0;
			double yRay = y / (double)_viewport.GetNumberOfPixels(2) * _viewport.GetDimension(2) - _viewport.GetDimension(2) / 2.0;
			Vector direction(xRay, yRay, z);

			Ray ray(_observer, direction);
			
			image.SetPixel(x, y, TraceRay(ray).Normalise());
		}
	}
	image.WriteToFile("spheres.bmp");	
}

int Scene::GetIndexOfClosestShape(std::vector<double> intersections)
{
	int minimumIntersection = -1;

	if (intersections.size() == 1 && intersections.at(0) > 0)
	{
		minimumIntersection =  0; //Only one object so no need to calculate.
	}
	else
	{
		double max = 0;
		for (int i = 0; i < intersections.size(); i++)
		{
			if (max < intersections.at(i))
			{
				max = intersections.at(i);
			}
			if (max > 0) // needs to be > -1
			{
				for (int i = 0; i < intersections.size(); i++)
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

	

	for (int i = 0; i < _sceneObjects.size(); i++)
	{
		intersections.push_back(_sceneObjects[i]->Intersection(ray));
	}
	int indexOfClosestShape = GetIndexOfClosestShape(intersections);
	
	if (indexOfClosestShape != -1 && intersections.at(indexOfClosestShape) > _epsilon)
	{
		Ray incidentRay = ray.RayLine(intersections.at(indexOfClosestShape));
		Shape *closestShape = _sceneObjects[indexOfClosestShape];
		RGBColour shapeColour = closestShape->Colour();
		RGBColour totalReflectedLight;
		ambientLight = shapeColour * _ambientCoefficient;

		if (closestShape->ReflectionCoefficient() > 0) //shape is reflective
		{
			totalReflectedLight = reflectRays(closestShape, incidentRay, ray);
		}
		light = ambientLight + illumination(incidentRay, closestShape, shapeColour, ray) + totalReflectedLight;
	}
	return light;
}

RGBColour Scene::illumination(Ray incidentRay, Shape *closestShape, RGBColour shapeColour, Ray ray)
{
	RGBColour diffuseLight = _backgroundColour;
	RGBColour specularLight = _backgroundColour;
	double projectionNormalToSource = 0.0;

	for (int i = 0; i < _lightSources.size(); i++)
	{
		Ray shadowRay(incidentRay.Direction(), (_lightSources.at(i).GetPosition() - incidentRay.Direction()).UnitVector());

		Vector surfaceNormal = closestShape->SurfaceNormal(incidentRay);

		//lambertian shading.
		projectionNormalToSource = surfaceNormal.ScalarProduct(shadowRay.Direction());

		if (projectionNormalToSource > 0)
		{
			/*std::fstream file;
			file.open("log.txt", std::ios_base::app);*/

			bool isShadow = false;

			std::vector<double> shadowIntersections;
			
			Ray temp(incidentRay.Direction(), (_lightSources.at(i).GetPosition() - incidentRay.Direction()));
			for (int j = 0; j < _sceneObjects.size(); j++)
			{
				shadowIntersections.push_back(_sceneObjects.at(j)->Intersection(temp));
			}

			//Test each point to see if it is in shadow.
			for (int j = 0; j < shadowIntersections.size(); j++)
			{
				if (shadowIntersections.at(j) != -1)
				{
					Ray test(ray.Direction(), temp.Direction().UnitVector() * shadowIntersections.at(j));

					/*file << "light source: " << _lightSources.at(i).GetPosition().X() << ", " << _lightSources.at(i).GetPosition().Y() << ", " << _lightSources.at(i).GetPosition().Z() << std::endl;
					file << "incident direction: " << incidentRay.Direction().X() << ", " << incidentRay.Direction().Y() << ", " << incidentRay.Direction().Z() << std::endl;
					file << "intersection: " << shadowIntersections.at(j) << std::endl;
					file << "test magnitude: " << test.Direction().Magnitude() << std::endl;
					file << "temp magnitude: " << temp.Direction().Magnitude() << std::endl;
					file << "test direction: " << (test.Direction().UnitVector() * shadowIntersections.at(j)).X() << ", " << (test.Direction().UnitVector() * shadowIntersections.at(j)).Y() << ", " << (test.Direction().UnitVector() * shadowIntersections.at(j)).Z() << std::endl;					*/

					if (temp.Direction().Magnitude() > _epsilon && test.Direction().Magnitude() <= temp.Direction().Magnitude() && closestShape != _sceneObjects.at(j))
					{
						isShadow = true;
					}
					break;
				}
			}			

			if (!isShadow)
			{
				diffuseLight = diffuseLight + (closestShape->Colour() * projectionNormalToSource * closestShape->DiffuseCoefficient() * _lightSources.at(i).DiffuseIntensity());
				specularLight = specularLight + specularReflection(_lightSources.at(i), projectionNormalToSource, closestShape, incidentRay, shadowRay, ray);			
			}

			/*file << "isShadow: " << isShadow << std::endl;
			file << "shadow ray Direction: " << temp.Direction().X() << ", " << temp.Direction().Y() << ", " << temp.Direction().Z() << std::endl;
			file << "shadow ray Origin: " << temp.Origin().X() << ", " << temp.Origin().Y() << ", " << temp.Origin().Z() << std::endl;
			file << "-------------------------------------------------" << std::endl;
			file.close();*/
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
			specularIllumination = pow(specularIllumination, closestShape->Shininess()); //^alpha
			specularLight = specularLight + lightSource.Colour() * specularIllumination * closestShape->ReflectionCoefficient() * lightSource.SpecularIntensity();
		}
	}
	return specularLight;
}

RGBColour Scene::reflectRays(Shape *shape, Ray incidentRay, Ray ray)
{
	RGBColour totalReflectedLight;
	Vector reflectionSurfaceNormal = shape->SurfaceNormal(incidentRay);
	Ray reflectedRay = incidentRay.Reflection(reflectionSurfaceNormal);

	std::vector<double> reflectionIntersections;

	for (int i = 0; i < _sceneObjects.size(); i++)
	{
		reflectionIntersections.push_back(_sceneObjects.at(i)->Intersection(reflectedRay));
	}

	int indexOfClosestReflectedShape = GetIndexOfClosestShape(reflectionIntersections);
	
	if (indexOfClosestReflectedShape != -1 && indexOfClosestReflectedShape > _epsilon && _sceneObjects[indexOfClosestReflectedShape] != shape)
	{
		Shape *closestReflectedShape = _sceneObjects[indexOfClosestReflectedShape];
		Vector reflectedIntersectionDirection = reflectedRay.Direction().UnitVector() * reflectionIntersections.at(indexOfClosestReflectedShape) * -1;
		
		Ray test(reflectedRay.Origin(), reflectedIntersectionDirection);
		RGBColour reflectedLight = illumination(test, closestReflectedShape, closestReflectedShape->Colour(), test);
		totalReflectedLight = totalReflectedLight + reflectedLight;

		std::fstream file;
		file.open("reflectionlog.txt", std::ios_base::app,std::fstream::trunc);
		file << "reflectionSurface normal: " << reflectionSurfaceNormal.X() << ", " << reflectionSurfaceNormal.Y() << ", " << reflectionSurfaceNormal.Z() << ", " << std::endl;
		file << "incident ray origin: " << incidentRay.Origin().X() << ", " << incidentRay.Origin().Y() << ", " << incidentRay.Origin().Z() << ", " << std::endl;
		file << "incident ray direction: " << incidentRay.Direction().X() << ", " << incidentRay.Direction().Y() << ", " << incidentRay.Direction().Z() << ", " << std::endl;
		file << "reflected ray origin: " << reflectedRay.Origin().X() << ", " << reflectedRay.Origin().Y() << ", " << reflectedRay.Origin().Z() << ", " << std::endl;
		file << "reflected ray direction: " << reflectedRay.Direction().X() << ", " << reflectedRay.Direction().Y() << ", " << reflectedRay.Direction().Z() << ", " << std::endl;
		file << "reflected intersection: " << reflectionIntersections.at(indexOfClosestReflectedShape) << std::endl;
		file << "reflected intersection direction: " << reflectedIntersectionDirection.X() << ", " << reflectedIntersectionDirection.Y() << ", " << reflectedIntersectionDirection.Z() << ", " << std::endl;
		file << "test origin: " << test.Origin().X() << ", " << test.Origin().Y() << ", " << test.Origin().Z() << ", " << std::endl;
		file << "test Direction: " << test.Direction().X() << ", " << test.Direction().Y() << ", " << test.Direction().Z() << ", " << std::endl;
		file << "reflected light: " << reflectedLight.Red() << ", " << reflectedLight.Green() << ", " << reflectedLight.Blue() << std::endl;
		file << "------------------------------------------------" << std::endl;
		file.close();

	}
	return totalReflectedLight;
}