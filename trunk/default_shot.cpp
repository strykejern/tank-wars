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
		damage = 10;
	}
};

struct mini_shot : public shot {
	mini_shot(Vector Pos, float Angle, int Index) : shot(Pos, Angle, 20, Index) {
		pos = Pos;
		points.push_back(Vector(-2,  1));
		points.push_back(Vector(5,  1));
		points.push_back(Vector(-7,  0));
		points.push_back(Vector(5, -1));
		points.push_back(Vector(-2, -1));
		update_angles();
		set_contact_point();
		damage = 1;
	}
};
