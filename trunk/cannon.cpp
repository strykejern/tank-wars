class cannon : virtual public top_view_object, virtual public angular {
	public:
	std::vector<shot> * shots;
	BITMAP * image;
	Vector image_offset;
	
	cannon(Vector Pos, std::vector<Vector> Points) : top_view_object(Pos, Points) {
		
	}
	
	cannon(Vector Pos, std::vector<Vector> Points, std::vector<shot> * Shots) : top_view_object(Pos, Points) {
		shots = Shots;
	}
	
	cannon(std::vector<shot> * Shots) {
		pos = Vector(0, 0);
		points.push_back(Vector(-5,  2));
		points.push_back(Vector(20,  2));
		points.push_back(Vector(20, -2));
		points.push_back(Vector(-5, -2));
		shots = Shots;
		update_angles();
		angle = 2*(PI/2);
	}
	
	cannon() {
		pos = Vector(0, 0);
		points.push_back(Vector(-5,  2));
		points.push_back(Vector(20,  2));
		points.push_back(Vector(20, -2));
		points.push_back(Vector(-5, -2));
		update_angles();
		angle = 2*(PI/2);
	}
	
	void draw(BITMAP * buffer) {
		if (image == NULL)
			draw_bounding_box(buffer);
		else
			pivot_sprite(buffer, 
						image, 
						pos.x, 
						pos.y, 
						image_offset.x, 
						image_offset.y, 
						itofix(angle*(128/PI)));
	}
	
	void draw_bounding_box(BITMAP * buffer) {
		int length = (int)points.size();
		std::vector<Vector> rot_points = abs_points();
		for (int i = 0; i < length; ++i) {
			triangle(buffer,
				rot_points[i].x,
				rot_points[i].y,
				rot_points[(i==length-1)?0:i+1].x,
				rot_points[(i==length-1)?0:i+1].y,
				pos.x,
				pos.y,
				makecol(0, 0, 255));
		}
	}
	
	virtual void shoot(int Index) {
		shots->push_back(mini_shot(pos, angle, Index));
	}
};
