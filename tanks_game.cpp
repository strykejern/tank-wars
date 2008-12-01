class tanks_game {
	public:
	std::vector<tank> tanks;
	std::vector<shot> shots;
	std::vector<explosion> explosions;
	
	std::vector<Vector> collision_vectors;
	
	BITMAP * bg;
	BITMAP * bg_collision;
	BITMAP * bld;
	BITMAP * bld_collision;
	
	tanks_game() {
		bg = NULL;
		init_bg_collision();
	}
	
	tanks_game(BITMAP * Bg, BITMAP * Bg_collision, BITMAP * Bld, BITMAP * Bld_collision) {
		bg = Bg;
		bg_collision = Bg_collision;
		bld = Bld;
		bld_collision = Bld_collision;
	}
	
	void init_bg_collision() {
		bg_collision = create_bitmap(SCREEN_X, SCREEN_Y);
	}
	
	void add_tank(tank tank1) {
		tanks.push_back(tank1);
		tanks[(int)tanks.size()-1].set_shots(&shots);
	}
	
	void add_obstruction(Vector pos, std::vector<Vector> points) {
		///////////Old//////////
		//obstructions.push_back(obstruction(pos, points));
		////////////////////////
		if (bg_collision == NULL) init_bg_collision();
		obstruction tmp = obstruction(pos, points);
		tmp.draw(bg_collision);
		
	}
	
	void add_obstruction(obstruction obs1) {
		///////////Old/////////
		//obstructions.push_back(obs1);
		///////////////////////
		//if (bg_collision == NULL) init_bg_collision();
		obs1.draw(bg_collision);
	}
	
	void update() {
		for (int i = 0; i < (int)tanks.size(); ++i) {
			if (tanks[i].alive()) tanks[i].update();
		}
		for (int i = 0; i < (int)tanks.size(); ++i) {
			if (collision_check(&tanks[i]))
				collision(&tanks[i]);
			
			for (int x = i+1; x < (int)tanks.size(); ++x)
				if(collision_check(&tanks[i], &tanks[x])) 
					collision(&tanks[i], &tanks[x]);
			
			for (int x = 0; x < (int)shots.size(); ++x)
				if (i != shots[x].parent)
					if(collision_check(&tanks[i], &shots[x])) {
						collision(&tanks[i], shots[x]);
						shots.erase(shots.begin()+x--);
					}
		}
		for (int i = 0; i < (int)shots.size(); ++i) {
			if (shots[i].update() || collision_check(&shots[i])) {
				collision(&shots[i]);
				shots.erase(shots.begin()+i--);
			}
		}
		for (int i = 0; i < (int)explosions.size(); ++i) {
			for (int x = 0; x < (int)tanks.size(); ++x)
				if (collision_check(&tanks[x], &explosions[i]))
					collision(&tanks[x], &explosions[i]);
			if (explosions[i].update())
				explosions.erase(explosions.begin()+i--);
		}
		cannon_to_mouse(&tanks[0]);
	}
	
	void draw(BITMAP * buffer) {
		blit(bg, buffer, 0, 0, 0, 0, SCREEN_X, SCREEN_Y);
		draw_sprite(buffer, bld, 0, 0);
		for (int i = 0; i < (int)shots.size(); ++i)
			shots[i].draw(buffer);
		for (int i = 0; i < (int)tanks.size(); ++i)
			tanks[i].draw(buffer);
		for (int i = 0; i < (int)explosions.size(); ++i) {
			explosions[i].draw(buffer);
			explosions[i].destroy(bld);
			explosions[i].destroy(bld_collision);
		}
		draw_health(buffer, tanks[0].health_int(), Vector(10, 10));
		draw_health(buffer, tanks[1].health_int(), Vector(10, 30));
		
		textprintf_ex(buffer, font, 10, 50, makecol(255, 0, 0), -1, "%f", (Vector(mouse_x, mouse_y) - tanks[0].pos).angle());
		textprintf_ex(buffer, font, 10, 70, makecol(255, 0, 0), -1, "%f", (tanks[0].pos - Vector(mouse_x, mouse_y)).angle());
		textprintf_ex(buffer, font, 10, 90, makecol(255, 0, 0), -1, "%f", tanks[0].cannons[0].angle);
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
	
	bool collision_check(angular * tank1, explosion * exp1) {
		/*
		std::vector<Vector> tmp = tank1->abs_points();
		for (int i = 0; i < (int)tmp.size(); ++i)
			if ((exp1->pos - tmp[i]).length() < exp1->radius)
				return true;
		return false;
		*/
		return (exp1->pos - tank1->pos).length() < exp1->radius;
	}
	
	bool collision_check(angular * tank1) {
		std::vector<Vector> tmp_points = tank1->abs_points();
		for (int i = 0; i < (int)tmp_points.size(); ++i)
			if (getpixel(bg_collision, tmp_points[i].x, tmp_points[i].y) == makecol(0,255,0) ||
				getpixel(bld_collision, tmp_points[i].x, tmp_points[i].y) == makecol(0,255,0)) {
				tank1->last_collision = i;
				return true;
			}
		return false;
	}
	
	bool collision_check(shot * shots1) {
		if (getpixel(bg_collision , shots1->pos.x - (shots1->speed.x/2), shots1->pos.y - (shots1->speed.y/2)) == makecol(0,255,0) ||
			getpixel(bld_collision, shots1->pos.x - (shots1->speed.x/2), shots1->pos.y - (shots1->speed.y/2)) == makecol(0,255,0)) {
			shots1->pos -= shots1->speed / 2;
			return true;
		}
		return getpixel(bg_collision, shots1->pos.x, shots1->pos.y) == makecol(0,255,0) ||
				getpixel(bld_collision, shots1->pos.x, shots1->pos.y) == makecol(0,255,0);
	}
	
	void collision(tank * tanks1, tank * tanks2) {
		tanks1->collide_drive();
		tanks2->collide_drive();
		if (collision_check(tanks1, tanks2)) {
			tanks1->collide_rotate();
			tanks2->collide_rotate();
		}
	}
	
	void collision(tank * tanks1) {
		tanks1->collide_drive();
		if (collision_check(tanks1)) {
			tanks1->collide_rotate();
		}
	}
	
	void collision(tank * tanks1, shot shots1) {
		explosions.push_back(default_explosion(shots1.pos));
		tanks1->damage(shots1.damage);
	}
	
	void collision(shot * shots1) {
		explosions.push_back(default_explosion(shots1->pos));
	}
	
	void collision(tank * tanks1, explosion  * exp1) {
		tanks1->damage(exp1->damage/exp1->radius);
		
		Vector tmp = (tanks1->pos - exp1->pos);
		tmp.set_length(tmp.length() - exp1->radius);
		tanks1->speed -= tmp;
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

	void cannon_to_mouse(tank * tank1) {
		tank1->cannons[0].angle = -(tank1->pos - Vector(mouse_x, mouse_y)).angle() + (PI/2);
	}
};
