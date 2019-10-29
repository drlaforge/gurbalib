/* ROOMMAKER..  Modified by Thorwald. */

inherit "room/room";

reset(arg) {
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "attic in a house in a cemetary";
    
    long_desc = 
        "You stand in the attic of the house. On the floor there is a\n"
        + "red painted pentagram. Looking closer at it you see that it is\n"
        + "made by blood and it is still fresh.\n";
items = ({
	"attic","It's not so dark in here. There are some cracks in the ceiling letting light in",
	"cracks","Nothing special about them"
	,"pentagram","It painted in blood",
	"blood","You taste it. It is still warm"
	,"floor","It looks sturdy",
	});
    dest_dir = 
        ({
        "/room/cemetary/house", "down",
        });
}

