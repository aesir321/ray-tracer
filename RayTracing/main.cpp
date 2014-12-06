#include <iostream>
#include "Scene.h"
#include "Ray.h"
#include "Sphere.h"
#include "Viewport.h"

using namespace std;
/* TODO
	* Overload populate to add all objects.
	* Major cleanup of vector class.
	* Add Plane class.
	* Correctly combine colours
	* Claify why they skew when too close?  Is this correct?
	* Shadows
	*/
int main()
{
	Vector observer(0, 0, 0, true);

	Vector lightSourcePosition(-1000, -1000, 1000, true); //y here is inverted: different coord system? right handed?
	RGBColour white(255, 0, 0);
	LightSource pointLightSource(lightSourcePosition, white, 0.1);

	Scene scene;
	scene.AddLightSource(pointLightSource);
	scene.AddObserver(observer);

	/*Vector spherePos(0, 250, 600, true);
	Sphere *sphere = new Sphere(spherePos, 200, 0.9);
	RGBColour blue(0, 0, 255);
	sphere->SetColour(blue);
	scene.Populate(sphere);

	Vector spherePos2(-200, -50, 300, true);
	Sphere *sphere2 = new Sphere(spherePos2, 200, 0.9);
	RGBColour red(255, 0, 0);
	sphere2->SetColour(red);
	scene.Populate(sphere2);*/

	Vector spherePos3(0, 0, 1000, true);
	Sphere *sphere3 = new Sphere(spherePos3, 500, 0.9);
	RGBColour green(0, 255, 0);
	sphere3->SetColour(green);
	scene.Populate(sphere3);

	Vector viewportOriginPosition(0, 0, 1, true);
	Viewport viewport(5, 5, 500, 500, viewportOriginPosition);
	scene.AddViewPort(viewport);

	scene.TraceRays();

	return 0;
}
