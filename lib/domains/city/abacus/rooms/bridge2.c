#include "../area.h"

inherit STD_ROOM; 

void setup(void){

	set_light(1);
	set_short("Abacus Shoreline Bridge");
	set_long("You are walking on a long bridge which connects the mainland to the shore. "+
		"To the side, a railing seems to sway in the wind and the river rumbles far "+
		"below you. You decide to stay in the center. East Street continues East to "+
		"the shore, and back to the mainland.\n");
    
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
	add_item("shore","island","peninsula","land","shoreline",
		"The shore is connected to the mainland by the bridge, and by an isthmus\n"+
		"further to the south. It serves as a break for the harsh current, and as\n"+
		"a platform for docking, as the former shipping district lies to the south.");
	add_item("mainland","city",
		"At the Eastern end of the bridge stands the city. Skyscrapers tower above\n"+
		"shanty towns and ruins, making the seawall look like a footnote. It's quite\n"+
		"a magnificent view.");
	add_item("rail","railing","wind",
		"A railing sways in the wind, you dare not touch it.\n"+
		"Fortunately, the rest of the bridge does not share this fate.");
	/*add_sound(({"water","river","roar","rumble","rumbling"}),
		"The river rumbles far below you.");*/
	add_exit("east", ROOMS + "bridge3");
	add_exit("west", ROOMS + "bridge1");
   

}