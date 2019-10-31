
inherit "room/room";
int moved;
object stone;
reset(arg) {
moved = 0;
  if(!present("stone",this_object()))
    {
      stone = clone_object("/obj/obj");
      move_object(stone,this_object());
    }
stone->set_name("stone");
stone->set_long("A big stone blocking the passage east.\n"+
                "Maybe you can push it aside.");
stone->set_short("a big stone blocking the passage east");
stone->set_get(1);
stone->set_weight(100);
    if (arg) return;

    set_outdoors(0);
    set_light(0);
    short_desc = "Nightbreeder mines";
    
    long_desc = 
        "You stand in the mines of the nightbreeders.\n"
        + "The cave is very narrow all over in here and the caves seems\n"
	+ "to continue to the west and to the east.\n";
    dest_dir = ({
        "/domains/areas/city/cemetary/room/d4", "west",
        "/domains/areas/city/cemetary/room/d6", "east",
        });
    items = ({
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

init(){
  ::init();
  add_action("east","east");
  add_action("push","push");
  add_action("push","move");
}
east(){
  if(!moved){
    write("There is a stone blocking the way.\n");
    say(this_player()->query_name()+" tries to pass the stone but fails.\n");
    return 1;
  }
}
push(str){
  if(!str){
    write(capitalize(query_verb())+" what?\n");
    return 1;
  }
if(moved){ write("No reason to move the stone now.\n"); return 1; }
if(this_player()->query_weight() > 1){
write("You can't move it.\n");
write("You are carrying too much.\n");
say(this_player()->query_name()+" pushes on the stone, but can't move it.\n");
return 1;
}
write("Ok.\n");
say(this_player()->query_name()+" moves the stone aside.\n");
stone->set_short("A stone pushed aside");
stone->set_long("Just a huge stone lying here.\n");
moved = 1;
return 1;
}
