inherit "std/room";
#include "../area.h"

#include <tune.h>

object board;

void setup(void){
   
  board=clone_object("/obj/SciBoard");
  board->SetShort("Request for Balance Approval Board (DBBS)");
  board->SetDir("boards/BalanceBoard");
  board->SetAccessLevel(APP_LEVEL);
  move_object(board,this_object());
  set_light(1);
  set_outdoors(0);
  set_short("The planners room");
  set_long("This is the office for the Balance Arches.  You should only come here when\n"+
	   "your area is ready.  The room has maps and models everywhere, and there\n"+
	   "is also a paradoxial-animation-time-flux generator on the wall.  To let the\n"+
	   "arches know your area is ready for Balance approval, just leave a note on\n"+
	   "the board.  But remember..if your area fails, then it is removed from the\n"+
	   "list, and moved to the bottom.\n");
  
  add_exit("east",ROOM+"sci_plan");

  add_item(({"maps","map"}), "The maps are of various areas under approval.");
  add_item(({"models","model"}), "The models are working toys that need approval.");
  add_item("machine","If you were an arch, you would understand how to use\n"+
	   "the machine.");
  add_item("wall","Plenty of maps hang on the wall.");
}

init(){
  ::init();
    if(this_player()->query_level() < APP_LEVEL)
    {
      write("Who said you can be in here? You are move_objected away.\n");
      say(this_player()->query_name()+
	  " got thrown out due to being a puny mortal.\n");
      move_object(this_player(), ROOM+"adv_guild");
      return 1;
    }
    return 0;
  }




