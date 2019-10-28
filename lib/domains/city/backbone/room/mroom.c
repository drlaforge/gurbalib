inherit "std/room";
#include "../area.h"

object bottle;
int max_bottle;

void setup(void) {

  max_bottle = 40;

   

  set_light(1);
  set_outdoors(0);
  short_desc = "A store room in the narrow alley";
  long_desc = 
    "You're standing in a very shabby room.\n"+
    "You can buy some molotov cocktail bottles in here.\n"+
    "Type 'buy bottle #' where # is the size in liters.\n"+
    "The maximum size is 10. The price is 'liters' * 20.\n"+
    "The bottle is empty, you need to fill it your self.\n";
  dest_dir = ({"players/ledough/alley/mroad3","north",});
}

init() {
  ::init();
  add_action("buy","buy");
}

buy(str) {
  int liters;
  string what;
  if(!str) 
    return 0;

  if(sscanf(str,"%s %d",what,liters) != 2)
    return 0;

  if(what!="bottle" && what!="molotov" && what!="cocktail") {
    write("The only thing sold here is molotov bottles.\n");
    return 1;
  }
  if(liters < 0) {
    write("Come on. Looking for bugs?\n");
    command("blush",this_player());
    return 1;
  }
  if(liters > 10) {
    write("The largest bottle is a 10 liter bottle. That's the limit.\n");
    return 1;
  }
  if(!max_bottle) {
    write("Sorry... We're out of bottles. Please come back later.\n");
    return 1;
  }
  if(this_player()->query_money() < (liters * 20)) {
    write("A molotov "+liters+" would cost you "+liters*20+" which you don't have.\n");
    return 1;
  }
  bottle = clone_object("players/ledough/obj/molotov");
  if(!bottle) {
    write("Ledough says: Uh oh! A little bug here...\n");
    write("Ledough says: The bottle file is missing.\n");
    this_player()->add_money(liters*20);
    write("Ledough gives the "+liters*20+" dollars back to you.\n");
  }
  if(move_object(bottle,this_player())) {
    write("It's too heavy for you now. You can't carry anymore.\n");
    return 1;
  }
  this_player()->add_money(-(liters*20));
  write("You just got your self a "+liters+" liters bottle.\n");
  say(this_player()->query_name() + " bought a molotov bottle.\n");
  bottle->set_tank(liters);
  max_bottle--;
  if(!max_bottle) 
    tell_room(this_object(),"That was the last bottle...\n");
  return 1;
}


