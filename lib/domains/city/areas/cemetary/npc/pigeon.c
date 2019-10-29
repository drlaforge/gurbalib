inherit "obj/walkingmonster.c";
#include "../area.h"

reset (arg) {
   ::reset(arg);
   if (arg) return;
   set_name("pigeon");
   set_short ("a pigeon");
set_long_f("A greyish-blue pigeon.",FORMAT);
set_id("greyish-blue pigeon");
   set_level (1);
   set_walking(25);
   setmout ("A pigeon flies #D");
   setmin ("A pigeon flies in");
   
}
