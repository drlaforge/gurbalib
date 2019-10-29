
inherit "room/room";

object man;
int fallen;
reset(arg) {
  fallen = 0;
  if(!present("my_man",this_object()))
    {
      man = clone_object("/obj/monster");
      man->set_name("my_man");
      man->set_short("");
      man->load_chat(15, ({
	"You hear some strange sounds from the north.\n",
	"There sounds like digging from the north.\n",
      }) );
      move_object(man,this_object());
    items = ({ "wall","The wall is made by quite soft mud", }); 
    }
    long_desc = 
        "You stand in the mines of the nightbreeders.\n"
        + "The cave is very narrow all over in here and the caves seems\n"
	+ "to continue to the west.\n"
	+ "The wall to the north seems to have fallen in.\n";
    dest_dir = ({
        "/room/cemetary/d5", "west",
        });
    if (arg) return;

    set_outdoors(0);
    set_light(0);
    short_desc = "Nightbreeder mines";
    
}


init(){
  ::init();
    add_action("dig","dig");
  }
dig(str){
  if(!present("shovel",this_player())){
    write("You dont have a shovel.\n");
    return 1;
  }
  if(!fallen)
    {
      write("You dig for a while.\n");
      write("Suddenly a nightbreeder man comes out of the hole you made.\n");
      writef("The man says: Thanks for rescueing me! I thought I would "+
          "be trapped in there forever!\n",78,14);
      write("The man gives you some money.\n");
      write("The man hurries away west.\n");
      this_player()->add_money(100+random(40));
      say(this_player()->query_name()+" digs a hole.\n");
      say("Suddenly a man comes from the hole.\n");
      say("The man gives something to "+this_player()->query_name());
      say(".\n");
      fallen = 1;
      destruct(man);
    items = ({ "wall","The wall seems abit dug up. Nothing special",
	       "hole", "The hole is very small, and very little. There is nothing of interest",
	       }); 
    long_desc = 
        "You stand in the mines of the nightbreeders.\n"
        + "The cave is very narrow all over in here and the caves seems\n"
	+ "to continue to the west.\n"
	+ "The wall to the north has a hole in it.\n";
        "/room/cemetary/w4"->foo();
        return 1;
    }
write("You dig for a while, but find nothing of interest.\n");
return 1;
}


