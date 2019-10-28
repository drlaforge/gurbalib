inherit "std/room";
#include "../area.h"

void setup(void) {
    
   if(arg)
      return;
   
   set_outdoors(1);
   set_light(1);
   short_desc = "a dark alley, southern part";
   long_desc =
   "This is the southern part of the dark alley.\n"+
   "This is one of those places one should stay away from at night.\n"+
   "From the buildings you see some lurking shadows following you.\n";
   dest_dir =
   ({ROOM+"south_alley5","south",
         ROOM+"south_alley3","north",
    });
   items =
   ({"buildings","The buildings rise high above the ground,\nand prevents the sun from letting the light in",
         "shadows","The shadows have strange forms. You wonder what it could be"
    });
}
