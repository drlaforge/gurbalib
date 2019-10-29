inherit "std/room";
#include "../../area.h"
object monster;
int taste;
void setup(void){
        taste = 0;
	 
	 
	set_outdoors(1);
	set_light(1);
	set_short("Nuclear Winter Park");
	set_long_f("You are now standing at the edge of the lake, there is a slight yellow "+
                "tinge to the water and it looks as if nothing could be alive in the lake. "+
                "All around the lake grow mutated plants and flowers, probably poisonous. "+
           	"You wonder if it is possible to taste the water?");
                
       	add_item(({"lake","edge of lake"}),"You are at the edge of a lake, there are plants surrounding it");
        add_item("nuclear winter park","You're stood in the park");
        add_item("tinge","Yellow tinge in the water");
        add_item("edge","Its the edge of lake");
       	add_item(({"water","yellow water"}),"You might want to taste it");
       	add_item(({"plants","flowers","flower","plant","mutated plant","mutated plants","poisonous flowers","poisionous plants"}),"These plants are horrible");	
       	add_smell(({"plant","plants","flower","flowers"}),"They smell of rotten flesh");	
       	add_exit("north",ROOM+"park/park8");
       	add_exit("west",ROOM+"park/park4");
	add_exit("east",ROOM+"park/park6");
}
init(){
	::init();
    add_action("taste","taste");
}

taste(str){
	if(str=="water"){
		action("#NA ## the water.","taste-tastes"); 
        if(present("mutant",this_object()))
            return 1;
	   	if(taste)
            return 1;
   		taste = 1;
		call_out("monster_comming",2);
		return 1;
	}
	return 0;
}

monster_comming(){
       	tell_room(ROOM+"park/park5","The water mutant appears.\n");
	monster=clone_object(ROOM+"park/monster.c");
	move_object(monster, this_object());
}


