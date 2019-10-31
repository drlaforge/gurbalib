inherit "std/room";
#include "../area.h"


void setup(void)
{
    set_light(1);
set_short("the cryogenic facility");
set_long("You are standing in a large laboratory that has been "+
"specifically designed for the artificial duplication of "+
"living beings. A number of capsules and vats line the "+
"northern wall, connected to a vast array of electronic "+
"control systems by a deluge of wires and cables. There "+
"is a monitor attached to the east wall which illustrates "+
"how to begin the cloning process. A small vdu flickers in "+
"front of you, and there is a constant hum in the air. "+
"A spiralling staircase with the words TOURGUIDE OFFICE "+
"engraved upon it leads down. You get the feeling that "+
"this is a very good place for a NEWBIE to get a good "+
"start.\n");
add_item("staircase","Please check in with the Tour Guide office down the stairs for details and a tour!");
add_item("computers", "systems", "control systems", "electronic control systems","The control system consists of a number of computers which have been programmed to copy the genetic structure of a living being. You notice a red button on the keypad in front of you");
add_item("keypad","A keypad that is used to initialise the cloning process");
add_item("button", "red button","The button has the word 'CLONE' stamped upon it");
set_exits((["south" : ROOMS+"west_street1"]));
#ifdef LOAD_CEM
    affect_long("An empty doorway leads north into a cemetary.\n");
    add_exit("north", "/domains/city/areas/cemetary/rooms/ent");
#endif
}



