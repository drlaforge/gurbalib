
inherit "room/room";

reset(arg) {
object boy;
if(!present("boy",this_object()))
{
boy = clone_object("/obj/monster");
boy->set_name("boy");
boy->set_race("nightbreeder");
boy->set_short("a small nightbreeder boy");
boy->set_long("This is a very young nightbreeder boy.\n"+
              "He is giggeling at things in the room.\n");
boy->set_level(1);
boy->set_hp(15);
boy->set_alias("nightbreeder");
boy->load_chat(15,({
    "The boy points at you and starts to giggle.\n",
    "The boy plays around with the hay.\n",
    "The boy coughs when he tries to eat some mud, and then starts to laugh.\n",
    }) );
move_object(boy,this_object());
}
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeder home";
    
    long_desc = 
        "You stand in a small home of a nightbreeder family.\n"
        + "There is hay on the floor and a small table in the middle of the room.\n";
    dest_dir = ({
        "/domains/areas/city/cemetary/room/w2", "south",
        });
    items = ({
              "hay",
              "The hay is strewn all over the floor. Probably nightbreeders sleep on it",
              "table",
              "The table is simply made of wood. There is a small note on it",
              "note",
              "The note is made of paper, and the writing looks like it is made of coal.\n"+
              "It is very poor handwriting but you might be able to read it",
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

init(){
  ::init();
  add_action("read","read");
}
read(str){
  if(str!="note") return 0;
  write("The note says: I am going to explore the mines.\nI'll be back tonight.\n");
  return 1;
}
