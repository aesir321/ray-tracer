#include "Scene.h"
#include "Ray.h"
#include "Sphere.h"
#include "Viewport.h"
#include "Plane.h"

#include <iostream>

using namespace std;
/* TODO
* Build scene script?
* REmove ellipsoid
* File management
* Fix plane
*/

void renderSceneOne()
{
	Vector observer(0, 0, 0);

	//y here is inverted: as easy bmp uses a top left (0,0) representation.
	double specularIntensity = 0.4;
	double diffuseIntensity = 0.8;

	Vector lightSourcePosition(-100, -10, -100);
	RGBColour white(255, 255, 255);
	LightSource pointLightSource(lightSourcePosition, white, specularIntensity, diffuseIntensity);

	Vector lightSourcePosition2(100, -100, 120);
	RGBColour red(255, 255, 255);
	LightSource pointLightSource2(lightSourcePosition2, red, specularIntensity, diffuseIntensity);

	Scene scene;
	scene.Populate(pointLightSource);
	scene.Populate(pointLightSource2);
	scene.Populate(observer);
	scene.SetAmbientCoefficient(0.3); // What is a realistic value?

	double shininess = 20;
	double diffuseCoeffcient = 0.9;
	double reflectiveCoefficient = 0.4;

	Vector spherePos(-7, 7, 80);
	Sphere *sphere = new Sphere(spherePos, 5, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour(0, 255, 0);
	sphere->SetColour(colour);
	scene.Populate(sphere);

	Vector spherePos2(0, 0, 100);
	Sphere *sphere2 = new Sphere(spherePos2, 15, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour2(255, 0, 0);
	sphere2->SetColour(colour2);
	scene.Populate(sphere2);

	Vector spherePos3(10, 10, 80);
	Sphere *sphere3 = new Sphere(spherePos3, 5, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour3(0, 0, 255);
	sphere3->SetColour(colour3);
	scene.Populate(sphere3);

	Vector planeNormal(0, -1, 0);
	RGBColour planeColour(0, 0, 0);
	Plane *plane = new Plane(planeNormal, planeColour, 101, 0.1, 0.2, shininess);
	scene.Populate(plane);

	Vector viewportOriginPosition(0, 0, 10);
	Viewport viewport(5, 5, 500, 500, viewportOriginPosition);
	scene.Populate(viewport);

	scene.TraceRays();
}

void renderSceneTwo()
{
	Vector observer(0, 0, 0);

	//y here is inverted: as easy bmp uses a top left (0,0) representation.
	double specularIntensity = 0.8;
	double diffuseIntensity = 0.2;

	Vector lightSourcePosition(-100, -100, 10);
	RGBColour white(255, 255, 255);
	LightSource pointLightSource(lightSourcePosition, white, specularIntensity, diffuseIntensity);

	Scene scene;
	scene.Populate(pointLightSource);
	scene.Populate(observer);
	scene.SetAmbientCoefficient(0.5);

	Vector spherePos(-7, -7, 100);
	Sphere *sphere = new Sphere(spherePos, 5, 0.3, 0.8, 150);
	RGBColour colour(0, 255, 0);
	sphere->SetColour(colour);
	scene.Populate(sphere);

	Vector spherePos2(3, 3, 20);
	Sphere *sphere2 = new Sphere(spherePos2, 2, 0.6, 0.2, 60);
	RGBColour colour2(54, 218, 251);
	sphere2->SetColour(colour2);
	scene.Populate(sphere2);

	Vector spherePos3(10, 0, 60);
	Sphere *sphere3 = new Sphere(spherePos3, 5, 0.8, 0.8, 90);
	RGBColour colour3(250, 142, 241);
	sphere3->SetColour(colour3);
	scene.Populate(sphere3);

	Vector viewportOriginPosition(0, 0, 10);
	Viewport viewport(5, 5, 500, 500, viewportOriginPosition);
	scene.Populate(viewport);

	scene.TraceRays();
}

void renderSceneThree()
{
	
}


int main()
{
	renderSceneOne();
	//renderSceneTwo();
	//renderSceneThree();

	return 0;
}
