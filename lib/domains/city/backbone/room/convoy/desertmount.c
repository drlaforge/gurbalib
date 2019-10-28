#include "convoy.h"

inherit STD_ROOM; 
#include "../area.h"

void setup(){
    
    
   set_light(1);
   set_outdoors(1);
   set_short("Western Foothills of the Kiran Mountains");
   set_long_f("It's getting hotter here. You look up at the snow peaked mountain range in envy. "+
      "Looking is all you do, as you dare not travel into them alone. Further to the south "+
      "is the start of the Great Desert. You have heard stories of a settlement out there, "+
      "but you're not quite sure where.");
   add_item(({"kiran mountain range", "mountain", "kiran range", "kiran mountains","mountains","mountain range"}),
      "A large mountain range that extends like a wall to the east and west of here");
   add_item(({"path","dirt path","dirt road"}),"A worn down path leading east from here");
   add_item(({"great desert","desert"}), "The Great Desert - permanently scared from past wars, "+
      "this region is devoid of all life. Or so you think.");
   skip_obvious = 1;
}



