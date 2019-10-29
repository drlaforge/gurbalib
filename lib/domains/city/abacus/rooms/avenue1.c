/* Darkman - Room Converted from data file - Sun Jun 23 22:51:18 2002 */

inherit "std/room";
#include "../area.h"

void setup(){
  set_light(1);
  /*set_outdoors(1); */
  /*set_dig(1); */
  set_short("Car Park");
  set_long("Around you lie the ruined relics of a bygone era, namely\n"+
    "many hulks of cars. Your nose wrinkles up in distaste at\n"+
    "the squallid remains, as you wonder which is the nearest\n"+
    "exit from the car park. Looking east you see the car park\n"+
    "continues, so maybe the avenue to the west is a better idea.\n");
  add_item("relics", "ruined relics", "hulks", "cars", "ruined cars", "hulks of cars", "remains", "squallid remains","Ruined cars");
  add_item("park","car park","A car park");
  add_item("avenue", "Hey, looks cool down there. Why not go see");
  set_exits((["east" : ROOMS+"7th_westpark",
  "west" : ROOMS+"avenue2"]));
}

