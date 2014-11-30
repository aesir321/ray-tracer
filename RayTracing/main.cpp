#include <iostream>
#include "Scene.h"
#include "Ray.h"
#include "Sphere.h"
#include "Viewport.h"

using namespace std;

int main()
{
	//Omit () if constructor takes no args.
	Vector observer(0, 0, 0, true);
	LightSource pointLightSource(5.0, 5.0, 5.0, true);
	Scene scene;
	scene.AddLightSource(pointLightSource);
	scene.AddObserver(observer);

	Sphere sphere(1.0);
	scene.Populate(sphere);

	Viewport viewport(1, 1, 1);	//Observer is in the middle so magnitude of the x length of the viewport here is 2x2 not 1x1.  
	scene.AddViewPort(viewport);

	scene.TraceRays();

	return 0;
}
