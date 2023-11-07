#include "Math.h"

Vector2f Math::Normalized(Vector2f vector) {
	vector.x /= sqrt(vector.x * vector.x + vector.y * vector.y);
	vector.y /= sqrt(vector.x * vector.x + vector.y * vector.y);
	return vector;
}