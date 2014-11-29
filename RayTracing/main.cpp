#include <iostream>

#include "Scene.h"

using namespace std;

int main()
{
  Scene scene();
  Vector vector();
  scene.CreateLightSource(vector);
  scene.Populate();
  scene.TraceRays();
  return 0;
}
