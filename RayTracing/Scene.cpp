#include "Scene.h"
#include "Ray.h"
#include <iostream>
#include <fstream>
#include "Shape.h"
#include "EasyBMP.h"
#include "EasyBMP_BMP.h"
#include "EasyBMP_DataStructures.h"
#include "EasyBMP_VariousBMPutilities.h"
#include "EasyBMP.cpp"


Scene::Scene()
{
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
	image.SetSize(500, 500);
	image.SetBitDepth(8);
	
	double deltaX = 2.0 * _viewport.GetDimension(1) / _viewport.GetNumberOfPixels(1);
	double deltaY = 2.0 * _viewport.GetDimension(2) / _viewport.GetNumberOfPixels(2);
	double z = 30;//Doesn't work as one _viewport.GetPosition().GetThirdComponent();

	for (int x = 0; x < _viewport.GetNumberOfPixels(1); x++)
	{
		for (int y = 0; y < _viewport.GetNumberOfPixels(2); y++)
		{
			Vector direction(deltaX * x, deltaY * y, z, true);
			Vector unitDirection = direction.UnitVector();
			Ray ray(_observer, unitDirection);

			image.SetPixel(x, y, TraceRay(ray));
		}
	}
	image.WriteToFile("test.bmp");	
}

RGBApixel Scene::TraceRay(Ray ray)
{
	RGBApixel illumination;
	Vector maxZ(0, 0, 30, true);
	Ray temp(_observer, maxZ);
	illumination.Red = 0;
	illumination.Green = 0;
	illumination.Blue = 0;
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		double intersection = sceneObjects[i]->Intersection(ray); 
		if (intersection != -1.0 && ray.Direction().GetThirdComponent() < temp.Direction().GetThirdComponent()) //There is something to see!
		{
			Vector intersectingDirection(ray.Direction().UnitVector().MultiplyScalar(intersection));
			Ray incidentRay(ray.Origin(), intersectingDirection);
			Vector surfaceNormal = sceneObjects[i]->SurfaceNormal(incidentRay);
			Ray reflectedRay = incidentRay.Reflection(surfaceNormal);
			
			illumination.Red = sceneObjects[i]->Colour().Red * reflectedRay.Illumination(LightSources()[0], surfaceNormal);
			illumination.Green = sceneObjects[i]->Colour().Green * reflectedRay.Illumination(LightSources()[0], surfaceNormal);
			illumination.Blue = sceneObjects[i]->Colour().Blue * reflectedRay.Illumination(LightSources()[0], surfaceNormal);
			temp = incidentRay;
		}
	}
	return illumination;
}
