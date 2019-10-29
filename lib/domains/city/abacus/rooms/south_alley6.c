inherit "std/room";
#include "../area.h"

void setup(void){
   
   set_outdoors(1);
   set_light(1);
   set_short("a dark alley, southern part");
   set_long_f("This is the southern part of the dark alley. "+
      "This is one of those places one should stay away from at night. "+
      "From the buildings you see some lurking shadows following you. "+
      "To the west is a hut made out of scrap metal.\n");
   dest_dir=({
      ROOM+"south_alley7","south",
      ROOM+"south_alley5","north",
      ROOM+"metalhut","west",
      });
   items =({
      "buildings","The buildings rise high above the ground,\nand prevents the sun from letting the light in",
      "shadows","The shadows have strange forms. You wonder what it could be",
      "hut","It's a hut made from bits of scrap metal, it's entrance is to the west.",
   });
}
