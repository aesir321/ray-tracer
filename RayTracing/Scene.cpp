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
	_backgroundColour.Red = 0;
	_backgroundColour.Green = 0;
	_backgroundColour.Blue = 0;
}

Scene::~Scene()
{
}

void Scene::AddLightSource(LightSource lightSource)
{
	_lightSources.push_back(lightSource);
}

std::vector<LightSource> Scene::LightSources()
{
	return _lightSources;
}

void Scene::AddObserver(Vector observer)
{
	_observer = observer;
}

void Scene::AddViewPort(Viewport viewport)
{
	_viewport = viewport;
}

void Scene::Populate(Shape* shape)
{
	sceneObjects.push_back(shape);
}

void Scene::TraceRays()
{
	BMP image;
	image.SetSize(_viewport.GetNumberOfPixels(1), _viewport.GetNumberOfPixels(2));
	image.SetBitDepth(32);
	RGBColour pixel;
	double z = _viewport.GetPosition().GetThirdComponent();

	for (int x = 0; x < _viewport.GetNumberOfPixels(1); x++)
	{
		for (int y = 0; y < _viewport.GetNumberOfPixels(2); y++)
		{
			double xRay = x / (double)_viewport.GetNumberOfPixels(1) * _viewport.GetDimension(1) - _viewport.GetDimension(1) / 2.0;
			double yRay = y / (double)_viewport.GetNumberOfPixels(2) * _viewport.GetDimension(2) - _viewport.GetDimension(2) / 2.0;
			Vector direction(xRay, yRay, z, true);

			Ray ray(_observer, direction);
			
			image.SetPixel(x, y, TraceRay(ray));

			/*pixel.Red = image.GetPixel(x, y).Red;
			pixel.Green = image.GetPixel(x, y).Green;
			pixel.Blue = image.GetPixel(x, y).Blue;

			image.SetPixel(x, y, CalculateShadows(x, y, pixel));*/
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
	RGBColour illumination(0, 0, 0);
	std::vector<double> intersections;
	bool isInShadow = false;

	for (int i = 0; i < sceneObjects.size(); i++)
	{
		intersections.push_back(sceneObjects[i]->Intersection(ray));
	}
	int indexOfClosestShape = GetIndexOfClosestShape(intersections);	
	
	if (indexOfClosestShape != -1)
	{
		isInShadow = false;
		Ray incidentRay = ray.RayLine(intersections.at(indexOfClosestShape));
		Vector surfaceNormal = sceneObjects[indexOfClosestShape]->SurfaceNormal(incidentRay);
		Ray reflectedRay = incidentRay.Reflection(surfaceNormal);

		illumination = reflectedRay.Illumination(LightSources(), sceneObjects[indexOfClosestShape]->Colour(), sceneObjects[indexOfClosestShape]->DiffuseCoefficient()); //sceneObjects[indexOfClosestShape]->Colour();
	}
	 
	return illumination;
}

RGBColour Scene::CalculateShadows(double x, double y, RGBColour colour)
{
	double z = _viewport.GetPosition().GetThirdComponent();
	Vector origin(x, y, z, true);
	
	if (colour == _backgroundColour)
	{
		for (int i = 0; i < _lightSources.size(); i++)
		{
			Vector direction = _lightSources.at(i).GetPosition() - _observer;
			Ray shadow(_observer, direction);
			std::vector<double> shadowIntersections;

			for (int j = 0; j < sceneObjects.size(); j++)
			{
				shadowIntersections.push_back(sceneObjects.at(j)->Intersection(shadow));
			}

			for (int k = 0; k < shadowIntersections.size(); k++)
			{
				colour = colour / 2.0;
			}
		}
	}

	return colour;
}
