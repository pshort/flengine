#ifndef RECT_H
#define RECT_H

struct Rect {

	Rect() {}
	Rect(float x, float y, float w, float h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	float x, y, w, h;
	float GetRight() { return this->x + this->w; }
	float GetBottom() { return this->y + this->h; }

	bool Intersects(Rect other) {
		if(this->x > other.GetRight() || this->GetRight() < other.x)
			return false;
		if(this->y > other.GetBottom() || this->GetBottom() < other.y)
			return false;

		return true;
	}
};

#endif
