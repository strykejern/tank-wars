#include <allegro.h>
#include <vector>
#include "vector.cpp"
#include "basic_physics_object.cpp"
#include "top_view_object.cpp"
#include "angular.cpp"
#include "shot.cpp"
#include "cannon.cpp"
#include "obstruction.cpp"
#include "tanks.cpp"
#include "default_tank.cpp"
#include "tanks_game.cpp"

#define SCREEN_X 640
#define SCREEN_Y 480

volatile long speed_counter = 0;

void increment_speed_counter() {
    speed_counter++;
}
END_OF_FUNCTION(increment_speed_counter);



int main() {
	allegro_init();
	install_timer();
	install_keyboard();
	
	LOCK_VARIABLE(speed_counter);
    LOCK_FUNCTION(increment_speed_counter);
    install_int_ex(increment_speed_counter, BPS_TO_TIMER(30));
	
	
	set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_X, SCREEN_Y, 0, 0);
    set_alpha_blender();
    
    BITMAP * buffer = create_bitmap(SCREEN_X, SCREEN_Y);
    
    std::vector<Vector> collision_vectors;
	for (int i = 0; i < 15; ++i) {
		collision_vectors.push_back(Vector(1.0f, 10.0f*i, 0));
	}
    
    tanks_game game;
    game.add_tank(default_tank(Vector(200, 200)));
    game.tanks[0].set_inputs(&key[KEY_UP], &key[KEY_DOWN], &key[KEY_LEFT], &key[KEY_RIGHT]);
    
    game.add_tank(default_tank(Vector(300, 300)));
    game.tanks[1].set_inputs(&key[KEY_W], &key[KEY_S], &key[KEY_A], &key[KEY_D]);
    
    game.set_collision_vectors(collision_vectors);
    
    std::vector<Vector> tmp_points;
    tmp_points.push_back(Vector(-10,  15));
    tmp_points.push_back(Vector( 10,  15));
    tmp_points.push_back(Vector( 10, -15));
    tmp_points.push_back(Vector(-10, -15));
    
    //srand((int)&tmp_points);
    for (int i = 0; i < 10; ++i) { 
    	game.add_obstruction(Vector(rand()%600, rand()%400), tmp_points);
	}
    
    while (!key[KEY_ESC]) {
        while (speed_counter > 0) {
        	//physics goes here
        	game.update();
        	speed_counter--;
		}
		//drawing goes here
		game.draw(buffer);
		
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_X, SCREEN_Y);
        clear_bitmap(buffer);

	}
	destroy_bitmap(buffer);
	
	return 0;
}
END_OF_MAIN();
