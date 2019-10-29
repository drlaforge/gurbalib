/* By all means, feel free to put quest items and what not into this room. 
   I can't think of a damn thing worth coding to put in here. */

inherit "room/room";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_outdoors(0);
set_light(0);
set_short("A shed");
set_long_f(
  "All around the walls of this shed are wooden shelves, broken and "+
  "tattered. The place is pretty ransacked. The doorway west is empty, "+
  "its edges well maimed.",FORMAT);
add_exit("west",CEMETARY+ROOM+"cem12");
items=({
  "walls",
   "Walls.",
  ({"shelves","wooden shelves"}),
   "Wooden shelves, broken and tattered.",
  "wood",
   "Wood.",
  ({"doorway","empty doorway"}),
   "An empty doorway.",
  "edges",
   "Jutting subtly from the right edge of the doorway is a fragment of wood, "+
   "attached to a lock at waist level. The entire left edge is splintered and broken.",
  ({"fragment","fragment of wood"}),
   "A fragment of wood hanging from a lock.",
  "lock",
   "A lock holding a fragment of wood to the doorway.",
  });
}
