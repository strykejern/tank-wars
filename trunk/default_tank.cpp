struct default_tank : public tank {
	default_tank(Vector Pos) : tank(Pos) {
		points.push_back(Vector(-10,  15));
		points.push_back(Vector( 10,  15));
		points.push_back(Vector(  0,  20));
		points.push_back(Vector( 10, -15));
		points.push_back(Vector(-10, -15));
		update_angles();
		image = NULL;
	}
};
