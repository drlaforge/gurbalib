
inherit "room/room";

reset(arg) {
  object chest,ob,test;
  if(!present("chest",this_object())){
    chest = clone_object("/obj/obj/container");
    chest->set_name("chest");
    chest->set_max_weight(2);
    chest->set_short("a chest");
    chest->set_long("Its a chest made of wood.\n");
    chest->set_can_get(0);
    move_object(chest,this_object());
  }
  test = present("chest",this_object());
  if(!present("armour",test)){
    ob = clone_object("/obj/armour");
    ob->set_name("armour");
    ob->set_alias("jacket");
    ob->set_short("a jacket");
    ob->set_class(17);
    ob->set_value(100);
    ob->set_long("A studded jacket. There are metal plates for the elbows.");
    ob->set_weight(4);
    ob->set_type("armour");
    move_object(ob,test);
    ob = clone_object("/obj/money");
    ob->set_money(random(50)+40);
    move_object(ob,test);
  }
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeders territory";
    
    long_desc = 
        "You are standing in a large chamber.\n"
        + "It is well dug up, and there is a hole with a ladder leading down\n"
        + "in the middle of the chamber.\n";
    items = ({
      "ladder","It's leading down",
      "hole","It's quite small",
    });
    dest_dir = 
        ({
        "/domains/areas/city/cemetary/room/hole3", "south",
        "/domains/areas/city/cemetary/room/hole_down1", "down",
        });
}
