
inherit ROOM+"casino/stdroom.c";

void setup(){
    
    
   set_light(1);
   set_outdoors(0);
   set_short("Andre's Casino: Blackjack Room");
   set_long_f("This room resembles the one you just came from - very "+
      "bland, empty, and packed. Here it seems that blackjack is the game "+
      "of choice. To your east is the main room of the casino housing the "+
      "slot machine addicts.\n", 78);
   add_object(ROOM+"casino/blackjack.c", 1);
   add_exit("north", ROOM+"casino/baRoom");
   add_exit("east", ROOM+"casino/sRoom");
}

