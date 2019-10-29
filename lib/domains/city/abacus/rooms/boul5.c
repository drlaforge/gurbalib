inherit "std/room";
#include "../area.h"

void setup(void) 
{
     
     

    set_outdoors(1);
    set_light(1);
    short_desc = "Angels boulevard";
     
    set_long_f( 
        "You are standing on the Angels boulevard. "
        + "To the west you can see small building with a sign over the door "
        + "which reads: 'Tyson & Kid's Ammo Shop'. "
        + "To the east stands what was once an almost identical building. "
	+ "Something catastrophic seems to have happened though, and it is "
	+ "no more than a burnt out shell now. You can just make out the "
	+ "text on its charred sign, which reads: 'Bison & Kid's Ammo Shop'. "
        + "The boulevard continues north and south.\n");
    items_arr=({
	({"boulevard","angels","angel","angels boulevard"}),"The boulevard continues north and south",
	({"small building","building"}),"There is one to the west and one to the east",
	"sign","Tyson & Kid's Ammo Shop",
	"charred sign","Bison & Kid's Ammo Shop",
	});
    dest_dir = 
        ({
        ROOM+"boul4", "south",0,
        ROOM+"boul6", "north",0,
        ROOM+"ammo", "east",0,
	ROOM+"new_ammo", "west",0
      });
}

