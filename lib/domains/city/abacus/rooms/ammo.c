inherit "std/room";
#include "../area.h"

reset (arg)
{
 
	 
	set_outdoors (0);
	set_light (1);
	short_desc = "An ammoshop";
	set_long_f("You stand in the burnt out remains of Bison & Kid's ammo shop. "+
		"There are charred shelves all over the walls that once held packets "+
		"of ammo. You heard about this: a short time ago Frank, the owner "+
		"of the adjacent Tyson & Kid's ammo shop decided he was sick of Hank "+
		"and his stupid non-metric ammo. He ordered a hit on this backward "+
		"looking old fool. One molotov cocktail and a hell of a lot of "+
		"exploding ammo later, this is all that remains.\n");
	dest_dir = ({ ROOM+"boul5","west",0,});

   items_arr = ({ 
		({"remains","burnt out remains","shop","ammo shop"}),
		"You are standing in the burnt out remains of an ammo shop",
		({"shelf","shelves","charred shelves"}),"The shelves are really charred",
           });
}
