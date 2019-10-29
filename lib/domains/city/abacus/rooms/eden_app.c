inherit "std/room";
#include "../area.h"
#include <def.h>
#include <tune.h>
object berne;
void setup(void){
    
    
   add_object("/obj/monsters/zoltan");
   set_light(1);
   set_outdoors(0);
  set_short("strange appartment");
   set_long_f("You're in a medium sized appartment. However, there is no bed and the room is dominated by a large "+
      "workbench in the centre of the room. Around the walls are various schematics and plans as though someone is "+
      "building something in here. The door is bolted and locked in several places leaving the only means of escape "+
      "to be a single window which is half covered by curtains that blow in a slight breeze.\n");
   add_item_f(({"appartment",ROOM+""}),"The appartment is quite dingy and dark with only a single light bulb hanging from the ceiling.");
   add_item_f(({"light","light bulb","bulb"}),"A single light bulb that illuminates the room.");
   add_item_f(({"workbench","bench"}),"The bench is covered in all sorts of electronics and circuitry.");
   add_item_f(({"electronics","circuitry"}),"Tiny complicated circuits, someone must be making something here.");
   add_item_f(({"schematics","plans","schematic"}),"They're really complicated, but it looks like some kind of helmet.");
   add_item_f(({"wall","walls"}),"The walls are covered in plans and schematics.");
   add_item("door","The door is bolted and locked.");
   add_item_f(({"bolts","bolt","locks","lock"}),"The door has many locks and bolts on it as though the occupant doesn't want to be disturbed.");
   add_item_f("window","The window exits to the street a couple of floors below.\n");
   add_item_f(({"curtain","curtains"}),"The curtains are blowing in the breeze from the open window.");
   add_item_f("breeze","You use your super-molecule-eyes to see the atoms moving caused by the pressure differences in the... "+
      "In fact you don't because you don't have super-molecule-eyes and YOU BREEZE IS INVISIBLE! Sheesh, it's people like you "+
      "that make writing descriptions take ages because you look at too much stuff that we have to laboriously make up descriptions "+
      "for. I even had to take time to look up how to spell 'laborious'! You're killing me!!!");
   add_exit("window",ROOM+"eden7","#my_out");
}

my_out(){
   action("#NA ## of the window to the street below.","jump-jumps");
   TP->reduce_hit_point(10);
   return 0;
}
