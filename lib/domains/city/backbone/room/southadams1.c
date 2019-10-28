/* [Halcyon, 2002/7] */

inherit "std/room";
#include "../area.h" 

void setup(void)
  {
    

  set_outdoors(1); 
  set_light(1); 
  short_desc = "South Adams Street";
   
  set_long_f(
   "South Adams Street extends south through a wasteland of wrecked buildings. "+
   "To the north is the intersection of West and Adams.");
  dest_dir = ({
   ROOM+"west_street4","north",
   ROOM+"southadams2","south",
   });
  items_arr = ({
   ({"wasteland","buildings","wrecked buildings"}),
   "A wasteland of wrecked buildings.",
   ({"street","adams street","south adams street"}),
   "The street is well decayed and runs narrowly in between wrecked buildings.", 
  });
}
