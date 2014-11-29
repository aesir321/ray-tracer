#include "Scene.h"

Scene::Scene()
{
  // By default have a single sphere..
  Sphere sphere();
  shapes.push_back(sphere);
};

Scene::~Scene()
{
}

void Scene::CreateLightSource(double coord1, double coord2, double coord3)
{
}

void Scene::Populate()
{
}

void Scene::TraceRays()
{
}

