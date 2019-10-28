inherit "std/room";
#include "../area.h"

void setup(void) {
  if(arg) 
    return;

  set_outdoors(0);
  set_light(1);
  
  short_desc = "Dark Alley Gang integration";
  long_desc =
    "You're standing in a very filthy room.\n"+
    "There is a man sitting in a sofa, picking his nails with a knife.\n"+
    "You can see some dirty magazines lying on the floor.\n"+
    "A sign is nailed on the eastern wall.\n";
  dest_dir = ({"players/ledough/alley/east_end","down",});
}

init() {
  ::init();
    add_action("exa","exa",1);
    add_action("look","look");
    add_action("exa","read",1);
    add_action("build","build");
}

look(str) {
  if(str=="at man" || str=="at sofa") {
    write("The old man in the sofa looks at you thoroughly as you examine him.\n");
    return 1;
  }
  if(str == "at magazines") {
    write("The old man says: Hey! Don't you touch my mags!!\n");
    return 1;
  }
  if(str == "at sign") {
    write("If you want to build a cool gang, just type <build>\n");
    return 1;
  }
}

exa(str) {
   return look("at "+str);
}

build() {
  object ob;
  ob = this_object();
  if(this_player()->query_cha() < 10) {
    write("Geez! You're too ugly to be a leader... Pick someone else!\n");
    return 1;
  }
  tell_room(ob,"The man says: So you wanna form a gang for fighting, eh?\n");
  tell_room(ob,"The man says: Well, fine with me!\n");
  ob = clone_object("players/ledough/alley/gang");
  move_object(ob,this_player());
  write("The man hands you a paper, and after you sign he grins evilly.\n");
  write("The man says: Just examine gang and you'll know how to do.\n");
  return 1;
}
