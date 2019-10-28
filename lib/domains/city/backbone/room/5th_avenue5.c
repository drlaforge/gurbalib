inherit "/std/room";
#include "../area.h"

void setup(void){
    
    
   set_short("5th Avenue");
 
   set_long_f("You are standing on 5th Avenue.  To the south of you there "+
	"is a street, blocked by a barricade. There seems no way to "+
	"cross it. 5th Avenue used to contuinue east, but the street "+
	"has subsided, leaving only a small path onwards. There is however a "+
	"road leading north.\n");
   set_outdoors(1);
   set_light(1);
   add_exit("north",ROOM+"s_boul10");
   add_exit("east",ROOM+"5th_avenue6");
   add_exit("west",ROOM+"5th_avenue4");
   items_arr=({
	({"street","south street","barricade"}),
      	"The street south of you is totally blocked.",
	"road","The road leads north.",
		});
}

init(){
   ::init();
   add_action("south","south");
   add_action("south","climb");
}
int south(){
   write("There is no way over the barricade!\n");
   return 1;
}
