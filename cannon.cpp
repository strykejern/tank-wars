class cannon : virtual public top_view_object, virtual public angular {
	public:
	cannon(Vector Pos, std::vector<Vector> Points) : top_view_object(Pos, Points) {
		
	}
	
	cannon() {
		pos = Vector(0, 0);
		points.push_back(Vector(-5,  2));
		points.push_back(Vector(20,  2));
		points.push_back(Vector(20, -2));
		points.push_back(Vector(-5, -2));
		angle = 90;
		update_angles();
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
				makecol(0, 0, 255));
			triangle(buffer,
				(pos + rot_points[i]).x,
				(pos + rot_points[i]).y,
				(pos + rot_points[(i==length-1)?0:i+1]).x,
				(pos + rot_points[(i==length-1)?0:i+1]).y,
				pos.x,
				pos.y,
				makecol(0, 0, 255));
		}
	}
};
