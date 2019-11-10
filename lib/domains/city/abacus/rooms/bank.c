#include "../area.h"
#include <def.h>

inherit STD_ROOM; 


void setup(){

	set_light(2);
	set_short("An old stock room");
	set_long("You stand in the Associated Corporation Bank's central office.\n"+
		"The walls are bare and cold, and the room is empty with the\n"+
		"exception of a series of monitors that hang from the roof. A\n"+
		"fully automated multi-user Quickbank supercomputer runs along\n"+
		"the length of the north wall.\n");
	add_item("rods", "A collection of long metallic rods which support the banks information monitors");
	add_item("roof", "A number of monitors are atrached to the high vaulted roof, via\n"+
		"a number of long steel rods\n");
	add_item("north wall", "The north wall is partially covered by a huge Quickbank AMT\n"+
		"which represents the latest form of hi-tec banking\n");
	add_item("rod", "A collection of long metallic rods which support the banks information monitors");
	add_item("monitor", "The monitor reads:\n"+
		"\n"+
		"Welcome to ACB's central banking office. We offer a wide range\n"+
		"of financial services. If you would like a bank account simply\n"+
		"examine the fully automated Quickbank machine in front of you,\n"+
		"where a full instructions are given.\n"+
		"\n"+
		"\n"+
		"ACB - 'YOU CAN BANK ON US!!'\n");
	add_item("monitors", "The monitor reads:\n"+
		"\n"+
		"Welcome to ACB's central banking office. We offer a wide range\n"+
		"of financial services. If you would like a bank account simply\n"+
		"examine the fully automated Quickbank machine in front of you,\n"+
		"where a full instructions are given.\n"+
		"\n"+
		"\n"+
		"ACB - 'YOU CAN BANK ON US!!'\n");
	add_item("vaulted roof", "A number of monitors are atrached to the high vaulted roof, via\n"+
		"a number of long steel rods\n");
	add_item("long steel rods", "A collection of long metallic rods which support the banks information monitors");
	add_item("walls", "The walls are whitewashed and plain in appearance, with the\n"+
		"exception of a large multi-user Quickbank attached to the\n"+
		"north wall.\n");
	add_item("wall", "The walls are whitewashed and plain in appearance, with the\n"+
		"exception of a large multi-user Quickbank attached to the\n"+
		"north wall.\n");
	add_item("steel rods", "A collection of long metallic rods which support the banks information monitors");
	add_item("information monitor", "The monitor reads:\n"+
		"\n"+
		"Welcome to ACB's central banking office. We offer a wide range\n"+
		"of financial services. If you would like a bank account simply\n"+
		"examine the fully automated Quickbank machine in front of you,\n"+
		"where a full instructions are given.\n"+
		"\n"+
		"\n"+
		"ACB - 'YOU CAN BANK ON US!!'\n");
	add_item("information monitors", "The monitor reads:\n"+
		"\n"+
		"Welcome to ACB's central banking office. We offer a wide range\n"+
		"of financial services. If you would like a bank account simply\n"+
		"examine the fully automated Quickbank machine in front of you,\n"+
		"where a full instructions are given.\n"+
		"\n"+
		"\n"+
		"ACB - 'YOU CAN BANK ON US!!'\n");
	set_objects("/domains/required/objects/bank_sign.c");
	add_exit("west", ROOMS + "eden1");

}
