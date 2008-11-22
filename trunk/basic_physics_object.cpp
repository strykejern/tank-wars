#include "basic_game_object.cpp"

class basic_physics_object : virtual public basic_game_object {
	public:
	Vector speed;
	Vector accel;
	
	void accelerate() {
		speed.x += accel.x;
		speed.y += accel.y;
	}
	
	void move() {
		pos.x += speed.x;
		pos.y += speed.y;
	}
	
	
};
