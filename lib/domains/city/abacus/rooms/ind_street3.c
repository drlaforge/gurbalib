/*  -*- LPC -*-  */
inherit "std/room";
#include "../area.h"

void setup(void)
{
  /*set_outdoors(1); */
  set_light(1);
  set_short("Near by the south end of Independence street");
set_long("You're at the south end of Independece Street. Along the street there are "+
"huge buildings. Some of them seem to house large Corporations. There isn't anything "+
"else on this street. The street continues north and south.");
  set_exits((["north" : ROOMS+"ind_street2",
  "south" : ROOMS+"ind_street4"]));
}

