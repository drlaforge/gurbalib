inherit "obj/obj";
#include "../area.h"

int torches_left;

reset(arg)
{
::reset(arg);
torches_left=3;
if(arg)
  return;
set_light(1);
set_name("trashcan");
set_id(({"trashcan","burning trashcan","old burning trashcan","rusty old burning trashcan"}));
set_short("a burning trashcan");
set_long_f(
  "A rusty, old, burning trashcan, flames billowing from the inside. "+
  "A few pieces of trash protrude from the small inferno. "+
  "Try snatching one.",FORMAT);
}

init()
{
::init();
add_action("cmd_snatch","snatch"); /* Get your mind out of the gutter. */
}

cmd_snatch(str)
{
object torch;

if(str!="trash" && str!="piece of trash" && str!="piece")
    return 0;
if(torches_left<=0)
  return write("There are none left within reach.\n");
torch=clone_object(CEMETARY+OBJ+"trash_torch");
if(transfer(torch,this_player()))
  {
  destruct(this_object());
  return write("You have too much shit.\n");
  }
torches_left--;
torch->message_fun(this_player());
return 1;
}
