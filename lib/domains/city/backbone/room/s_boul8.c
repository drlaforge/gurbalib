inherit "/std/room";
#include "../area.h"

void setup(void){
    
    
   set_short("Angels boulevard");
 
   set_long_f("You are standing on Angels boulevard. The road swings "+
	"south, and west towards the heart of Abacus city. "+
      	"East of you is a parking lot, with a fence surrounding it, "+
	"and a gate at its entrance. The gate is closed and locked.\n");
   set_light(1);
   set_outdoors(1);
   add_exit("south",ROOM+"s_boul9");
   add_exit("west",ROOM+"s_boul7");
   add_item(({"angels boulevard","angels"}),
      "You stand on Angels boulevard, which swings west and south.");
   add_item(({"lot","parking lot"}),
      "The parking lot is to the east.");
   add_item(({"fence"}),
      "There is a fence around the parking lot.");
   add_item(({"locked gate","gate","gate to parking lot","gate to lot"}),
      "There is a gate leading into the parking lot, it is locked.");
   add_item(({"entrance"}),
      "The entrance to the parking lot is to your south.");
   add_item(({"lock","rusted lock","pad lock","rusted pad lock"}),
      "The gate has a rusted pad lock on it, locking it shut.");
}
init(){
   ::init();
   add_action("bah",({"break","enter","open","unlock","climb"}));
}
bah(str){
   if(!str){
      notify_fail("Do what?\n");
      return 0;
   }
   if(str != "gate" && str != "lock" && str != "pad lock" && str != "fence"){
      notify_fail("Do what?\n");
      return 0;
   }
   write("You try, but see no way to do it.\n");
   return 1;
}
