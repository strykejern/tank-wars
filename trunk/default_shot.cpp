struct default_shot : public shot {
	default_shot(Vector Pos, float Angle, int Index) : shot(Pos, Angle, 20, Index) {
		pos = Pos;
		points.push_back(Vector(-5,  2));
		points.push_back(Vector(10,  2));
		points.push_back(Vector(-15,  0));
		points.push_back(Vector(10, -2));
		points.push_back(Vector(-5, -2));
		update_angles();
		set_contact_point();
	}
};
