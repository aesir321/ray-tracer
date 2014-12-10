#include "Scene.h"
#include "Ray.h"
#include "Sphere.h"
#include "Viewport.h"
#include "Plane.h"

#include <iostream>

using namespace std;
/* TODO
	* Correctly combine colours
	* Shadows
	* Build scene script?
	*/
int main()
{
	Vector observer(0, 0, 0);

	//y here is inverted: as easy bmp uses a top left (0,0) representation.
	double specularIntensity = 1;
	double diffuseIntensity = 1;

	/*Vector lightSourcePosition(-100, -10, -100);
	RGBColour white(255, 255, 255);
	LightSource pointLightSource(lightSourcePosition, white, specularIntensity, diffuseIntensity);*/

	Vector lightSourcePosition2(0, -10, 10);
	RGBColour red(255, 255, 255);
	LightSource pointLightSource2(lightSourcePosition2, red, specularIntensity, diffuseIntensity);

	//test

	Scene sceneaaa;
	//scene.Populate(pointLightSource);
	scene.Populate(pointLightSource2);
	scene.Populate(observer);
	scene.SetAmbientCoefficient(0.2); // What is a realistic value?

	double shininess = 20;
	double diffuseCoeffcient = 0.4;
	double reflectiveCoefficient = 0.9;

	Vector spherePos(-5, 0, 80);
	Sphere *sphere = new Sphere(spherePos, 5, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour(0, 255, 0);
	sphere->SetColour(colour);
	scene.Populate(sphere);

	Vector spherePos2(0, 0, 100);
	Sphere *sphere2 = new Sphere(spherePos2, 15, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour2(255, 0, 0);
	sphere2->SetColour(colour2);
	scene.Populate(sphere2);

	Vector spherePos3(5, 0, 80);
	Sphere *sphere3 = new Sphere(spherePos3, 5, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour3(0, 0, 255);
	sphere3->SetColour(colour3);
	scene.Populate(sphere3);

	/*Vector planeNormal(0, -1, 0);
	RGBColour planeColour(255, 255, 255);
	Plane *plane = new Plane(planeNormal, planeColour, 101, diffuseCoeffcient, reflectiveCoefficient, shininess);
	scene.Populate(plane);*/

	Vector viewportOriginPosition(0, 0, 10);
	Viewport viewport(5, 5, 500, 500, viewportOriginPosition);
	scene.Populate(viewport);

	scene.TraceRays();

	return 0;
}
