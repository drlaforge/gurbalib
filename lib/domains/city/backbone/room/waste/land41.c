inherit "std/room";
#include "../area.h"

void setup(void) 
 {
   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland";
  set_long_f(
	"This is the northern edge of a large desolate wasteland. "+
	"There are high broken cliff walls to the north and a vast "+
	"quantity of rubble to the southeast.\n");
  dest_dir = ({
	ROOM+"waste/land31","south",
	ROOM+"waste/land42","east",
       });
  items_arr = ({
	"edge","You are at the northern edge of the wasteland",
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"wall","walls","cliff","cliffs"}),"The cliff walls are broken here",
	({"building","rubble"}),"Lots of rubble. It may have been a building, once",
       });
 }
