
inherit "room/room";

reset(arg) {
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeders territory";
    
    set_long_f(
        "You are very far below the ground now. "+
        "It is very dark in here. To the north end of the room you can "+
        "see some kind of a throne.\n");
    items = ({
      "throne","Its not really a throne. More like a chair of mud",
    });
    dest_dir = 
        ({
        "/room/cemetary/hole4", "up",
        });
}

init(){
  ::init();
    add_action("sit","sit");
  }

sit(){
  write("You sit down on the throne, but slide off onto the mud.\n");
  say(this_player()->query_name()+" slides around on the ground.\n");
  return 1;
}
