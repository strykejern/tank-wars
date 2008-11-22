#include <math.h>

class Vector {
	public:
	float x, y;
	
	Vector() { x=0; y=0; }
	Vector(float X, float Y) { x=X; y=Y; }
	Vector(float length, float angle, int dummy) {
		x = cos(angle) * length;
		y = sin(angle) * length;
	}
	Vector operator +  (Vector v) {
		return Vector(x + v.x, y + v.y);
	}
	Vector operator -  (Vector v) {
		return Vector(x - v.x, y - v.y);
	}
	Vector operator += (Vector v) { 
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector operator -= (Vector v) { 
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vector operator *= (float m)  {
		x *= m;
		y *= m;
		return *this;
	}
	Vector operator /= (float d)  {
		x /= d;
		y /= d;
		return *this;
	}
	Vector operator /  (int d)    {
		return Vector(x/d, y/d);
	}
	Vector operator *  (float m)  {
		return Vector(x*m, y*m);
	}
	float  operator *  (Vector v) {
		return (x * v.x) + (y * v.y);
	}
	Vector operator -  ()         {
		Vector temp;
		temp.x = -x;
		temp.y = -y;
		return temp;
	}
	bool   operator != (Vector v) {
		return x!=v.x || y!=v.y;
	}
	
	float length() {
		return sqrt(pow(x, 2)+pow(y, 2));
	}
	float angle()  {
		return atan2(x, y);
	}
	
	Vector ccper () {
		return Vector(-y, x);
	}
	Vector cper  () {
		return Vector(y, -x);
	}
	
	Vector rotated_cp(float angle) {
		float X = length() * cos(angle);
		float Y = length() * sin(angle);
		return Vector (X, Y);
	}
	
	void rotate_to(float angle) {
		float X = length() * cos(angle);
		float Y = length() * sin(angle);
		x = X;
		y = Y;
	}
	void set_length(float l) {
		float fx = x / length();
		float fy = y / length();
		x = l * fx;
		y = l * fy;
	}
};
