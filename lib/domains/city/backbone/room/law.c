inherit "std/room";
#include "../area.h"

#include <tune.h>

object board;

void setup(void)
{
  if(arg)  return;
    board = clone_object("/obj/SciBoard");
    board -> SetShort("the Law board");
    board -> SetDir("/boards/Law/");
    board -> SetLong("The Law board with all the latest rulings.\n");
    board -> SetAccessLevel(ARCH_LEVEL);
    move_object(board, this_object());
      
  set_outdoors(0);
  no_clean_up = 0;
  set_light(1);
  set_short("The Law Room.");
  set_long_f("You have entered the Law Room. This is where you will "+
             "find an update on what's happend law-wise in town. This is also where "+
             "you can find out when, why, for how long, someone got demoted. "+
	     " ");

add_exit("up", ROOM+"announce");
add_exit("east", ROOM+"adv_cellar");
  }

query_peace() 
{
  return 1; 
}


