inherit "std/room";
#include "../area.h"

void setup(void) 
 {
   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland";
  set_long_f(
	"This is the western edge of a large desolate wasteland. "+
	"There are high cliff walls running to the west that give "+
	"the impression that this wasteland is actually an immense blast crater.\n");
  dest_dir = ({
	ROOM+"waste/land2","north",
	ROOM+"waste/land11","east",
       });
  items_arr = ({
	"edge","You are at the western edge",
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"wall","walls","cliff","cliffs"}),"The cliff walls run north and east here",
	({"crater","blast crater"}),"This whole area is one large blast crater",
       });
 }
