/* 
 * circle_controller.c handles the game state. 
 * It keeps track of if we are in menu/title/game etc. 
 */


#include "circle_controller.h"


//Settings for the circles.
#define MAX_SIZE 0 	//Max_Size of circle_array

//Starting point + a random distance
#define X 0 
#define Y 0
#define RADIUS 4


#define DO_DRAW 1
#define DO_SQUARE 1



//Initialize CircleController. Create an empty array of circles.
CircleController circle_controller_init() {
	CircleController self = malloc(sizeof *self);
	if (self == NULL) return NULL;
	
	/* Create reference circle */
	self->circle_timer = malloc(sizeof *self->circle_timer);
	self->circle_timer->x = 0; self->circle_timer->y = 120; self->circle_timer->x_velocity = 5; self->circle_timer->y_velocity = 0;
	
	
	
	srand((int)"to be honest, it doesn't really matter");
	self->circle_array = malloc(sizeof(Circle) * MAX_SIZE);
	circle_controller_create_all_circles(self);
	
	
	if (self->circle_array == NULL) { //If bullet_array init failed. Abort init.
		free(self->circle_array);
		return NULL;
	}
	
	self->frame = 0;
	
	self->flag_exit = false;

	return self;
}

void circle_controller_create_all_circles(CircleController self) {
	int i;
	
	for (i=0; i < MAX_SIZE; i++) {
		//This is all sloppy. w.ew.e
		int x_velocity = 1 + rand() % 5; //This isn't the real way. But I don't actually need good randomness.
		int y_velocity = 1 + rand() % 6; //This isn't the real way. But I don't actually need good randomness.
		if (rand() % 2 == 0) x_velocity = -x_velocity;
		if (rand() % 2 == 0) y_velocity = -y_velocity;
		
		
		Circle circle = malloc(sizeof *circle);
		circle->x = X+(rand()%400); circle->y = Y+(rand()%320); circle->radius = RADIUS; circle->x_velocity = x_velocity; circle->y_velocity = y_velocity;
		self->circle_array[i] = circle;
	}
}


//Freeing CircleController and its inner structs.
void circle_controller_free(CircleController self) {
	if (self != NULL) {
		free(self);
	}
}


void circle_controller_update_all_circles(CircleController self) {
	int i;
	
	/* Update the reference cirlce */
	if (self->circle_timer->x > 320) {
		self->circle_timer->x = 320;
		self->circle_timer->x_velocity = -(self->circle_timer->x_velocity);
	}
	if (self->circle_timer->x < 0) {
		self->circle_timer->x = 0;
		self->circle_timer->x_velocity = -(self->circle_timer->x_velocity);
	}
	self->circle_timer->x = self->circle_timer->x + self->circle_timer->x_velocity;
	
	
	/* Update the array of circles */
	for (i=0; i < MAX_SIZE; i++) {
		Circle circle = self->circle_array[i];
		
		if (circle->x > 400) {
			circle->x = 400;
			circle->x_velocity = -(circle->x_velocity);
		}
		
		if (circle->x < 0) {
			circle->x = 0;
			circle->x_velocity = -(circle->x_velocity);
		}
		
		if (circle->y > 240) {
			circle->y = 240;
			circle->y_velocity = -(circle->y_velocity);
		}
		
		if (circle->y < 0) {
			circle->y = 0;
			circle->y_velocity = -(circle->y_velocity);
		}

		
		circle->x = circle->x + circle->x_velocity;
		circle->y = circle->y + circle->y_velocity;
		
		
	}

	
}

void circle_controller_update(CircleController self) {
	self->frame = (self->frame+1) % 32000; //Silly Safetry. Lazy code.
	circle_controller_update_all_circles(self);
}


//Handles the CircleController app
void circle_controller_handle_state(CircleController self) {
	circle_controller_input(self);
	circle_controller_update(self);
	circle_controller_draw(self);
	
	
	
}


//Draw these lovely circles on the screen.
void circle_controller_draw(CircleController self) {

	sf2d_start_frame(GFX_TOP, GFX_LEFT); //Left for Standard Vision
		sf2d_draw_rectangle(0, 0, 400, 240, RGBA8(0xFF, 0xFF, 0x89, 0xFF)); //Background
		if (DO_DRAW) circle_controller_draw_all_circles(self);
		
	sf2d_end_frame();
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		
		sf2d_draw_rectangle(0, 0, 400, 240, RGBA8(0xFF, 0xEE, 0x89, 0xFF)); //Background
		sf2d_draw_fill_circle(self->circle_timer->x, self->circle_timer->y, 4, RGBA8(0xFF, 0xA5, 0xC4, 0xFF));
		float fps_percentage = sf2d_get_fps() / 60;
		sf2d_draw_rectangle(0, 200, fps_percentage * 320, 10, RGBA8(0x00, 0x00, 0x00, 0xFF));

			
	sf2d_end_frame();
	
	sf2d_swapbuffers();
}


//Goes through and draws all the circles.
void circle_controller_draw_all_circles(CircleController self) {
	int i;
	for (i=0; i < MAX_SIZE; i++) {
	Circle circle = self->circle_array[i];
		if (DO_SQUARE) {
			sf2d_draw_rectangle(circle->x - RADIUS, circle->y - RADIUS, RADIUS, RADIUS, RGBA8(0xFF, 0xA5, 0xC4, 0xFF));
		} else {
			sf2d_draw_fill_circle(circle->x, circle->y, circle->radius, RGBA8(0xFF, 0xA5, 0xC4, 0xFF));

		}
	}
}




//Handles input relating to the circle_controller
void circle_controller_input(CircleController self) {
	hidScanInput();
	u32 kDown = hidKeysDown();
	if (kDown & KEY_B) { //B -> Exit app
		self->flag_exit = true;
	}
}