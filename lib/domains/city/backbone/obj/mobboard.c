#include "../backbone.h"
inherit "/obj/board";
void setup(void){
    
    
   set_max_notes(60);
   set_save_path("boards/bulletin");
   set_short("the MOB board");
   set_delete_level (ARCH_LEVEL-1);
   set_show_levels(ROOKIE_LEVEL-1);
   set_arch_path("boards/archive/main");
   set_archive(1);
   set_new_level(3);
   set_new_fail("You're still a little too inexperienced for anyone to care what you have to say.\n");
}
