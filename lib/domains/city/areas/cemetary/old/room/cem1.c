

inherit "room/room";

reset(arg) {
    if (arg) return;

    set_light(1);
    set_outdoors(1);
    short_desc = "cemetary";
    
    long_desc = 
        "You stand in the corner of the cemetary. There is a fence blocking the way\n"
	+ "to the west and south. There are a lot of tombstones here.\n"
	+ "There is a hole in the ground here.\n";
items =	({
	"hole","#hole",
	"cemetary","You stand in the southwest corner of the cemetary",
	"fence","The fence is very high",
	"tombstones","There are some tombstones here, most of them in pieces",
	"tombstone","You see nothing special about a broken tombstone",
	"pieces","Pieces of broken tombstones. You cant take them",
	});
    dest_dir = 
        ({
        "/room/cemetary/cem4", "north",
        "/room/cemetary/cem2", "east",
	"/room/cemetary/small_hole", "down",
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
	add_action("down","down");
	add_action("climb","climb");
}
climb(str){
	if(str != "fence") return 0;
	write("The fence is to high for you to climb.\n");
	return 1;
	}
down(){
	if(this_player()->query_level() > 2){ write("You are too big to go down in the hole.\n"); return 1; }
}
hole () {
        if (this_player()->query_level() >2)
	  write ("The hole is too small for you to enter.\n");
        else
	  write ("It's a quite large hole.\nMaybe you should try enter it.\n");
	return 1;
}
