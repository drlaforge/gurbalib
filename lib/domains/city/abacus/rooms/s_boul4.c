inherit "std/room";
#include "../area.h"

void setup(void) {
     

    set_outdoors(1);
    set_light(1);
    short_desc = "Angels boulevard";
 
    long_desc = 
        "You are walking along Angels boulevard.\n"
        + "It continues north and south. East you have the swimming centre.\n";
    dest_dir = ({
        ROOM+"s_boul5", "south",
        ROOM+"s_boul3", "north",
	/* "players/poldark/swim/room/entrance", "east", */        });
    items_arr = ({
      "swimming centre",
      "Abacus swimming centre",
          });
}


int my_east(){
  tell_room(this_object(),"The swimming centre is temporarily closed.\n");
  return 1;
}
  

