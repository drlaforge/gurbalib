
inherit "room/room";

int shovel;
reset(arg) {
shovel = 0;
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "a toolshed";
    
    long_desc = 
        "You are in a small toolshed.\n"
        + "There is a long box on the floor.\n";
    dest_dir = ({
        "/room/cemetary/cem12", "west",
        });
    items = ({
              "toolshed",
              "Nothing in here except for the long box",
              "box",
              "#box",
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

box(){
if(!shovel){
  write("You find a shovel.\n");
  shovel = 1;
  move_object(clone_object("/obj/obj/shovel"), this_object());
  return 1;
}
write("The box seems empty.\n");
return 1;
}
