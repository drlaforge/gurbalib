#include <tune.h>
#include <def.h>
inherit "std/room";
#include "../area.h"
#include <tune.h>

object board;

reset (arg) {
   
  board = clone_object("obj/SciBoard");
  board -> SetShort ("the apprentice/scientist discussion board");
  board -> SetDir("/boards/SciBoard/");
  board -> SetLong("This is the bulletin board where scientists discuss\n"+
		   "most things, concerning the mud.\n");
  board->SetAccessLevel(APP_LEVEL);
  move_object(board, this_object());

  set_light (1);
  dest_dir=([
	     "north": ({ROOM+"adv_guild",0}),
	     "up":    ({ROOM+"sci_plan",0}),
	     "south": ({ROOM+"sci_flame", 0}),
	    "east":  ({ROOM+"arch_inner",0}),
	   ]);
  short_desc="The inner room of adventurers guild";
   set_long_f(
    "This is the SPOK-members room. Only scientists can enter here. The "+
    ROOM+" to the south is for flaming other scis. The Board room is to the "+
    "east, but only levels "+ARCH_LEVEL+" and higher have access to there. "+
    "A spiral staircase leads up to the second floor, where you can get "+
    "information about who is designing what area and about the concerns "+
    "of the Quality Control and Balance board members. A small and very "+
    "dirty staircase leads down into an elevator.\n");

/* an elevator to leo is here! */
ROOM+"leo_elev"->reset();
}

init() {
  ::init();
  if (this_player()->query_level() < APP_LEVEL) {
    write("You aren't allowed to be here. You are move_objected away\n");
    say(this_player()->query_name()+" is move_objected away.\n");
    move_object(this_player(),ROOM+"adv_guild");
    return 1;
  }
  add_action("east","east");
}


east() {
string myname;
if (this_player()->query_npc() || this_player()->query_level() < RET_LEVEL) {
  myname = this_player()->query_name();
  write("A bright flash hits your head and a far away voice says:\n"+
	"- When did you become an archscientist ?  HA HA HA ha ha ...\n");
  say("Suddenly a bright flash hits "+myname+" as "+
      this_player()->query_pronoun()+" tried\n"+
      "to enter the archscientists room.\n");
  tell_room(ROOM+"arch_inner",myname+" tried to enter.\n");
  return 1;
}	
this_player()->move_player("east#room/arch_inner");
return 1;
}
