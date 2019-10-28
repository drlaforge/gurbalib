inherit "/std/room";
#include "../area.h"

void setup(void){
    
    
   set_short("5th Avenue redevelopment");
   set_light(1);
   set_outdoors(1);
 
   set_long_f("You are standing on 5th Avenue. To the north of you is a "+
      	"large empty corporate building. Like the rest of the buildings "+
	"here, there is no way into it, and it is due for redevelopment.\n");
   add_exit("east",ROOM+"5th_avenue5");
   add_exit("west",ROOM+"5th_avenue3");
   add_item(({"building","corporate building","empty corporate building"}),
      "A large corporate building, now abandoned. No way in.");
   add_item("buildings",
      "The buildings are all due for redevelopment.");
}

