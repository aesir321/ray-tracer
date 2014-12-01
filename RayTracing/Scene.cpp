#include "Scene.h"
#include "Ray.h"
#include <iostream>;
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

void Scene::Populate(Sphere sphere)
{
	sceneObjects.push_back(sphere);
}

void Scene::TraceRays()
{
	std::ofstream file;
	file.open("Intensity.txt");
	for (int y = -1 *_viewport.GetDimension(1); y < _viewport.GetDimension(1); y++) //How many pixels in the grid?  What is the resolution?
	{
		for (int x = -1 * _viewport.GetDimension(2); x < _viewport.GetDimension(2); x++)
		{
			double depth = _viewport.GetDimension(3);
			double viewportZPosition = _viewport.Centre().GetThirdComponent();

			Ray ray(x * depth / viewportZPosition, y * depth / viewportZPosition, viewportZPosition, true);
			

			for (int i = 0; i < sceneObjects.size(); i++)
			{
				double intersection = _viewport.Intersection(ray, sceneObjects[i]);

				if (intersection != -1.0) //There is something to see!
				{
					//Use lambda to get full ray equation
					//double x = ray
					Ray fullRay(ray.GetFirstComponent() + intersection, ray.GetSecondComponent() + intersection, ray.GetThirdComponent() + intersection, true);
					
					// Get the reflected ray					
					Ray reflectedRay;
					Vector surfaceNormal;
					surfaceNormal = sceneObjects[i].SurfaceNormal(fullRay);
					reflectedRay = fullRay.Reflection(surfaceNormal);
					
					// Calculate the illumination
					double illumination = fullRay.Illumination(reflectedRay, _lightSources[i], surfaceNormal);
								
					file << x << "," << y << "," << illumination << std::endl;					
				}
				else
				{
					double illumination = 0.0;
					
					file << x << "," << y << "," << illumination << std::endl;
				}
			}
		}
	}
	file.close();
}