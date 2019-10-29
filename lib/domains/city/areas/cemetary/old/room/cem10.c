/* ROOMMAKER..  Modified by Thorwald. */

inherit "room/room";

int tomb_door_status,pushed;
reset(arg) {
tomb_door_status = 0;
pushed = 0;
if(!present("flashlight",this_object()))
move_object(clone_object("/obj/obj/flashlight"),this_object());
    if (arg) return;

    set_outdoors(1);
    set_light(1);
    short_desc = "cemetary";
    
    long_desc = 
        "You stand in the corner of the cemetary. There is a fence blocking the way\n"
        + "to the west and north. The vegetation here is very thick, making the \n"
        + "tombstones hard to discover. You can see a house to the east but doubt that\n"
        + "you can go there because of the extremely thick vegetation.\n"
	+ "There is a big stone tomb by the fence.\n";
items = ({
  ({ "tomb", "stone tomb", "big stone tomb" }),
  "#tomb",
  ({ "inscription", "small inscription" }),
  "#text",
  ({ "stones", "strange stones" , "smooth stones" }),
  "#stones",
  ({ "door", "tomb door" }),
  "#door",
  ({ "stone", "smooth stone" }),
  "The stone is very smooth. It looks like you can push it",
	"cemetary","You stand at the northwest corner of the cemetary",
	"fence","The fence is very high",
	"vegetation","It's very thick. It looks impossible to go east from here",
	"tombstones","You notice nothing special about them",
        "house","The house is made of stone and looks very old",
	});
    dest_dir = 
        ({
        "/room/cemetary/cem7", "south",
        });
}

init(){
	add_action("dig","dig");
	add_action("climb","climb");
	add_action("read","read");
	add_action("push","push");
	add_action("push","pull");
	add_action("push","move");
	add_action("push","kick");
	add_action("push","smash");
	add_action("open","open");
	add_action("close","close");
	add_action("enter","enter");
	add_action("enter","in");
	::init();
}
enter(str){
  if(str=="tomb"||str=="door"||str=="tomb door"||str=="stone tomb"){
    if(!tomb_door_status){
      write("The door is closed.\n");
      return 1;
    }
    this_player()->move_player("into the tomb#/room/cemetary/tomb");
    return 1;
  }
}
dig(){
	write("You dig for awhile. Nothing here.\n");
	return 1;
}
climb(str){
	if(str != "fence") return 0;
	write("The fence is to high to climb.\n");
	return 1;
}
door(){
  if(!tomb_door_status){
    write("The door is closed.\n");
    return 1;
  }
  write("The door is open.\n");
  return 1;
}
open(str){
  if(str=="door"||str=="huge door"){
    if(!pushed){
      write("The door seem impossible to move.\n");
      say(this_player()->query_name()+" struggles with the tomb door, but fails to open it.\n");
     return 1;
    }
    if(!tomb_door_status){
      write("Ok. With great effort you open the huge door.\n");
      say(this_player()->query_name()+" opens the tomb door.\n");
      tomb_door_status = 1;
      return 1;
    }
    write("It is already opened.\n");
    return 1;
  }
}
close(str){
  if(str=="door"||str=="huge door"){
    write("The door seems to be stuck, you cant close it.\n");
    return 1;
  }
}
push(str){
  if(str=="stones"||str=="smooth stones"||str=="stone"||str=="smooth stone"){
    write("Ok. You hear a click from the door.\n");
    say(this_player()->query_name()+" pushes a stone on the side to it's right position.\n");
    say("There is a click from the door.\n");
    pushed = 1;
    return 1;
  }
}
stones(){
  write("One of the stones of the side is smoother than the rest of the stones.\n"+
	"It looks like it is possible to move it somehow.\n");
  if(!pushed) return 1;
  write("It is pushed in.\n");
  return 1;
}
    
text(){
  say(this_player()->query_name()+" read a small inscription.\n");
  write("Sealed on the 6th of august 1972.\n");
  return 1;
}
read(str){
  if(!str=="inscription") return 0;
  text();
  return 1;
}
tomb(){
  write("The big tomb is completely made of stone.\n"+
	"Some of the stones on the side of the tomb looks strange.\n"+
	"There is a small inscription on the front of the tomb.\n");
  if(!tomb_door_status){
    write("The huge door on the tomb is closed.");
    write("\n");
    return 1;
  }
  write("The door to the tomb is open. You can enter the tomb.\n");
  return 1;
}
    
  
