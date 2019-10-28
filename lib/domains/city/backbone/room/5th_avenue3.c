inherit "/std/room";
#include "../area.h"

void setup(void){
   set_short("5th Avenue redevelopment");
 
   set_long_f("You are standing on 5th avenue, a wide road on the south "+
      	"side of the city. This place looks like it was once a rather "+
      	"well travelled and populated. This whole area is due for "+
	"redevelopment under a new scheme to provide much needed "+
	"accomodation.\n");
   set_outdoors(1);
   set_light(1);
   add_exit("east",ROOM+"5th_avenue4");
   add_exit("west",ROOM+"5th_avenue2");
   add_item(({"road","5th","5TH","5th avenue","5TH Avenue"}),
      "The road seems to held up quite well through the years.");
}
