/*  -*- LPC -*-  */
inherit "std/room";
#include "../area.h"

void setup(void)
{
  set_outdoors(1);
  set_light(1);
  set_short("Near by the south end of Independence street");
 
set_long_f("You're at the south end of Independece Street. Along the street there are "+
"huge buildings. Some of them seem to house large Corporations. There isn't anything "+
"else on this street. The street continues north and south.");

  add_exit("north",ROOM+"ind_street2");
  add_exit("south",ROOM+"ind_street4");
	   
}
