inherit "std/room";
#include "../../area.h"
void setup(void){
	 
	set_outdoors(1);
	set_light(1);
	set_short("Nuclear Winter Park");
	set_long_f("From the north you hear various noises you might want to investigate. While "+
                   "surrounding you there is nothing but dead wood and tree stumps, it must have "+
                   "been part of the wood that was in the park before being killed by radiation "+
                 "and acid rain. In the distance you can see a shimmering lake.");
		
        add_sound(({"various noises","noises"}),"You hear various noises from the north you might want to investigate \n"+ "it sounds like rats running");
        add_item("nuclear winter park","You're stood in the park");
        add_item(({"dead wood","wood","tree","tree stumps","stump","stumps"}),"Whats left of the wood is all dead mainly just tree stumps left");
        add_item(({"radiation","rain","acid rain"}),"The radation has subsided but the acid rain has killed the trees here");
        add_item("park","This park of the park has been killed off by the acid rain");
        add_item(({"lake","shimmering lake"}),"A shimmering lake in the distance");
	add_exit("south",ROOM+"park/park4");
        add_exit("north",ROOM+"park/park2");
        add_exit("east",ROOM+"park/park8");
}

