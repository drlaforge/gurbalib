inherit "std/room";
#include "../area.h"

void setup(void) 
 {
   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland";
  set_long_f(
	"This is part of a large desolate wasteland. There is a huge pile "+
        "of rubble to the northeast. You can travel around it easily. "+
        "A smaller pile of rubble blocks the way south.\n");
  dest_dir = ({
	ROOM+"waste/land2","west",
	ROOM+"waste/land22","east",
	ROOM+"waste/land31","north",
       });
  items_arr = ({
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"wall","walls","cliff","cliffs"}),"The cliff walls run north and east here",
	({"building","rubble"}),"Lots of rubble. It may have been a building, once",
       });
 }
