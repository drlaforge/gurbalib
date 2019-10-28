inherit "std/room";
#include "../area.h"

void setup(void) 
 {
   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland";
  set_long_f(
	"This is the part of a large desolate wasteland. "+
        "A vast quantity of rubble blocks the way north, but you can "+
	"easily travel in any other direction.\n");
  dest_dir = ({
        ROOM+"waste/land_s","south",
	ROOM+"waste/land1","west",
	ROOM+"waste/land12","east",
       });
  items_arr = ({
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"building","rubble"}),"Lots of rubble. It may have been a building, once",
       });
 }
