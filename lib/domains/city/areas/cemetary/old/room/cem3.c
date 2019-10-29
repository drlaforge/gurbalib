

inherit "room/room";

reset(arg) {
if(!present("boy",this_object()))
move_object(clone_object("/obj/cemetary/boy"),this_object());
if (arg) return;

    set_light(1);
    set_outdoors(1);
    short_desc = "cemetary";
    
    long_desc = 
        "You stand in the corner of the cemetary. There is a fence blocking the way\n"
        + "to the east and south. There are alot of tombstones here.\n";
items =	({
	"cemetary","You stand in the southeast corner of the cemetary",
	"fence","The fence is very high",
	"tombstones","There are some tombstones here, most of them in pieces",
	"tombstone","You see nothing special about a broken tombstone",
	"pieces","Pieces of broken tombstones. You cant take them",
	});
    dest_dir = 
        ({
        "/room/cemetary/cem6", "north",
        "/room/cemetary/cem2", "west",
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
	add_action("climb","climb");
}
climb(str){
	if(str != "fence") return 0;
	write("The fence is to high for you to climb.\n");
	return 1;
	}

