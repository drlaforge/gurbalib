#include <tune.h>
#include <def.h>
inherit "std/room";
#include "../area.h"

void setup(void) {
   
  
  set_outdoors(1);
  set_light(1);
  short_desc = "Sci prison";
  
  long_desc = 
    "A sci prison.\n";
}

init(){
  ::init();
    add_action("blah","",1);
  }

blah(){
  if(this_player()->query_level()<ARCH_LEVEL){
    return(write("Think a bit before you do illegal stuff.\n"));
  }
}
