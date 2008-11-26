class top_view_object : virtual public basic_game_object {
	public:
	std::vector<Vector> points;
	
	top_view_object(Vector Center) {
		pos = Center;
	}
	top_view_object(Vector Center, std::vector<Vector> Points) {
		pos	   = Center;
		points = Points;
	}
	top_view_object() {
		pos = Vector();
	}
	
	virtual void draw_bounding_box(BITMAP * buffer) {
		int length = (int)points.size();
		for (int i = 0; i < length; ++i) {
			line(buffer,
				(pos + points[i]).x,
				(pos + points[i]).y,
				(pos + points[(i==length-1)?0:i+1]).x,
				(pos + points[(i==length-1)?0:i+1]).y,
				makecol(255, 0, 0));
		}
	}
	
	virtual std::vector<float> project_to(Vector v) {
		int length = (int)points.size();
		std::vector<float> border;
		border.push_back((pos + points[0]) * v);
		border.push_back((pos + points[0]) * v);
		for (int i = 1; i < length; ++i) {
			float tmp = (pos + points[i]) * v;
			if (tmp < border[0]) border[0] = tmp;
			else if(tmp > border[1]) border[1] = tmp;
		}
		return border;
	}
};
