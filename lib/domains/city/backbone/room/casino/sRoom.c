
inherit ROOM+"casino/stdroom.c";

void setup(){
    
    
   set_short("Andre's Casino");
   set_light(1);
   set_outdoors(0);
   set_long_f("You have wandered into a small and tightly packed casino room. There's not "+
      "much here. Just gaming -- no waitresses, drinks, no hookers, or any of the other "+
      "shit like that. Just gambling. Why don't you go "+
      "blow money on some of the games. In front of you are a row of slot machines, to the north is Roulette, Blackjack to the west "+
      "and Poker to the east. The stairs down are to your south.", 80);
   add_exit("east", ROOM+"casino/pRoom");
   add_exit("west", ROOM+"casino/bRoom");
   add_exit("northwest", ROOM+"casino/baRoom");
   add_exit("north", ROOM+"casino/rRoom");
   add_exit("south", ROOM+"casino/lobby", "#preSouth");
   add_object(ROOM+"casino/slot.c", 10);
}

int preSouth(){
  write("You walk down the stairs and out of the casino.\n");
  return 0;
}

