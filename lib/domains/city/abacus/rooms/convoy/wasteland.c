#include "convoy.h"
inherit STD_ROOM; 
#include "../area.h"

void setup(){
    
   if( arg ) return;
   (ROOM+"convoy/westConvoy.c")->foo();
   set_light(1);
    
   set_outdoors(1);
   set_short("Dusty road through the Wastelands");
   set_long_f("You are standing a dusty old road in The Wastelands. This isn't exactly a safe place. "+
      "You're not quite sure why you got off the bus, or how to get out of here. Hopefully another bus "+
      "will come soon so you can leave - it feels like someone is watching you. There is what looks like "+
      "a volleyball court to the north and a vast area to the west.\n");
   add_item(({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),"Yes, that's where you are");
   add_item(({"court","volleyball","volleyball court"}),"It's to the north.");
   add_object(ROOM+"convoy/bench", 1);
   add_exit("north",ROOM+"waste/volleyball");
   add_exit("west",ROOM+"waste/land23");
}
