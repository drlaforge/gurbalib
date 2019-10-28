inherit "/std/room";
#include "../area.h"
void setup(void){
	 
	 
   	set_outdoors(1);
   	set_light(1);
	set_short("5th Avenue");
 
   	set_long_f("The road is covered in bricks here, it's all that remains of a wall that once "+
		"ran along the north side of the road. To the south is an empty building which from "+
		"it's looks has been deserted for some time. You think you see a large lake or something "+
		"to the east. The road continues east and west.");
	add_item(({"brick","bricks"}),"A few bricks are all that is left of a once impressive wall");
	add_item("wall","The wall has been demolished, all that is left are a few bricks");
	add_item(({"empty building","building"}),"An empty building with it's entrance barricaded to\n"+
		"prevent people like you getting in");
	add_item("road","The road goes from east to west");
	add_item(({"large lake","lake"}),"You can't quite make it out from here");
   	add_exit("east",ROOM+"5th_avenue8");
	add_exit("west",ROOM+"5th_avenue6");
}
