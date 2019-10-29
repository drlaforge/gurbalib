inherit "std/room";
#include "../area.h"

object outob;
string grafitti;

init ()
{
  ::init();
  add_action ("mout","out");
  add_action ("mout","leave");
  add_action ("mout","exit");
  add_action ("sit","sit");
  add_action ("scribble","scribble");
}

void setup(void) 
{
   
   
  set_outdoors(0);
  set_light(1);
  short_desc = "In a subway train.";
  no_clean_up=1;
  long_desc = 
    "This subway train is one of the few which have been salvaged from the\n"+
    "riots and destruction following the last great world war. Although it\n"+
    "is operational, most of the seats are still broken and the walls are\n"+
    "covered with grafitti. There is a worn schedule hanging on the wall.\n";
  dest_dir = 
    ({
      "dummy","out",
    });
  items =
    ({
      ({"walls","wall"}),
        "The walls have not been maintained, and it is so grimy, you feel\n"+
	"sick after looking at them.",
      "grafitti",
      "#graff",
      "seats",
        "Most of the seats look at if someone had smashed them with a bat,\n"+
        "and the ones which have not been destroyed seem about to fall apart",
      "schedule","#schedule",
    });
}

graff() 
{
  if (!grafitti)
    grafitti = ({
      "Life's a bitch, and then you marry one.",
      "It's better to burn out then fade away!",
      "Kilroy wasn't here - yet.",
      "Harry is dead meat.",
      "Cigarettes will kill you, so will I.",
      "Your killer instinct must be pure and clean, or else you will not kill.",
      "In this world that you have entered, things are rarely as they seem.",
      "Tired of hangover? - visit Willie in the city park.",
      "Killing is our business - business is good.",
      "Hitech - lowlife.",
      "There's no place like away.",
    });
  write ("There is a lot of grafitti here.. you read one:\n");
  write ("\""+grafitti[random (sizeof(grafitti))]+"\"\n");
  
}
scribble (s) 
{
  if (!grafitti) graff();
  grafitti += s;
  write ("You scribble some grafitti on the wall.\n");
  say (this_player()->query_name()+" scribbles some grafitti on the wall.\n");
  return 1;
}

schedule () 
{
  ROOM+"train_room"->stations();
  return 1;
}

set_out(obb) 
{
  outob=obb; 
}

mout ()
{
  if (!outob->query_dest()) 
  {
    write ("The doors are closed and the train is still moving.\n");
    return 1;
  }
  
  this_player()->move_player("the train#"+outob->query_dest());
  return 1;
}

sit(str) 
{
  if(!str) 
  {
    write("Sit on what? The floor?\n");
    return 1;
  }
  if((str == "on seats" || str == "on seat" || str == "on a seat")) 
  {
    write("After looking at the condition of the seats, you decide not to.\n");
    return 1;
  }
  return 0;
}
