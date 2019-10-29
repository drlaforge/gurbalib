inherit "room/room"; /* Hole with heal helmet. */
#include "../area.h"

int treasure_stolen;

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_no_clean_up(1);
set_outdoors(1);
set_light(1);
set_short("A hole");
items=({
  ({"upper body","entire upper body"}),
  "The entire upper body of the skeleton.",
  "skeleton",
  "A partial skeleton.",
  });
}

id(str)
{
if(::id(str))
  return 1;
if(str=="skull")
  return 1;
if(!treasure_stolen)
  return str=="helmet";
}

long(str)
{
switch(str)
  {
  case 0:
    if(!treasure_stolen)
      writef("The hole is about two metres deep. "+
      "The entire upper body of a skeleton is exposed. "+
      "Lying lopsided on the skull is a helmet.",FORMAT);
    else
      writef("The hole is about two metres deep. "+
        "The entire upper body of a skeleton is exposed.",FORMAT);
    break;
  case "skull":
    write("A skull.");
    if(!treasure_stolen)
      write(" Lying lopsided on it is a helmet.");
    write("\n");
    break;
  case "helmet":
    write("A helmet. It could be stolen.\n");
    break;
  }
::long(str);
}

init()
{
::init();
add_action("cmd_steal","steal");
}

cmd_steal(str)
{
object treasure;

if(str!="helmet")
  return 0;
if(treasure_stolen)
  return 0;
treasure=clone_object(CEMETARY+OBJ+"heal_helmet");
if(!transfer(treasure,this_player()))
  {
  write("You lift the "+str+" from the skull of the skeleton.\n");
  say(this_player()->query_name()+" lifts the "+str+" from the skull of the skeleton.\n");
  treasure_stolen=1;
  return 1;
  }
if(treasure)
  destruct(treasure);
write("You fail to steal the "+str+".\n");
return 1;
}

my_add_exit(room)
{
add_exit("out",source_file_name(room));
update_actions();
}
