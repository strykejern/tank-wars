class shot : virtual public top_view_object, virtual public basic_physics_object, virtual public angular {
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
	
	void set_drag(float Drag) {
		drag = Drag;
		accel = -speed;
		accel.set_length(drag);
	}
	
	void update_drag() {
		accel = -speed;
		accel.set_length(drag);
	}
	
	void update() {
		accelerate();
		move();
		if (homing) update_drag();
	}
};
