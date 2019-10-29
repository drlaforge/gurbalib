#include <def.h>
inherit STD_ROOM; 
#include "../area.h"
void setup(){
    
    
   set_light(2);
   set_short("Money Exchange Offices");
   set_long_f("The Money Exchange Offices is actually a small well lit office which is unstaffed. "+
      "In the centre of the room is the Money Exchange System Terminal, this allows you to "+
      "move_object money to other citizens even when they are not online.\n");
   add_object("std/object/mex", 1);
   add_exit("east", ROOM+"eden1");

}
