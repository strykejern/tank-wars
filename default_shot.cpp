struct default_shot : public shot {
	default_shot(Vector Pos, float Angle, int Index) : shot(Pos, Angle, 20, Index) {
		pos = Pos;
		damage = 10;
	}
};

struct mini_shot : public shot {
	mini_shot(Vector Pos, float Angle, int Index) : shot(Pos, Angle, 20, Index) {
		pos = Pos;
		damage = 1;
	}
};
