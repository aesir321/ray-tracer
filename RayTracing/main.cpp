#include <iostream>
#include "Scene.h"
#include "Ray.h"
#include "Sphere.h"
#include "Viewport.h"
#include "SingleTracer.h"

using namespace std;

int main()
{
	Vector observer(0, 0, 0, true);
	Vector lightSourcePosition(50, 50, 50, true);
	RGBApixel white;
	white.Red = 255;
	white.Green = 255;
	white.Blue = 255;
	LightSource pointLightSource(lightSourcePosition, white);

	Scene scene;
	scene.AddLightSource(pointLightSource);
	scene.AddObserver(observer);

	RGBApixel red;
	red.Red = 255;
	red.Green = 0;
	red.Blue = 0;

	Vector spherePos(20, 20, 20, true);
	Sphere *sphere = new Sphere(spherePos, 5);
	sphere->SetColour(red);
	scene.Populate(sphere);

	Vector spherePos2(30, 30, 20, true);
	Sphere *sphere2 = new Sphere(spherePos2, 5);
	RGBApixel green;
	green.Red = 0;
	green.Green = 255;
	green.Blue = 0;
	sphere2->SetColour(green);
	scene.Populate(sphere2);

	Vector spherePos3(0, 0, 20, true);
	Sphere *sphere3 = new Sphere(spherePos3, 5);
	RGBApixel blue;
	blue.Red = 0;
	blue.Green = 0;
	blue.Blue = 255;
	sphere3->SetColour(blue);
	scene.Populate(sphere3);

	Vector viewportOriginPosition(0, 0, 1, true);
	Viewport viewport(50, 50, 500, 500, viewportOriginPosition);
	scene.AddViewPort(viewport);

	scene.TraceRays();

	return 0;
}
