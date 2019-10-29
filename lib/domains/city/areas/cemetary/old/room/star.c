
inherit "room/room";

int amulet,placed,chest,chest_status;
reset(arg) {
  placed = 0;
  chest = 0;
  amulet = 0;
    long_desc = 
        "You stand in a quite large chamber in the underground.\n"
        + "The room is full of cobwebs, and the only thing in the room \n"
        + "is a pedestal that is located in the middle of the room.\n";
    dest_dir = ({
        "/room/cemetary/coffin_end", "south",
        });
    items = ({
      ({ "chamber" , "large chamber" }),
      "It looks that noone has been here in ages. Cobwebs in the corners",
      ({ "star shaped hole" , "hole" }), "It is shaped like a star",
      ({ "corners" , "cobwebs" , "webs" , "web" }),
      "You look around at the web, but you cannot seem to find the spider",
      "pedestal","#pedestal"
          });
    if (arg) return;

    set_outdoors(0);
    set_light(0);
    short_desc = "the room of the star";
    
}
init(){
  ::init();
    add_action("place","place");
    add_action("place","put");
    add_action("place","use");
    add_action("place","insert");
    add_action("open_chest","open");
    add_action("close_chest","close");
    add_action("take","take");
    add_action("take","get");
  }

place(str){
object ob;
  if(str=="star on pedestal"||str=="star on top of pedestal"||str=="star in hole"||str=="star"){
    if(ob=present("star",this_player())){
      write("You put the star in the pedestal.\n");
      say(this_player()->query_name()+" puts a star on top of the pedestal.\n");
      destruct(ob);
      call_out("bullet",2);
      return 1;
    }
  }
}
bullet(){
  write("Suddenly the pedestal lowers into the ground and a chest comes up instead.\n");
    long_desc = 
        "You stand in a quite large chamber in the underground.\n"
        + "The room is full of cobwebs, and the only thing in the room \n"
        + "is a chest on the middle of the room.\n";
    dest_dir = ({
        "/room/cemetary/coffin_end", "south",
        });
    items = ({
      ({ "chamber" , "large chamber" }),
      "It looks that noone has been here in ages. Cobwebs in the corners",
      ({ "corners" , "cobwebs" , "webs" , "web" }),
      "You look around at the web, but you cannot seem to find the spider",
      "chest","#chest",
      "bones","#bones",
          });
  chest = 1;
  chest_status = 0;
  return 1;
}
pedestal(){
  if(!placed){
    write("The pedestal has a star shaped hole on top of it.\n");
    return 1;
  }
}
chest(){
  if(chest_status) write("The chest is opened.\nThe chest contains some bones.\n");
  else write("The chest is closed.\n");
  return 1;
}
open_chest(str){
  object snake;
  int i,lvel;;
  if(!chest) return 0;
  if(str!="chest") return 0;
  if(chest_status){ write("The chest is already opened.\n"); return 1; }
  chest_status = 1;
  write("You open the chest. Slimy snakes starts to crawl out of it.\n");
  say(this_player()->query_name()+" opens the chest. Slimy snakes starts to crawl out of it.\n");
  for(i=0; i-5; i++){
    snake = clone_object("/obj/monster");
    snake->set_name("snake");
    snake->set_alias("snake");
    lvel = random(1+(6));
    if(lvel < 7) snake->set_short("a huge snake");
    if(lvel < 4) snake->set_short("a big snake");
    if(lvel < 2) snake->set_short("a small snake");
    snake->set_level(lvel);
    snake->set_long("This is "+snake->short()+". It looks quite dangerous.\n");
    snake->set_aggressive(random(2));
    move_object(snake,this_object());
  }
  return 1;
}
close_chest(str){
  if(!chest) return 0;
  if(str!="chest") return 0;
  write("The chest seems impossible to close again.\n");
  return 1;
}
bones(){
  write("You see the bones of someone.\n");
  if(amulet) return 1;
  write("There is an amulet on the bones.\n");
  return 1;
}
take(str){
  object amu;
  if(amulet) return 0;
  if(!chest_status) return 0;
  if(!chest) return 0;
  if(str=="amulet"||str=="amulet from bones"){
    write("Ok.\n");
    say(this_player()->query_name()+" takes something from the chest.\n");
    
    amu = clone_object("/obj/armour");
    amu->set_name("amulet");
    amu->set_short("a silver amulet");
    amu->set_long("An amulet made of silver. With a flying eagle on the front of it.\n");
    amu->set_type("amulet");
    amu->set_class(5);
    amu->set_value(100+random(50));
    amu->set_weight(1);
    if(transfer(amu,this_player())){ write("You cant carry it so you drop it on the floor.\n"); move_object(amu,this_object()); }
    amulet = 1;
   return 1;
  }
}


