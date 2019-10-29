inherit "room/room";

int last;

reset(arg) {
  if(!present("shovel",this_object()))
    move_object(clone_object("/obj/obj/shovel"),this_object());
  if (arg) return;

  set_light(1);
  short_desc = "in a grave";
  
  set_long_f(
    "You are standing in an uncompletely dug grave. This is probably the "+
    "home for many unpleasant bugs. "+
    "It looks like someone has done even more digging, and made a small "+
    "hole leading down into darkness.\n");

  items = ({
    "hole","Its quite small. You must be quite small to get down there",
    "grave","It's quite deep",
    "bugs","Looking closer on the ground you notice alot of small unpleasant bugs",
  });
  dest_dir = 
    ({
      "/room/cemetary/cem9", "up",
      "/room/cemetary/hole1", "down",
    });
}

init(){
  ::init();
    test();
    add_action("dig","dig");
    add_action("down","down");
}

test(){
  int a;
  string mon;

  if((time() - last) < 200)  return;
  if(present("worm",this_object())) return;
  if(present("beetle",this_object())) return;
  if(present("spider",this_object())) return;
  a = random(100);
  if(a<33)        mon = "worm";
  else if (a<66)  mon = "beetle";
  else            mon = "spider";
  move_object(clone_object("/obj/cemetary/"+mon),this_object());
  last = time();
  return 1;
}

dig(){
  if(!present("shovel",this_player())){
    write("You need a shovel to dig.\n");
    return 1;
  }
  write("You dig for a while but find nothing.\n");
  say(break_string(this_player()->query_name()+" digs in the ground, "+
      "but "+this_player()->query_pronoun()+" doesn't find anything.\n",
      78,0));
  return 1;
}

down(){
  if(this_player()->query_exp() > 6000){
    write("You feel too experienced to go down.\n");
    return 1;
  }
  if(this_player()->query_level() > 5){
    write("You are to big to enter the hole.\n");
    say(break_string(this_player()->query_name()+" tries to squeeze "+
        this_player()->query_objective()+"self down the hole, but "+
        this_player()->query_pronoun()+" fails.\n",78,0));
    return 1;
  }
}
