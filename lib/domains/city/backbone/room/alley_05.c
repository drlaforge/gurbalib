inherit "std/room";
#include "../area.h"

object ob;
object ob2;

init () {
  ::init();
  add_action ("enter","enter");
  add_action ("open","open");
}

void setup(void) {
  if (!ob) {
    ob=clone_object("/std/object");
    ob->set_name ("the box");
    ob->set_alias ("box");
    ob->set_short ("a large paper box");
    ob->set_weight (200);
    ob->set_long ("It's a really large paper box.\n"+
		  "You might even be able to enter it.\n");
    move_object (ob,this_object());
  }

     

    ROOM+"boxroom"->foo();  /* start the snoring */
    set_outdoors(1);
    set_light(1);
    short_desc = "in an alley";
    
    long_desc = 
        "You stand in an alley.\n"
        + "The alley stops to the south.\n";
    dest_dir = ({
        ROOM+"alley_04", "north",
        });
    items_arr = ({
          });
    add_sound ("box", "#boxing");
}

boxing () { 
  if (present ("sleeping man",find_object(ROOM+"boxroom"))) write ("You hear a snoring sound.\n"); return 1; 
}

enter (s) {
   if (!s || s!="box") { return 0; }
   if (!present ("box",this_object())) return 0;
   ob2=find_object (ROOM+"boxroom");
   if (ob2 && !present ("drunkard",ob2)) {
    write ("You look into the box, but realize it's empty.\n"); return 1; }
   this_player()->move_player("into the box#/room/boxroom");
   return 1;
}

set_chat (s,s2) {
   chats = ({ s,s2 });
}

open (s) {
  if (!s || s!="box") return 0;
  write ("It's already open.\n");
  return 1;
}

/* Used in One's area to move a guard here - Wishbone 9APR04 */
query_guard()
{
 if(present("guard",this_object()))
  {
   return 1;
  }
 else return 0;
}
