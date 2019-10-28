inherit "std/room";
#include "../area.h"
 object ob1;
void setup(void) {
  if(!ob1)
ob1=move_object(clone_object("obj/monsters/workerh"),this_object());
    set_outdoors(1);
    set_light(1);
    short_desc = "Angels boulevard";
 
    set_long_f("Angels boulevard came to an end here, for many years. "+
	"However, due to rising populations in the city, this area "+
	"is being redeveloped to provide much needed accomodation. At "+
	"the moment, there is a road improvement program under way, "+
	"to allow access to the areas targetted for development.\n");
    dest_dir = ({
        ROOM+"s_boul5", "north",
	ROOM+"s_boul7","east",
        });
    items_arr = ({
	({"boulevard","angels boulevard","road"}),
	"Angels boulevard is being improved, to allow better access.",
	({"program","improvement program"}),
	"The road will be improved, as a first step in redevelopment.",
	"redevelopment","There is no redevelopment... yet.",
          });
}

