/* [Halcyon, 2002/7] */

inherit "std/room";
#include "../area.h" 

void setup(void)
  {
    

  set_outdoors(1); 
  set_light(1); 
  short_desc = "Intersection of S. Adams and Porsche";
   
  set_long_f(
   "The intersection of South Adams Street and Porsche Avenue. "+
   "Porsche extends west through a wasteland of wrecked buildings, "+
   "while Adams continues north and south.");
  dest_dir = ({
   ROOM+"southadams3","north",
   ROOM+"southadams5","south",
   ROOM+"porsche1","west",
   });
  items_arr = ({
   ({"wasteland","buildings","wrecked buildings"}),
   "A wasteland of wrecked buildings.",
   ({"street","adams street","south adams street"}),
   "The street is well decayed and runs narrowly in between wrecked buildings.",
   ({"avenue","porsche avenue"}),
   "The avenue is well decayed and runs narrowly in between wrecked buildings.",
  });
}
