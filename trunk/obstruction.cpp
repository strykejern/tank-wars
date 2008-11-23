class obstruction : virtual public top_view_object, virtual public angular {
	public:
	obstruction(Vector Pos, std::vector<Vector> Points) : top_view_object(Pos, Points) {
		//angle = 90;
	}
	
	void draw(BITMAP * buffer) {
		
	}
	
	void draw_bounding_box(BITMAP * buffer) {
		int length = (int)points.size();
		std::vector<Vector> rot_points = ang_points();
		for (int i = 0; i < length; ++i) {
			line(buffer,
				(pos + rot_points[i]).x,
				(pos + rot_points[i]).y,
				(pos + rot_points[(i==length-1)?0:i+1]).x,
				(pos + rot_points[(i==length-1)?0:i+1]).y,
				makecol(0, 255, 0));
		}
	}
};
