#include "../area.h"

inherit STD_ROOM;

void setup(void){
    
	/*set_outdoors(1);*/
    set_light(1);
    set_short("Angels boulevard");
     
    set_long("You are standing on the Angels boulevard. "
        + "To the west you can see small building with a sign over the door "
        + "which reads: 'Tyson & Kid's Ammo Shop'. "
        + "To the east stands what was once an almost identical building. "
		+ "Something catastrophic seems to have happened though, and it is "
		+ "no more than a burnt out shell now. You can just make out the "
		+ "text on its charred sign, which reads: 'Bison & Kid's Ammo Shop'. "
        + "The boulevard continues north and south.\n");
    
	add_item("boulevard","angels","angel","angels boulevard","The boulevard continues north and south");
	add_item("small building","building","There is one to the west and one to the east");
	add_item("sign","Tyson & Kid's Ammo Shop");
	add_item("charred sign","Bison & Kid's Ammo Shop");
    set_exits(([
		"south" : ROOMS + "boul4",
		"north": ROOMS + "boul6",
		"east" : ROOMS + "ammo",
		"west" : ROOMS + "new_ammo",
      ]));
}

