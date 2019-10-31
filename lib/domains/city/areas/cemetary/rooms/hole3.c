
inherit "room/room";

reset(arg) {
  object guard;
  if(!present("guard",this_object())){
    guard = clone_object("/obj/monster");
    guard->set_name("guard");
    guard->set_level(4);
    guard->set_gender(2);
    guard->set_short("a nightbreeder guard");
    guard->set_long("She is guarding the tunnel to the north.\n");
    guard->set_alias("nightbreeder");
    guard->add_money(20+random(34));
    move_object(guard,this_object());
  }
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeders territory";
    
    long_desc = 
        "You are quite deep in the nightbreeders territory now.\n"
        + "The tunnels continues north and south. The room to the north\n"
        + "looks quite dark.\n";
    dest_dir = 
        ({
        "/domains/areas/city/cemetary/room/hole4", "north",
        "/domains/areas/city/cemetary/room/hole2", "south",
        });
}
init(){
  ::init();
    add_action("north","north");
  }
north(){
  if(present("guard",this_object())){
    write("Guard stops you.\n");
    say("Guard stops "+this_player()->query_name()+".\n");
    return 1;
  }
}
