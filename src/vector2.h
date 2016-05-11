#ifndef VECTOR2_H
#define VECTOR2_H


class Vector2 {

	public:

	float x, y;

	Vector2() { this->x = 0; this->y = 0; }

	Vector2(float x, float y) { this->x = x; this->y = y; }

	Vector2 operator * (const float scale) {
		return Vector2(x * scale, y * scale);
	}

	Vector2 operator + (const Vector2& other) {
		return Vector2(x + other.x, y + other.y);
	}
	
	Vector2 operator - (const Vector2& other) {
		return Vector2(x - other.x, y - other.y);
	}

	const Vector2& operator += (const Vector2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	const Vector2& operator -= (const Vector2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	const Vector2& operator *= (const float scale) {
		x *= scale;
		y *= scale;
		return *this;
	}

};


#endif
