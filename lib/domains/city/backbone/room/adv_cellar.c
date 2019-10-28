
/* Darkman - Room Converted from data file - Sun May 20 18:56:52 2007 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(2);
  set_short("The cellar under an old school");
  set_long_f("You have entered a gloomy cellar under the old school. Another small room is off to the east - you hear plenty of foul language coming from there. There is also a stairway leading up to an old lecture room.", 75);
  add_item("stairway", "It looks rather dusty and the woods seems very old");
  add_object("obj/grafittiwall", 1);
  add_exit("up", ROOM+"adv_guild");
  add_exit("west", ROOM+"poets");
  add_exit("east", ROOM+"adv_cellar2");

}
