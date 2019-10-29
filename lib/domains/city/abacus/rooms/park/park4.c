inherit "std/room";
#include "../../area.h"


void setup(void)
{
     
    set_outdoors(1);
    set_light(1);
    set_short("Nuclear Winter Park");
    set_long_f("The ground is totally barren and with a few tiny boulders jutting up through "+
	       "the ground, there is nothing much else to do or see. You could stay here and "+
	       "let time pass by if you had nothing else to do. Some of the boulders could be sat "+
	       "on. There is a lake to the east you might want to visit.");
    
    add_item(({"ground","barren ground"}),"The ground is totally barren apart from a few boulders jutting up through the"+ " ground");
    add_item(({"boulders","boulder","tiny boulders"}),"These boulders actually look comfortable enough to sit on");
    add_item("nuclear winter park","You,re stood in the park");
    add_item("park","This park of the park has been killed off by the acid rain");
    add_item("lake","A shimmering lake in the distance");
    add_exit("north",ROOM+"park/park3");
    add_exit("east",ROOM+"park/park5");
    add_exit("south","/domains/attachments/scope/room/entrance");

}

init() 
{
    ::init();
    add_action("sit","sit");
}

sit(str) 
{
    if(!str || str !="on boulder")
    {
    notify_fail("Sit on what?\n");	
    return 0; 
}
say(this_player()->query_name()+" sits on a comfortable boulder.\n");
write("You sit on a comfortable boulder.\n");
    return 1;
}     



