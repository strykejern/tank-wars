struct ove_tank : public tank {
	ove_tank(Vector Pos) : tank(Pos) {
		pos = Pos;
		image = load_tga("img/ove_tank_b.tga", palette);
		image_offset = Vector(18, 12);
		add_point(Vector(-18,  12));
		add_point(Vector(-18, -12));
		add_point(Vector( 18, -12));
		add_point(Vector( 18,  12));
		cannons.push_back(cannon());
		cannons[0].image = load_tga("img/ove_tank_c.tga", palette);
		cannons[0].image_offset = Vector(28, 9);
		MAX_SPEED = 5;
		ACCEL = 0.1f;
	}
};