inherit "std/room";
#include "../area.h"

void setup(void) 
 {
   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland";
  set_long_f(
	"This is the eastern edge of a large desolate wasteland. "+
	"There are high broken cliff walls to the east and what looks like "
	"an old abandoned volleyball court to the north.\n");
  dest_dir = ({
	ROOM+"waste/volleyball","north",
	ROOM+"waste/land23","west",
       });
  items_arr = ({
	"edge","You are at the eastern edge of the wasteland",
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"wall","walls","cliff","cliffs"}),"The cliff walls are broken here",
	({"court","volleyball","volleyball court"}),"It's to the north",
       });
 }
