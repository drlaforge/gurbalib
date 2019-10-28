inherit "std/room";
#include "../../area.h"
void setup(void){
 
	 
	set_outdoors(1);
	set_light(1);
	set_short("Nuclear Winter Park");
	set_long_f("You think this is the main footpath through the park, but your not quite "+
                   "sure as you can only tell by the hardness of the ground under your feet. "+
                   "The park is a large open space with what looks to be a lake far in the "+
                   "distance. There are noises coming from different directions.");
		
	add_item(({"footpath","main footpath","path"}),"It looks to be a footpath");
	add_item("park","A park");
        add_item("nuclear winter park","You're stood in the park");
        add_item("ground","The ground");
        add_item(({"large open space","large space","space"}),"A park");
        add_item("lake","What looks to be a lake in the distance");
        add_sound(({"noise","noises"}),"Noises comming from different directions");
        add_exit("north",ROOM+"west_streetend");
        add_exit("west",ROOM+"park/park1");
        add_exit("south",ROOM+"park/park7");
}

