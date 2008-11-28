#include <list>

struct angle_vector {
	float angle;
	float length;
	
	angle_vector(float Angle, float Length) {
		angle = Angle;
		length = Length;
	}
};

	bool less_than(angle_vector av1, angle_vector av2) {
		return av1.angle < av2.angle;
	}

class angular : virtual public top_view_object, virtual public basic_physics_object {
	public:
	float angle;
	std::vector<float> angles;
	std::vector<float> lengths;
	bool fixed_rot;
	BITMAP * image;
	
	angular() {
		angle = 0;
		update_angles();
		fixed_rot = false;
	}
	angular(bool fixed) {
		angle = 0;
		fixed_rot = fixed;
		if (!fixed) update_angles();
	}
	
	void update_angles() {
		angles.clear();
		lengths.clear();
		int length = (int)points.size();
		std::list<angle_vector> tmp_list;
		for (int i = 0; i < length; ++i) {
			tmp_list.push_back(angle_vector(points[i].angle() - (PI/2), points[i].length()));
		}
		tmp_list.sort(less_than);
		std::list<angle_vector>::iterator av;
		for (av = tmp_list.begin(); av != tmp_list.end(); ++av) {
			angles.push_back(av->angle);
			lengths.push_back(av->length);
		}
	}
	
	void add_point(Vector pnt) {
		points.push_back(pnt);
		update_angles();
	}
	
	std::vector<Vector> abs_points() {
		if (fixed_rot) {
			return points;
		}
		else {
			int length = (int)points.size();
			std::vector<Vector> tmp_points ;
			for (int i = 0; i < length; ++i) {
				tmp_points.push_back(pos + Vector(lengths[i], angle + angles[i], 0));
			}
			return tmp_points;
		}
	}
	
	std::vector<float> project_to(Vector v) {
		int length = (int)points.size();
		std::vector<Vector> rot_points = abs_points();
		std::vector<float> border;
		border.push_back(rot_points[0] * v);
		border.push_back(rot_points[0] * v);
		for (int i = 1; i < length; ++i) {
			float tmp = rot_points[i] * v;
			if (tmp < border[0]) border[0] = tmp;
			else if(tmp > border[1]) border[1] = tmp;
		}
		return border;
	}
	
	void border_collide() {
		int length = (int)points.size();
		std::vector<Vector> tmp_points = abs_points();
		
		for (int i = 0; i < length; ++i) {
			if (tmp_points[i].x > SCREEN_X){ 
				pos.x -= tmp_points[i].x - SCREEN_X;
				speed.x = 0;
			}
			else if (tmp_points[i].x < 0){ 
				pos.x += -tmp_points[i].x;
				speed.x -= 0;
			}
			if (tmp_points[i].y > SCREEN_Y){ 
				pos.y -= tmp_points[i].y - SCREEN_Y;
				speed.y = 0;
			}
			else if (tmp_points[i].y < 0){ 
				pos.y += -tmp_points[i].y;
				speed.y = 0;
			}
		}
	}
};
