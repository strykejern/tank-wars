struct default_obstruction : public obstruction {
	default_obstruction(Vector Pos) : obstruction(Pos) {
		pos = Pos;
		points.push_back(Vector(-20, -6));
		points.push_back(Vector( -6,-20));
		points.push_back(Vector(  6,-20));
		points.push_back(Vector( 20, -6));
		points.push_back(Vector( 20,  6));
		points.push_back(Vector(  6, 20));
		points.push_back(Vector( -6, 20));
		points.push_back(Vector(-20,  6));
		update_angles();
	}
};
