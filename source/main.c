#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <3ds.h>


#include "circle_controller.h"

#include <sf2d.h>





int main()
{
	sf2d_init(); //Graphics Load
	//Create Touhou Game	
	CircleController circle_controller = circle_controller_init();

    while (aptMainLoop()) { //Program loop

		if (circle_controller->flag_exit == 1) break; //Exit Application
		circle_controller_handle_state(circle_controller);
		
		

		
		
	}
	sf2d_fini(); //Graphics Exit
    return 0;
}
