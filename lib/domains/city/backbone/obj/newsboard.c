#include "../backbone.h"
inherit "/obj/SciBoard";
void setup(void){
    
    
   SetShort("the News board");
   SetDir("/boards/News/");
   SetLong("The News board with all the latest official gossip.\n");
   SetAllowPseudo(1);
   SetAccessLevel(ARCH_LEVEL);
}
