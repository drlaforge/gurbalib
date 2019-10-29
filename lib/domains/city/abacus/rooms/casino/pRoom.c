
inherit ROOM+"casino/stdroom.c";

void setup(){
    
    
   set_light(1);
   set_outdoors(0);
   set_short("Andre's Casino: Poker Room");
   set_long_f("As soon as you enter the room you begin to cough; the cigar smoke is choking. "+
      "As your eyes adjust to the hazy conditions you see a room full of Video Poker machines "+
      "with many old men sitting, spitting and cursing at them. Luckily for addicts like you "+
      "there seems to be an open machine right in front of you. To the west you can hear the "+
      "cheers from the Roulette game\n", 78);
   add_object(ROOM+"casino/poker.c", 1);
   add_exit("west", ROOM+"casino/sRoom");
}

