inherit "room/room"; /* Hole with nothing. */
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_outdoors(1);
set_light(1);
set_short("A hole");
set_long_f(
  "The hole is a good two metres deep. "+
  "A skeleton is exposed at the bottom.",
  FORMAT);
items=({"skeleton","A bare skeleton.",});
set_no_clean_up(1);
}

my_add_exit(room)
{
add_exit("out",source_file_name(room));
update_actions();
}
