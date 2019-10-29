inherit "std/room";
#include "../area.h"

void setup(){
   set_light(1);
   /*set_outdoors(0); */
   set_short("Eve Street");
   set_long("You're walking down Eve Street. High buildings are running on each side of the street. "+
      "You don't feel comfortable in this area, the shadows could hide anything...or anyone.");
   add_item("high buildings","buildings","building","The buildings extend way up in the sky");
/*
    add_object( "/obj/monsters/thief", 1, 1 );
*/   
   add_exit("north", ROOMS+"eve_street3");
   add_exit("south", ROOMS+"eve_street1");
}


