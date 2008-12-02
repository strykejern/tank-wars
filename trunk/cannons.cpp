struct default_cannon : public cannon {
	default_cannon() : cannon() {
		image = images[5];
		image_offset = Vector(28, 9);
	}
};

struct bodhi_cannon : public cannon {
	bodhi_cannon() : cannon() {
		image = images[8];
		image_offset = Vector(30,12);
	}	
};
