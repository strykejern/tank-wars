class obstruction : virtual public top_view_object, virtual public angular {
	public:
	obstruction(Vector Pos, std::vector<Vector> Points) : top_view_object(Pos, Points), angular(true) {
		//angle = 90;
		image = NULL;
	}
	obstruction(Vector Pos) : top_view_object(Pos), angular(true) {
		image = NULL;
	}
	
	void draw(BITMAP * buffer) {
		draw_bounding_box(buffer);
	}
	
	void draw_bounding_box(BITMAP * buffer) {
		int length = (int)points.size();
		std::vector<Vector> rot_points = abs_points();
		for (int i = 0; i < length; ++i) {
			line(buffer,
				rot_points[i].x,
				rot_points[i].y,
				rot_points[(i==length-1)?0:i+1].x,
				rot_points[(i==length-1)?0:i+1].y,
				makecol(0, 255, 0));
			triangle(buffer,
				rot_points[i].x,
				rot_points[i].y,
				rot_points[(i==length-1)?0:i+1].x,
				rot_points[(i==length-1)?0:i+1].y,
				pos.x,
				pos.y,
				makecol(0, 255, 0));
		}
	}
};
