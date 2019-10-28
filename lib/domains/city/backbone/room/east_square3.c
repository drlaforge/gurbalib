/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */
/* Kal - Updated description to more accurately depict the mud - August '03 */

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

void setup(){

   
   
  set_light(1);
  set_outdoors(1);
  set_dig(1);
  set_short("Intersection of East and Angels");
  set_long_f(
    "A major intersection in the city, despite the lack of cars.\n"+
    "East Street continues eastward over a bridge, and you see "+
    "Central Square to the west. Angels Boulevard runs to the North "+
    "and South from here.\n");
  add_item("bridge","East Street runs over a bridge to the east.");
  add_item("street","It is just a street, like any other.");
  add_item("intersection","Two streets meet here, making it an intersection.");
  add_item(({"central square","central"}),"You see the hustle and bustle of Central Square to the west.");
  add_item("river", "You cannot see the river clearly from here.");
  add_exit("south",ROOM+"s_boul1");
  add_exit("north",ROOM+"boul1");
  add_exit("west",ROOM+"east_square2");
  add_exit("east",ROOM+"bridge1");
   

}