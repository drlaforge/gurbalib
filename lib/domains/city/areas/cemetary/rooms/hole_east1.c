
inherit "room/room";

reset(arg) {
  object child;
  if(!present("child",this_object())){
    child = clone_object("/obj/monster");
    child->set_gender(2);
    child->set_name("girl");
    child->set_short("A small girl");
    child->set_long("Its a small girl playing with something.\n");
    child->set_level(1);
    child->add_money(6);
    child->set_hp(25);
    child->set_alias("child");
    move_object(child,this_object());
  }
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeders territory";
    
    long_desc = 
        "You stand in a small hole.\n"
        + "There are a lot of toys on the floor.\n";
    items = ({
      "toys","The toys are made of wood and mud. Nothing special about them",
    });
    dest_dir = 
        ({
        "/domains/areas/city/cemetary/room/hole2", "west",
        });
}

