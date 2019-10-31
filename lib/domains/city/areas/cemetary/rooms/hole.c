inherit "room/room";
#include "../area.h"

#define BUGS ({"spider","worm","beetle","roly-poly"})
#define LEVEL_LIMIT 10

int last;

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_light(1);
set_outdoors(1);
set_short("A hole");
set_long_f(
 "The hole is a bit over two metres deep. At the bottom and "+
 "to the side is a small opening.",FORMAT);
items=({
  ({"opening","small opening"}),
   "It leads into a skinny tunnel. It could be entered.",
  ({"tunnel","skinny tunnel"}),
   "It's dark.",
  });
add_exit("out",CEMETARY+ROOM+"cem9");
add_exit("down",CEMETARY+ROOM+"hole1","#check");
}

init()
{
::init();
test();
}

test()
{
string type;
object the_bug;

if((time()-last)<200)
  return;
if(present("bug",this_object()))
  return;
type=BUGS[random(sizeof(BUGS))];
the_bug=clone_object(CEMETARY+NPC+"bug");
the_bug->set_name(type);
the_bug->set_short("a "+type);
the_bug->set_long_f("A small "+type+".\n",FORMAT);
the_bug->set_id("small "+type);
move_object(the_bug,this_object());
last=time();
}

check()
{
if(this_player()->query_level()>LEVEL_LIMIT && ! present("tgsash", this_player()))
 {
  write("You don't fit.\n");
  return 1;
 }
write("You squeeze yourself down the tunnel and into a cavern.\n");
return 0;
}
