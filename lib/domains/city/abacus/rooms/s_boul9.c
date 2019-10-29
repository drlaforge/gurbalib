inherit "/std/room";
#include "../area.h"

void setup(void){
    
    
   set_short("Angels boulevard");
 
   set_long_f("You are on Angels boulevard. This whole area is being "+
	"redeveloped and improved, for the first time since the war. "+
      	"The population of the city had decreased, and the survivors "+
	"stayed in the north of the city, but that is now changing. "+ 
	"East of you there is a parking lot, but it is fenced off.\n");
   set_outdoors(1);
   set_light(1);
   add_exit("north",ROOM+"s_boul8");
   add_exit("south",ROOM+"s_boul10");
   add_item(({"angels boulevard","angels"}),
      "Angels boulevard leads north and south.");
   add_item(({"lot","parking lot"}),
      "An old parking lot to the east, however you cannot enter it as\n"+
      "it is fenced off.");
   add_item(({"fence"}),
      "A fence blocks people from entering the parking lot.");
}
