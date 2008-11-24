struct shot : virtual public top_view_object, virtual public basic_physics_object, virtual public angular {
	float blast_radius;
	float damage;
	float drag;
	bool homing;
	
	shot() {
		blast_radius = 0;
		damage = 0;
		drag = 0;
		homing = false;
	}
	
	shot(Vector Pos, float Angle, float Speed) : top_view_object(Pos, std::vector<Vector>()) {
		blast_radius = 0;
		damage = 0;
		drag = 0;
		homing = false;
		pos = Pos;
		angle = Angle;
		speed = -Vector(Speed, angle, 0);
	}
	
	void set_drag(float Drag) {
		drag = Drag;
		accel = -speed;
		accel.set_length(drag);
	}
	
	void update_drag() {
		accel = -speed;
		accel.set_length(drag);
	}
	
	bool update() {
		accelerate();
		move();
		if (homing) update_drag();
		return pos.x < 0 || pos.x > SCREEN_X || pos.y < 0 || pos.y > SCREEN_Y;
	}
	
	void draw(BITMAP * buffer) {
		draw_bounding_box(buffer);
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
				makecol(0, 0, 255));
			triangle(buffer,
				(pos + rot_points[i]).x,
				(pos + rot_points[i]).y,
				(pos + rot_points[(i==length-1)?0:i+1]).x,
				(pos + rot_points[(i==length-1)?0:i+1]).y,
				pos.x,
				pos.y,
				makecol(0, 0, 255));
		}
	}
};
