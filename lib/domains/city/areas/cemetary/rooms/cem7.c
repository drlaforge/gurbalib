inherit "room/room";
#include "../area.h"

int grave_dug;
int the_grave;

reset(arg)
{
::reset(arg);
if(arg)
  return;
add_local_unique(CEMETARY+NPC+"fat_man");
set_light(1);
set_outdoors(1);
set_short("Northwest corner of the Cemetary");
items=({
  ({"fence","metal fence","tall metal fence","tall fence"}),
  "A tall fence made of metal rods.",
  ({"rods","metal rods"}),
  "They make up the fence. The gap between them is generally not more than 20cm.",
  ({"tombstone","rock","piece of rock","cracked piece of rock"}),
  "The inscription has been scraped away by time. Now it is just a "+
    "cracked piece of rock sticking out of the ground.",
  ({"gateway","small gateway"}),
  "A small gateway in the tall metal fence. A mangled sign hangs above it.",
  ({"sign","wooden sign","mangled wooden sign"}),
  "A mangled wooden sign. It looks readable.",
  });
add_exit("north",CEMETARY+ROOM+"cem10");
add_exit("south",CEMETARY+ROOM+"cem4");
add_exit("east",CEMETARY+ROOM+"cem8");
add_exit("west",CEMETARY+ROOM+"petc");
}

id(str)
{
if(::id(str))
  return 1;
if(grave_dug)
  return 
    str=="hole" || str=="large hole" || str=="fairly large hole" || 
    str=="dirt" || str=="pile of dirt" || str=="large pile of dirt" ||
    str=="pile" || str=="large pile";
}

long(str)
{
switch(str)
  {
  case 0:
    if(!grave_dug)
      writef(
      "To the west is a small gateway in the tall metal fence. "+
      "Above it is a mangled wooden sign. "+
      "In front of you is a tombstone.",FORMAT);
    else
      writef(
      "To the west is a small gateway in the tall metal fence. "+
      "Above it is a mangled wooden sign. "+
      "A fairly large hole has been dug in front of the tombstone nearest to you. "+
      "Near the hole is a large pile of dirt.",FORMAT);
    break;
  case "hole": case "large hole": case "fairly large hole":
    write("A hole has been dug in front of the tombstone nearest to you. "+
      "It should be easy to go into.\n");
    break;
  case "dirt": case "pile of dirt": case "large pile of dirt":
  case "pile": case "large pile":
    write("A large pile of dirt lying against the fence.\n");
    break;
  }
::long(str);
}

init()
{
::init();
add_action("cmd_read","read");
add_action("cmd_dig","dig");
}

cmd_read(str)
{
if(str!="sign" && str!="wooden sign" && str!="mangled wooden sign")
  return 0;
write("It reads: \"PET CEMETARY\".\n");
return 1;
}

cmd_dig(str)
{
if(str!="grave")
  return 0;
if(present("shovel",this_player()) && !grave_dug)
  {
  write("You begin digging into the grave.\n");
  say(this_player()->query_name()+" begins digging into the grave.\n");
  call_out("digging",2,0);
  return 1;
  }
return 0;
}

digging(arg)
{
if(!present(this_player(),this_object()))
  return;
if(!present("shovel",this_player()) || grave_dug)
  return;
if(arg<2)
  {
  write("You continue digging into the grave.\n");
  say(this_player()->query_name()+" continues digging into the grave.\n");
  arg++;
  call_out("digging",2,arg);
  }
else
  call_out("digging2",2);
}

digging2()
{
if(!present(this_player(),this_object()))
  return;
if(!present("shovel",this_player()) || grave_dug)
  return;
write("You finish digging and find you've dug yourself into a hole!\n");
say(this_player()->query_name()+" digs "+this_player()->query_objective()+
  "self into a hole.\n");
(CEMETARY+ROOM+"grave"+the_grave)->my_add_exit(this_object());
this_player()->move_player("hole#"+CEMETARY+ROOM+"grave"+the_grave);
add_exit("hole",CEMETARY+ROOM+"grave"+the_grave);
update_actions();
grave_dug=1;
}

query_grave(){ return the_grave; }
set_grave(x){ the_grave=x; }