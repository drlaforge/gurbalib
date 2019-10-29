inherit "/std/room";
#include "../area.h"

void setup(void){
    
      
     set_light(1);
     /*set_outdoors(1); Removed, it worked to put in the lampost in nuke*/
     set_short("5th Avenue");
      
     set_long("You are standing on 5th Avenue.  To the north of you "+
		"there is an alley. 5th Avenue continues eastwards from "+
		"here as a wide road, and seems as though it were once "+
		"well traveled. It is a brick road, and seems as if it "+
		"was well maintained when it was in use, as it is "+
		"still in pretty good shape.");
     set_exits((["north": ROOMS + "east_end",
                 "east" : ROOMS + "5th_avenue2",
				 ]));

     add_item("alley","north alley",
	      "There is an alley north of you.");
     add_item("road","brick road",
	      "You look at the road and ponder, 'road', 'ro-ad', 'row-add', what\n"+
	      "a wierd word.  Bah, forget it.");
}    


















