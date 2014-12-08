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
	Vector lightSourcePosition(-1000, 0, 200);
	RGBColour white(1, 1, 1);
	double specularIntensity = 1;
	double diffuseIntensity = 1;
	LightSource pointLightSource(lightSourcePosition, white, specularIntensity, diffuseIntensity);

	/*Vector lightSourcePosition2(-1000, -1000, 600);
	RGBColour red(1, 0, 0);
	LightSource pointLightSource2(lightSourcePosition2, red, 0.1);*/

	Scene scene;
	scene.Populate(pointLightSource);
	//scene.Populate(pointLightSource2);
	scene.Populate(observer);
	scene.SetAmbientCoefficient(0.5); // What is a realistic value?

	//Vector spherePos(195, -195, 500);
	double shininess = 100;
	double diffuseCoeffcient = 0.9;
	double reflectiveCoefficient = 0.9;
	/*Sphere *sphere = new Sphere(spherePos, 200, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour(0, 1, 0);
	sphere->SetColour(colour);
	scene.Populate(sphere);

	Vector spherePos2(-195, -195, 500);
	Sphere *sphere2 = new Sphere(spherePos2, 200, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour2(1, 0, 0);
	sphere2->SetColour(colour2);
	scene.Populate(sphere2);*/

	Vector spherePos3(0, 0, 500);
	Sphere *sphere3 = new Sphere(spherePos3, 200, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour3(0, 0, 1);
	sphere3->SetColour(colour3);
	scene.Populate(sphere3);

	Vector planeNormal(0, -1, 0);
	RGBColour planeColour(1, 1, 1);
	Plane *plane = new Plane(planeNormal, planeColour, 201, diffuseCoeffcient, reflectiveCoefficient, shininess);
	scene.Populate(plane);

	Vector viewportOriginPosition(0, 0, 1);
	Viewport viewport(5, 5, 500, 500, viewportOriginPosition);
	scene.Populate(viewport);

	scene.TraceRays();

	return 0;
}
