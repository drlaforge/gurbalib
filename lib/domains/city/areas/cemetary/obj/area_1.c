#include <def.h>
#include <tune.h>

#define DEST "/domains/areas/city/abacus/room/west_street1"


void setup(void)
{
    object qst;
    string dest_dir;

    dest_dir = DEST->query_dest_dir();
    DEST->affect_long(this_object());
    this_object()->move(DEST);
    DEST->add_exit("nnorth","domains/city/areas/cemetary/rooms/ent");
    DEST->update_actions();
}

affect_environment()
{
  write("West you can hear clashings of pans and what not.\n");
}




