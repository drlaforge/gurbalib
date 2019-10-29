#include "convoy.h"

inherit STD_ROOM; 
#include "../area.h"

static object ControlObj;

void setControl(object ob){
   ControlObj = ob;
   return;
}

string query_peace(){
   return "A voice beeps: Happiness is mandatory, citizen.";
}

void setup(){
    
    
   set_no_boost(1);
   set_no_clean_up(1);
   set_short("An black submarine");
   set_long_f(
	"This is the interior of the submarine. It is almost totally bare. There are "+
	"no windows, and no instruments. A small monitor on the wall indicates that "+
	"the submarine is operating normally. You just have to wait for it to take you "+
	"wherever it is going.\n");
   add_item(({"submarine", "sub", "interior"}), "You are inside the bare submarine");
   add_item(({"window", "windows", "instrument" ,"instruments"}), "There aren't any!");
   add_item(({"monitor", "small monitor", "wall"}), "The monitor shows the submarine is working");
   set_light(1);
   set_outdoors(0);
   add_exit("out", "OffTheSub", "#catchOut");
}

int catchOut(){
   string room;
   if(!ControlObj){
      write("A voice beeps: Something is wrong, returning to Abacus!\n");
      TP->move_player("out of the submarine#"+Abacus);
      destruct(TO);
      return 1;
   }
   if( ControlObj->query_moving() ){
      write("You cannot leave whilst the submarine is under water!\n");
      return 1;
   }
   
   room = ( (mapping)ControlObj->query_locations() )[(int)ControlObj->query_location()];
   TP->move_player("out of the submarine#"+room);
   return 1;
}

