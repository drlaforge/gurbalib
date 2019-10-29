inherit "std/room";
#include "../area.h"

init () {
  ::init();
   add_action ("south","south");
}
void setup(void) {
/* Warlord's pie machine */
        if(!present("machine",this_object())) 
         move_object(clone_object("obj/piemachine"),
                this_object()); 

   
   
  set_outdoors(0);
  set_light(1);
  short_desc = "Central Square subway station";  
  set_long_f( 
    "You are standing on the platform of Central Square subway station, "+
    "and a schedule on the wall shows the route the train travels. Every "+
    "now and then, the floor vibrates a little. The rails for the train "+
    "are to the south, and there is a sign above them warning you against "+
    "entering the track area.\n");
  dest_dir = 
    ({
      ROOM+"central_under", "east",
    });
  items_arr = ({
    "schedule", "#schedule",
    "sign", "The sign reads:\n"+
            "    CAUTION: DO NOT ENTER THE TRACK AREA!!",
    "wall","It has grime all over it.",
    ({"rails","tracks","track area"}),"The train travels on the tracks.",
    "floor","It is apparent that no one has cleaned the place in years.",
  });
  add_readable("sign");
}

schedule () {
   ROOM+"train_room"->stations();
}
south() {
  write("You are about to walk off the platform, but you change your mind.\n");
   return 1;
}
