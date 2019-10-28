/* Wishbone 12/96 */

#include <def.h>
#include <tune.h>
inherit "std/room";
#include "../area.h"

#include <tune.h>

init () {
  ::init();
  add_action ("mic","mic");
  add_action ("mic","microphone");
  add_action ("mic","phone");
}

object ob;
void setup(void) {
   
  
/*
 ob = clone_object("obj/board");
ob->set_name("doc_board");
ob->set_alias("board");
ob->set_short("Document Planning Board");
ob->set_long("Here is were you can request/discuss the documentation ('help' files) on the MUD.\n");
ob->set_save_path("boards/doc");
ob->set_delete_level(ROOKIE_LEVEL);
ob->set_max_notes(50);
move_object(ob, this_object());
*/
  set_outdoors(0);
  set_light(1);
  short_desc = "The Scientist calling room.";

  set_long_f(  
    "You stand in a small room. There is a single window on the west wall. "+
    "Other than a dusty microphone hanging down from the ceiling in "+
    "the center of the room, there is nothing of noticable interest. It is "+
    "obvious from the thick layer of dust on the floor that hardly anyone "+
    "ever comes in here.\n");
add_exit("east", ROOM+"school_entr");
add_exit("south", ROOM+"announce");
  add_item("microphone",
     "It still seems operational, but you do not see any speakers in here.\n"+
     "This microphone may be connected to the scientists message system, so\n"+
     "if you have an URGENT message, you can 'mic <message>'");
  add_item("window",
     "It looks like it has been jammed shut for a long time.");
  add_item(({"layer","layer of dust","dust"}),
    "There are some footprints on the dust, as if someone was here recently.");
  add_item("footprints",
     "With a closer look, these footprints are older than you thought.");
  add_item(({"wall","west wall"}),"It has a window.");
}

mic (str) {
  object ob;
  int i;
  string myname;
  ob=users();
  myname = capitalize(this_player()->query_real_name());
  while (i < sizeof (ob)) {
    if (ob[i]->query_level() >= SCI_LEVEL && ob[i]->listen_level()<=this_player()->query_level()) {
      tell_object (ob[i],"You hear "+myname+" on the microphone: -"+str+"-\n");
    }
    i++;
  }
  write ("Your message was sent.\n");
  return 1;
}
