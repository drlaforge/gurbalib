#include "../area.h"

inherit "/std/room/";

void setup(void){

	set_light(2);
	set_short("The cellar under an old school");
	set_long("You have entered a gloomy cellar under the old school. Another small room is off to the east - you hear plenty of foul language coming from there. There is also a stairway leading up to an old lecture room.");
	add_item("stairway", "It looks rather dusty and the woods seems very old");
	add_object("obj/grafittiwall", 1);
	add_exit("up", ROOMS + "adv_guild");
	add_exit("west", ROOMS + "poets");
	add_exit("east", ROOMS + "adv_cellar2");

}
