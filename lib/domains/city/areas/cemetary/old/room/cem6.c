

inherit "room/room";

reset(arg) {
    if (arg) return;

    set_light(1);
    set_outdoors(1);
    short_desc = "cemetary";
    
    long_desc = 
        "You stand in a cemetary. There is a fence blocking the way to the east,\n"
        + "but you notice that the fence is slightly broken and got a hole in it.\n"
        + "The tombstones in this area are totally destroyed.\n";
items = ({
	"cemetary","You stand at the east side of the cemetary",
	"fence","The fence got a hole in it",
	"hole","The hole is very small. Nothing to worry about",
	"tombstones","It's not easy to identify these tombstones. They are totally destroyed",
	"tombstone","You look closer at one of the tombstones. Totally destroyed",
	});
    dest_dir = 
        ({
        "/room/cemetary/cem3", "south",
        "/room/cemetary/cem9", "north",
        "/room/cemetary/cem5", "west",
        
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
	::init();
	add_action("dig","dig");
}
dig(){
	if(!present("shovel",this_player())) return 0;
	write("You dig for awhile. There is nothing here.\n");
	return 1;
}
