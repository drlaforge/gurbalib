inherit "std/room";
#include "../../area.h"
object spirit;
int kicked;
void setup(void){
	 
	kicked=0;
	 
	set_outdoors(1);
	set_light(1);
	set_short("Nuclear Winter Park");
	set_long_f("You are now standing in the center of the park on top of a mound with a "+
                   "very familar looking statue. The cold nuclear winter and the virtually bare "+
                   "open mound make this one of the most inhospitable places to be. The statue "+
                "looks to be very scuffed around the base. To the south there is an interesting "+
                "looking lake.");
                
        add_item(({"center of park","park"}),"You are in the middle of the park with a statue");
       add_item(({"open mound","mound"}),"You are standing on an open mound with a statue");
       add_item("nuclear winter park","You're stood in the park");
       add_item(({"statue","base","scuffed base"}),"The statue is of the present ruler, it looks as if it has been kicked a lot");
      add_item(({"lake","intersting lake"}),"There is lake to the south");
       add_item("ruler","The statue of the present ruler of the land");	
	

        add_exit("north",ROOM+"park/park1");
        add_exit("south",ROOM+"park/park5");
        add_exit("east",ROOM+"park/park7");
        add_exit("west",ROOM+"park/park3");
}
init(){

  ::init();
  add_action("kick","kick");
}
kick(str)
{
	if(str=="statue"){
		if(kicked){
			action("#NA ## the statue.","kick-kicks");
			return 1;
		}
		action("#NA ## the statue.","kick-kicks");
		kicked=1;
		call_out("monster_coming",5);
		return 1;
	}
	return 0;
}

monster_coming(){
             tell_room(ROOM+"park/park8","The ghost of the ruler appears.\n");
spirit=clone_object(ROOM+"park/spirit.c");
move_object(spirit, this_object());
}


living_died(corpse) {
  if(previous_object()->id("ghost")) destruct(corpse);
}
