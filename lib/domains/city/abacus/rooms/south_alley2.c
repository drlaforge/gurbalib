inherit "std/room";
#include "../area.h"

void setup(void) {
   

  set_outdoors(1);
  set_light(1);
  short_desc = "a dark and gloomy alley";
  long_desc =
    "You're walking in a dark and dirty narrow alley.\n"+
    "You don't feel very comfortable in these neighbourhoods.\n"+
    "The alley is getting even darker and more scary to the south.\n"+
    "You see a sign: 'GAS STATION -> EAST'.\n";
  dest_dir =
    ({ROOM+"south_alley3","south",
      ROOM+"south_alley1","north",
/* - This area removed, Wishbone Apr04 
      "players/ledough/building/lobby","west",
*/
      ROOM+"gas","east",
      });
}

init() {
  ::init();
    add_action("look","look");
    add_action("exa","exa",1);
}
look(str) {
  if(str=="at sign") {
    write("The sign reads: GAS STATION EAST.\n");
    return 1;
  }
}
exa(str) {
  if(str == "sign")
    return look("at " + str);
}
