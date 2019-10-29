#include "../area.h"

inherit "/std/room";
inherit "/std/modules/m_block_exits";


void setup(void){
     
	set_short("5th Avenue");
 
	set_long("You are standing on 5th Avenue.  To the south of you there "+
		"is a street, blocked by a barricade. There seems no way to "+
		"cross it. 5th Avenue used to contuinue east, but the street "+
		"has subsided, leaving only a small path onwards. There is however a "+
		"road leading north.\n");

	set_light(1);
	add_exit("north",ROOMS + "s_boul10");
	add_exit("east", ROOMS + "5th_avenue6");
	add_exit("west", ROOMS + "5th_avenue4");
	add_exit("south", "#my_south");
	
	
	add_item("street","south street","barricade",
      	"The street south of you is totally blocked.");
	
	add_item("road","The road leads north.");
	
	
}
int my_south(){
   write("There is no way over the barricade!\n");
   return 1;
}

