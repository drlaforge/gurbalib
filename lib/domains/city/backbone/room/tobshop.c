inherit "std/room";
#include "../area.h"

object joss,matt,ob;
int pop,candy;

void setup(void) {
  if(!joss){
    if(random(3)){
      joss=clone_object("/obj/monsters/joss.c");
      move_object(joss,this_object());
      tell_room(ROOM+"tobshop","Joss arrives and opens the store.\n");
      if(ob=present("matt")){
	"/std/object/dest_inv"->dest_inv(ob);
	destruct(ob);
	tell_room(ROOM+"tobshop","Matt leaves for home.\n");
      }
    }
    else{
      if(!matt){
	matt=clone_object("/obj/monsters/matt.c");
	move_object(matt,this_object());
      }
    }
  }
  else{
    if(!random(2)){
      tell_room(ROOM+"tobshop","Joss closes the store and goes home.\nMatt arrives with his mop and Joss gives him some instructions.\n");
      "/std/object/dest_inv.c"->dest_inv(ob=present("joss"));
      destruct(ob);
      matt=clone_object("/obj/monsters/matt.c");
      move_object(matt,this_object());
    }
  }
  candy=40;
  pop=10;
  
   
  set_outdoors(0);
  set_light(1);
  short_desc = "Small tobacco shop";
  
  long_desc = 
    "You are in a tobacco shop that once sold a vast array of tobacco products,\n"
  + "snacks and magazines. Today however, it only sells candy, soft drinks\n"
  + "and some cigarettes. Behind a small counter in the far end of the room\n"
  + "there is a price list.\n";

  dest_dir = ({ 
    ROOM+"pub_vet", "south",
  });

  items_arr = ({
    ({"candy","tobacco","cigarettes","soft drinks"}),
    "Some goodies for sale. Look at the price list behind the counter",
    ({"list","price list"}),
    "A price list behind the counter:\n"+
    "---------------------------------------\n"+
    "   Tobacco products:\n\n"+
    "   Davidoff Cigarilles   - 400 dollars.\n\n"+
    "   Soft drinks:\n\n"+
    "   Pepsi Cola            -  80 dollars.\n"+
    "   Zingo                 - 120 dollars.\n\n"+
    "   Candy:\n\n"+
    "   Snickers              -  50 dollars.\n"+
    "   Baberuth              -  75 dollars",
    ({"counter","small counter"}),"A small counter made of dark wood. There is a price list on the wall behind it",
  });
}

init() {
  ::init();
    add_action("read","read");
    add_action("order","buy");
    add_action("order","order");
}

read (str) {
  if (str=="list" || str == "price list"){
    command ("exa list",this_player());
    return 1;
  }
}

order (str) {
  if(joss){
    if(joss->query_attack()){
      write("Joss is in combat and can't help you now.\n");
      return 1;
    } 
    if (!str)
      return reply ("What do you want to order?");
    
    if (lowercase(str) == "snickers"){
      buy_candy (lowercase(str),"a",50,5,"snickers");
      return 1;
    }
    if (lowercase(str) == "baberuth"){
      buy_candy (lowercase(str),"a",75,7,"baberuth");
      return 1;
    }
    if (lowercase(str) == "cigarilles" || lowercase(str) == "davidoff"){
      if(this_player()->query_level()>19){
	return buy_cigarilles("davidoff");
      }
      return(write("These cigarilles are too strong for you kid.\n"));
    }
    if (lowercase(str) == "cola" || lowercase(str) == "pepsi"){
      buy_drink("pepsi",10,6,80,"cola");
      return 1;
    }
    if (lowercase(str) == "zingo"){
      buy_drink("zingo",15,8,120,"Zingo");
      return 1;
    }
    return reply ("No such item on the price list.");
  }
  else if(matt) return(write("Joss is not here right now, the shop is closed!\n"));
  else write("But there is no one in the shop!\n");
  return 1;
}

buy_cigarilles(name) {
  object ob;
  if(name=="davidoff"){
    ob=clone_object("/std/object/cigarillbox");
    if (move_object(ob,this_player())) { 
      destruct (ob);
      return reply ("You can't carry more.");
    }
    if (!this_player()->add_money(-400)) {
      destruct(ob);
      return reply ("You can't afford that.");
    }
    return reply("I hope you will enjoy these Davidoff cigarilles.\nYou pay $400 for them.");
  }
}

buy_candy (name, art, price, heal, alias) {
  object ob;
  if(!candy) return(write("Joss says: I am sorry, I am out of that.\n"));
  ob=create_candy(name, art, price, heal, alias);
  if (move_object(ob,this_player())) { 
    destruct (ob);
    return reply ("You can't carry more.");
  }
  if (!this_player()->add_money(-price)) {
      destruct(ob);
      return reply ("You can't afford that.");
  }
  candy--;
  return reply("Thanks, and welcome back!\nYou pay "+price+" for the "+capitalize(name)+".");
}

buy_drink (name, heal, strength, price, alias) {
  object ob;
  if(!pop) return(write("Joss says: I am sorry, I am out of that.\n"));
  ob=create_drink(name, heal, strength, price, alias);
  if (move_object(ob,this_player())) { 
    destruct (ob);
    return reply ("You can't carry more.");
  }
  if (!this_player()->add_money(-price)) {
    destruct(ob);
    return reply ("You can't afford that.");
  }
  pop--;
  return reply("Thanks, and welcome back!\nYou pay "+price+" for the "+capitalize(name)+".");
}

create_candy(name, art, price, heal, alias) {
  object ob;
  ob = clone_object("obj/food");
  ob->set_name(name);
  if (alias) ob->set_alias(alias);
  ob->set_short(capitalize(art)+" "+name);
  ob->set_heal(heal);
  ob->set_full_value(price/2);
  ob->set_weight(1);
  ob->set_consumer_mess("Yum Munch Shmack, really good!\n");
  return ob;
} 

create_drink(name, heal, strength, price, alias) {
  object ob;
  ob = clone_object("obj/soft_drink");
  ob->set_name(name);
  if (alias) ob->set_alias(alias);
  ob->set_short("A "+capitalize(name));
  ob->set_heal(heal);
  ob->set_strength(strength);
  ob->set_full_value(price/2);
  ob->set_weight(1);
  ob->set_consumer_mess("You drink a "+capitalize(name)+".");
  ob->set_empty_container("can");
  ob->set_alt_name("can");
  return ob;
} 

reply (str) {
  write("Joss says: " + str + "\n");
  return 1;
}
