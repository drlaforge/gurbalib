#include "../area.h"

inherit STD_ROOM; 

void setup(void){

	set_light(1);
	/*set_outdoors(1);
	set_dig(1);*/
	set_short("East Street at the Shoreline Bridge");
	set_long("You are walking on East Street.\n"+
		"A massive bridge starts here, and a great concrete seawall rises "+
		"almost to street level below you. The river rumbles quietly below "+
		"the bridge. East Street runs back West to Central Square, and East "+
		"over the Abacus Shoreline Bridge to the shore.\n");
	
	add_item("bridge","shoreline bridge","abacus shoreline bridge",
		"A massive bridge of steel and concrete, crossing the river. However\n"+
		"it looks fragile - A victim of the nuclear war. Someone decided to reinforce\n"+
		"it recently, as you can see steel beams haphazardly welded to the structure.");
	add_item("seawall","concrete seawall","sea wall",
		"A large concrete seawall has been poured to protect the city from\n"+
		"the hazardous ocean water. It must be at least three stories high.");
	add_item("river","ocean","basin","sewage","water","sea",
		"You look over the side of the bridge at the river, and notice it isn't\n"+
		"really a river at all. It's an inlet from the sea, which you can see\n"+
		"further to the north. As you look closer, you notice a river does flow\n"+
		"into it - an underground river of sewage, forming a large basin between\n"+
		"the sea wall and the peninsula.");
	add_item("central","central square","You cannot see Central Square clearly from here.");
	add_item("shore","island","peninsula","land","shoreline",
		"The shore is connected to the mainland by the bridge, and by an isthmus\n"+
		"further to the south. It serves as a break for the harsh current, and as\n"+
		"a platform for docking, as the former shipping district lies to the south.");
	/*add_sound(({"water","river","roar","rumble","rumbling"}),
		"The river rumbles far below you.");*/  
	
	add_exit("west", ROOMS + "east_square3");
	add_exit("east", ROOMS + "bridge2");
   

}