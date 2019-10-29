/*  -*- LPC -*-  */
inherit "std/room";
#include "../area.h"

void setup(void)
{
  /*set_outdoors(1); */
  set_light(1);
  set_short("Further down Independence street");
  set_long("High skyscrapers surround the street here. "+
	     "The security forces of these corporations are keeping the "+
	     "street clean from the scums in the slum. Thieves and murderers "+
	     "are not looked upon with pleased eyes around here.");
  set_exits((["north" : ROOMS+"ind_street1",
  "south" : ROOMS+"ind_street3"]));

  add_item("high skyscrapers","skyscrapers","high skyscrape","skyscrape","The high skyscrapers are surrounding the street");
  add_item("inc","incs","corporation","corporations","Odic","TWS","tws","odic","Odic inc","Odic incorporation","odic inc","odic incorporation","tws inc","TWS inc","TWS incorporation","tws incorporation","The corporations like Odic inc and TWS inc are ruling this street"+
	   "as they are the two largest corporations. Other smaller "+
	   "corporations are taking advantage of the protection these "+
	   "larger corporations security forces mean"); 
}




