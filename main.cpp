#include "Scene.h"
#include "Geometry/Ray.h"
#include "Geometry/Sphere.h"
#include "Viewport.h"
#include "Geometry/Plane.h"

using namespace std;

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
	scene.SetAmbientCoefficient(0.3);

	double shininess = 20;
	double diffuseCoeffcient = 0.9;
	double reflectiveCoefficient = 0.4;

	Vector spherePos(-7, 7, 80);
	Sphere *sphere = new Sphere(spherePos, 5, diffuseCoeffcient, reflectiveCoefficient, shininess, RGBColour(0, 255, 0));
	scene.Populate(sphere);

	Vector spherePos2(0, 0, 100);
	Sphere *sphere2 = new Sphere(spherePos2, 15, diffuseCoeffcient, reflectiveCoefficient, shininess, RGBColour(255, 0, 0));
	scene.Populate(sphere2);

	Vector spherePos3(10, 10, 80);
	Sphere *sphere3 = new Sphere(spherePos3, 5, diffuseCoeffcient, reflectiveCoefficient, shininess, RGBColour(0, 0, 255));
	scene.Populate(sphere3);

	Vector viewportOriginPosition(0, 0, 10);
	Viewport viewport(5, 5, 500, 500, viewportOriginPosition);
	scene.Populate(viewport);

	scene.TraceRays("varying-sized-spheres.bmp");
}

void renderSceneTwo()
{
	Vector observer(0, 0, 0);

	//y here is inverted: as easy bmp uses a top left (0,0) representation.
	double specularIntensity = 0.3;
	double diffuseIntensity = 0.6;

	Vector lightSourcePosition(10, -100, 10);
	RGBColour white(255, 255, 255);
	LightSource pointLightSource(lightSourcePosition, white, specularIntensity, diffuseIntensity);

	Scene scene;
	scene.Populate(pointLightSource);
	scene.Populate(observer);
	scene.SetAmbientCoefficient(0.5);

	Vector spherePos(-7, -7, 100);
	Sphere *sphere = new Sphere(spherePos, 5, 0.3, 0.4, 150, RGBColour(0, 255, 0));
	scene.Populate(sphere);

	Vector spherePos2(0, 3, 20);
	Sphere *sphere2 = new Sphere(spherePos2, 2, 0.6, 0.8, 60,RGBColour(54, 218, 251));
	scene.Populate(sphere2);

	Vector spherePos3(5, 0, 60);
	Sphere *sphere3 = new Sphere(spherePos3, 5, 0.8, 0.2, 90, RGBColour(250, 142, 241));
	scene.Populate(sphere3);

	Vector planeNormal(0, 0, 1);
	RGBColour planeColour(0, 255, 255);
	Plane *plane = new Plane(planeNormal, planeColour, 102, 0.6, 0.1, 0.9);
	scene.Populate(plane);

	Vector planeNormal1(0, 1, 0);
	RGBColour planeColour1(200, 200, 200);
	Plane *plane1 = new Plane(planeNormal1, planeColour1, 11, 0.4, 0.1, 0.9);
	scene.Populate(plane1);

	Vector viewportOriginPosition(0, 0, 10);
	Viewport viewport(5, 5, 500, 500, viewportOriginPosition);
	scene.Populate(viewport);

	scene.TraceRays("plane-testing.bmp");
}

void renderSceneThree()
{
	Vector observer(0, 0, 0);

	//y here is inverted: as easy bmp uses a top left (0,0) representation.
	double specularIntensity = 1;
	double diffuseIntensity = 1;

	Vector lightSourcePosition(100, 0, -100);
	RGBColour white(255, 255, 255);
	LightSource pointLightSource(lightSourcePosition, white, specularIntensity, diffuseIntensity);

	Scene scene;
	scene.Populate(pointLightSource);
	scene.Populate(observer);
	scene.SetAmbientCoefficient(0.4);

	double shininess = 20;
	double diffuseCoeffcient = 0.9;
	double reflectiveCoefficient = 0.8;

	Vector spherePos(-5, -5, 80);
	Sphere *sphere = new Sphere(spherePos, 5, diffuseCoeffcient, reflectiveCoefficient, shininess, RGBColour(255, 0, 0));
	scene.Populate(sphere);

	Vector spherePos2(5, -5, 80);
	Sphere *sphere2 = new Sphere(spherePos2, 5, diffuseCoeffcient, reflectiveCoefficient, shininess, RGBColour(0, 255, 0));
	scene.Populate(sphere2);

	Vector spherePos3(0, 4, 100);
	Sphere *sphere3 = new Sphere(spherePos3, 5, diffuseCoeffcient, reflectiveCoefficient, shininess, RGBColour(0, 0, 255));
	scene.Populate(sphere3);

	Vector spherePos4(-10, 3.5, 80);
	Sphere *sphere4 = new Sphere(spherePos4, 5, diffuseCoeffcient, reflectiveCoefficient, shininess, RGBColour(0, 255, 255));
	scene.Populate(sphere4);

	Vector spherePos5(10, 3.5, 80);
	Sphere *sphere5 = new Sphere(spherePos5, 5, diffuseCoeffcient, reflectiveCoefficient, shininess, RGBColour(255, 255, 0));
	scene.Populate(sphere5);

	Vector spherePos6(-5, 12, 80);
	Sphere *sphere6 = new Sphere(spherePos6, 5, diffuseCoeffcient, reflectiveCoefficient, shininess, RGBColour(255, 145, 0));
	scene.Populate(sphere6);

	Vector spherePos7(5, 12, 80);
	Sphere *sphere7 = new Sphere(spherePos7, 5, diffuseCoeffcient, reflectiveCoefficient, shininess, RGBColour(255, 0, 255));
	scene.Populate(sphere7);

	Vector viewportOriginPosition(0, 0, 10);
	Viewport viewport(5, 5, 1000, 1000, viewportOriginPosition);
	scene.Populate(viewport);

	scene.TraceRays("reflecting-coloured-spheres.bmp");
}

int main()
{
    renderSceneOne();
  	renderSceneTwo();
  	renderSceneThree();
  
	return 0;
}
