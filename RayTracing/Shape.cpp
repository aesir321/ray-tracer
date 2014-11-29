// Author: Will Parker
#include "Shape.h"
#include <iostream>

Shape::Shape()
{
}

Shape::~Shape()
{
}
void Shape::PrintShapeStats(Shape &shape)
{
	shape.Name();
	std::cout << "The surface area is: " << shape.SurfaceArea() << std::endl;
	std::cout << "The volume area is: " << shape.Volume() << std::endl;
	std::cout << std::endl;
}
