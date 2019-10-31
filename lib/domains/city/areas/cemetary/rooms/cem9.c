inherit "room/room";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_light(1);
set_outdoors(1);
set_short("Northeast corner of the Cemetary");
set_long_f(
 "To the east is a tall metal fence, a gaping hole having been "+
 "blasted in it. A hole has been dug in front of the tombstone "+
 "nearest to you.",FORMAT);
items=({
  ({"fence","metal fence","tall metal fence","tall fence"}),
  "A tall fence made of metal rods. A hole has clearly been blasted in it, allowing"+
   "travel to the east.",
  ({"rods","metal rods"}),
  "They make up the fence. The gap between them is generally not more than 20cm.",
  ({"tombstone","rock","piece of rock","cracked piece of rock"}),
  "The inscription has been scraped away by time. Now it is just a "+
    "cracked piece of rock sticking out of the ground.",
  "hole",
  "There are two holes, the 'grave hole' and the 'fence hole'.",
  "grave hole",
  "A hole dug up in front of the tombstone. It is large enough to be an "+
   "obvious exit.",
  "fence hole",
  "A hole blasted into the tall metal fence. It is roughly a metre in radius, "+
   "and is big enough to be an obvious exit east.",
  });
add_exit("north",CEMETARY+ROOM+"cem12");
add_exit("south",CEMETARY+ROOM+"cem6");
add_exit("east","/domains/areas/outskirts/scav/dcE");
add_exit("west",CEMETARY+ROOM+"cem8");
add_exit("hole",CEMETARY+ROOM+"hole");
}
