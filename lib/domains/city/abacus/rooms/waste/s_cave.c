inherit "std/room";
#include "../area.h"

object wolf;

void setup(void) 
 {
  
  if(!wolf) {
    wolf = clone_object("/std/monster");
    move_object(wolf,this_object());
    wolf->set_name("Wolf");
    wolf->set_alias("wolf");
    wolf->set_short("a wolf");
    wolf->set_long_f("It's a fierce looking wolf. "+
	  "It probably lived here and became the hunter's pet.\n");
    wolf->set_level(8);
    wolf->set_aggressive(1);
  }

   
   
  set_light(0);
  set_outdoors(0);
  short_desc = "a small cave";
  set_long_f("A dark and damp cave. The floor is covered with damp soil. "+
	"The place is very filthy.\n");
  dest_dir = ({
	ROOM+"waste/land_s12","south",
       });
  items_arr = ({
	"cave","You are in the cave right now",
	"floor","The floor is covered with damp soil",
	({"soil","damp soil"}),"The soil is soaked with wolf urine...",
	({"urine","wold urine"}),"What exactly would you expect?",
       });
 }
