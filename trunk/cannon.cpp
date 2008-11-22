class cannon : virtual public top_view_object, virtual public angular {
	public:
	cannon(Vector Pos, Vector * Points, int Length) : top_view_object(Pos, Points, Length) {
		
	}
	
	cannon() {
		pos = Vector(0, 0);
		Vector * tmp_points = new Vector[4];
		tmp_points[0] = Vector(-5,  2);
		tmp_points[1] = Vector(20,  2);
		tmp_points[2] = Vector(20, -2);
		tmp_points[3] = Vector(-5, -2);
		points = tmp_points;
		length = 4;
		angle = 90;
		update_angles();
	}
	
	/*~cannon() {
		delete [] points;
	}*/
	
	void draw_bounding_box(BITMAP * buffer) {
		Vector * rot_points = ang_points();
		for (int i = 0; i < length; ++i) {
			line(buffer,
				(pos + rot_points[i]).x,
				(pos + rot_points[i]).y,
				(pos + rot_points[(i==length-1)?0:i+1]).x,
				(pos + rot_points[(i==length-1)?0:i+1]).y,
				makecol(255, 0, 0));
		}
	}
};
