inherit "room/room";
#include "../area.h"

object door;

reset(arg)
{
   ::reset(arg);
   if(arg)
      return;
   
   door=clone_object("obj/door");
   door->set_breakable(12);
   door->set_id(({"entrance","entrance to a cellar",
            "door","square door","sturdy square door","big sturdy square door","cellar door"}));
   door->set_long("The entrance has a big sturdy square door. It has a padlock "+
      "around the latch.\n");
   door->set_id_os(({"door","square door","sturdy square door","big sturdy square door"}));
   door->set_long_os("A big sturdy square door.\n");

/* DM */
door->set_lock_ob( this_object() );
door->set_unlock_fun( "cmd_unlock" ); /* this will default to "door_unlock" */
door->set_lock_fun( "cmd_lock" ); /* this will default to "door_lock" */
/* -- */

   door->make_door("cellar",CEMETARY+ROOM+"tomb",0,2,"door","","");
   move_object(door,this_object());
   
   add_local_unique(CEMETARY+NPC+"pigeon");
   set_light(1);
   set_outdoors(1);
   set_short("Side of a house");
   set_long_f(
      "The grass is waist high here. A tall metal fence is to the "+
      "west and north. East is the side of a house, with the entrance "+
      "to a cellar in front of it. South is the cemetary.",FORMAT);
   items=({
         ({"grass"}),
         "The grass is waist high!",
         ({"fence","metal fence","tall metal fence","tall fence"}),
         "A tall fence made of metal rods.",
         ({"rods","metal rods"}),
         "They make up the fence. The gap between them is generally not more than 20cm.",
         ({"house","side of a house"}),
         "The side of a house.",
         "latch",
         "A latch on the cellar door.",
          });
   add_exit("south",CEMETARY+ROOM+"cem7");
}

init()
{
   ::init();
// Mycon 21-03-2008: WTF? Someone has recoded the padlock func below, but failed to have the query_padlock_combo() _anywhere_ so this just bugs!
   add_action("cmd_pad","pad");
   add_action("cmd_enter","enter");
}

cmd_pad(str)
{
// this func blatantly doesn't work!!!
   int *combo;
   string *entry;
   
   (CEMETARY+ROOM+"housecell2")->foo();
   combo=(CEMETARY+ROOM+"housecell2")->query_padlock_combo();

   if(str)
      entry=explode(str,"-");
   
   if(door->query_closed()!=2)
      return write("The padlock is not locked.\n");
   if(sizeof(entry)!=3)
      return write("Padlock syntax: pad #-#-#\n");
   write("You twist the padlock, but fail to unlock it.\n");
   return 1;
   write("You twist the padlock.\n");
   door->unlock("cellar door",1);
   return 1;
}

cmd_unlock(str)
{
   if(!door->id(str))
      return 0;
   if(door->query_closed()==2)
      return write("To unlock the "+str+", enter a combination into the padlock.\n"+
      "Padlock syntax: pad #-#-#\n");
   return 0;
}

cmd_lock(str)
{
   if(str!="padlock")
      return 0;
   if(door->query_closed()==2)
      return write("The padlock is already locked.\n");
   if(door->query_closed()!=1)
      return 0;
   door->lock("cellar door",1);
   return 1;
}

id(str)
{
   if(::id(str))
      return 1;
   return str=="padlock";
}

long(str)
{
   if(str=="padlock")
      {
      if(door->query_closed()==2)
         write("A simple, locked padlock. 'pad #-#-#' "+
         "to enter a combination.\n");
      else if(door->query_closed()==1)
         write("A simple, unlocked padlock. It could be locked.\n");
      else
         write("A simple, unlocked padlock.\n");
   }
   ::long(str);
}

cmd_enter(str)
{
   if(str!="cellar")
      return 0;
   door->move_it();
   return 1;
}
