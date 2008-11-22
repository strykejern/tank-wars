#include "basic_physics_object.cpp"
#include "top_view_object.cpp"
#include "angular.cpp"

#define SCREEN_X 640
#define SCREEN_Y 480

class tank : virtual public top_view_object, virtual public basic_physics_object, virtual public angular {
	public:
	float ACCEL;
	float MAX_SPEED;
	float HANDLING;
	float ROT_DEC;
	int last_rot;
	volatile char * input[4];
	
	tank(Vector Pos, Vector * Points, int Length) : top_view_object(Pos,Points, Length) {
		ACCEL = 0.2f;
		MAX_SPEED = 10;
		HANDLING = 0.1f;
		ROT_DEC = 0.95f;
		volatile char dummy;
		for (int i = 0; i < 4; ++i)
			input[i] = &dummy;
	}
	
	void draw(BITMAP * buffer) {
		
	}
	
	void draw_bounding_box(BITMAP * buffer) {
		Vector * rot_points = ang_points();
		for (int i = 0; i < length; ++i) {
			line(buffer,
				(pos + rot_points[i]).x,
				(pos + rot_points[i]).y,
				(pos + rot_points[(i==length-1)?0:i+1]).x,
				(pos + rot_points[(i==length-1)?0:i+1]).y,
				makecol(255, 0, 0));
		}
	}
	
	void update() {
		if ((bool)*input[2]) {
			angle -= HANDLING;
			speed *= ROT_DEC;
			last_rot = -1;
		}
		else if ((bool)*input[3]) {
			angle += HANDLING;
			speed *= ROT_DEC;
			last_rot = 1;
		}
		else last_rot = 0;
		
		speed = Vector(speed.length(), angle, 0);
		if ((bool)*input[0])
			accel = Vector(ACCEL, angle, 0);
		else if ((bool)*input[1])
			accel = -Vector(ACCEL, angle, 0);
		else {
			accel = Vector();
			speed = Vector();
		}
		
		accelerate();
		if (speed.length() > MAX_SPEED)
			speed.set_length(MAX_SPEED);
		move();
		border_collide();
	}
	
	void set_inputs(volatile char * drive, volatile char * reverse, volatile char * turn_left, volatile char * turn_right) {
		input[0] = drive;
		input[1] = reverse;
		input[2] = turn_left;
		input[3] = turn_right;
	}
};
