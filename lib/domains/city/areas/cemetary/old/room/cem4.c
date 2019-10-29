inherit "room/room";

reset(arg) {

if(!present("girl",this_object()))
move_object(clone_object("/obj/cemetary/girl"),this_object());
if(arg) return;

    set_light(1);
    set_outdoors(1);
    short_desc = "cemetary";
    long_desc = 
        "You stand in a cemetary. There is a fence blocking the way to the west.\n"
        + "There are alot of tombstones here, and most of them broken.\n";
items = ({
	"cemetary","You stand at the west side of the cemetary",
	"fence","The fence is very high",
	"tombstone","The tombstone is broken in half",
	"tombstones","Most of the tombstones are broken. Not so much though",
	});
    dest_dir = 
        ({
        "/room/cemetary/cem1", "south",
        "/room/cemetary/cem7", "north",
        "/room/cemetary/cem5", "east",
        });
}

query_light() {
    return 1;
}

init(){
	::init();
	add_action("climb","climb");
}
climb(str){
	if(str != "fence") return 0;
	write("The fence is very high. You fail to climb it.\n");
	return 1;
}
