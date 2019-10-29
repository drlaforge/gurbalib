inherit "room/room";

reset(arg) 
{
  if (arg) return;

  set_light(1);
  set_outdoors(1);
  short_desc = "cemetary";
  
  long_desc = 
      "You stand in a cemetary. There are more bushes here and the grass is\n"
    + "much more wildgrown than south of here. There are some tombstones here.\n"
    + "There is a big hole in the ground here, probably from an unfinished\n"
    + "dug grave. To the east there is a large bunker.\n";
  /* - Taken out from long_desc 940609 - Warlord
       To the east there is a large bunker.\n";
     - Put back in 960902 - Aladdin,Wishbone
   */

items = ({
	"grass","It's very wildgrown.It must have been a long time since anyone was here",
	"bushes","These bushes grows wildly here",
	"cemetary","You stand on the east side of the cemetary",
	"tombstones","You notice nothing special",
	"tombstone","You notice nothing special",
	"hole","The hole looks quite deep",
	"grave","The grave looks quite deep",
	"bunker","The famous Domination Control Bunker",
	});
    dest_dir = 
        ({
        "/room/cemetary/cem12", "north",
        "/room/cemetary/cem6", "south",
        "/room/cemetary/cem8", "west",
        "/room/cemetary/hole", "down",
	"/players/miko/scav/dcE", "east",
     });
     /* - Taken out from dest_dir 940609 - Warlord
          "/players/miko/scav/dcE.c","east",
        - Put back in 960902 - Aladdin,Wishbone
      */
}

init(){
  ::init();
	  add_action("no_pass","down");
}
no_pass()
{
  if(this_player()->query_exp() > 5000){
  write("You cannot go down. You feel too experienced for that hole.\n");
  return 1;
  }
}

