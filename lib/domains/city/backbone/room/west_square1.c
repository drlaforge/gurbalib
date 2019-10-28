/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h"

void setup(void) {
    set_outdoors(1);
    set_light(1);
    short_desc = "west of the Central Square.";
    
    set_long_f( 
     "You stand on the western side of Central Square. The main street "+
     "starts here and heads to the west, and you can see an alley "+
     "going northwards between some deserted buildings. There is a "+
     "glowing pub sign, part way up the alley. There is a sense "+
     "of desolation here as a lot of the buildings look as though they "+
     "have been empty for many years. The only one which is still in use "+
     "is the famous post office to the south.\n");
 
    dest_dir = ({
                  ROOM+"west_square2","west",0,
                  ROOM+"central_square","east",0,
                  ROOM+"yard","north",0,
                  ROOM+"test","south","#test_npc",
               });
   items_arr = ({
      ({"sign","pub sign","glowing pub sign","glowing sign"}),
      "You can't make it out from here, but it is definitly a pub sign.",
      "alley", 
       "It starts off brightly enough, but the buildings cast such a big\n"+
       "shadow that you can barely see the end, it is so dark.",
      ({"post office", "post" }), 
       "This is one of the few buildings around which is still used. You\n"+
       "can go inside and mail to other players inside.",
      ({"square","Square","central square"}),
       "It looks like it could accomodate a lot of people and must have\n"+
       "been a bustling place in the past. Alas, those days are gone.",
      ({"main street","street"}), 
       "The main street starts here and looks to be in better shape than it\n"+
       "is further to the west.",
      ({"buildings","building","deserted buildings"}),
       "They surround the square, but most of them are deserted."
    });  

}
	
int test_npc() {
  if (this_player() && this_player()->query_npc())
    return 1;
  return 0;
}

