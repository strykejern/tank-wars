struct default_cannon : public cannon {
	default_cannon() : cannon() {
		image = load_tga("img/ove_tank_c.tga", palette);
		image_offset = Vector(28, 9);
	}
};
