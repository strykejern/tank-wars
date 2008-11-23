#include <list>

#define SCREEN_X 640
#define SCREEN_Y 480
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
	
	angular() {
		angle = 0;
		update_angles();
	}
	
	void update_angles() {
		angles.clear();
		lengths.clear();
		int length = (int)points.size();
		std::list<angle_vector> tmp_list;
		for (int i = 0; i < length; ++i) {
			tmp_list.push_back(angle_vector(points[i].angle(), points[i].length()));
		}
		tmp_list.sort(less_than);
		std::list<angle_vector>::iterator av;
		for (av = tmp_list.begin(); av != tmp_list.end(); ++av) {
			angles.push_back(av->angle);
			lengths.push_back(av->length);
		}
	}
	
	std::vector<Vector> ang_points() {
		int length = (int)points.size();
		std::vector<Vector> tmp_points ;
		for (int i = 0; i < length; ++i) {
			tmp_points.push_back(Vector(lengths[i], angle + angles[i], 0));
		}
		return tmp_points;
	}
	
	std::vector<float> project_to(Vector v) {
		int length = (int)points.size();
		std::vector<Vector> rot_points = ang_points();
		std::vector<float> border;
		border.push_back((pos + rot_points[0]) * v);
		border.push_back((pos + rot_points[0]) * v);
		for (int i = 1; i < length; ++i) {
			float tmp = (pos + rot_points[i]) * v;
			if (tmp < border[0]) border[0] = tmp;
			else if(tmp > border[1]) border[1] = tmp;
		}
		return border;
	}
	
	void border_collide() {
		int length = (int)points.size();
		std::vector<Vector> rot_points = ang_points();
		std::vector<Vector> abs_points;
		for (int i = 0; i < length; ++i) {
			abs_points.push_back(pos + rot_points[i]);
		}
		
		for (int i = 0; i < length; ++i) {
			if (abs_points[i].x > SCREEN_X){ 
				pos.x -= abs_points[i].x - SCREEN_X;
				speed.x = 0;
			}
			else if (abs_points[i].x < 0){ 
				pos.x += -abs_points[i].x;
				speed.x -= 0;
			}
			if (abs_points[i].y > SCREEN_Y){ 
				pos.y -= abs_points[i].y - SCREEN_Y;
				speed.y = 0;
			}
			else if (abs_points[i].y < 0){ 
				pos.y += -abs_points[i].y;
				speed.y = 0;
			}
		}
	}
};
