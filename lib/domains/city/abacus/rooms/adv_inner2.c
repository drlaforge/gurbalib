inherit "std/room";
#include "../area.h"

#include <tune.h>

object ob;

reset (arg)  {
   
  ob = clone_object("obj/SciBoard");
  ob -> SetDir("/boards/LPCBoard/");
  ob -> SetShort("a LPC discussion DBBS");
  ob -> SetLong(
	  "This digital bullentin board system is here for discussing LPC.\n"+
	  "Please respect that. ");
  ob->SetAccessLevel(APP_LEVEL);
  move_object(ob, this_object());
  dest_dir = ({ROOM+"sci_plan", "north"});
  short_desc = "The LPC board";
  long_desc = 
    "This is the LPC discussion room where scientists may discuss various\n"+
    "issues involving the complexity of LPC. To make the job easier, a DBBS\n"+
    "just for this topic is on the eastern wall. Surrounding this board are\n"+
    "some diagrams and flow charts on a large table which depict how object\n"+
    "oriented programming works. A flourescent lamp above the table lights\n"+
    "up the room.\n";
  set_light(1);
  set_outdoors(0);
  items = 
    ({
      ({"flow charts","diagrams","drawings","charts"}),
        "#lpc_skill",
     "table",
	   "It is absolutely covered with different schematic drawings.",
     "lamp", "It provides the light for this room.",
    });
}

init()  {
  ::init();
    if (this_player()->query_level() < APP_LEVEL)  {
      write("You are not allowed in here. You are move_objected away.\n");
      move_object(this_player(),ROOM+"adv_guild");
      say(this_player()->query_name()+" is move_objected away.\n");
      return 1;
    }
}

lpc_skill() {
  if(this_player()->query_level() == SCI_LEVEL) {
    write("They look a little confusing and complicated.\n");
    return 1;
  }
  write("They are useless, telling you nothing you do not already know.\n"+
	"Perhaps if you ask the SourceMaster or other experienced Sci's,\n"+
	"you can get the help you seek.\n");
  return 1;
}
