/* [Halcyon, 2002/7] */

inherit "std/room";
#include "../area.h" 

void setup(void)
  {
    

  set_outdoors(1); 
  set_light(1); 
  short_desc = "South Adams Street";
   
  set_long_f(
   "South Adams Street extends through a wasteland of wrecked buildings.");
  dest_dir = ({
   ROOM+"southadams1","north",
   ROOM+"southadams3","south",
   });
  items_arr = ({
   ({"wasteland","buildings","wrecked buildings"}),
   "A wasteland of wrecked buildings.",
   ({"street","adams street","south adams street"}),
   "The street is well decayed and runs narrowly in between wrecked buildings.", 
  });
}
