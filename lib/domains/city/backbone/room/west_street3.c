/* Wishbone 12/96 */

inherit "std/room";
#include "../area.h" 

void setup(void) {
    
   
    
   set_outdoors(1); 
   set_light(1); 
   short_desc = "In front of the old cryogenic center";
   set_long_f(
      "The main road here looks in better condition here than in "+
      "many other parts of the city. Most of the potholes have been "+
      "filled, and it looks as though someone has completely renovated "+
      "the building to the north. There is a large plaque above the "+
      "entrance suggesting that this place served a very important "+
      "function to the welfare of the citizens. However, it is showing "+
      "signs of wear, as though it has been abandonded once again.\n");
   dest_dir = ({
         ROOM+"west_street2","east",
         ROOM+"west_street4","west",
         });
   items_arr = ({
         ({"potholes","road","main road"}),
         "The potholes have been filled here.",
         ({"building","north"}),"The building was renovated, then abandoned.",
         ({"plaque","large plaque"}),"You could read it!",
         "entrance","There seems to be no way in now.",
         "wear","The building has been abandoned.",
         });
}

void init(){
   ::init();
   add_action("read_it","read");
}

int read_it(string str){
   if(str=="plaque"||str=="large plaque"){
      write("CryoCorp Cloning Facilities - A Subsidiary of Dragon Industries.\n");
      return 1;
   }
   return 0;
}
