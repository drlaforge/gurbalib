inherit "std/room";
#include "../area.h"

void setup(void)
{
    if (arg)
        return;
    set_outdoors(1);
    set_light(1);
    short_desc = "The sci line room";
    long_desc =	"The sci line room\n"+
                "FOO1 = FOOn + gnu\n"+
		"where n goes from 0 to infinity\n"+
		"and gnu is the pan galactic gnu constant\n";
    add_exit("void", ROOM+"void");
    "/obj/sci_line_catcher"->force_load();
    "/obj/sci_line_player"->force_load();
}

init() 
{
    if(!present("Sci_Line_Player",this_object()))
	"/obj/sci_line_player"->force_load();
    if(!present("Sci_Line_Catcher",this_object()))
	"/obj/sci_line_catcher"->force_load();
	
/* room::init();
   add_action("nope",({"bomb","drop","give","put","get","take"}));*/
}

nope() 
{
    write("Nope!\n");
    return 1; 
}
