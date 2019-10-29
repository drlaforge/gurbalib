
inherit "room/room";

reset(arg) {
  if(arg) return;
    set_outdoors(0);
    set_light(1);
    short_desc = "a backyard of a cemetary house";
    
    long_desc = 
        "You stand on the backyard of the house. There is a tombstone standing here.\n"
	+ "The only possible exit is to the south to a house.\n";
items = ({
	"tombstone","The tombstone looks very new. There is something written on it",
	});
    dest_dir = 
        ({
        "/room/cemetary/housekitch", "south",
        });
}

init(){
  add_action("dig","dig");
  add_action("read","read");
  ::init();
}
dig(){
  write("You dig for a while and find a coffin.\n"+
	"You open the coffin and see a rotten corpse.\n"+
	"The sight is so disgusting you start to throw up.\n"+
	"You puke.\n"+
	"You puke again.\n"+
	"You decide to cover the grave again.\n");
  say(this_player()->query_name()+" digs and suddenly starts to puke.\n"+
      "Then "+this_player()->query_pronoun()+" starts to cover the grave again.\n");
  return 1;
}
read(str){
	if(str!="tombstone") return 0;
	write("You read on the tombstone:    R.I.P\n");
	write("                           Cliff Burton.\n");
	return 1;
}

