#include "convoy.h"

inherit STD_ROOM; 
#include "../area.h"

void setup(){
    
    
   set_light(1);
   set_outdoors(1);
   set_short("Great Desert");
   set_long_f("You stand in the middle of the Great Desert. Not wise. There is no water for miles "+
      "in either direction. Though to the South you think you see the very faint outlines of some "+
      "structure...must be a mirage. Far to the east and west the Kiran mountains loom. "+
      "There is nothing around you, after inspecting the desert you see a definite path "+
      "worn away by some large vehicle, hopefully it will be here soon!");
   add_item(({"great desert","desert"}), "The Great Desert - permanently scared from past wars, "+
      "this region is devoid of all life. Or so you think.");
   add_item(({"structure","faint outlines","east"}),"If it's real, it's quite a way to the south.");
   add_item(({"kiran","kiran mountains",}),"The huge mountains, a natural wall, lay to the west and east.");
   add_item(({"path","defined path","tracks","track","vehicle tracks"}),
      "Vehicle tracks, they have to be vehicle tracks -- right?");
}


