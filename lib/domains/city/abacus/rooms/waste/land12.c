inherit "std/room";
#include "../area.h"

object lizard;

void setup(void) {

  if(!lizard) {
    lizard = clone_object("/std/monster");
    move_object(lizard,this_object());
    lizard->set_name("Lizard");
    lizard->set_alias("lizard");
    lizard->set_short("a desert lizard");
    lizard->set_long_f("It's a rather huge lizard living in the boulders. "+
	     "Its skin is very thick and its fangs are fairly sharp.\n");
    lizard->set_level(18);
    lizard->set_aggressive(1);
  }

   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland";
  set_long_f(
	"This is the eastern edge of a large desolate wasteland. "+
	"There are high cliff walls to the east and some rubble to the south.\n");
  dest_dir = ({
	ROOM+"waste/land22","north",
	ROOM+"waste/land11","west",
       });
  items_arr = ({
	"edge","You are at the southern edge of the wasteland",
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"wall","walls","cliff","cliffs"}),"The cliff walls are to the south",
	({"rubble","building"}),"The rubble looks as though it was once a building",
       });
 }
