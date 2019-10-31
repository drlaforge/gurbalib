inherit "std/room";
#include "../area.h"

void setup(void) {
    /*add_object(CEMETARY+OBJ+"warning_sign"); */
/* I don't feel a map is necessary. [Mystiq, 2001/11/10]
    pole = clone_object("/domains/areas/city/cemetary/obj/pole");
    pole->set_name("/domains/areas/city/cemetary/room/cemetary.map");
    move_object(pole,this_object());
*/
    set_light(1);
    /*set_outdoors(1); */
    /*set_conditional_lighting(2); */
    set_short("Backyard of the Cryo");
    set_long("A rugged stone path "+
    "leads north to the cemetary front gates. Dead grass lies to the side. "+
    "There is a lamp above the doorway back to the Cryo.");
    add_item("path","stone path","rugged stone path","A rugged stone path leading between the Cryo back doorway and the cemetary's front gates.");
    add_item("doorway","back doorway","cryo back doorway","Allows you access back to the cryo.");
    add_item("gates","front gates","cemetary front gates","They are bent, mangled, and gaping open.");
    add_item("grass","dead grass","Dead grass.");
    add_exit("north",CEMETARY+ROOM+"cem2");
    add_exit("south","/domains/city/abacus/rooms/church");
}

/*
going_south(){
   if (this_player()->query_npc()) return 1;
}
*/

