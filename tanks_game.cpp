class tanks_game {
	public:
	std::vector<tank> tanks;
	std::vector<obstruction> obstructions;
	
	Vector * collision_vectors;
	
	tanks_game() {
		
	}
	
	void add_tank(Vector pos, Vector * points, int length) {
		tanks.push_back(tank(pos, points, length));
	}
	void add_obstruction(Vector pos, Vector * points, int length) {
		obstructions.push_back(obstruction(pos, points, length));
	}
	
	void update() {
		for (int i = 0; i < (int)tanks.size(); ++i) {
			tanks[i].update();
		}
		for (int i = 0; i < (int)tanks.size(); ++i) {
			for (int x = i+1; x < (int)tanks.size(); ++x)
				if(collision_check(tanks[i], tanks[x])) 
					collision(&tanks[i], &tanks[x]);
					
			for (int x = 0; x < (int)obstructions.size(); ++x)
				if(collision_check(tanks[i], obstructions[x]))
					collision(&tanks[i], obstructions[x]);
		}
	}
	
	void draw(BITMAP * buffer) {
		for (int i = 0; i < (int)tanks.size(); ++i)
			tanks[i].draw_bounding_box(buffer);
		for (int i = 0; i < (int)obstructions.size(); ++i)
			obstructions[i].draw_bounding_box(buffer);
	}
	
	bool collision_check(angular tank1, angular tank2) {
		int overlaps = 0;
		for (int i = 0; i < 9; ++i) {
			float * ttmp1 = tank1.project_to(collision_vectors[i]);
			float tmp1[] = {ttmp1[0], ttmp1[1]};
			float * ttmp2 = tank2.project_to(collision_vectors[i]);
			float tmp2[] = {ttmp2[0], ttmp2[1]};
			if (between(tmp1[0], tmp2[0], tmp2[1]) ||
				between(tmp1[1], tmp2[0], tmp2[1]) ||
				between(tmp2[0], tmp1[0], tmp1[1]) ||
				between(tmp2[1], tmp1[0], tmp1[1]))
					overlaps++;
		}
		if (overlaps == 9)
			return true;
		return false;
	}
	
	void collision(tank * tanks1, tank * tanks2) {
		tanks1->pos -= tanks1->speed;
		tanks1->speed = Vector();
		tanks2->pos -= tanks2->speed;
		tanks2->speed = Vector();
		if (collision_check(*tanks1, *tanks2)) {
			tanks1->angle -= tanks1->last_rot * tanks1->HANDLING;
			tanks2->angle -= tanks2->last_rot * tanks2->HANDLING;
		}
	}
	
	void collision(tank * tanks1, obstruction obs) {
		tanks1->pos -= tanks1->speed;
		tanks1->speed = Vector();
		if (collision_check(*tanks1, obs)) {
			tanks1->angle -= tanks1->last_rot * tanks1->HANDLING;
		}
	}
	
	bool between (float x, float min, float max) {
		if ((min < x) && (x < max))
			return true;
		return false;
	}
	
	void set_collision_vectors(Vector * collisions) {
		collision_vectors = collisions;
	}
};
