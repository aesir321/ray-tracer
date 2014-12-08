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

			image.SetPixel(x, y, TraceRay(ray).GetPixelColour());
		}
	}
	image.WriteToFile("spheres.bmp");	
}

int Scene::GetIndexOfClosestShape(std::vector<double> intersections)
{
	//still needs checking to make sure logic is correct.
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
			if (max > 0)
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
	RGBColour totalReflectedLight;

	std::vector<double> intersections;

	for (int i = 0; i < _sceneObjects.size(); i++)
	{
		intersections.push_back(_sceneObjects[i]->Intersection(ray));
	}
	int indexOfClosestShape = GetIndexOfClosestShape(intersections); //Find a way to refactor this out?  Shouldn't need to do it every time.
	
	if (indexOfClosestShape != -1 && intersections.at(indexOfClosestShape) > _epsilon)
	{
		Ray incidentRay = ray.RayLine(intersections.at(indexOfClosestShape));
		Shape *closestShape = _sceneObjects[indexOfClosestShape];
		RGBColour shapeColour = closestShape->Colour();
		//RGBColour totalReflectedLight;
		ambientLight = shapeColour * _ambientCoefficient;

		if (closestShape->ReflectionCoefficient() > 0) //shape is reflective
		{
			totalReflectedLight = reflectRays(closestShape, incidentRay);
		}

		light = ambientLight + illumination(incidentRay, closestShape, shapeColour) +totalReflectedLight;
	}
	/*if (ambientLight.Red() != 0)
	{
		std::fstream file;
		file.open("log.txt", std::ios_base::app);
		file << "ambient: " << ambientLight.Red() << ", " << ambientLight.Green() << ", " << ambientLight.Blue() << std::endl;
		file << "totalReflectedLight: " << totalReflectedLight.Red() << ", " << totalReflectedLight.Green() << ", " << totalReflectedLight.Blue() << std::endl;
		file << "light: " << light.Red() << ", " << light.Green() << ", " << light.Blue() << std::endl;
		file << "-----------------------------------------------------------" << std::endl;
		file.close();
	}*/
	return light;
}

