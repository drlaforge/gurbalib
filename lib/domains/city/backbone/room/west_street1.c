inherit "std/room";
#include "../area.h"

object dennis;
object grinchie;
int once_a_dennis;
 
void setup(void) {
  if (dennis)
    dennis->move_player("somewhere#/room/west_street1");
  /* added by Thorwald. This is an easy quest!
   * otherwise Dennis would run far, far away.
   */

    dest_dir = ({
                  ROOM+"viaduct","west",
                  ROOM+"west_square2","east",
                  ROOM+"church","north",
               });
    short_desc = "the main road of the city.";
    set_long_f(
     "You are standing on a large road in the middle of the city. The "+
     "buildings that surround you are mostly barren and on the verge of "+
     "falling apart. You can see some tall, lonely skyscrapers to the "+
     "west. Apparently, the city has yet to recover from the devastation "+
     "of the nuclear war and start rebuilding again.\n");

    set_outdoors(1);
    set_light(1);
    add_item("road","It looks very worn.");
    add_item(({"buildings","building"}),
	   "They look abondoned and empty. You have no reason to go in them.");
    add_item("skyscrapers","You are too far to see them clearly.");
/*

  else if(!dennis) {
      dennis = clone_object("obj/monsters/dennis");
      move_object(dennis, this_object());
  }
*/

}
