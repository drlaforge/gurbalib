inherit "std/room";
#include "../area.h"

void setup(void) 
 {
   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland";
  set_long_f(
	"This is the southern edge of a large desolate wasteland. "+
	"There are high cliff walls blocking the way south and a vast "+
	"quantity of rubble to the northwest.\n");
  dest_dir = ({
	ROOM+"waste/land22","west",
        ROOM+"convoy/wasteland","east",
	ROOM+"waste/land33","north",
       });
  items_arr = ({
	"edge","You are at the southern edge of the wasteland",
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"wall","walls","cliff","cliffs"}),"The cliff walls run west and east here",
	({"building","rubble"}),"Lots of rubble. It may have been a building, once",
       });
 }
