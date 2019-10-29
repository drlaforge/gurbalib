
inherit "std/room";
#include "../area.h"

#include <tune.h>

void setup(void){
 
 
set_outdoors(0);
set_light(1);
set_short("The Voting Room.");
set_long_f("You have entered a small well light room. There isn't much here "+
"but a machine standing in the middle of the room. This is where the citizens "+
"can come and vote on current topics of discussion.");
add_exit("down", ROOM+"adv_cellar2");
add_exit("west", ROOM+"adv_guild");

if(!present("voter", this_object()))
move_object( clone_object("/std/object/voter2.c"), this_object() );
}
query_peace(){ return 1; }

