
#include <def.h>
#include <tune.h>
inherit "std/room";
#include "../area.h"
object ob;

void setup() {
	 
     
	ob=clone_object("obj/board");
	ob->set_delete_level(ARCH_LEVEL);
	ob->set_max_notes(40);
	ob->set_short("The Dead Poets Board");
        ob->set_save_path("boards/poet_notes");
	move_object(ob,this_object());

    set_outdoors(0);
    set_light(1);
	set_short("Poet's Lounge");
    
    set_long_f( 
        "A multitude of sweet smelling candles decorate the walls "
        + "of this low-lit room. You see nothing but a few chairs and a "
        + "posting board. This is the "
        + "Poets Louge room, a remanent of Old Abacus, where aspiring writers can post their "
        + "original work on the board. No subject is forbidden, no work is "
        + "too long, though the management does reserve the right to delete "
        + "posts he feels are not done in good taste. To the west is a hallway.\n", 78);

    add_item( ({ "various candles", "small candles", "large candles", "sweet candles", "sweet smelling candles",
		"candles", "various candle", "small candle", "large candle", "sweet candle", "sweet smelling candle",
		"candle"  }),
		"These candles provide the only light in the room.");
	add_item( ({ "chair", "chairs" }), "Just average chairs, to sit in.");
	add_item( ({ "hall", "west hall", "west hallway", "hallway" }), "A hallway leading back to the grand hall.");

add_exit("up", ROOM+"announce");
add_exit("east", ROOM+"adv_cellar");

}

int query_peace() { return 1; }

void init(){
	::init();
	add_action("sit","sit");
}

int sit(string str){
	if( str == "in chair" )
		action("#NA ## in a chair.","sit-sits");
	return 0;
}
