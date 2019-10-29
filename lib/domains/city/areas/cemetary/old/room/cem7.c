

inherit "room/room";

reset(arg) {
    if (arg) return;

    set_light(1);
    set_outdoors(1);
    short_desc = "cemetary";
    
    long_desc = 
        "You stand in a cemetary. You notice that there are more bushes and that the\n"
        + "grass is more wildgrown in this area. There are some tombstones here.\n"
        + "To the west there is a passage leading through the fence.\n"
        + "There is a sign above the passage.\n";
items =	({
	"cemetary","You are standing in the west side of the cemetary",
	"bushes","There are more bushes on this side of the cemetary",
	"grass","The grass is growing high here",
	"tombstones","The tombstones in this part is not that broken",
	"passage","There is a passage leading west through the fence",
	"sign","Maybe you should read it",
	"fence","There is a passage leading through the fence",
	});
    dest_dir = 
        ({
        "/room/cemetary/cem4", "south",
        "/room/cemetary/cem10", "north",
        "/room/cemetary/petc", "west",
        "/room/cemetary/cem8", "east",
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

init(){
	add_action("read","read");
	add_action("dig","dig");
	::init();
}
read(str){
	if(str != "sign") return 0;
	write("The sign says: PET CEMETARY.\n");
	return 1;
}
dig(){
	if(!present("shovel",this_player())) return 0;
	write("You dig for awhile but come up empty.\n");
	return 1;
}
