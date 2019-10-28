inherit "std/room";
#include "../area.h"
#define   CASE(XX,YY)     case XX:  write(YY);   break;

void setup(void) {
   
  set_light(1);
  short_desc = "old school building entrance";
  
  set_long_f(
    "You stand in the entrance of a large school building. Although it may "+
    "have been a pleasant place in the past, years of neglect have made it "+
    "very unpleasant. There is bad smelling grime on the floor and ceiling, "+
    "and the walls are completely covered with various forms of grafitti. "+
    "Garbage and debris partially cover the floor. The doorway to the south "+
    "used to have a door, but now it is just plank of wood on hinges.\n");
  dest_dir = 
    ({
      ROOM+"adv_guild.c", "south",
      ROOM+"central_square.c", "north",
      ROOM+"sci_callroom","west",
      ROOM+"donation","east",
    });
  items_arr = ({
    ({"walls","wall"}),
      "The walls are dirty and covered with grafitti.",
    "grafitti", "#grafitti",
    "debris", "They look like some pieces of the ceiling.",
    "garbage", "You have no idea where the garbage came from.",
    "grime", 
      "It looks like a combination of dirt and other putrid things.",
      "@It smells absolutely awful.",
    "doorway",
      "Now that it doesn't have a door, maybe it is not a doorway anymore.",
    ({"plank","plank of wood","wood","hinges"}),
      "The plank of wood on the hinges is the only thing left of the door.",
    });
}

int grafitti() {
  string text;
  int i;
  i = random(5);
  write("You read the words:  ");
  switch(i) {
    CASE(0, "Support the police - Nuke yourself.\n");
    CASE(1, "I don't need light. I'm radioactive.\n");
    CASE(2, "Why do you spray on this wall???  /Harry.\n");
    CASE(3, "Join the Air Force - Ride a nuclear war head.\n");
    CASE(4, "If you're looking for a good time visit the Hog House!\n");
    default:
      write("Need a refreshing shower? Stand in the rain!  /Anonymous\n");
      return 1;
  }
}

