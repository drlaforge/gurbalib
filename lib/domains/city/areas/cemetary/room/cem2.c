inherit "room/room";
#include "../area.h"

#define MAX_PIGEONS 6

reset(arg)
{
   ::reset(arg);
   if(arg) return;
   add_object("/obj/obj/WAmachine");
add_local_unique(CEMETARY+NPC+"butterfly");
add_local_unique(CEMETARY+NPC+"pigeon",MAX_PIGEONS);
   set_light(2);
   set_outdoors(1);
set_short("Entrance to the Cemetary, on a path");
   set_long_f(
      "Just south are the front gates for the cemetary. "+
      "A rugged stone path leads north towards an ominous house. "+
      "Sprawled around this clearing are heavily decayed tombstones.",FORMAT);
   items=({
         ({"gates","front gates"}),
         "They are bent, mangled, and gaping open.",
         ({"path","stone path","rugged stone path"}),
         "It stretches through the cemetary to the house as well as "+
         "south through the front gates.",
         ({"house","ominous house"}),
         "An ominous house at the end of the cemetary.",
         ({"tombstones","decayed tombstones","heavily decayed tombstones"}),
         "Heavily decayed tombstones.",
          });
   add_exit("south", CEMETARY+ROOM+"ent");
   add_exit("north",CEMETARY+ROOM+"cem5");
   add_exit("west",CEMETARY+ROOM+"cem1");
   add_exit("east",CEMETARY+ROOM+"cem3");
}

