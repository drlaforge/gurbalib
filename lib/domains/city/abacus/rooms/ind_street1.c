/*  -*- LPC -*-  */
inherit "std/room";
#include "../area.h"

void setup(void)
{
  /*set_outdoors(1); */
  set_light(1);
  set_short("North part of Independence street");
  set_long("Standing at the north part of the Independence street you "+
	     "see several skyscrapers rising towards the sky. The whole "+
	     "area look a little more civilized than the other parts of "+
	     "the city. You guess that this street is newly renovated and "+
	     "that the security forces of the Incorporations and research "+
	     "centers south from here are keeping the worst scum away.\n");
  set_exits((["north" : ROOMS+"clst3",
  "south" : ROOMS+"ind_street2"]));

  add_item("north part","north part of independence street","independence street","Independence street","north part of Independence street","north part of street","street","You are standing at the north part of "+
	   "Independence street. It looks like its one of the more "+
	   "civilized parts of the city");
  add_item("inc","incs","incorporations","research centers","centers","center","research center","skyscrapers","skyscrape","Odic","odic","TWS","tws","Tws","ODIC","TWS research center","Tws research center","tws research center","Odic research center","ODIC research center","odic research center","Among the other skyscrapers you see TWS and Odic research centers");
  add_item("security forces","security","force","forces","security force","You can't see them anywhere but you guess that they are there somewhere");
}



