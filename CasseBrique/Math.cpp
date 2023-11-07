#include "Math.h"

Vector2f Math::Normalized(Vector2f vector) {
	Vector2f cache = vector;
	vector.x /= sqrt(cache.x * cache.x + cache.y * cache.y);
	vector.y /= sqrt(cache.x * cache.x + cache.y * cache.y);
	return vector;
}