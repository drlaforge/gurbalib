

inherit "room/room";

init () {
::init();
   add_action ("south","south");
}
reset(arg) {
object pole;
    if (arg) return;
    pole = clone_object("/obj/cemetary/pole");
    pole->set_name("/room/cemetary/cemetary.map");
    move_object(pole,this_object());
    set_light(1);
    set_outdoors(1);
    short_desc = "Cemetary gates";
    
    long_desc = 
	"You stand in the backyard of the city church.\n"
        + "To the north you can see the cemetary gates. \n";
	items = ({
	"gates","The cemetary looks abandoned",
	"cemetary","The cemetary is to the north",
	"backyard","You smell rotting corpses",
	});
    dest_dir = 
        ({
        "/room/cemetary/cem2", "north",
        "/domains/areas/city/crematorium/room/16","south",
        });
}

query_light() {
    return 1;
}
query_room_maker() {
    return 101;
}

/*
    remove the comments around the "room is modified()" code
    below to prevent changes you have done to this room to
    to be lost by using the room maker
*/
/*
room_is_modified() {
    return 1;
}
*/

/*
 make your additions below this comment, do NOT remove this comment
--END-ROOM-MAKER-CODE--
*/
south () {
   if (this_player()->query_npc()) return 1;
}
