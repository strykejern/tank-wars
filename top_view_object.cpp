class top_view_object : virtual public basic_game_object {
	public:
	Vector * points;
	int 	length;
	
	top_view_object(Vector Center, Vector * Points, int Length) {
		pos	   = Center;
		points = Points;
		length = Length;
	}
	top_view_object() {
		length = 0;
	}
	
	virtual void draw_bounding_box(BITMAP * buffer) {
		for (int i = 0; i < length; ++i) {
			line(buffer,
				(pos + points[i]).x,
				(pos + points[i]).y,
				(pos + points[(i==length-1)?0:i+1]).x,
				(pos + points[(i==length-1)?0:i+1]).y,
				makecol(255, 0, 0));
		}
	}
	
	virtual float * project_to(Vector v) {
		static float border[2];
		border[0] = (pos + points[0]) * v;
		border[1] = (pos + points[0]) * v;
		for (int i = 1; i < length; ++i) {
			float tmp = (pos + points[i]) * v;
			if (tmp < border[0]) border[0] = tmp;
			else if(tmp > border[1]) border[1] = tmp;
		}
		return border;
	}
};
