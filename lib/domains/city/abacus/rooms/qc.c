inherit "std/room";
#include "../area.h"
#include <tune.h>
object board;

void setup(void){
   
  board=clone_object("/obj/SciBoard");
  board->SetShort("The Quality Control and Area Maintenance DBBS");
  board->SetDir("boards/QCBoard");
  board->SetAccessLevel(APP_LEVEL);
  move_object(board,this_object());
  set_light(1);
  set_outdoors(0);
  set_short("The Quality Control Rewm");
  set_long(
"You stand in a cold, bare rewm devid of any decoration.\n"+
"A smal window in the north wall casts lite on your gloomysurroundings,\n"+
"and it noticeable that the floor\n"+
"is karpetless. A layer thick of dust covers\n"+
"the hard wooden floorbords, and it is obvious that whoever\n"+
"works in this room doesnt have time to clean it. you\n"+
"feel sorry for the unfortunate QC archis and wander if you're area\n"+
"is good enuf to be\n"+
"included on the mud. It would be a shame to waste the time of these poor ov\n");
		/* Ok ok, so I got bored... Wishbone */

  add_exit("west",ROOM+"sci_plan");
  
  add_item(({"cold room","bare room","environment","surroundings","gloomy surroundings"}),
	   "A cold, bleak room. A DBBS is all that occupies the empty space");
  add_item(({"window","small window"}),
	   "A small window which allows light to seep into the room during the day.\n"+
	   "This adds a touch of warmth to what is otherwise a dull environment.\n"+
	   "Peering more closely you realise that this window overlooks the whole mud");
  add_item(({"mud","whole mud"}),
	   "Wow, there are a lot of bugs out there!");
  add_item(({"wall","north wall",}),
	   "The wall is plain, with the exception of a small window");
  add_item(({"walls","plain walls","stark walls"}),
	   "Plain, stark walls");
  add_item("light","What do you expect light to look like?");
  add_item(({"floor","hard wooden floorboards","floorboards","wooden floorboards","hard floorboards"}),
	   "The floor is made from wooden floorboards, which are barely visible\n"+
	   "beneath a thick layer of dust");
  add_item(({"dust","thick layer of dust","layer of dust","thick dust"}),
	   "The floor is almost hidden by a thick layer of dust, which has accumulated\n"+
	   "because the poor QC arches do not have enough time to clean the room.\n"+
	   "A trail of footsteps is clearly visible in the dust"); 
  add_item(({"trail","footsteps","trail of footsteps"}),
	   "A trail of footsteps lead through the dust to the DBBS");
}

init(){
  ::init();
    if(this_player()->query_level() < APP_LEVEL)
    {
      write("Since when did you become a Sci? You are move_objected away.\n");
      say(this_player()->query_name()+
	  " got thrown out for being a puny mortal.\n");
      move_object(this_player(), ROOM+"adv_guild");
      return 1;
    }
    return 0;
  }
