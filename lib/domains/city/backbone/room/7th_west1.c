inherit "std/room";
#include "../area.h"

object thief;
 
void setup(void) 
{
/*
 THIEF IS MOVED TO CENTRAL TRAIN STATION, Mindmaster Mastermind 970720
  if(thief)
    move_object(thief,this_object());
*/
    /* added by Aladdin. The thief should come back here once in
     * a while, or else he might wander away where noone is
     * hunting, and the thief wouldn't affect anything. 
     */
     set_outdoors(1);
     set_light(1);
     set_short("7th avenue");
 
     set_long_f("You stand on the 7th avenue west from Eden street. "+
		"The avenue continues west and to the east there is a "+
		"large crossing.");

     add_exit("east",ROOM+"eden5");
     add_exit("west",ROOM+"7th_west2");

/*
  if(!thief) 
  {
    thief = clone_object("obj/monsters/thief");
    move_object(thief,this_object());
  }
*/
}
