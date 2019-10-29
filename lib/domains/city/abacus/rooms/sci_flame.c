inherit "std/room";
#include "../area.h"

#include <tune.h>

object board;

void setup(void){
   
  board=clone_object("obj/SciBoard");
  board->SetShort ("Scientist FLAME board (DBBS)");
  board->SetDir("boards/FlameBoard/");
  board->SetAccessLevel(SCI_LEVEL);
  move_object(board,this_object());
  
  set_light(1);
  set_outdoors(0);
  short_desc="The room of flames";
  long_desc=
    "This is the room where angry scientists go when things aren't going\n"+
    "their way, and they want to blame it on someone. The ancient art of\n"+
    "meaningless insulting is practiced here, and all kinds of insults\n"+
    "can be placed on this board. Nothing is restricted on this board,\n"+
    "and remember: if you read something about you here, don't get angry,\n"+
    "just flame back...\n";
  dest_dir=({ROOM+"adv_inner","north"});
}

