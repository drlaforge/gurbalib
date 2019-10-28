inherit "std/room";
#include "../area.h"

#include <tune.h>

object board;

void setup(void)
{
  if(arg)  return;
    board = clone_object("/obj/SciBoard");
    board -> SetShort("the News board");
    board -> SetDir("/boards/News/");
    board -> SetLong("The News board with all the latest gossip.\n");
    board -> SetAllowPseudo(1);
    board -> SetAccessLevel(ARCH_LEVEL);
    move_object(board, this_object());
      
  set_outdoors(0);
  no_clean_up = 0;
  set_light(1);
  set_short("The News Room.");
  set_long_f("You have entered the News Room. This is where you will "+
             "find an update on what's new in town. This is also where "+
             "you can find out if the latest rumours are true or not. "+
	     "Please stay tuned....");

add_exit("north", ROOM+"sci_callroom");
add_exit("down", ROOM+"poets");
add_exit("up", ROOM+"archive");
   add_exit("east",ROOM+"adv_guild");
  }

query_peace() 
{
  return 1; 
}


