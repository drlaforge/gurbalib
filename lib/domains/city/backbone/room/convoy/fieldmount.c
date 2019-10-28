#include "convoy.h"

inherit STD_ROOM; 
#include "../area.h"

void setup(){
    
    
(ROOM+"convoy/westConvoy.c")->foo();
   set_light(1);
    
   set_outdoors(1);
   set_short("Eastern Foothills of the Kiran Mountains");
   set_long_f("You stand in the wilderness, all alone. To the west is the mountain range, and it's foothills "+
      "run north and south. The jungle is a bit to the north of here, while most "+
      "of the region is littered with grass and rocks. The flat Clenar Fields extend south and southeast. "+
      "There is a dirt path which leads north and south from here. You can't see any safe passage into the "+
      "mountain range. Thinking about going back down the path by foot? Don't even think about it!\n");
   add_item(({"kiran mountain range", "mountain", "kiran range", "kiran mountains","mountains","mountain range"}),
      "A large mountain range that extends like a wall to the north and south of here");
   add_item(({"rock","rocks"}),"Rocks that have come free of the mountains.");
   add_item("grass","Small patches of living grass litter the region.");
   add_item(({"jungle","fresad jungle","north",}),"A large expanse of land covered by jungles");
   add_item(({"fields","clenar fields","clenar","south","southeast"}),"The Clenar Fields extend far to the "+
      "south and southwest from here");
   add_item(({"path","dirt path","dirt road"}),"A worn down path leading north and south from here");
   add_object(ROOM+"convoy/bench");
}

