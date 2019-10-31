inherit "room/room";
#include "../area.h"

reset(arg)
{
   ::reset(arg);
   if(arg)
      return;
   set_light(1);
   set_outdoors(1);
   set_short("Southwest corner of the Cemetary");
   set_long_f(
      "A tall metal fence creates a perimeter for the clearing. "+
      "A fairly large hole has been dug in front of the tombstone nearest to you. "+
      "Near the hole is a large pile of dirt.",
      FORMAT);
   
   items=({
         ({"fence","metal fence","tall metal fence","tall fence"}),
         "A tall fence made of metal rods.",
         ({"rods","metal rods"}),
         "They make up the fence. The gap between them is generally not more than 20cm.",
         "clearing",
         "All across the clearing are heavily decayed tombstones.",
         ({"tombstones","decayed tombstones","heavily decayed tombstones"}),
         "Heavily decayed tombstones.",
         ({"hole","large hole","fairly large hole"}),
         "A hole has been dug in front of the tombstone nearest to you. "+
         "It should be easy to go into.",
         ({"tombstone","rock","piece of rock","cracked piece of rock"}),
         "The inscription has been scraped away by time. Now it is just a "+
         "cracked piece of rock sticking out of the ground.",
         ({"dirt","pile of dirt","large pile of dirt","pile","large pile"}),
         "A large pile of dirt lying against the fence.",
          });
   
   add_exit("north",CEMETARY+ROOM+"cem4");
   add_exit("east",CEMETARY+ROOM+"cem2");
   add_exit("hole",CEMETARY+ROOM+"small_hole");
}
