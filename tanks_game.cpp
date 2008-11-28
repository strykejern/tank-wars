class tanks_game {
	public:
	std::vector<tank> tanks;
	std::vector<obstruction> obstructions;
	std::vector<shot> shots;
	std::vector<explosion> explosions;
	
	std::vector<Vector> collision_vectors;
	
	tanks_game() {
		
	}
	
	void add_tank(Vector pos, std::vector<Vector> points) {
		tanks.push_back(tank(pos, points, &shots));
	}
	
	void add_tank(tank tank1) {
		tanks.push_back(tank1);
		tanks[(int)tanks.size()-1].set_shots(&shots);
	}
	
	void add_obstruction(Vector pos, std::vector<Vector> points) {
		obstructions.push_back(obstruction(pos, points));
	}
	
	void add_obstruction(obstruction obs1) {
		obstructions.push_back(obs1);
	}
	
	void update() {
		for (int i = 0; i < (int)tanks.size(); ++i) {
			if (tanks[i].alive()) tanks[i].update();
		}
		for (int i = 0; i < (int)tanks.size(); ++i) {
			for (int x = i+1; x < (int)tanks.size(); ++x)
				if(collision_check(&tanks[i], &tanks[x])) 
					collision(&tanks[i], &tanks[x]);
					
			for (int x = 0; x < (int)obstructions.size(); ++x)
				if(collision_check(&tanks[i], &obstructions[x]))
					collision(&tanks[i], obstructions[x]);
					
			for (int x = 0; x < (int)shots.size(); ++x)
				if (i != shots[x].parent)
					if(collision_check(&tanks[i], &shots[x])) {
						collision(&tanks[i], shots[x]);
						shots.erase(shots.begin()+x--);
					}
		}
		for (int i = 0; i < (int)obstructions.size(); ++i) {
			for (int x = 0; x < (int)shots.size(); ++x)
				if(collision_check(&obstructions[i], &shots[x])) {
					collision(obstructions[i], shots[x]);
					shots.erase(shots.begin()+x--);
				}
		}
		for (int i = 0; i < (int)shots.size(); ++i) {
			if (shots[i].update()) {
				collision(&shots[i]);
				shots.erase(shots.begin()+i--);
			}
		}
		for (int i = 0; i < (int)explosions.size(); ++i) {
			if (explosions[i].update())
				explosions.erase(explosions.begin()+i--);
		}
	}
	
	void draw(BITMAP * buffer) {
		for (int i = 0; i < (int)shots.size(); ++i)
			shots[i].draw(buffer);
		for (int i = 0; i < (int)tanks.size(); ++i)
			tanks[i].draw(buffer);
		for (int i = 0; i < (int)obstructions.size(); ++i)
			obstructions[i].draw(buffer);
		for (int i = 0; i < (int)explosions.size(); ++i)
			explosions[i].draw(buffer);
		draw_health(buffer, tanks[0].health_int(), Vector(10, 10));
		draw_health(buffer, tanks[1].health_int(), Vector(10, 30));
	}
	
	bool collision_check(angular * tank1, angular * tank2) {
		int overlaps = 0;
		for (int i = 0; i < (int)collision_vectors.size(); ++i) {
			std::vector<float> tmp1 = tank1->project_to(collision_vectors[i]);
			std::vector<float> tmp2 = tank2->project_to(collision_vectors[i]);
			if (between(tmp1[0], tmp2[0], tmp2[1]) ||
				between(tmp1[1], tmp2[0], tmp2[1]) ||
				between(tmp2[0], tmp1[0], tmp1[1]) ||
				between(tmp2[1], tmp1[0], tmp1[1]))
					overlaps++;
		}
		if (overlaps == (int)collision_vectors.size())
			return true;
		return false;
	}
	
	bool collision_check(angular * tank1, shot * shots1) {
		int overlaps = 0;
		for (int i = 0; i < (int)collision_vectors.size(); ++i) {
			std::vector<float> tmp1 = tank1->project_to(collision_vectors[i]);
			float tmp2 = shots1->project_to(collision_vectors[i]);
			if (between(tmp2, tmp1[0], tmp1[1]) ||
				between(tmp2, tmp1[0], tmp1[1]))
					overlaps++;
		}
		if (overlaps == (int)collision_vectors.size())
			return true;
		return false;
	}
	
	void collision(tank * tanks1, tank * tanks2) {
		tanks1->collide_drive();
		tanks2->collide_drive();
		if (collision_check(tanks1, tanks2)) {
			tanks1->collide_rotate();
			tanks2->collide_rotate();
		}
	}
	
	void collision(tank * tanks1, obstruction obs) {
		tanks1->collide_drive();
		if (collision_check(tanks1, &obs)) {
			tanks1->collide_rotate();
		}
	}
	
	void collision(tank * tanks1, shot shots1) {
		explosions.push_back(default_explosion(shots1.pos));
		tanks1->damage(shots1.damage);
	}
	
	void collision(obstruction obstructions1, shot shots1) {
		explosions.push_back(default_explosion(shots1.pos));
	}
	
	void collision(shot * shots1) {
		explosions.push_back(default_explosion(shots1->pos));
	}
	
	bool between (float x, float min, float max) {
		if ((min < x) && (x < max))
			return true;
		return false;
	}
	
	void set_collision_vectors(std::vector<Vector> collisions) {
		collision_vectors = collisions;
	}

	void draw_health(BITMAP * buffer, int health, Vector pos) {
		health = (health>0) ? health : 0;
        int color = 0;
        if (health>70&&health<=100) color = makecol(0,255,0);
        else if (health>30&&health<=70) color = makecol(255,128,0);
        else if (health<30) color = makecol(255,0,0);
        else if (health>100) color = makecol(0,255,255);
        rectfill(buffer, pos.x  , pos.y  , pos.x+101, pos.y+10, makecol(0  ,0,0));
        rectfill(buffer, pos.x+1, pos.y+1, pos.x+((health<=100)?health:100), pos.y+9 , color);
        textprintf_ex(buffer, font, pos.x+40, pos.y+2, makecol(255,255,255), -1, "%i", health);
	}
};
