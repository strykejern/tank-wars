class tank : virtual public top_view_object, virtual public basic_physics_object, virtual public angular, public timer_class {
	public:
	float ACCEL;
	float MAX_SPEED;
	float HANDLING;
	float ROT_DEC;
	int last_rot;
	volatile char * input[7];
	std::vector<cannon> cannons;
	
	tank(Vector Pos, std::vector<Vector> Points, std::vector<shot> * Shots) : top_view_object(Pos,Points), timer_class(1) {
		ACCEL = 0.2f;
		MAX_SPEED = 10;
		HANDLING = 0.1f;
		ROT_DEC = 0.95f;
		volatile char dummy;
		for (int i = 0; i < 7; ++i)
			input[i] = &dummy;
		cannons.push_back(cannon(Shots));
	}
	tank() {
		ACCEL = 0.2f;
		MAX_SPEED = 10;
		HANDLING = 0.1f;
		ROT_DEC = 0.95f;
		volatile char dummy;
		for (int i = 0; i < 4; ++i)
			input[i] = &dummy;
		cannons.push_back(cannon());
	}
	
	void set_shots(std::vector<shot> * Shots) {
		for (int i = 0; i < (int)cannons.size(); ++i) {
			cannons[i].shots = Shots;
		}
	}
	
	void draw(BITMAP * buffer) {
		
	}
	
	void draw_bounding_box(BITMAP * buffer) {
		int length = (int)points.size();
		std::vector<Vector> rot_points = ang_points();
		for (int i = 0; i < length; ++i) {
			line(buffer,
				(pos + rot_points[i]).x,
				(pos + rot_points[i]).y,
				(pos + rot_points[(i==length-1)?0:i+1]).x,
				(pos + rot_points[(i==length-1)?0:i+1]).y,
				makecol(255, 0, 0));
			triangle(buffer,
				(pos + rot_points[i]).x,
				(pos + rot_points[i]).y,
				(pos + rot_points[(i==length-1)?0:i+1]).x,
				(pos + rot_points[(i==length-1)?0:i+1]).y,
				pos.x,
				pos.y,
				makecol(255, 0, 0));
		}
		
		for (int i = 0; i < (int)cannons.size(); ++i)
			cannons[i].draw_bounding_box(buffer);
		
	}
	
	void update() {
		update_timers();
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
		else if (accel.length() > 0.5f)
			accel.set_length(accel.length() - 0.01f);
		else {
			accel = Vector();
			speed = Vector();
		}
		
		if ((bool)*input[4])
			if (zero(0, 30))
				for (int i = 0; i < (int)cannons.size(); ++i)
					cannons[i].shoot();
		
		accelerate();
		if (speed.length() > MAX_SPEED)
			speed.set_length(MAX_SPEED);
		move();
		border_collide();
		update_cannon();
	}
	
	void update_cannon() {
		for (int i = 0; i < (int)cannons.size(); ++i) {
			cannons[i].pos = pos;
			cannons[i].angle += last_rot * HANDLING;
		}
	}
	
	void set_inputs(volatile char * drive, volatile char * reverse, volatile char * turn_left, volatile char * turn_right, volatile char * Shoot) {
		input[0] = drive;
		input[1] = reverse;
		input[2] = turn_left;
		input[3] = turn_right;
		input[4] = Shoot;
	}
	
	void collide_drive() {
		pos -= speed;
		speed = Vector();
	}
	
	void collide_rotate() {
		angle -= last_rot * HANDLING;
		last_rot = -last_rot;
		update_cannon();
	}
};
