struct default_cannon : public cannon {
	default_cannon() : cannon() {
		image = images[3];
		image_offset = Vector(28, 9);
	}
};
