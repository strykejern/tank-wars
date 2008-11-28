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
};
