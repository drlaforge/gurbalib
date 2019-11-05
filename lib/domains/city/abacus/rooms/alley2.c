#include "../area.h"

inherit "std/room";

void setup(void) {
  short_desc = "a dark alley";
  set_long("You are walking along a very dark alley.\n"+
            "Your mind screams of fear and tells you to leave.\n"+
            "Some wierd disgusting smell of rotten meat reaches your\n"+
	    "nose and makes you wanna puke. The alley splits up in four\n"+
	    "directions here.\n");
		
         set_exits((["north" : ROOMS + "alley3",
					 "west" : ROOMS + "alley4",
					 "east" : ROOMS + "alley5",
					 "south" : ROOMS + "alley1",
					 ]));
	
    /*add_smell("meat","The smell of rotten meat makes you want to puke.");
		add_smell("rotten meat","The smell of rotten meat makes you want to puke.");
	*/
  }



