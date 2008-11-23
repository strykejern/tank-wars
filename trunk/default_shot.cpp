struct default_shot : public shot {
	default_shot(Vector Pos, float Angle) : shot(Pos, Angle, 20) {
		points.push_back(Vector(-5,  2));
		points.push_back(Vector(10,  2));
		points.push_back(Vector(20,  0));
		points.push_back(Vector(10, -2));
		points.push_back(Vector(-5, -2));
		update_angles();
	}
};
