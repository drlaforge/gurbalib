#include "/domains/city/areas/cemetary/area.h"
#define DEST "/domains/city/abacus/rooms/church"
#define DIRECTION "north"
#define EXIT_ROOM CEMETARY+ROOM+"ent"
#define ENTRANCE_MSG "An empty doorway leads north into a cemetary.\n"

void create(void) {}

void setup(void)
{
  object ob;
  /*randomize_graves(); see below */
  if (empty_str(DEST->query_exit(DIRECTION)))
  {
    DEST->affect_long(ENTRANCE_MSG);
    this_object()->move(DEST);
    DEST->add_exit(DIRECTION, EXIT_ROOM);
/* Lib uses different quest implementation? I'm not sure.
    ob=clone_object("obj/quest_obj");
    ob->set_name("cemetary");
    ob->set_hint("A whole bunch of people have gone missing in the cemetary - find out why!\n");
    ob->set_qp(10);
    move_object(ob,"room/quest_room");
*/
  }
}

/*other rooms aren't live so we can't call them
randomize_graves()
{
int *graves;
int tmp,n;

n = 0;
graves=({3,6,7}); Corresponds to cem3.c, cem6.c, etc
while(sizeof(graves)>0)
  {
  tmp=random(sizeof(graves));
  (CEMETARY+ROOM+"cem"+graves[tmp])->set_grave(n);
  graves=exclude_array(graves,tmp);
  n++;
  }
}
*/

