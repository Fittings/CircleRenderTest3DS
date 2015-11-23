/* 
 * circle_controller.c handles the game state. 
 * It keeps track of if we are in menu/title/game etc. 
 */


#include "circle_controller.h"


//Settings for the circles.
#define MAX_SIZE 30//Max_Size of circle_array
#define X 200
#define Y 120
#define RADIUS 10
#define VELOCITY 5



//Initialize CircleController. Create an empty array of circles.
CircleController circle_controller_init() {
	CircleController self = malloc(sizeof *self);
	if (self == NULL) return NULL;
	
	
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
		int direction = rand() % 4; //This isn't the real way. But I don't actually need good randomness.
		Circle circle = malloc(sizeof *circle);
		circle->x = X; circle->y = Y; circle->radius = RADIUS; circle->direction = direction;
		circle->velocity = VELOCITY;
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
	for (i=0; i < MAX_SIZE; i++) {
		Circle circle = self->circle_array[i];
		
		if ( (circle->x > 400) || (circle->x < 0) || circle->y > 240 || circle->y < 0) {
			circle->direction = circle->direction + .85;
		}
		
		int x_dist = circle->velocity * sin(circle->direction);
		int y_dist = circle->velocity * cos(circle->direction);
		
		circle->x = circle->x + x_dist;
		circle->y = circle->y + y_dist;
		
		
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

void circle_controller_draw_all_circles(CircleController self) {
	int i;
	for (i=0; i < MAX_SIZE; i++) {
	Circle circle = self->circle_array[i];
		sf2d_draw_fill_circle(circle->x, circle->y, circle->radius, RGBA8(0xFF, 0xA5, 0xC4, 0xFF));
	}
}

//Draw these lovely circles on the screen.
void circle_controller_draw(CircleController self) {

	sf2d_start_frame(GFX_TOP, GFX_LEFT); //Left for Standard Vision
		sf2d_draw_rectangle(0, 0, 400, 240, RGBA8(0xFF, 0xFF, 0x89, 0xFF)); //Background
		circle_controller_draw_all_circles(self);
		
	sf2d_end_frame();
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_rectangle(0, 0, 400, 240, RGBA8(0xFF, 0xFF, 0x89, 0xFF)); //Background
	sf2d_end_frame();
	
	sf2d_swapbuffers();
}


//Handles input relating to the circle_controller
void circle_controller_input(CircleController self) {
	hidScanInput();
	u32 kDown = hidKeysDown();
	if (kDown & KEY_B) { //B -> Exit app
		self->flag_exit = true;
	}
}