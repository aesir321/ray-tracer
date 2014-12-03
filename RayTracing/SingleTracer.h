#ifndef STRACER_H
#define STRACER_H

#include "Tracer.h"
#include "Scene.h"
#include "Ray.h"

class SingleTracer : public Tracer
{
public :
	SingleTracer();
	SingleTracer(Scene* scene);
	~SingleTracer();
	double TraceRay(Ray& ray);
};

#endif