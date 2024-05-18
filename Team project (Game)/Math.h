#ifndef MATH_H
#define MATH_H
#include "Charachter.h"

// Implementation of class templates
template<typename T>
class Math
{
public:
	static T normalizeVector(T&);
};

#include "Math.tpp"
#endif