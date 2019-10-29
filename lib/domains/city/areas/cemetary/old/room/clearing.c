
inherit "room/room";

reset(arg) {
object crow;
int i;
if(!present("crow", this_object())){
  for(i=0;i<2;i++){
   crow = clone_object("/obj/monster");
   crow->set_name("crow");
   crow->set_short("a black crow");
   crow->set_long("It is a black crow flying around in the clearing.\n");
   crow->set_alias("crow");
   crow->set_level(4);
   crow->set_hp(50+random(20));
   crow->set_ac(1);
   crow->set_wc(5);
   crow->load_chat(10,({ "The crow makes a loud unpleasant sound.\n",
			 "The crow flies down against you and nearly misses.\n",
			 }));
    crow->add_money(10 + random(6));
   move_object(crow,this_object());
  }
}
    if (arg) return;

    set_outdoors(1);
    set_light(1);
    short_desc = "a clearing";
    
    set_long_f("You stand in a clearing in the bushes. "+
      "There is a fence to the east with a hole, which you came in through.\n");
items = ({
        ({"bushes","bush"}),"Scraggly bushes surrounding you",
        "fence","The fence to the east has a hole in it you could go out of",
        "hole","You could go out it back into the pet cemetary",
	});
    dest_dir = 
        ({
        "/room/cemetary/petc", "out",
        });
}

init(){
	::init();
}









