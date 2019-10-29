#include "convoy.h"

inherit STD_ROOM; 
#include "../area.h"


void setup(){
    
    
   set_light(1);
   set_outdoors(1);
    
   
   set_short("Abacus Bus Stop");
   set_long_f("You're standing in at an old bus stop. Far to the west you see a mountain range "+
      "that runs for miles to the north and south. Directly to the south are the wastelands while to the north "+
      "lie the open fields, neither of which are safe places to wander. "+
      "Directly in front of you is a rusty old bench and a sign that says \"Ded City Bus\". Though the "+
      "sign is quite old, the dirt road leading north and south of here has obviously been used recently. "+
      "Perhaps if you wait long enough, a bus will come by to pick you up. Twilight Avenue lays to your east.");
   add_item(({"field","Clenar Fields","grass","open field","fields"}),
      "A huge expanse of land, the Clenar Fields, assumed to be uninhabited.\n"+
      "Though no one really knows, no one has explored it - and survived");
   add_item(({"dusty road", "dirt road", "old road", "used road", "road"}), "A dusty road that has been used recently");
   add_item(({"mountain range","mountains","mountains"}),"The mountains are quite some distance away to to the west.\n"+
      "They run along the horizon to the north and south.");
   add_item(({"twilight avenue", "east"}), "An old avenue is to the east");
   add_exit("west", "ILikeMonkies", "#noWest");
   add_exit("east", ROOM+"twilight_3");
   set_no_clean_up(1);
   add_local_unique(ROOM+"convoy/control.c", 1);
   add_object(ROOM+"convoy/bench.c", 1);
   add_item(({"old sign", "ded sign", "sign",}), "An old sign which reads, \"Ded City Bus\".\n"+
      "Under it someone has scribbled - $"+TicketPrice+" per bus trip!!");
   add_readable(({"old sign", "ded sign", "sign"}));
}

int noWest(){
   write("You begin to step out into the wilderness...then you hear a sound that you're\n"+
      "pretty sure didn't come from a human...you quickly retreat.\n");
   return 1;
}
