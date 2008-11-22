#define SCREEN_X 640
#define SCREEN_Y 480

class angular : virtual public top_view_object, virtual public basic_physics_object {
	public:
	float angle;
	float * angles;
	
	angular() {
		angle = 0;
		angles = new float[length];
		for (int i = 0; i < length; ++i) {
			angles[i] = points[i].angle();
		}
	}
	
	Vector * ang_points() {
		static Vector * tmp_points = new Vector[length];
		for (int i = 0; i < length; ++i) {
			tmp_points[i] = points[i].rotated_cp(angle + angles[i]);
		}
		return tmp_points;
	}
	
	float * project_to(Vector v) {
		Vector * rot_points = ang_points();
		static float border[2];
		border[0] = (pos + rot_points[0]) * v;
		border[1] = (pos + rot_points[0]) * v;
		for (int i = 1; i < length; ++i) {
			float tmp = (pos + rot_points[i]) * v;
			if (tmp < border[0]) border[0] = tmp;
			else if(tmp > border[1]) border[1] = tmp;
		}
		return border;
	}
	
	void border_collide() {
		Vector * rot_points = ang_points();
		Vector abs_points[length];
		for (int i = 0; i < length; ++i) {
			abs_points[i] = pos + rot_points[i];
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
