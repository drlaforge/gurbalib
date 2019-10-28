#include <def.h>
#include <tune.h>

inherit "std/room";
#include "../area.h"

#include <tune.h>
object board;

void setup(void){
    
    
   
   board = clone_object("obj/archiveboard");
   board -> set_show_level(ROOKIE_LEVEL);
   board -> set_arch_path("boards/archive");
   move_object(board, this_object());
   set_outdoors(0);
   set_light(1);
   set_short("The Archive Room.");
   set_long_f("A single board stands in the center of this room. By the looks of it "+
      "it doesn't look like most the other boards. This is where the archives of the main "+
      "board are kept. If you need to load an archive, looking at the board may help.\n");
   add_exit("east", ROOM+"jokesboard");
   add_exit("down", ROOM+"announce");
   
}

query_peace(){ return 1; }

