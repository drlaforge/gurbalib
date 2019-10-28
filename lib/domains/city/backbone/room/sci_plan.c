#include <tune.h>
inherit "std/room";
#include "../area.h"

#include <tune.h>

object board;

void setup(void){
   
  board=clone_object("obj/SciBoard");
  board->SetShort("Scientist PLANNING board (DBBS)");
  board->SetDir("boards/PlanningBoard");
  board->SetAccessLevel(APP_LEVEL);
  move_object(board,this_object());
  set_light(1);
  set_outdoors(0);
  set_short("The Scientists' planning room.");
  set_long("This room is where scientists can talk about what they are going to\n"+
    "build next. If they want some cooperation for their projects, or if\n"+
    "they want to see if other scientists are already working on something\n"+
    "with the same theme, then they can check the DBBS for information.\n"+
    "Since no one usually has any problems coordinating their efforts, the\n"+
    "floor is slightly dusty and there is a sense of neglect in the air.\n");
  
  add_exit("down",ROOM+"adv_inner");
  add_exit("west",ROOM+"balance");
  add_exit("south",ROOM+"adv_inner2");
  add_exit("east",ROOM+"qc");
/*
  add_exit("north",ROOM+"app_moan");
*/
  
  add_item("dust", "You can see the dust lightly cover the floor.");
}

init()
{
  ::init();
    if(this_player()->query_level() < APP_LEVEL)
    {
      write("Who said you were allowed in here? You are forced to leave.\n");
      move_object(this_player(),ROOM+"adv_guild");
      say(this_player()->query_name()+
	  " bounced off the energy shield surrounding the room.\n");
      return 1;
    }
    return 0;
  }
