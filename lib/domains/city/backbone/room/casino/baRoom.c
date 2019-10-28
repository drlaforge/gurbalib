
inherit ROOM+"casino/stdroom.c";

void setup(){
    
    
   set_light(1);
   set_outdoors(0);
   set_short("Andre's Casino: Baccarat Room");
   set_long_f("This is the Baccart room, a simple game of odds that brings "+
      "mathematicians and gamblers from all over, itching to make their millions. More often than "+
      "not however, they end up leaving as losers. Nothing else adorns this room, just the "+
      "Baccarat table in the center - beconing you. The slots are southeast from here, to the south "+
      "Blackjack and the Roulette room is to the east.");
   add_object(ROOM+"casino/baccarat2.c", 1);
   add_exit("east", ROOM+"casino/rRoom");
   add_exit("south", ROOM+"casino/bRoom");
   add_exit("southeast", ROOM+"casino/sRoom");
}

