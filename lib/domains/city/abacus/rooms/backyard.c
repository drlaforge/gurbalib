#include "../area.h"

inherit "std/room";

     
void setup(void) {
     
    set_light(1);
    set_short("a gloomy backyard");
    set_long("You are in a very dark backyard. "+
		"The air is filled with the smell of rotten trash. "+
		"All around you see rusty trashbins spread out on the ground. "+
		"Big rats feast on some old food scraps. Pieces of the gray "+
		"walls have fallen to ground. In front of you the backyard "+
		"ends with a high wooden fence containing the old text 'The Devils "+
		"rule the world!'.\n");
		
	add_exit("east", ROOMS + "alley3");
	
    add_item("rats","They seems to have lived well on leftovers");
	add_item("pieces", "small pieces of cement","walls","They look old and dusty");
    add_item("fence","A high wooden fence with a lot of writing on it. The\n"+
             "biggest one reads: The Devil's rule the world!");
    add_item("bins", "trashbins", "bin", "#my_search");
    add_item("text","writing","grafitti", "The largest of the grafitti reads:"+
		"The Devil's rule the world!");
}
    
int my_search(){
    if(present("ricky",this_object())) {
      write("A wicked blow from Ricky's iron bar takes your mind off "+
          "of that.\n");
      return 1;
	}
    /*if(sword_present) {
      write("A very rusty trashbin with a lot of bulges\n"+
	    "In it you find an antique sword.\n");
      say(this_player()->query_name()+" finds a antique sword.\n");
    sword = clone_object("/std/object/headcutter");
      move_object(sword,this_object());
      sword_present = 0;
      return 1;
    }
    write("A very rusty trashbin with a lot of bulges\n"+
	  "You don't find anything of interest in it.\n");
    return 1;*/
}
  

