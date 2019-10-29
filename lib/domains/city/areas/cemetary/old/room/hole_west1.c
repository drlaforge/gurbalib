
inherit "room/room";

reset(arg) {
  object boy,boots;
  if(!present("boy",this_object())){
    boy = clone_object("/obj/monster");
    boy->set_name("boy");
    boy->set_gender(1);
    boy->set_level(2);
    boy->set_alias("nightbreeder");
    boy->set_short("a nightbreeder boy");
    boy->set_long("The boy is really ugly.\n"+
		  "He is trying to catch some fish with his hands.\n");
    boots = clone_object("/obj/armour");
    boots->set_name("boots");
    boots->set_type("boot");
    boots->set_short("a pair of rubber boots");
    boots->set_plural_short("pairs of rubber boots");
    boots->set_class(3);
    boots->set_value(50);
    boots->set_weight(1);
    boots->set_long("A pair of rubber boots.\n"+
		    "They are yellow with red stripes on the side.\n");
    move_object(boots,boy);
    move_object(boy,this_object());
    boy->command("wear boots");
  }
  if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeders territory";
    
    long_desc = 
        "You stand in a small tunnel leading east.\n"
        + "There is a small lake in the middle of this tunnel.\n";
    items = ({
      "lake","The water is very clear. Looks inviting for a swim",
    });
    dest_dir = 
        ({
        "/room/cemetary/hole1", "east",
        });
}
init(){
  ::init();
    add_action("swim","swim");
    add_action("swim","dive");
  }
swim(){
  this_player()->move_player("into the water#/room/cemetary/lake");
  return 1;
}
