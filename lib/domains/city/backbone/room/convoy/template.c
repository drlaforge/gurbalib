
#include "convoy.h"

inherit STD_ROOM; 
#include "../area.h"

void setup(){
    
   if( arg ) return;
   set_light(1);
    
   set_outdoors(1);
   set_short("Convoy route");
   set_long_f(" long description ");
   add_object(ROOM+"convoy/bench", 1);
}

