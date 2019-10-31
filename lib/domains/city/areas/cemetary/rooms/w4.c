
inherit "room/room";

int found;
reset(arg) {
object woman;
object ring;
found = 0;
if(!present("woman",this_object()))
{
woman = clone_object("/obj/monster");
woman->set_name("woman");
woman->set_race("nightbreeder");
woman->set_alias("nightbreeder");
woman->set_short("a nightbreeder woman");
woman->set_level(2);
woman->set_gender(2);
woman->set_long("She looks very sad about something.\n"+
                "She got a quite nice face, but the rest of her body is very odd shaped.\n"+
               "She is wearing a small bronze ring on one of her seven fingers.\n");
woman->load_chat(10,({
                "The woman says: My boy went down some days ago and hasnt returned yet.\n",
               "The woman says: Please help me find him!\n",
                      "You can see tears in the woman's eyes.\n",
               }) );
ring = clone_object("/obj/armour");
ring -> set_name("ring");
ring -> set_type("ring");
ring -> set_ac(5);
ring -> set_short("a small bronze ring");
ring -> set_long("A small bronze ring. There is a symbol of a flying eagle\n"+
                 "on the front of it.\n");
ring ->set_value(120);
ring ->set_weight(1);
move_object(ring, woman);
move_object(woman,this_object());
woman->init_command("wear ring");
}
woman = present("woman",this_object());
if(woman)
woman ->load_chat(15,({
      "The woman says: My boy went down some days ago and hasn't returned.\n",
      "The woman says: Please help me find him!\n",
      "You can see tears in the womans eyes.\n",
   }));
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeder tunnels";
    
    long_desc = 
        "You stand in a small tunnelsystem. The tunnels continue east\n"
        + "and with a ladder downwards.\n";
    dest_dir = ({
        "/domains/areas/city/cemetary/room/w3", "east",
        "/domains/areas/city/cemetary/room/d1", "down",
        });
    items = ({
              "ladder",
              "The ladder is made of wood and looks quite sturdy. The ladder leads down.",
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

foo(){
object woman;
if(!present("woman",this_object())) return 0;
woman = present("woman",this_object());
woman->load_chat(20, ({
       "The woman smiles at you.\n",
       "The woman whistles something merry.\n",
       }) );
}
