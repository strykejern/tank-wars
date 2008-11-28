struct ove_tank : public tank {
	ove_tank(Vector Pos) : tank(Pos) {
		pos = Pos;
		image = load_tga("img/ove_tank_b.tga", palette);
		image_offset = Vector(18, 12);
		add_point(Vector(-18,  12));
		add_point(Vector(-18, -12));
		add_point(Vector( 18, -12));
		add_point(Vector( 18,  12));
		cannons.push_back(default_cannon());
		MAX_SPEED = 15;
		ACCEL = 0.2f;
		ROT_DEC = 0.99f;
		HANDLING = 0.2f;
		health = 100;
	}
};
