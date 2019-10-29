
inherit "room/room";

reset(arg) {
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "a Nightbreeder ladder";
    
    long_desc = 
        "You stand on a ladder leading down. \n"+
        "There is a small sign on the tunnel wall.\n";
    dest_dir = ({
        "/room/cemetary/w4", "up",
        "/room/cemetary/d2", "down",
        });
    items = ({
              "sign",
              "The sign is made of wood and hangs on the wall. The text on it is written\n"+
              "with big red letters to make it look more dangerous. You think you can\n"+
              "understand what it says if you try to read it.",
              "ladder",
              "The ladder is made of wood. You notice that is a little broken so you should\n"+
              "be careful not making to fast moves, like jump, or anything.",
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

init(){
::init();
add_action("read","read");
}
read(str){
  if(str!="sign") return 0;
  write("The sign says 'DANGER!'.\n");
  return 1;
}
