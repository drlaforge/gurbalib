
inherit "room/room";

reset(arg) {
  object man,armour;
  if(!present("man",this_object())){
    man = clone_object("obj/monster");
    man->set_name("man");
    man->set_level(2);
    man->set_gender(1);
    man->set_short("a nightbreeder man");
    man->set_alias("nightbreeder");
    man->set_long("He has a horrible looking face.\n");
    armour = clone_object("/obj/armour");
    armour->set_class(4);
    armour->set_name("gloves");
    armour->set_type("glove");
    armour->set_value(75);
    armour->set_weight(1);
    armour->set_short("a pair of gloves");
    armour->set_plural_short("pairs of gloves");
    move_object(armour,man);
    move_object(man,this_object());
    man->init_command("wear gloves");
    }
	  
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeders territory - below hole";
    
    long_desc = 
        "You are in the nightbreeders territory now.\n"
        + "There are tunnels leading north and west.\n";
    dest_dir = 
        ({
        "/domains/areas/city/cemetary/room/hole2", "north",
        "/domains/areas/city/cemetary/room/hole_west1", "west",
	"/domains/areas/city/cemetary/room/hole", "up",
        });
}

