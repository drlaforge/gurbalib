inherit "/std/room";
#include "../area.h"

void setup(void){
   
     
    set_short("5th Avenue");
 
    set_long("You are standing on the east end of 5th Avenue. "+
	       	"It appears that this was once a main road through town, "+
		"however it is in rather bad condition now. There are old "+
		"run down buildings to both the north and south. "+
		"According to rumors, these buildings are going to be "+ 
		"torn down as part of a redevelopment scheme.\n");
    /*set_outdoors(1);*/
    set_light(1);
    add_exit("west",ROOMS + "5th_avenue1");
    add_exit("east",ROOMS + "5th_avenue3");

    add_item("road","5th avenue","5th Avenue","5TH Avenue",
	     "The road your are standing on is in rather poor condition.");
    add_item("buildings","north building","south building","building",
		 "old run down buildings","old buildings","run down buildings",
	     "Old buildings to your north and town, subject to removal with\n"+
	     "the revitalization process for 5th Avenue.");
  }
