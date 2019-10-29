inherit "room/room";
#include "../area.h"

int key_taken;
object door;

reset(arg)
{
::reset(arg);
key_taken=0;
if(arg)
  return;
door=clone_object("obj/door");
door->set_breakable(46);
door->set_id(({"door","front door"}));
door->set_long("The front door looks sturdy.\n");
door->set_id_os(({"door","south door"}));
door->set_long_os("A solid looking door.\n");
door->make_door("north",CEMETARY+ROOM+"house","cemetary_key",2,"door","","");
move_object(door,this_object());
set_light(1);
set_outdoors(1);
set_short("In front of a house in the Cemetary");
set_long_f(
 "A rugged stone path leads right up to the front porch of a dark brown "+
 "house and south through a clearing littered with heavily "+
 "decayed tombstones.",FORMAT);
items=({
  ({"path","stone path","rugged stone path"}),
   "It stretches south through a clearing littered with heavily decayed tombstones.",
  ({"porch","front porch","small porch"}),
   "A small porch about one meter squared in area. A heavily tattered "+
   "mat lies in front of the door.",
  ({"mat","tattered mat","heavily tattered mat"}),
   "It is heavily tattered and is nearly paper-thin. It looks liftable.",
  ({"house","brown house","dark brown house"}),
   "A dark brown house to the north.",
  "clearing",
   "A clearing littered with heavily decayed tombstones.",
  ({"tombstones","decayed tombstones","heavily decayed tombstones"}),
   "Heavily decayed tombstones.",
  });
add_exit("south",CEMETARY+ROOM+"cem5");
add_exit("east",CEMETARY+ROOM+"cem9");
add_exit("west",CEMETARY+ROOM+"cem7");
}

init()
{
::init();
add_action("cmd_lift","lift");
add_action("cmd_enter","enter");
}

cmd_lift(str)
{
if(str!="mat" && str!="tattered mat" && str!="heavily tattered mat")
  return 0;
if(key_taken)
  {
  say(this_player()->query_name()+" lifts the "+str+".\n");
  write("You lift the "+str+".\n");
  tell_room(environment(this_player()),
   "A cockroach scurries out from underneath the rug and into a crack in the wall.\n");
  return 1;
  }
say(this_player()->query_name()+" lifts the "+str+" and finds a key!\n");
write("You lift the "+str+" and find a key!\n");
move_object(clone_object(CEMETARY+OBJ+"cem_key"),this_object());
key_taken=1;
return 1;
}

cmd_enter(str)
{
if(str!="house" && str!="brown house" && str!="dark brown house")
  return 0;
door->move_it();
return 1;
}
