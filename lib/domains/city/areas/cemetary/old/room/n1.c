
inherit "room/room";

reset(arg) {
object man,lamp;
if(!present("man",this_object()))
{
man = clone_object("/obj/monster");
man->set_name("man");
man->set_short("a nightbreeder man");
man->set_alias("nightbreeder");
man->set_long("The man seems to be writing something on the wall.\n");
man->set_level(5);
man->set_race("nightbreeder");
man->set_gender(1);
lamp = clone_object("/obj/obj/flashlight");
lamp->set_name("lamp");
lamp->set_long("Looks like an old fashion mining lamp.\n");
lamp->set_short("a lamp");
move_object(lamp,man);
move_object(man,this_object());
}

    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeders territory";
    
    long_desc = 
        "You stand in a tunnel. The tunnel stops north and continues to the south.\n"
        + "There is a torch on the wall that lit up the place.\n";
    dest_dir = ({
        "/room/cemetary/w1", "south",
        });
    items = ({
              "torch",
              "The torch is stuck in the mud in one of the walls",
              "mud",
              "The mud is hard",
              "walls",
              "The walls are of hard mud",
              "wall",
              "There is something written on it, but you cannot understand it",
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

