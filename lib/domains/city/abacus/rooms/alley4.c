#include "../area.h"

inherit "std/room";

void setup(void) {
 
	set_short("a dark alley");
	set_long("The dark alley end here.\n"+
            "The walls rise mightily above you and you feel very small.\n"+
            "The smell of rotten meat is less intense now but you can\n"+
            "still get a strong whiff of it.\n");
	
	add_exit("east", ROOMS + "alley2");
	
	add_item("walls","The walls is made of dark-gray concrete. Some pieces have"+
           " fallen off\nand the red stones under those can be seen");
}
