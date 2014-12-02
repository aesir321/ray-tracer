#include "Scene.h"
#include "Ray.h"
#include <iostream>
#include <fstream>

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
	std::ofstream file;
	file.open("Intensity.txt");
	
	double deltaX = 2 * _viewport.GetDimension(1) / _viewport.GetNumberOfPixels(1);
	double deltaY = 2 * _viewport.GetDimension(2) / _viewport.GetNumberOfPixels(2);
	double z = 30;//Doesn't work as one _viewport.GetPosition().GetThirdComponent();

	for (int y = -_viewport.GetNumberOfPixels(2) / 2.0; y < _viewport.GetNumberOfPixels(2) / 2.0; y++)
	{
		for (int x = -_viewport.GetNumberOfPixels(2)/ 2.0; x < _viewport.GetNumberOfPixels(1) / 2.0; x++)
		{	
			Vector origin(0, 0, 0, true);
			Vector direction(deltaX * x, deltaY * y, z, true);
			Vector unitDirection = direction.UnitVector();
			Ray ray(origin, unitDirection);

			for (int i = 0; i < sceneObjects.size(); i++)
			{
				double intersection = sceneObjects[i]->Intersection(ray);

				if (intersection != -1.0) //There is something to see!
				{
					//Use lambda to get full ray equation
					Vector intersectingDirection(unitDirection.MultiplyScalar(intersection));
					Ray incidentRay(origin, intersectingDirection);
					Vector surfaceNormal = sceneObjects[i]->SurfaceNormal(incidentRay);
					Ray reflectedRay = incidentRay.Reflection(surfaceNormal);
										
					double illumination = reflectedRay.Illumination(_lightSources[i], surfaceNormal);
								
				  file << x << ","
				       << y << ","
				       << z << ","				       
				       << illumination << std::endl;					
				}
				else
				{
					double illumination = 0.0;
					file << x << ","
						<< y << ","
						<< z << ","
				        << illumination << std::endl;
				}
			}
		}
	}
	file.close();
}
