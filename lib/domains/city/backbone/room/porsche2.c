/* [Halcyon, 2002/7] */

inherit "std/room";
#include "../area.h" 

void setup(void)
  {
    

  set_outdoors(1); 
  set_light(1); 
  short_desc = "Porsche Avenue";
   
  set_long_f(
   "Porsche Avenue extends east through a wasteland of wrecked buildings. "+
   "At this end of the avenue, however, the buildings have been renovated "+
   "and well maintained, showing few signs of the devestation that lies to the east. ");
  dest_dir = ({
   ROOM+"porsche1","east"
   });
  items_arr = ({
   ({"wasteland","buildings","wrecked buildings"}),
   "A wasteland of wrecked buildings.",
   ({"mountain","huge mountain","rubble","mountain of rubble",
   "huge mountain of rubble","building","fallen building"}),
   "A huge mountain of rubble from a fallen building.",
   ({"avenue","porsche avenue"}),
   "The avenue is well decayed and runs narrowly in between wrecked buildings.",
  });
}
