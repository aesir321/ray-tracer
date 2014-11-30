#include "Scene.h"
#include "Ray.h"


Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddLightSource(Vector vector)
{
	//Light source has a position, what about dimensions, colour etc...
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
	for (int x = -1 *_viewport.GetDimension(1); x < _viewport.GetDimension(1); x++) //How many pixels in the grid?  What is the resolution?
	{
		for (int y = -1 * _viewport.GetDimension(2); y < _viewport.GetDimension(2); y++)
		{
			Ray ray(x * _viewport.GetDimension(3) / _viewport.Centre().GetThirdComponent(), y * _viewport.GetDimension(3) / _viewport.Centre().GetThirdComponent(), _viewport.GetDimension(3), true);

			for (int i = 0; i < sceneObjects.size(); i++)
			{
				double intersection = _viewport.Intersection(ray, sceneObjects[i]);

				if (intersection != -1.0)
				{
					
				}
				
			}
		}
	}
}