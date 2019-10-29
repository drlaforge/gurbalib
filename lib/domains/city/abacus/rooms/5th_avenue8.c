#include "../area.h"

inherit "/std/room";

void setup(void){
	 
   	set_light(1);
	set_short("5th Avenue, near the ocean");
 
   	set_long("You're at what seems to be an ocean. If you hadn't seen it for yourself, "+
		"you would never have believed that there'd be an ocean near here. The noise "+
		"of the sea is drowned by the noise of the city back to the west. You notice "+
		"there isn't a seagull in sight, it makes you wonder just what's in the sea-water "+
		"these days. 5th Avenue leads back to the west, while a smaller coastal road leads "+
		"off to the north");
	add_item("ocean","The sea looks so calm");
	add_item("sea","waves","You could stand and watch the waves all day");
	add_item("city","You look back onto the city. The ocean looks far more welcoming");
	add_item("seagull","You don't see any anywhere");
	add_item("sea-water","water","You see some crap floating in the water");
	add_item("crap","Yuck! Someone's taken a dump in the water");
	add_item("coastal road","5th avenue","avenue","road","5th Avenue leads west, while the coastal road leads north");
	/*add_sound("city","Gunshots, cars, all noise, too much noise");
	*/
	add_exit("north",ROOMS +" coast1");
	add_exit("west",ROOMS + "5th_avenue7");
}

