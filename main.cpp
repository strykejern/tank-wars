#include <allegro.h>
#include <vector>

#define PI 3.14159265358979323846264338327950288419716f
#define SCREEN_X 980
#define SCREEN_Y 540

std::vector<BITMAP *> images;

#include "vector.cpp"

bool is_green(BITMAP*, Vector);

#include "timer_class.cpp"
#include "health_class.cpp"
#include "basic_physics_object.cpp"
#include "top_view_object.cpp"
#include "angular.cpp"
#include "explosion.cpp"
#include "default_explosion.cpp"
#include "shot.cpp"
#include "default_shot.cpp"
#include "cannon.cpp"
#include "cannons.cpp"
#include "obstruction.cpp"
#include "default_obstruction.cpp"
#include "tanks.cpp"
#include "ove_tank.cpp"
#include "default_tank.cpp"
#include "enemy.cpp"
#include "tanks_game.cpp"

volatile long speed_counter = 0;

void increment_speed_counter() {
    speed_counter++;
}
END_OF_FUNCTION(increment_speed_counter);

void init();
void end();
void load_bmp();

int main() {
	init();
    
    BITMAP * buffer = create_bitmap(SCREEN_X, SCREEN_Y);
    
    std::vector<Vector> collision_vectors;
	for (int i = 0; i < 7; ++i) {
		collision_vectors.push_back(Vector(1.0f, 20.0f*i, 0));
	}
    
    tanks_game game (images[0], images[1], images[2], images[3]);
    
    volatile char shoot = false;
    
    game.add_tank(bodhi_tank(Vector(40, 40)));
    game.tanks[0].set_inputs(&key[KEY_W], &key[KEY_S], &key[KEY_A], &key[KEY_D], &shoot, &key[KEY_G], &key[KEY_H]);
    
    game.add_enemy(Vector(950, 520));
    
    game.set_collision_vectors(collision_vectors);
    
    while (!key[KEY_ESC]) {
        while (speed_counter > 0) {
        	//physics goes here
        	if (mouse_b & 1) shoot = true;
        	else shoot = false;
        	game.update();
        	speed_counter--;
		}
		//drawing goes here
		game.draw(buffer);
		if (key[KEY_F5]) save_bitmap("screenshot.bmp", buffer, NULL);
		
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_X, SCREEN_Y);
        clear_to_color(buffer, makecol(25, 25, 25));

	}
	destroy_bitmap(buffer);
	end();
	
	return 0;
}
END_OF_MAIN();

void init() {
	allegro_init();
	install_timer();
	install_keyboard();
	install_mouse();
	
	LOCK_VARIABLE(speed_counter);
    LOCK_FUNCTION(increment_speed_counter);
    install_int_ex(increment_speed_counter, BPS_TO_TIMER(30));
	
	
	set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_X, SCREEN_Y, 0, 0);
    set_alpha_blender();
    
    load_bmp();
}

void end() {
	for (int i = 0; i < (int)images.size(); ++i)
		destroy_bitmap(images[i]);
}

void load_bmp() {
	images.push_back(load_tga(		"img/bg.tga", 			NULL));// 0
	images.push_back(load_tga(		"img/bg_c.tga", 		NULL));// 1
	images.push_back(load_tga(		"img/bld.tga",			NULL));// 2
	images.push_back(load_tga(		"img/bld_c.tga",		NULL));// 3
	images.push_back(load_tga(		"img/ove_tank_b.tga", 	NULL));// 4
	images.push_back(load_tga(		"img/ove_tank_c.tga", 	NULL));// 5
	images.push_back(load_bitmap(	"img/soldat1.bmp", 		NULL));// 6
	images.push_back(load_tga(		"img/torso.tga", 		NULL));// 7
	images.push_back(load_tga(		"img/kanon.tga",	 	NULL));// 8
}

bool is_green(BITMAP* collision, Vector point) {
	return getpixel(collision, point.x, point.y) == makecol(0,255,0);
}
