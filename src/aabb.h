#ifndef AABB_H
#define AABB_H

class AABB {
	
public:

	float x;
	float y;
	float w;
	float h;

public:

	float Left() {
		return this->x;
	}

	float Right() {
		return this->x + this->w;
	}

	float Top() { 
		return y;
	}

	float Bottom() {
		return y + h;
	}

	bool Contains(int x, int y) {
		if ( x < this->Left() || x > this->Right() )
			return false;

		if ( y < this->Top() || y > this->Bottom() )
			return false;

		return true;
	}

	bool IsColliding(AABB* other) {
		if(((this->x + this->w) < other->x) || ((other->x + other->w) < this->x))
			return false;
		if(((this->y + this->h) < other->y) || ((other->y + other->h) < this->y))
			return false;
		return true;
	}

};

#endif
