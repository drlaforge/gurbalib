/*  -*- LPC -*-  */
inherit "std/room";
#include "../area.h"

void setup(void) {
     
    set_light(1);
    short_desc = "Christopher Lange Square";
 
    long_desc = "This is the square of a private road called Christopher\n"+
		"Lange.	This road continues to the east and west, and in\n"+
		"the middle of the road there is a statue. The street goes\n"+
		"on to the east and west.\n";
		
		dest_dir = ({
		    ROOM+"clst2", "east",
		    ROOM+"clst3", "west",
		});
		items_arr = ({
		    "road", "The road continues east and west.",
		    "statue", "The statue is of Berne Tyrell, President of Tyrell Abacus.",
		});
	    }



