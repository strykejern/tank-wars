class obstruction : virtual public top_view_object, virtual public angular {
	public:
	obstruction(Vector Pos, Vector * Points, int Length) : top_view_object(Pos, Points, Length) {
		//angle = 90;
	}
	
	void draw(BITMAP * buffer) {
		
	}
	
	void draw_bounding_box(BITMAP * buffer) {
		Vector * rot_points = ang_points();
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
