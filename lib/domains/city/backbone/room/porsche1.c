/* [Halcyon, 2002/7] */

inherit "std/room";
#include "../area.h" 

void setup(void)
  {
    

  set_outdoors(1); 
  set_light(1); 
  short_desc = "Porsche Avenue";
   
  set_long_f(
   "Porsche Avenue extends west through a wasteland of wrecked buildings. "+
   "To the east is the intersection of Adams Street and Porsche Avenue.");
  dest_dir = ({
   ROOM+"adams_porsche","east",
   ROOM+"porsche2","west",
   });
  items_arr = ({
   ({"wasteland","buildings","wrecked buildings"}),
   "A wasteland of wrecked buildings.",
   ({"avenue","porsche avenue"}),
   "The avenue is well decayed and runs narrowly in between wrecked buildings.",
  });
}
