#include "convoy.h"

inherit STD_ROOM; 
#include "../area.h"

void setup(){
    
    
(ROOM+"convoy/westConvoy.c")->foo();
   set_light(1);
    
   set_outdoors(1);
   set_short("Road Between Fresad Jungle and Clenar Fields");
   set_long_f("You stand in the wilderness, to the north is the edge of Fresad Jungle and to the south "+
      "the endless Clenar Fields extend. The Fields, though they look very peaceful, have long been rumored "+
      "to be the romping ground of many strange things. Few people in Abacus would dare come out this far. "+
      "To the north and south a road extends...more of a dirt path actually. Any thoughts of traveling by foot "+
      "quickly fade. Off to the west you see the outlines of a mountain range, and far to the southeast the dark "+
      "shapes of Abacus pollute the sky.");
   add_item(({"fresad jungle","jungle","fresad","north","dark jungle"}),
      "Fresad Jungle is really unknown off - no one really knows whats in there. The jungle is very dark, so it's "+
      "hard to tell whats in there");
   add_item(({"clenar fields", "fields", "clenar", "endless fields"}),
      "The Clenar Fields extend as far as you can see to the south. They look very "+
      "calm and peaceful, though in a weird way");
   add_item(({"road", "north road", "south road", "dirt road", "dusty road", "dirt path"}),
      "A worn down dusty road that runs north to south from here");
   add_item(({"mountain", "mountains", "mountain range"}), "You can't really make it out, they seem very large");
   add_item(({"dark shapes", "city", "abacus"}), "A faint outline of Abacus is to the east");
   add_object(ROOM+"convoy/bench");
   add_exit("north","domains/Areas/jungle/backbone/jungle6");
}
