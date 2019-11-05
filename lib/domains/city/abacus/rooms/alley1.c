#include "../area.h"

inherit "/std/room"; 

void setup(void){
	
	set_light(1);
	set_short("the beginning of a dark alley");
	set_long("You are in the beginning of a dark alley. Your body\n"+
		"throws long pale shadows on the ground. A sign on the\n"+
		"wall says: 'Keep out! This domain belongs to the Devils, the\n"+
		"warriors of the street.' The alley continues to the north.\n"+
		"The west steet is to the south.\n");
	/*add_readable("sign");*/
	add_item("sign", "A dirty sign with the text: 'Keep out! This domain belongs to the\n"+
		"Devils, the Warriors of the Street!'");
	add_exit("south", ROOMS + "west_streetend");
	add_exit("north", ROOMS + "alley2");

}
