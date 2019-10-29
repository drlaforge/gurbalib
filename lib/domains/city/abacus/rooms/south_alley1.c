inherit "std/room";
#include "../area.h"

void setup(void) {
   

  set_outdoors(1);
  set_light(1);
  
  short_desc = "a dark and gloomy alley";
  long_desc =
    "You're walking in a narrow dark alley.\n"+
    "All around you are decadent sky scrapers rising to the sky.\n"+
    "Under your feet you can hear the creatures living in the sewers.\n";
  dest_dir =
    ({ROOM+"south_alley2","south",
      ROOM+"west_square2","north",
      });
  items = 
    ({"scrapers","They used to be prominent buildings before the war\nBut now they're just shattered ruins rising to the sky"
      });
}
