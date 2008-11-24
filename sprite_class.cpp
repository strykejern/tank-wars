struct sprite_class : public angular {
	BITMAP * image;
	Vector image_offset;
	
	sprite_class() { }
	
	sprite_class(BITMAP * Image, Vector Image_offset) {
		image = Image;
		image_offset = Image_offset;
	}
	
	virtual void draw(BITMAP * buffer) {
		pivot_sprite(buffer, 
					image, 
					image_offset.x, 
					image_offset.y, 
					pos.x - image_offset.x, 
					pos.y - image_offset.y, 
					256/(angle*PI));
	}
	
	void set_image(BITMAP * Image, Vector Image_offset){
		image = Image;
	}
}
