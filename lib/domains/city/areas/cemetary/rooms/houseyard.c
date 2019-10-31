
inherit "room/room";

reset(arg) {
    if(!present("grave",this_object()))
      move_object(clone_object("/domains/areas/city/cemetary/obj/grave"),this_object());
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
        "/domains/areas/city/cemetary/room/housekitch", "south",
        });
}

init(){
  add_action("read","read");
  ::init();
}
read(str){
	if(str!="tombstone") return 0;
	write("You read on the tombstone:    R.I.P\n");
	write("                           Cliff Burton.\n");
	return 1;
}

