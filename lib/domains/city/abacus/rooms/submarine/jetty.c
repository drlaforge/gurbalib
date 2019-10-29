#include "convoy.h"

inherit STD_ROOM; 
#include "../area.h"


void setup(){
    
    
   set_light(1);
   set_outdoors(1);
    
   
   set_short("Abacus Jetty");
   set_long_f("You have reached the end of the jetty. You look out accross a "+
		"forbidding ocean. The water here is very deep and cold, and "+
		"you would not survive it. There is a sign on the jetty.\n");
   items_arr=({
	({"jetty","end"}),"You are at the end of the jetty",
	({"ocean","forbidding ocean"}),"The ocean does not look at all welcoming",
	"water","The water is very deep and cold",
	});
   add_exit("west", ROOM+"submarine/jetty2");
   set_no_clean_up(1);
   add_local_unique(ROOM+"submarine/control.c", 1);
   add_item("sign", "An old sign which reads, \"Submarine Trips!\".\n"+
      "Under it someone has scribbled - $"+TicketPrice+" per journey!!");
   add_readable("sign");
}

