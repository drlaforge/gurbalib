
inherit "room/room";

reset(arg) {
object man;
if(!present("man",this_object()))
move_object(clone_object("/obj/cemetary/digger"),this_object());
man = present("man",this_object());
man->reset();
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "a hole in the cemetary";
    
    long_desc = 
        "You stand in a hole in the cemetary.\n"
        + "This hole was probably made by a lazy grave-digger since it is\n"
        + "far from being dug deep enough for a coffin to fit.\n";
    dest_dir = 
        ({
        "/room/cemetary/cem1", "up",
        });
}

query_peace(){ return ""; }
