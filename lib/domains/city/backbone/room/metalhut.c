#include <def.h>
inherit STD_ROOM; 
#include "../area.h"

setup(){
    
   add_object("/obj/monsters/bob");
    
   set_light(1);
   set_outdoors(0);
   set_dig(1);
   set_short("inside the metal hut");
   set_long_f("The metal hut is made entirely out of scrap metal, infact everything in the hut is too! There is a table which resembles and "+
      "old car door, a plant pot made from a robot's head, even the floor is tiled in flattened metal panels.\n");
   add_item_f(({"metal hut","hut"}),"The metal hut has been constructed just out of old scrap metal.");
   add_item_f(({"metal","scrap metal","scrap"}),"Everything is made from scrap metal in here.");
   add_item(({"car door","door","table"}),"The table has been made out of an old door from a car.");
   add_item(({"plant pot","robot head","head"}),"The plant pot is made from a robot's head, perhaps one from the bunker.");
   add_item(({"floor","flattened metal panels","metal panels","panels"}),"The floor is made up of metal panels, one dark panel looks quite loose.");
   add_item(({"metal panel","panel","dark panel"}),"No, you were wrong, it's not lose at all.");
   add_exit("east", ROOM+"south_alley6");
}
