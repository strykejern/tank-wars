class basic_game_object {
	public:
	Vector pos;
	
	basic_game_object() {
		pos = Vector();
	}
	basic_game_object(Vector Pos) {
		pos = Pos;
	}
};
