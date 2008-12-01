struct shot : virtual public basic_physics_object {
	float blast_radius;
	float damage;
	float drag;
	bool homing;
	int parent;
	
	shot() {
		blast_radius = 0;
		damage = 0;
		drag = 0;
		homing = false;
		pos = Vector();
	}
	
	shot(Vector Pos, float Angle, float Speed, int Index) {
		blast_radius = 0;
		damage = 0;
		drag = 0;
		homing = false;
		pos = Pos;
		speed = -Vector(Speed, Angle, 0);
		parent = Index;
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
		circlefill(buffer,
			pos.x,
			pos.y,
			10,
			makecol(0, 0, 255));		
	}
	
	float project_to(Vector v) {
		return pos * v;
	}
};
