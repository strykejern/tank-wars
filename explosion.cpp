struct explosion : public timer_class, public basic_game_object {
	int radius;
	int max_radius;
	float damage;
	explosion(Vector Pos, int Max_radius, float Damage) : timer_class(1) {
		radius = 2;
		pos = Pos;
		max_radius = Max_radius;
		damage = Damage;
	}
	
	bool update() {
		update_timers();
		if (radius<max_radius&&zero(0, 1))radius++;
		if (radius >= max_radius) return true;
		return false;
	}
	
	void draw(BITMAP * buffer) {
		draw_bounding_box(buffer);
	}
	
	void draw_bounding_box(BITMAP * buffer) {
		circle(buffer, pos.x, pos.y, radius-2, makecol(0, 255, 255));
		circle(buffer, pos.x, pos.y, radius  , makecol(0, 255, 255));
		circle(buffer, pos.x, pos.y, radius+2, makecol(0, 255, 255));
	}
};
