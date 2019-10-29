
inherit "room/room";
int lid_status,urn_status;
reset(arg) {
  object rat;
  lid_status = 0;
  urn_status = 0;
 if(!present("rat",this_object())){
   rat = clone_object("/obj/monster");
   rat->set_name("rat");
   rat->set_alias("rat");
   rat->set_short("a small rat");
   rat->set_long("A small brown rat running along the walls.\n");
   rat->set_level(1);
   rat->set_hp(14);
   rat->load_chat( 10 , ({ "The rat runs between your legs.\n",
			     "The rat runs around the coffin.\n",
			     "The rat runs and hides beside a small urn in the corner.\n",
			   }) );
   move_object(rat,this_object());
 }

    if (arg) return;

    set_outdoors(0);
    set_light(0);
    short_desc = "in a cellar";
    
    long_desc = 
        "You stand in a big stone cellar.\n"
        + "The walls are black and covered with cobwebs.\n"
        + "On the middle of the floor there is a big coffin made of stone.\n";
    dest_dir = ({
        "/domains/areas/city/cemetary/room/cem10", "out",
        });
    items = ({
      ({ "tomb", "stone tomb" }),
      "The tomb is totally made out of big stones",
      ({ "wall" , "walls" , "stones" , "big stones" }),
      "The stone walls are cold and dark and covered with web. The web is\nespecially thick in a corner",
      ({ "webs" , "cobwebs" , "thick web" , "web" , "cobweb" , "corner" }),
      "Behind the cobwebs in the corner you can see a small urn",
      ({ "urn" , "small urn" }),
      "#urn",
      ({ "lid" , "stonelid" }),
      "#lid",
     ({ "coffin" , "big coffin" , "stone coffin" , "floor" }),
      "#coffin"
          });
}
init(){
  ::init();
    add_action("move","push");
    add_action("move","pull");
    add_action("move","move");
    add_action("down","down");
    add_action("down","enter");
    add_action("open","open");
  }
open(str){
  if(str!="coffin") return 0;
  if(!lid_status){ write("You must move the lid.\n"); return 1; }
  write("It is already opened.\n");
  return 1;
}
lid(){
  if(!lid_status){ write("The lid is on the coffin.\n"); return 1; }
  write("The lid is moved abit revealing stairs down the coffin.\n");
  return 1;
}
down(str){
  if(!lid_status) return 0;
  if(!str||str=="coffin"){
    this_player()->move_player("down into the coffin#/domains/areas/city/cemetary/room/stairs");
    return 1;
  }
}
move(str){
  if(str=="lid"||str=="stonelid"){
    if(!lid_status){
      write("You push with all strength that you got.\n");
      write("The lid slowly moves aside revealing stairs down into the earth.\n");
      say(this_player()->query_name()+" pushes the stonelid aside.\n");
      lid_status = 1;
      return 1;
    }
    write("The lid is already moved.\n");
    return 1;
  }
}
coffin(){
  write("The coffin is completely made of stone.\n");
  if(!lid_status){
    write("There is a big stonelid on the coffin.\n");
    return 1;
  }
  write("There is a stonelid moved aside on the coffin, revealing stairs\n"+
	"going down into the earth.\n");
  return 1;
}
  
urn(){
  object star;
  if(!urn_status){
    say(this_player()->query_name()+" finds something in an urn in a corner.\n");
   write("You find a small silver star in the urn.\n");
    star = clone_object("/obj/treasure");
    star->set_name("star");
    star->set_short("a small silver star");
    star->set_long("A small silver star, with sharp ends on it.\n");
    star->set_value(25);
    star->set_alias("star");
    star->set_alt_name("silver star");
    move_object(star,this_player());
    urn_status = 1;
    return 1;
  }
  write("The urn seems empty.\n");
  return 1;
}


