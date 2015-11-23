#ifndef CIRCLE_CONTROLLER_H_
#define CIRCLE_CONTROLLER_H_

//Include C Libraries
#include <stdlib.h> //Malloc
#include <stdbool.h>
#include <math.h> //sine cosine

#include <3ds.h> //For input
#include <sf2d.h>

struct _Circle {
	float x, y;
	int radius;
	float velocity;
	float direction; //In radians
};
typedef struct _Circle *Circle;



struct _CircleController {
	bool flag_exit; //Closes application if true.
	int frame;
	
	Circle *circle_array; 
	

};
typedef struct _CircleController *CircleController;



//Memory Management
extern CircleController circle_controller_init();
extern void circle_controller_free(CircleController t_control);

//Main Control
extern void circle_controller_handle_state(CircleController t_controller);
extern void circle_controller_create_all_circles(CircleController self);

//Draw
extern void circle_controller_draw_all_circles(CircleController self);
extern void circle_controller_draw(CircleController self);

//Input
extern void circle_controller_input(CircleController self);




#endif




