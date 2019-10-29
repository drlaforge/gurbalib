inherit "std/room";
#include "../area.h"

void setup(void) 
 {
   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland";
  set_long_f(
	"This is part of a large desolate wasteland. There is a huge pile "+
	"of rubble to the north. There is no way through it.\n");
  dest_dir = ({
	ROOM+"waste/land21","west",
	ROOM+"waste/land23","east",
	ROOM+"waste/land12","south",
       });
  items_arr = ({
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"building","rubble"}),"Lots of rubble. It may have been a building, once",
       });
 }
