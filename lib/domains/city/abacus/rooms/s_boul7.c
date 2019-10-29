inherit "/std/room"
#include "../area.h"
object ob, ob1;

void setup(void){
  if(!ob) 
ob=move_object(clone_object("obj/monsters/workerp"),this_object()); 
  if(!ob1) 
ob1=move_object(clone_object("obj/monsters/workerh"),this_object()); 

    
   set_short("Angels boulevard east");
 
   set_long_f("You are standing on Angels boulevard. Abacus City lies "+
      	"to the west. To the east, the boulevard once again swings south. "+
	"The road here is being worked on, as a first step towards "+
	"making this part of the city habitable again.");
   set_light(1);
   set_outdoors(1);
   add_exit("east",ROOM+"s_boul8");
   add_exit("west",ROOM+"s_boul6");
   add_item(({"angels boulevard","boulevard","road"}),
      "The road is being reconstructed here.");
}
