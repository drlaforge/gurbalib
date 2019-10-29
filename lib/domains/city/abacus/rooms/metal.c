
inherit "std/room";
#include "../area.h"

void setup(){
    
    
   
   set_outdoors(0);
   set_light(1);
   set_short("a dark alley");
   set_long_f(
      "You are standing in, what looks to be, a smashed out wall. "+
      "Whomever smashed the wall can not be weak, that's for sure. "+
      "You can also see some decorated skulls on the wall. "+
      "The floor is either painted brown, or totally stained by old blood. ",78);
   
   add_exit("south", ROOM+"east_road2", 0);
   add_item( ({ "wall", "smashes wall" }),
      "The smash in the wall was either made by a car or \nsome incredibly strong creature");
   add_item( ({ "skull", "skulls", "decorated skull", "decorated skulls" }),
      "All the skulls are decorated with ray-ban sun glasses");
   add_item(({ "painted floor","blood stained floor","brown floor","floor" }),
      "When you look closer, you notice that it isn't brown paint...");
   
   add_object("/obj/monsters/knight.c",1);
}

