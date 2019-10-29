#include "../area.h" 
inherit "/std/room/";

void setup(void) {
  
	set_light(1); 
	set_short("Intersection of S. Adams and Porsche");
   	set_long("The intersection of South Adams Street and Porsche Avenue. "+
		"Porsche extends west through a wasteland of wrecked buildings, "+
		"while Adams continues north and south.");
	set_exits((["north" : ROOMS + "southadams3",
			  "south" : ROOMS + "southadams5",
			  "west" : ROOMS + "porsche1",
			]));
	add_item("wasteland","buildings","wrecked buildings",
		"A wasteland of wrecked buildings.");
	add_item("street","adams street","south adams street",
		"The street is well decayed and runs narrowly in between wrecked buildings.");
	add_item("avenue","porsche avenue","The avenue is well decayed and runs narrowly in between wrecked buildings.");
}
