#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

struct Vector
{
	float x;
	float y;

	Vector()
	{
		x = 0;
		y = 0;
	}

	Vector(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	~Vector() 
	{
		/*std::cout << "VECTOR DESTRUCTOR CALLED " << std::endl;*/
	}
};

#endif VECTOR_H