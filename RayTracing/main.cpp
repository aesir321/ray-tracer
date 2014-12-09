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
	double specularIntensity = 0.9;
	double diffuseIntensity = 0.8;

	Vector lightSourcePosition(100, -100, -100);
	RGBColour white(255, 255, 255);	
	LightSource pointLightSource(lightSourcePosition, white, specularIntensity, diffuseIntensity);

	Vector lightSourcePosition2(-100, -100, 50);
	RGBColour white2(255, 255, 255);
	LightSource pointLightSource2(lightSourcePosition2, white2, specularIntensity, diffuseIntensity);

	Scene scene;
	scene.Populate(pointLightSource);
	scene.Populate(pointLightSource2);
	scene.Populate(observer);
	scene.SetAmbientCoefficient(0.5); // What is a realistic value?

	double shininess = 50;
	double diffuseCoeffcient = 0.2;
	double reflectiveCoefficient = 0.6;
	
	Vector spherePos(-1, -5, 85);
	Sphere *sphere = new Sphere(spherePos, 5, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour(0, 255, 0);
	sphere->SetColour(colour);
	scene.Populate(sphere);

	Vector spherePos2(5, -3, 60);
	Sphere *sphere2 = new Sphere(spherePos2, 3, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour2(255, 0, 0);
	sphere2->SetColour(colour2);
	scene.Populate(sphere2);

	Vector spherePos3(-5, 5, 50);
	Sphere *sphere3 = new Sphere(spherePos3, 5, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour3(0, 0, 255);
	sphere3->SetColour(colour3);
	scene.Populate(sphere3);

	/*Vector spherePos4(5, -5, 100);
	Sphere *sphere4= new Sphere(spherePos4, 5, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour4(0, 125, 125);
	sphere4->SetColour(colour4);
	scene.Populate(sphere4);

	Vector spherePos5(0, 0, 120);
	Sphere *sphere5 = new Sphere(spherePos5, 15, diffuseCoeffcient, reflectiveCoefficient, shininess);
	RGBColour colour5(125, 125, 0);
	sphere5->SetColour(colour5);
	scene.Populate(sphere5);*/

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
