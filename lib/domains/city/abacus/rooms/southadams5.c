/* [Halcyon, 2002/7] */

inherit "std/room";
#include "../area.h" 

void setup(void){
    
     
   add_object("/domains/freekill/npc/baddaz",1);
  set_outdoors(1); 
  set_light(1); 
  short_desc = "South Adams Street";
   
  set_long_f(
   "South Adams Street extends north through a wasteland of wrecked buildings. "+
   "To the south, a huge mountain of rubble from a fallen building prevents "+
   "passage. "+
   "To the north is the intersection of Adams Street and Porsche Avenue.");
  dest_dir = ({
   ROOM+"adams_porsche","north"
   });
  items_arr = ({
   ({"wasteland","buildings","wrecked buildings"}),
   "A wasteland of wrecked buildings.",
   ({"mountain","huge mountain","rubble","mountain of rubble",
     "huge mountain of rubble","building","fallen building"}),
   "A huge mountain of rubble from a fallen building.",
   ({"street","adams street","south adams street"}),
   "The street is well decayed and runs narrowly in between wrecked buildings.", 
  });
}
