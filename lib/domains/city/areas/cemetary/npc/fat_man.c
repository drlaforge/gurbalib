inherit "obj/walkingmonster";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
add_object(CEMETARY+OBJ+"rifle",1,"wield rifle");
add_object("/obj/obj/exp_flashlight");
add_object(CEMETARY+OBJ+"overcoat",1,"wear overcoat");
set_level(4);
set_name("man");
set_id("stocky man");
set_id("dirty, stocky man");
set_short("a stocky man");
set_gender(1);
set_long_f("A dirty, stocky man.\n",FORMAT);
load_chat(6,({"The stocky man hawks up something in his throat.\n#light",
  "The stocky man spits a big ass loogy into the grass.\n#light"}));
set_kill_shout("I killed that dirty bastard #N.");
set_walking(35+random(5));
setmout("The stocky man struts #D hick-style");
setmin("The stocky man struts in hick-style");
set_light(1);
set_mass_defend(1);
}

init()
{
::init();
add_action("cmd_dig","dig");
}

cmd_dig(str)
{
if(!present("shovel",this_player()))
  return 0;
tell_room(environment(),"The stocky man yells: Oh no you don't, you fucking freak.\n");
attack_object(this_player());
return 1;
}
