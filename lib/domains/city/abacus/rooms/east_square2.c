/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */
/* Kal - Updated description to more accurately depict the mud - August '03 */

inherit "std/room";
#include "../area.h"

void setup(){
  set_light(1);
  /*set_outdoors(1); */
  /*set_dig(1); */
  set_short("East Street");
  set_long("This is East Street.\n"+
    "The street continues eastwards, and you can see Central Square to the "+
    "west. Plain looking buildings tower above you on the sides of the street.\n");
  add_item("bridge","You cannot see the bridge clearly from here");
  add_item("street","It is just a street, like any other.");
  add_item("buildings","The buildings look very plain, especially with thier ruined facades.");
   add_item("central square","central","You see the hustle and bustle of Central Square to the west.");
  set_exits((["west" : ROOMS+"east_square1",
  "east" : ROOMS+"east_square3"]));
}

