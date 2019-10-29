/* ROOMMAKER..  Modified by Thorwald. */

inherit "room/room";
int free;

reset(arg) {
    if (arg) return;
    free = 0;

    set_outdoors(0);
    set_light(1);
    short_desc = "attic in a house in a cemetary";
    
    long_desc = 
        "You stand in the attic of the house. On the floor there is a\n"
        + "red painted pentagram. Looking closer at it you see that it is\n"
        + "made by blood and it is still fresh.\n";
items = ({
	"attic","It's not so dark in here. There are some cracks in the ceiling letting light in",
	"cracks","Nothing special about them"
	,"pentagram","It painted in blood, and has a hole at its center",
	"hole","A small hole - looks like something should be inserted.",
	"blood","You taste it. It is still warm"
	,"floor","It looks sturdy",
	});
    dest_dir = 
        ({
        "/domains/areas/city/cemetary/room/house", "down",
        });
}

init()
{
  ::init();
 add_action("stick_it_in","insert");
}

stick_it_in(str)
{
 int crystal;
 crystal = (present("crystal",this_player()));
 if(!str || (str != "crystal"))
 {
    notify_fail("Insert what?\n");
    return 0;
 }
 
   if(crystal)
    {
	if(free)
	 {
	  write("You ram the crystal home, but nothing happens.\n");
	  return 1;
	 }
     writef("You ram the crystal into the center of "+
	"the pentagram. The whole house shakes... "+
	"You hear a cheer from outside, and see about "+
	"a dozen people fleeing the house into the "+
	"cemetary!  You have solved the mystery and freed "+
	"the victims! (And they would have got away with it "+
	"if it wasn't for you pesky kids)\n");
   free = 1;
   destruct(crystal);
	if(this_player()->query_quests("cemetary"))
	 {
	  write("You've saved these before - you must really care!\n");
	  return 1;
	 }
	else
	 {
	  this_player()->set_quest("cemetary");
	  this_player()->add_exp(10000);
	  return 1;
	 }
      return 1;
     }
    write("You don't have a crystal to insert!\n");
    return 1;
}
  

