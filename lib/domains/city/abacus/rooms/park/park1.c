inherit "std/room";
#include "../../area.h"
void setup(void){
	 
	set_outdoors(1);
	set_light(1);
	set_short("Nuclear Winter Park");
	set_long_f("The path seems to run out now. You are looking at some mutated plants looking"+
                 " closer at the plants you notice a gap leading to the west. "+ 
                   "From that direction you hear muffled noises of what seems to be "+
                   "an argument. You might get in trouble if you go that way, best leave them to"+ 
                   " it. You can still see what seems to be a lake to the south you might want to "+ "investigate it.");
		
	add_item(({"plants","plant","mutated plant","mutated plants"}),"Mutated plants there is a gap to the west");
        add_item("gap","The is a gap in the plants to the west");
        add_item("nuclear winter park","You're stood in the park");
        add_item("path","A path which seems to run out");
        add_sound(({"muffled noises","noises","argument","noise"}),"#pin_drop");
       	add_item("lake","There seems to be a lake to the south you might want to investigate it");
	add_exit("east",ROOM+"park/park0");
        add_exit("west",ROOM+"park/park2");
        add_exit("south",ROOM+"park/park8");
}

pin_drop(){
  	if(!find_object(ROOM+"park/park2")) return 1;
	if(present("bully",find_object(ROOM+"park/park2"))){
		write("You can't make out the muffled noises of the argument
");
		return 1;
	}
	write("No, you were wrong, you never heard a thing.\n");
	return 1;
}
