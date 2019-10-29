/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h" 

void setup(void) {
   /*set_outdoors(1); */
   set_light(1); 
   set_short("In front of the old cryogenic center");
   set_long(
      "The main road here looks in better condition here than in "+
      "many other parts of the city. Most of the potholes have been "+
      "filled, and it looks as though someone has completely renovated "+
      "the building to the north. There is a large plaque above the "+
      "entrance suggesting that this place served a very important "+
      "function to the welfare of the citizens. However, it is showing "+
      "signs of wear, as though it has been abandonded once again.\n");
   set_exits((["east" : ROOMS+"west_street2",
         "west" : ROOMS+"west_street4"]));
   add_item("potholes","road","main road","The potholes have been filled here.");
         add_item("building","north","The building was renovated, then abandoned.");
         add_item("plaque","large plaque","You could read it!");
         add_item("entrance","There seems to be no way in now.");
         add_item("wear","The building has been abandoned.");
   add_action("read_it","read");
}


int read_it(string str){
   if(str=="plaque"||str=="large plaque"){
      write("CryoCorp Cloning Facilities - A Subsidiary of Dragon Industries.\n");
      return 1;
   }
   return 0;
}

