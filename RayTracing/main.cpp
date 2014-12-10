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

<<<<<<< HEAD
	//Vector lightSourcePosition2(-100, -100, 50);
	//RGBColour white2(255, 255, 255);
	//LightSource pointLightSource2(lightSourcePosition2, white2, specularIntensity, diffuseIntensity);

	Scene scene;
	scene.Populate(pointLightSource);
	
=======
	Vector lightSourcePosition2(0, -10, 10);
	RGBColour red(255, 255, 255);
	LightSource pointLightSource2(lightSourcePosition2, red, specularIntensity, diffuseIntensity);

	Scene scene;
	//scene.Populate(pointLightSource);
	scene.Populate(pointLightSource2);
>>>>>>> normColour
	scene.Populate(observer);
	scene.SetAmbientCoefficient(0.2); // What is a realistic value?

	double shininess = 20;
<<<<<<< HEAD
	double diffuseCoeffcient = 0.8;
	double reflectiveCoefficient = 1;
	
	Vector spherePos(0, 0, 80);
	Sphere *sphere = new Sphere(spherePos, 15, diffuseCoeffcient, reflectiveCoefficient, shininess);
=======
	double diffuseCoeffcient = 0.4;
	double reflectiveCoefficient = 0.9;

	Vector spherePos(-5, 0, 80);
	Sphere *sphere = new Sphere(spherePos, 5, diffuseCoeffcient, reflectiveCoefficient, shininess);
>>>>>>> normColour
	RGBColour colour(0, 255, 0);
	sphere->SetColour(colour);
	scene.Populate(sphere);

<<<<<<< HEAD
	Vector spherePos2(5, 0, 50);
	Sphere *sphere2 = new Sphere(spherePos2, 3, diffuseCoeffcient, reflectiveCoefficient, shininess);
=======
	Vector spherePos2(0, 0, 100);
	Sphere *sphere2 = new Sphere(spherePos2, 15, diffuseCoeffcient, reflectiveCoefficient, shininess);
>>>>>>> normColour
	RGBColour colour2(255, 0, 0);
	sphere2->SetColour(colour2);
	scene.Populate(sphere2);

<<<<<<< HEAD
	Vector spherePos3(-5, 0, 50);
	Sphere *sphere3 = new Sphere(spherePos3, 3, diffuseCoeffcient, reflectiveCoefficient, shininess);
=======
	Vector spherePos3(5, 0, 80);
	Sphere *sphere3 = new Sphere(spherePos3, 5, diffuseCoeffcient, reflectiveCoefficient, shininess);
>>>>>>> normColour
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
