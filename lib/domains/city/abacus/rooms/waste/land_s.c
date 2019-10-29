inherit "std/room";
#include "../area.h"

void setup(void) 
 {
   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland";
  set_long_f(
	"This is the southwestern corner of a large desolate wasteland. "+
	"There are high cliff walls running to the north and east. They give "+
	"the impression that this wasteland is actually an immense blast crater.\n");
  dest_dir = ({
	ROOM+"waste/land11","north",
	ROOM+"waste/land_s11","east",
       });
  items_arr = ({
	"corner","You are in the southwestern corner",
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"wall","walls","cliff","cliffs"}),"The cliff walls run north and east here",
	({"crater","blast crater"}),"This whole area is one large blast crater",
       });
 }
