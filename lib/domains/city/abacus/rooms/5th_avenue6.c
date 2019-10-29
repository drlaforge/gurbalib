#include "../area.h"

inherit "/std/room";

void setup(void){
	 
	 
   	set_light(1);
	set_short("5th Avenue");
 
   	set_long("The street continues east and west here. The road is deteriorating "+
		"due to lack of care and maintenance. There's a small burnt out car "+
		"still smouldering blocking the pavement. The fumes from the burning "+
		"paint gives you a slight headache.");
	add_item("road","street","The road is in a bad way");
	add_item("small burnt out car","burnt out car","burnt car","small car","small burnt car","car",
		"It was some cheap Japanese car, now totally gutted");
	add_item("pavement","The burnt out car is blocking the pavement");
	/*add_smell(({"paint","fumes"}),"The smell of the paint gives you a slight headache");
   	*/
	add_exit("east",ROOMS + "5th_avenue7");
	add_exit("west",ROOMS + "5th_avenue5");
}

