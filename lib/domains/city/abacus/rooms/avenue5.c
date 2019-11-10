#include "../area.h"

inherit "std/room";

void setup(){
  
	set_light(1);
	/*set_outdoors(1); */
	/*set_dig(1); */
	set_short("An avenue");
	set_long("An avenue going east and west. Garbage litters the street to either\n"+
		"either side of it. Tall dark buildings stand to the north and south.\n"); 
  
	add_item("garbage", "litter","Garbage littered all over the avenue and sidewalks");
	add_item("sidewalk","sidewalks","Sidewalks on either side of the avenue");
	add_item("building","buildings","dark building","dark buildings","tall buildings","tall building","tall dark buildings","tall dark building","Dark buildings to the north and south");
	add_item("avenue", "An avenue going east and west");
	
	set_exits((["east" : ROOMS+"avenue4",
		    "west" : ROOMS+"avenue6"]));
}

