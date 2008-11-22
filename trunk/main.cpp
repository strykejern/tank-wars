#include <allegro.h>
#include <vector>
#include "vector.cpp"
#include "tanks.cpp"
#include "obstruction.cpp"
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
    
    Vector collision_vectors[4];
	for (int i = 0; i < 9; ++i) {
		collision_vectors[i] = Vector(1.0f, 20.0f*i, 0);
	}
    
    Vector points[] = {
    	Vector(-10,  15),
    	Vector(  0,  20),
    	Vector( 10,  15),
    	Vector( 10, -15),
    	Vector(-10, -15)
	};
	
	Vector points2[] = {
    	Vector(-10,  15),
    	Vector(  0,  20),
    	Vector( 10,  15),
    	Vector( 10, -15),
    	Vector(-10, -15)
	};
    
    tanks_game game;
    game.add_tank(Vector(200, 200), points, 5);
    game.tanks[0].set_inputs(&key[KEY_UP], &key[KEY_DOWN], &key[KEY_LEFT], &key[KEY_RIGHT]);
    
    game.add_tank(Vector(300, 300), points2, 5);
    game.tanks[1].set_inputs(&key[KEY_W], &key[KEY_S], &key[KEY_A], &key[KEY_D]);
    
    game.set_collision_vectors(collision_vectors);
    
    //for (int i = 0; i < 1; ++i) {
    	Vector tmp_points[] = {
    		Vector(-10,  150),
    		Vector( 10,  150),
			Vector( 10, -150),
			Vector(-10, -150)
		};
    	game.add_obstruction(Vector(100, 100), tmp_points, 4);
	//}
    
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
