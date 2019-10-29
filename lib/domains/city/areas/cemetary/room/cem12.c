inherit "room/room";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
add_local_unique(CEMETARY+NPC+"rabbit",2);
set_light(1);
set_outdoors(1);
set_short("A beaten path");
set_long_f(
 "The grass is beaten down to form a path leading "+
 "south along the eastern side of a house. East is a shed.",FORMAT);
items=({
  ({"grass","long grass"}),
   "Long grass.",
  "path",
   "A path created by grass being beaten down. It runs north and south "+
   "along the eastern side of a house.",
  ({"house","side of a house","eastern side of a house"}),
   "The eastern side of a house.",
  ({"shed","beaten-down shed"}),
   "A beaten-down shed with an empty doorway.",
  ({"doorway","empty doorway"}),
   "Big enough to be an obvious exit east."
  });
add_exit("south",CEMETARY+ROOM+"cem9");
add_exit("east",CEMETARY+ROOM+"toolshed");
}