RGBColour Scene::illumination(Ray incidentRay, Shape *closestShape, RGBColour shapeColour)
{
	RGBColour diffuseLight = _backgroundColour;
	RGBColour specularLight = _backgroundColour;

	for (int i = 0; i < _lightSources.size(); i++)
	{
		Ray shadowRay(incidentRay.Direction(), (_lightSources.at(i).GetPosition().UnitVector() - incidentRay.Direction().UnitVector()));
		Vector surfaceNormal = closestShape->SurfaceNormal(shadowRay);

		//lambertian shading.
		double projectionNormalToSource = surfaceNormal.ScalarProduct(shadowRay.Direction().UnitVector());

		if (projectionNormalToSource > 0)
		{
			//bool isShadow = false;

			//std::vector<double> shadowIntersections;

			//for (int j = 0; j < _sceneObjects.size() && isShadow == false; j++)
			//{
			//	shadowIntersections.push_back(_sceneObjects.at(j)->Intersection(shadowRay));
			//}

			////Test each point to see if it is in shadow.
			//for (int j = 0; j < shadowIntersections.size(); j++)
			//{
			//	Ray test(incidentRay.Direction(), shadowRay.Direction().UnitVector() * shadowIntersections.at(j));

			//	/*std::fstream file;
			//	file.open("log.txt", std::ios_base::app);
			//	file << "incidentRay Origin: " << incidentRay.Origin().X() << ", " << incidentRay.Origin().Y() << ", " << incidentRay.Origin().Z() << std::endl;
			//	file << "incidentRay Direction: " << incidentRay.Direction().X() << ", " << incidentRay.Direction().Y() << ", " << incidentRay.Direction().Z() << std::endl;
			//	file << "shadowRay Origin: " << shadowRay.Origin().X() << ", " << shadowRay.Origin().Y() << ", " << shadowRay.Origin().Z() << std::endl;
			//	file << "shadowRay Direction: " << shadowRay.Direction().X() << ", " << shadowRay.Direction().Y() << ", " << shadowRay.Direction().Z() << std::endl;
			//	file << "LightSource position: " << _lightSources.at(i).GetPosition().X() << ", " << _lightSources.at(i).GetPosition().Y() << ", " << _lightSources.at(i).GetPosition().Z() << std::endl;
			//	file << "shadowIntersection: " << shadowIntersections.at(k) << std::endl;
			//	file << "test Origin: " << test.Origin().X() << ", " << test.Origin().Y() << ", " << test.Origin().X() << std::endl;
			//	file << "test Direction: " << test.Direction().X() << ", " << test.Direction().Y() << ", " << test.Direction().Z() << std::endl;
			//	file << "test Magnitude: " << test.Direction().Magnitude() << std::endl;
			//	file << "shadowRay Magnitude: " << shadowRay.Direction().Magnitude() << std::endl;
			//	file << "-------------------------------------------------------------------------" << std::endl;
			//	file.close();*/

			//	if (test.Direction().Magnitude() > _epsilon && test.Direction().Magnitude() <= shadowRay.Direction().Magnitude())
			//	{
			//		isShadow = true;
			//	}	
			//	break;
			//}			

			//if (!isShadow)
			//{
			//	diffuseLight = diffuseLight + shapeColour * _lightSources.at(i).Colour() * projectionNormalToSource * closestShape->DiffuseCoefficient() * _lightSources.at(i).DiffuseIntensity();
			//	specularLight = specularLight + specularReflection(_lightSources.at(i), projectionNormalToSource, closestShape, incidentRay, shadowRay);
			//}
			diffuseLight = diffuseLight + shapeColour * _lightSources.at(i).Colour() * projectionNormalToSource * closestShape->DiffuseCoefficient() * _lightSources.at(i).DiffuseIntensity();
			specularLight = specularLight + specularReflection(_lightSources.at(i), projectionNormalToSource, closestShape, incidentRay, shadowRay);
		}
	}
	/*std::fstream file;
	file.open("log.txt", std::ios_base::app);
	file << "diffuse: " << diffuseLight.Red() << ", " << diffuseLight.Green() << ", " << diffuseLight.Blue() << std::endl;
	file << "specular: " << specularLight.Red() << ", " << specularLight.Green() << ", " << specularLight.Blue() << std::endl;
	file.close();*/
	return diffuseLight + specularLight;
}

RGBColour Scene::specularReflection(LightSource lightSource, double projectionNormalToSource, Shape *closestShape, Ray incidentRay, Ray rayToSource)
{
	RGBColour specularLight;
	if (closestShape->ReflectionCoefficient() > 0)
	{
		Vector reflectionSurfaceNormal = closestShape->SurfaceNormal(incidentRay);
		Ray reflectedRay = incidentRay.Reflection(reflectionSurfaceNormal);
		double specularIllumination = reflectedRay.Direction().UnitVector().ScalarProduct(incidentRay.Direction().UnitVector());

		if (specularIllumination > 0)
		{
			specularIllumination = pow(specularIllumination, closestShape->Shininess()); //^gamma
			specularLight = lightSource.Colour() * specularIllumination * closestShape->ReflectionCoefficient() * lightSource.SpecularIntensity();
		}
	}
	return specularLight;
}

RGBColour Scene::reflectRays(Shape *shape, Ray incidentRay)
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
	
	if (indexOfClosestReflectedShape != -1 && indexOfClosestReflectedShape > _epsilon)
	{
		Shape *closestReflectedShape = _sceneObjects[indexOfClosestReflectedShape];
		Vector reflectedIntersectionOrigin = reflectedRay.Origin() + reflectedRay.Direction() * reflectionIntersections.at(indexOfClosestReflectedShape);
		Ray test(reflectedIntersectionOrigin, reflectedRay.Direction());
		RGBColour reflectedLight = illumination(test, closestReflectedShape, closestReflectedShape->Colour());
		totalReflectedLight = totalReflectedLight + reflectedLight;
	}
	return totalReflectedLight;
}