inherit "std/room";
#include "../area.h"
void setup(void) {
    
   set_light(1);
   set_outdoors(1);
   short_desc =
   "Surfer's Island";
   long_desc =
   "You are standing on a small jetty that leads out over the sea. You\n"+
   "can see an automatic ticket booth here that dispenses tickets for\n"+
   "the boat that travels between here and the mainland.\n";
   items_arr = ({
         ({"jetty","short jetty"}),
         "The jetty is made from wooden planks nailed onto a supporting structure\n"+
         "that is hidden from view by the murky water. The planks creak as you walk\n"+
         "on them, but they seem sturdy enough to hold you",
         ({"plank","planks","wooden planks","wood"}),
         "The planks look old and worn, but strong enough to hold your weight",
         ({"nail","nails"}),
         "The nails in the planks are old and rusty",
         "rust",
         "It is rust",
         ({"support","supports","structure","supporting structure"}),
         "The supporting structure is hidden from view by the murky water beneath you",
         ({"water","murky water"}),
         "It is murky water",
         ({"booth","ticket booth","end","end of jetty","end of the jetty"}),
         "The ticket booth is a fully automatic device for selling tickets.\n"+
         "All you need to do is have $10 ready and press the button on the\n"+
         "front of the booth",
         ({"front","front of the booth"}),
         "The front reads 'KryTech Boothomatic Ticket Dispensor'\n"+
         "                'Please 'press button' to recieve a ticket'\n"+
         "There is a button here to press",
         ({"button","red button"}),
         "The button is round, red, and has 'PRESS' written on it",
         });

}
init() {
   :: init();
   add_action("press","press");
   add_action("buy","buy");
}

press(arg) {
 if(arg=="button" | arg=="red button") 
  {
   write("A voice beeps: The boat has sunk, alternative arrangements have been made.\n");
   return 1;      
  }
 write("What was that again?\n"); 
 return 1;
}

buy(arg) {
   if(arg=="ticket") {
      this_object()->press("button");
      return 1;
   }
   else
   {
      notify_fail("Buy what?\n");
      return 0;
   }
}
