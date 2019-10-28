inherit "std/room";
#include "../area.h"

object hunter,mincer;

void setup(void) {

   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland";
  set_long_f(
	"This is the southern edge of a large desolate wasteland. "+
	"There are high cliff walls to the south and some rubble to the east. "+
	"A small cave is to the north, dark and forboding.\n");
  dest_dir = ({
	ROOM+"waste/s_cave","north",
	ROOM+"waste/land_s11","west",
       });
  items_arr = ({
	"edge","You are at the southern edge of the wasteland",
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"wall","walls","cliff","cliffs"}),"The cliff walls are to the south",
	({"rubble","building"}),"The rubble looks as though it was once a building",
	"cave","The cave is small, dark, and forboding",
       });
 }
