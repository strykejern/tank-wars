class tank : 
		virtual public top_view_object, 
		virtual public basic_physics_object, 
		virtual public angular, 
		public timer_class, 
		public health_class {
	public:
	float ACCEL;
	float MAX_SPEED;
	float HANDLING;
	float ROT_DEC;
	int last_rot;
	volatile char * input[7];
	std::vector<cannon> cannons;
	Vector image_offset;
	static int num_tanks;
	int index;
	
	tank(Vector Pos, std::vector<Vector> Points, std::vector<shot> * Shots) : 
			top_view_object(Pos,Points), 
			timer_class(1) {
		ACCEL = 0.2f;
		MAX_SPEED = 10;
		HANDLING = 0.1f;
		ROT_DEC = 0.95f;
		volatile char dummy;
		for (int i = 0; i < 7; ++i)
			input[i] = &dummy;
		cannons.push_back(cannon(Shots));
		index = num_tanks++;
		image = NULL;
	}
	tank(Vector Pos) : 
			top_view_object(Pos), 
			timer_class(1) {
		ACCEL = 0.2f;
		MAX_SPEED = 10;
		HANDLING = 0.1f;
		ROT_DEC = 0.95f;
		volatile char dummy;
		for (int i = 0; i < 4; ++i)
			input[i] = &dummy;
		index = num_tanks++;
		image = NULL;
	}
	
	void set_shots(std::vector<shot> * Shots) {
		for (int i = 0; i < (int)cannons.size(); ++i) {
			cannons[i].shots = Shots;
		}
	}
	
	void draw_bounding_box(BITMAP * buffer) {
		int length = (int)points.size();
		std::vector<Vector> rot_points = abs_points();
		for (int i = 0; i < length; ++i) {
			line(buffer,
				rot_points[i].x,
				rot_points[i].y,
				rot_points[(i==length-1)?0:i+1].x,
				rot_points[(i==length-1)?0:i+1].y,
				makecol(255, 0, 0));
			triangle(buffer,
				rot_points[i].x,
				rot_points[i].y,
				rot_points[(i==length-1)?0:i+1].x,
				rot_points[(i==length-1)?0:i+1].y,
				pos.x,
				pos.y,
				makecol(255, 0, 0));
		}
		
		for (int i = 0; i < (int)cannons.size(); ++i)
			cannons[i].draw_bounding_box(buffer);
		
	}
	
	void update() {
		update_timers();
		if (*input[2]) {
			angle -= HANDLING;
			speed *= ROT_DEC;
			last_rot = -1;
		}
		else if (*input[3]) {
			angle += HANDLING;
			speed *= ROT_DEC;
			last_rot = 1;
		}
		else last_rot = 0;
		
		speed = (speed * Vector(1, angle, 0) < 0) ? -Vector(speed.length(), angle, 0) : Vector(speed.length(), angle, 0);
		if (*input[0])
			accel = Vector(ACCEL, angle, 0);
		else if (*input[1])
			accel = -Vector(ACCEL, angle, 0);
		else {
			accel = Vector();
			speed *= 0.95f;
			if (speed.length() <= 0.5f) speed = Vector(0, 0);
		}
		
		if (*input[4])
			if (zero(0, 20))
				for (int i = 0; i < (int)cannons.size(); ++i)
					cannons[i].shoot(index);
		if(*input[5])
			for (int i = 0; i < (int)cannons.size(); ++i)
				cannons[i].angle -= HANDLING;
		if(*input[6])
			for (int i = 0; i < (int)cannons.size(); ++i)
				cannons[i].angle += HANDLING;
		
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
	
	void set_inputs(volatile char * drive, 
					volatile char * reverse, 
					volatile char * turn_left, 
					volatile char * turn_right, 
					volatile char * Shoot, 
					volatile char * cannon_left, 
					volatile char * cannon_right) {
		input[0] = drive;
		input[1] = reverse;
		input[2] = turn_left;
		input[3] = turn_right;
		input[4] = Shoot;
		input[5] = cannon_left;
		input[6] = cannon_right;
	}
	
	void collide_drive() {
		pos -= speed;
		speed *= 0.95f;
		Vector tmp = points[last_collision];
		if (tmp.x > 0) {
			if (tmp.y > 0)
				angle -= HANDLING * 1.5f;
			else
				angle += HANDLING * 1.5f;
		}
		else {
			if (tmp.y > 0) 
				angle += HANDLING * 1.5f;
			else
				angle -= HANDLING * 1.5f;
		}
		
	}
	
	void collide_rotate() {
		angle -= last_rot * HANDLING;
		last_rot = -last_rot;
		update_cannon();
	}

	void set_images(BITMAP * Image, Vector Image_offset) {
		set_image(Image, Image_offset);
	}
	
	void draw(BITMAP * buffer) {
		if (image == NULL)
			draw_bounding_box(buffer);
		else {
			pivot_sprite(buffer, 
						image, 
						pos.x, 
						pos.y, 
						image_offset.x, 
						image_offset.y, 
						itofix(angle*(128/PI)));
			for (int i = 0; i < (int)cannons.size(); ++i)
				cannons[i].draw(buffer);
		}
	}
	
	void set_image(BITMAP * Image, Vector Image_offset){
		image = Image;
	}
};

int tank::num_tanks = 0;
