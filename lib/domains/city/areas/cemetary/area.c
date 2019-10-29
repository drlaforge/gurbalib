#include "/domains/areas/city/cemetary/area.h"
#define DEST "/room/church"
#define DIRECTION "north"
#define EXIT_ROOM CEMETARY+ROOM+"ent"

reset(arg)
{
  string dest_dir;
  object ob;
  if(arg) return;
  randomize_graves();
  dest_dir = DEST->query_dest_dir();
  if (dest_dir && member_array(DIRECTION, dest_dir) < 0)
  {
    DEST->affect_long(this_object());
    move_object(this_object(),DEST);
    DEST->add_exit(DIRECTION, EXIT_ROOM);

    ob=clone_object("obj/quest_obj");
    ob->set_name("cemetary");
    ob->set_hint("A whole bunch of people have gone missing in the cemetary - find out why!\n");
    ob->set_qp(10);
    move_object(ob,"room/quest_room");
  }
}

affect_environment()
{
write("An empty doorway leads north into a cemetary.\n");
}

randomize_graves()
{
int *graves;
int tmp,n;

n = 0;
graves=({3,6,7}); /* Corresponds to cem3.c, cem6.c, etc */
while(sizeof(graves)>0)
  {
  tmp=random(sizeof(graves));
  (CEMETARY+ROOM+"cem"+graves[tmp])->set_grave(n);
  graves=exclude_array(graves,tmp);
  n++;
  }
}
