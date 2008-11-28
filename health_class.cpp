struct health_class {
	float health;
	
	health_class(float Health) {
		health = Health;
	}
	health_class() {
		health = 1;
	}
	
	void damage(float dmg) {
		health -= dmg;
	}
	
	int health_int() {
		return (int)health;
	}
	
	bool alive() {
		return health > 0;
	}
};
