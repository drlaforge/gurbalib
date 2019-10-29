inherit "room/room"; /* Hole with machete. */
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
  ({"bones","white bones","crusty white bones","old crusty white bones"}),
  "Old crusty white bones.",
  ({"shoulder","right shoulder","shoulder of a skeleton","right shoulder of a skeleton"}),
  "The bones that make up a shoulder.",
  "skeleton",
  "A partial skeleton.",
  });
}

id(str)
{
if(::id(str))
  return 1;
if(str=="arm")
  return 1;
if(!treasure_stolen)
  return str=="machete" ||
    str=="rusty machete";
}

long(str)
{
switch(str)
  {
  case 0:
    if(!treasure_stolen)
      writef("The hole is nearly two metres deep. "+
        "The right shoulder of a skeleton is exposed. "+
        "The arm protrudes upwards from the shoulder, "+
        "tightly gripping a rusty machete.",FORMAT);
    else
      writef("The hole is nearly two metres deep. "+
        "The right shoulder of a skeleton is exposed, "+
        "the arm protruding upwards from the shoulder.",FORMAT);
    break;
  case "arm":
    write("The bones that make up an arm.");
    if(!treasure_stolen)
      write(" It tightly grips a rusty machete.");
    write("\n");
    break;
  case "machete": case "rusty machete":
    write("A rusty machete. It could be stolen.\n");
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
if(str!="machete" && str!= "rusty machete")
  return 0;
if(treasure_stolen)
  return 0;
treasure=clone_object(CEMETARY+OBJ+"machete");
if(!transfer(treasure,this_player()))
  {
  write("You pry the "+str+" free from the grip of the skeleton.\n");
  say(this_player()->query_name()+" prys the "+str+" free from the grip of the skeleton.\n");
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
