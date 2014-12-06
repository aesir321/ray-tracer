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
	double _ambientCoefficient = ambientCoefficient;
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

void Scene::AddViewPort(Viewport viewport)
{
	_viewport = viewport;
}

void Scene::Populate(Shape* shape)
{
	_sceneObjects.push_back(shape);
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
	RGBColour finalColour;
	std::vector<double> intersections;
	
	for (int i = 0; i < _sceneObjects.size(); i++)
	{
		intersections.push_back(_sceneObjects[i]->Intersection(ray));
	}
	int indexOfClosestShape = GetIndexOfClosestShape(intersections);	
	
	if (indexOfClosestShape != -1 && intersections.at(indexOfClosestShape) > 0.00000001) // To help identify if point is on inside or outside of sphere.
	{
		Ray incidentRay = ray.RayLine(intersections.at(indexOfClosestShape));
		RGBColour objectColour = _sceneObjects[indexOfClosestShape]->Colour();
		finalColour = objectColour * _ambientCoefficient;

		for (int i = 0; i < _lightSources.size(); i++)
		{
			Ray rayToSource(incidentRay.Direction(), (_lightSources.at(i).GetPosition().UnitVector() - incidentRay.Direction().UnitVector()).UnitVector());			
			Vector surfaceNormal = _sceneObjects[indexOfClosestShape]->SurfaceNormal(rayToSource);
			double projectionNormalToSource = surfaceNormal.ScalarProduct(rayToSource.Direction());
			
			if (projectionNormalToSource > 0)
			{
				bool isShadow = false;

				std::vector<double> shadowIntersections;

				for (int j = 0; j < _sceneObjects.size() && isShadow == false; j++)
				{
					shadowIntersections.push_back(_sceneObjects.at(j)->Intersection(rayToSource));
				}

				for (int k = 0; k < shadowIntersections.size(); k++)
				{
					if (shadowIntersections.at(k) > 0.00000001)
					{
						if (shadowIntersections.at(k) <= rayToSource.Direction().Magnitude())
						{
							isShadow = true;
						}						
					}
					break;
				}

				if (isShadow == false)
				{
					finalColour = finalColour + (_sceneObjects[indexOfClosestShape]->Colour() * _lightSources.at(i).Colour() * projectionNormalToSource);

					if (_sceneObjects[indexOfClosestShape]->DiffuseCoefficient() > 0) //between 0-1 be shiny. REflection coefficient.
					{
						Vector reflectionSurfaceNormal = _sceneObjects[indexOfClosestShape]->SurfaceNormal(incidentRay);
						Ray reflectedRay = incidentRay.Reflection(reflectionSurfaceNormal);
						double specularIllumination = reflectedRay.Direction().UnitVector().ScalarProduct(rayToSource.Direction().UnitVector());
						if (specularIllumination > 0)
						{
							specularIllumination = pow(specularIllumination, 10);
							finalColour = finalColour + _lightSources.at(i).Colour() * specularIllumination * _sceneObjects[indexOfClosestShape]->DiffuseCoefficient();
						}
					}
				}
			}
		}		
		
		/*Ray incidentRay2 = ray.RayLine(intersections.at(indexOfClosestShape));
		
		Vector surfaceNormal2 = sceneObjects[indexOfClosestShape]->SurfaceNormal(incidentRay2);
		Ray reflectedRay2 = incidentRay.Reflection(surfaceNormal2);

		illumination = reflectedRay2.Illumination(LightSources(), sceneObjects[indexOfClosestShape]->Colour(), sceneObjects[indexOfClosestShape]->DiffuseCoefficient());*/
	}
	 
	return finalColour;
}
