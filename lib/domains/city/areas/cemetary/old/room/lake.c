
inherit "room/room";

reset(arg) {
  object weapon;
  int a;
  if(!present("weapon",this_object())){
    weapon = clone_object("/obj/weapon");
    weapon->set_value(20);
    weapon->set_weight(1);
    weapon->set_class(5);
    weapon->set_alias("weapon");
    a = random(3);
    if(!a){
      weapon->set_name("knife");
      weapon->set_short("A swiss army knife");
      weapon->set_long("The main things such as the cork-screw and the fork\n"+
		       "is gone.\n");
    }
    if(a==1){
      weapon->set_name("ironbar");
      weapon->set_short("A steel ironbar");
      weapon->set_long("The ironbar looks like it can be used as a weapon.\n");
    }
    if(a==2){
      weapon->set_name("stick");
      weapon->set_short("A big stick");
      weapon->set_long("This stick is shaped like a baseball bat.\n");
    }
    move_object(weapon,this_object());
  }
  if (arg) return;
  
  set_outdoors(0);
  set_light(1);
  short_desc = "Lake(leave)";
  
  long_desc = 
    "You are swimming in a beautiful lake.\n"
      + "The water is crystal clear and you can see some fishes swimming around.\n";
  items = ({
    "fishes","They swim all around you",
  });
  dest_dir = 
    ({
      "/room/cemetary/hole_west1", "leave",
    });
}
init(){
  ::init();
  
    add_action("ca","catch");
  }
     ca(str){
       if(str=="fishes"){
	 write("They swim much to rapidly for you to catch.\n");
	 return 1;
       }
     }




