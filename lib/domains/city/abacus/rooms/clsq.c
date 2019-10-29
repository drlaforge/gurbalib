/*  -*- LPC -*-  */
inherit "std/room";
#include "../area.h"

void setup(void) {
    set_light(1);
    set_short("Christopher Lange Square");
    set_long("This is the square of a private road called Christopher\n"+
		"Lange.	This road continues to the east and west, and in\n"+
		"the middle of the road there is a statue. The street goes\n"+
		"on to the east and west.\n");
		set_exits((["east" : ROOMS+"clst2",
		    "west" : ROOMS+"clst3"]));
		add_item("road", "The road continues east and west.");
		    add_item("statue", "The statue is of Berne Tyrell, President of Tyrell Abacus.");
	    }




