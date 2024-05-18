#ifndef MATH_TPP
#define MATH_TPP

// Divides bullets into smaller parts for displaying purposes
template<typename T>
T Math<T>::normalizeVector(T &vector)
{
	float m = sqrt(vector.x * vector.x + vector.y * vector.y);
	T normalizedVector;

	normalizedVector.x = vector.x / m;
	normalizedVector.y = vector.y / m;

	return normalizedVector;
}
#endif