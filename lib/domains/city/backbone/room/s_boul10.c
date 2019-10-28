inherit "/std/room";
#include "../area.h"

void setup(void){
    
    
   set_short("Angels boulevard Sunco station");
 
   set_long_f("You are on Angels boulevard. "+
      "East of you is a Sunoco gas station that appears "+ 
      "to be under repair. There are large holes dug out, "+
      "and a few equipment trucks around the gas station.  "+
      "The entrance and perimeter are all fenced off to "+
      "prevent people entering.");
   set_outdoors(1);
   set_light(1);
   add_exit("south",ROOM+"5th_avenue5");
   add_exit("north",ROOM+"s_boul9");
   add_item(({"angels boulevard","angels"}),
      "You are standing on it.");
   add_item(({"entrance","perimiter","fence"}),
      "The entrance and perimiter are fenced.");
   add_item(({"sunoco","Sunoco","gas","gas station","station"}),
      "The gas station is closed.");
   add_item(({"construction","equipment","trucks","equipment trucks"}),
      "There are large trucks in the gas station in order for the\n"+
      "reconstruction of the gas station.");
   add_item(({"hole","holes"}),
      "Large holes dug into the ground of the gas station.");
}
