#ifndef TRACER_H
#define TRACER_H

#include "Ray.h"
#include "Scene.h"

class Tracer
{
public :
	Tracer();
	Tracer(Scene* scene);
	~Tracer();
	virtual double TraceRay(Ray& ray);

protected:
	Scene* _scene;
};

#endif