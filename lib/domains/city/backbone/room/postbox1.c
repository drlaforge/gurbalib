#include <def.h>
inherit STD_ROOM; 
#include "../area.h"

void setup(){
    
    
   add_object("/std/object/postbox.c",1);
   set_light(1);
   set_outdoors(0);
   set_short("The Parcel Room");
   set_long_f("This busy part of the post office allows you to send parcels to other "+
      "citizens. When you have an item that you need delivered to someone who is not "+
      "around right now, you can use one of the post boxes.\n");
   add_exit("down", ROOM+"post");
}
