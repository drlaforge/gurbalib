inherit "std/room";
#include "../../area.h"
object child,mother;
void setup(void){ 
	 
	if(!child){
		child=clone_object(ROOM+"park/child");
		move_object(child,this_object());
	}
	 
	set_outdoors(1);
	set_light(1);
	set_short("Nuclear Winter Park");
	set_long_f("In this part of the park you can see this is a childrens play area with"+ 
		" various swings and children's items all round the place. The ground is cleared"+ 
		" of broken glass and bottles and other objects which could cause injury to"+ 
		" young children. The path continues in various directions.");

	add_item("park","You are standing in the childrens play area of the park");
        add_item("nuclear winter park","You're stood in the park");
 	add_item(({"varoius swings","play items","childrens play items","swing","swings","items","childrens items"}),"Various childrens play items");
	add_item(({"broken glass","glass","bottle","bottles"}),"There is no broken glass about");
	add_item(({"ground","cleared ground"}),"The ground is cleared of broken glass and other dangerous items");
	add_item("path","The path continues in various directions");
	add_exit("north",ROOM+"park/park0");
	add_exit("west",ROOM+"park/park8");
        add_exit("south",ROOM+"park/park6");
}

