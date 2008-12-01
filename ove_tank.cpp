struct ove_tank : public tank {
	ove_tank(Vector Pos) : tank(Pos) {
		pos = Pos;
		image = images[4];
		image_offset = Vector(18, 12);
		points.push_back(Vector(-18,  12));
		points.push_back(Vector(-18, -12));
		points.push_back(Vector( 18, -12));
		points.push_back(Vector( 18,  12));
		update_angles();
		cannons.push_back(default_cannon());
		MAX_SPEED = 8;
		ACCEL = 0.1f;
		ROT_DEC = 0.95f;
		HANDLING = 0.08f;
		health = 100;
	}
};
