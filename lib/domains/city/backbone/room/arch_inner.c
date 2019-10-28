#include <tune.h>
#include <def.h>
/* Added the invasion stuff - Wishbone 13May06 */

#define INVASION "domains/Areas/outskirts/muncher/invasion/"

inherit "std/room";
#include "../area.h"
#include <tune.h>

init()
{
  ::init();
    if (this_player()->query_level() >= RET_LEVEL )
    add_action("push_it","push");
      return;
    write("You aren't supposed to be here!!\n"+
	  "You are move_objected away.\n");
    say(this_player()->query_name() + " isn't allowed to be here and is move_objected away.\n");
    move_object(this_player(),ROOM+"adv_inner");
    say(this_player()->query_name() + " arrives.\n");
    return 1;
  }

void setup(void)
{
  object ob;

   
  
  ob = move_object(clone_object("obj/SciBoard"),this_object());
  ob->SetDir("/players/arch/board/");
  ob->SetShort("the arch discussion board");
  ob->SetAccessLevel(RET_LEVEL);
  
  set_light(1);
  set_outdoors(0);
  set_short("Main office of the Administration");
  set_long_f("You are in the room where the great arch "+
	   "scientists can discuss the lousy scientists. Three buttons are on "+
	   "the wall, next to a small note.\n");

  add_exit("west", ROOM+"adv_inner");
  
  items_arr = ({
	({"button","buttons"}),
	"Buttons to clone the Invasion control computer. Make sure you examine the note first. Syntax: 'push invasion', 'push easter', or 'push xmas'",
	({"small note","note"}),"#note",
	});

}

note()
{
 write("\nInvasion event:\n\n");
 writef("This is only suppose to run once every few reboots and never more "+
	"than once a reboot. The way it works is that you press the button "+
	"to clone the correct computer.");
 write("\n");
 writef("Once cloned you can start the invasion. When you start the invasion, "+
	"a few warning shouts go out over the mud. Then the troops parachute "+
	"into the city and start wacking ANY players that have weapon class over 0.");
 write("\n");
 return 1;
}

push_it(string str)
{
 if(present("computer",this_object())) 
  {
   writef("There is already a computer here!\n");
   return 1;
  }
 if(str=="invasion") 
  {
   move_object(clone_object(INVASION+"orig/computer"),this_object());
   writef("The original invasion computer is cloned.\n");
   return 1;
  }
 if(str=="easter")
  {
   move_object(clone_object(INVASION+"easter/computer"),this_object());
   writef("The Easter invasion computer is cloned.\n");
   return 1;
  }
 if(str=="xmas")
  {
   move_object(clone_object(INVASION+"xmas/computer"),this_object());
   writef("The Xmas invasion computer is cloned.\n"); 
   return 1;
  }
 writef("Push what..?\n");
 return 1;
}
