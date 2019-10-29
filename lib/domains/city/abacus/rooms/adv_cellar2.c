
inherit "std/room";
#include "../area.h"

void setup(void) {
  object ob;
   
    
  ob=clone_object("obj/board");
  ob->set_max_notes(100);
  ob->set_save_path("boards/flame_board");
  ob->set_short("the FLAME board");
  move_object(ob,this_object());

    set_outdoors(0);
    set_light(1);
    short_desc = "the 'flame' room";
    
    long_desc = 
        "This room is for players who wish to let off some steam, or to\n"+
        "put it simply, bitch! The flame board is here so you can insult\n"+
        "whoever or whatever you like. Remember, don't get mad get even!\n";
    dest_dir = ({
        ROOM+"vote", "up",
        ROOM+"adv_cellar", "west",
        });
    items_arr = ({
          });
}
query_peace()
{
return 1;
}
