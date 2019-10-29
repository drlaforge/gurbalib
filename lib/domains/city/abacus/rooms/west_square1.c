/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"

void setup(void) {
    /*set_outdoors(1); */
    set_light(1);
    set_short("west of the Central Square.");    
    set_long( 
     "You stand on the western side of Central Square. The main street "+
     "starts here and heads to the west, and you can see an alley "+
     "going northwards between some deserted buildings. There is a "+
     "glowing pub sign, part way up the alley. There is a sense "+
     "of desolation here as a lot of the buildings look as though they "+
     "have been empty for many years. The only one which is still in use "+
     "is the famous post office to the south.\n");
 
    set_exits(([
                  "west" : ROOMS+"west_square2",
                  "east" : ROOMS+"central_square",
                  "north" : ROOMS+"yard",
                 "south" : ROOMS+"test",
               ]));
   add_item("sign","pub sign","glowing pub sign","glowing sign","You can't make it out from here, but it is definitely a pub sign.");
      add_item("alley","It starts off brightly enough, but the buildings cast such a big\n"+
       "shadow that you can barely see the end, it is so dark.");
      add_item("post office","post","This is one of the few buildings around which is still used. You\n"+
       "can go inside and mail to other players inside.");
      add_item("square","Square","central square","It looks like it could accomodate a lot of people and must have\n"+
       "been a bustling place in the past. Alas, those days are gone.");
      add_item("main street","street","The main street starts here and looks to be in better shape than it\n"+
       "is further to the west.");
      add_item("buildings","building","deserted buildings","They surround the square, but most of them are deserted.");  
}
	

