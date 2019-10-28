#include <ansi2.h>
#define RED ESC+ANSICODES[COLOURS["RED"]]
#define BLUE ESC+ANSICODES[COLOURS["BLUE"]]
#define GREEN ESC+ANSICODES[COLOURS["GREEN"]]
#define RE ESC+ANSICODES[COLOURS["RESET"]]
#define CYAN ESC+ANSICODES[COLOURS["CYAN"]]
#define MAG ESC+ANSICODES[COLOURS["MAGENTA"]]
#define BOLD ESC+ANSICODES[COLOURS["BOLD"]]
#define ITALIC ESC+ANSICODES[COLOURS["ITALIC"]]
#define UNDERL ESC+ANSICODES[COLOURS["UNDERLINE"]]
#define FLASH ESC+ANSICODES[COLOURS["FLASH"]]

inherit "std/room";
#include "../area.h"

void setup(void){
   object poker,bj,roul;
   /*
   poker = present("machine",this_object());
   bj = present("table",this_object());
   roul = present("roulette",this_object());
   if(!roul){
      move_object(clone_object(ROOM+"casino/roulette"),this_object());
   }  
   
   if(!poker){
      move_object(clone_object(ROOM+"casino/poker"),this_object());
      if(!bj){
         move_object(clone_object(ROOM+"casino/blackjack.c"),this_object());
      }
      */
       
       
      set_short(CYAN+"The Lickin' Lips Lizard Lounge"+RE);
      set_light(1);
      set_outdoors(0);
      set_long_f(CYAN+"You have wandered into a small and tightly packed casino room. There's not "+
         "much here. Just gaming -- no waitresses, drinks, no hookers, or any of the other "+
         "really groovy things that World War III took away. Thinking about that just pisses you off. "+
         "And makes you want to blow money on some of the games. There is a large sign here that might be "+
         "worth examining."+RE);
   add_exit("east",ROOM+"eve_street1");
   add_item(({"large sign","sign"}),
      "STANDARD PRODUCTS GAMING accepts no responsibility for any losses.\n"+
      "A maximum of eight players can be accommodated at any one time on\n"+
      "our roulette table.\n"+
      "And if you're looking for the poker instructions, try 'read sign'.\n"+"\n"+
      "                       -- The Gaming Commission");
   
   
   
}



void init(){
   this_player()->move_player("to the real casino#room/casino/lobby");
}

