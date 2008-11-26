struct default_tank : public tank {
	default_tank(Vector Pos) : tank(Pos) {
		add_point(Vector(-10,  15));
		add_point(Vector( 10,  15));
		add_point(Vector(  0,  20));
		add_point(Vector( 10, -15));
		add_point(Vector(-10, -15));
		update_angles();
		image = NULL;
	}
};
