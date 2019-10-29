
inherit "room/room";

reset(arg) {
    if (arg) return;

    set_outdoors(0);
    set_light(0);
    short_desc = "Stairs in tomb";
    
    long_desc = 
        "You stand at the end of the stairs in the coffin.\n"
        + "The roof is very low here. There is a small passage leading north.\n";
    dest_dir = ({
        "/room/cemetary/coffin_end", "north",
        "/room/cemetary/tomb", "up",
        });
    items = ({
      "stairs","The stairs leads up to the coffin",
      ({ "roof", "passage" }), 
      "It is very low roof here. If you want to proceed north you probably\nhave to crawl north",
          });
}

init(){
  ::init();
    add_action("north","north");
    add_action("crawl","crawl");
  }
north(){
  write("You try to walk upstraight and pound your head against the roof.\n");
  say(this_player()->query_name()+" tries to proceed north without crawling.\n");
  say("It looks like it hurts when the head hits the roof.\n");
  return 1;
}
crawl(str){
  if(!str||str=="north"){
    this_player()->move_player("crawling north#/room/cemetary/coffin_end");
    return 1;
  }
}
