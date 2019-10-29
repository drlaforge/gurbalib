#include <tune.h>


#define retLog ROOM+"casino/data/log.ret"
#define storeLog ROOM+"casino/data/log.store"

#include <def.h>

inherit "std/room";
#include "../area.h"

static mapping objList;

void setup(){
    
    
   set_light(1);
   set_outdoors(0);
   set_short("WTF!?");
   set_long("Why are you here?\n");
   if(!objList)
      objList = ([ ]);
}

void init(){
   ::init();
   if( this_player() && environment( this_player() ) == this_object() &&
         this_player()->query_level() < ARCH_LEVEL ){
      write("You shouldn't be here.\n");
      this_player()->move_player("out#room/casino/lobby");
   }
}

void store(object obj, string who){
   if(!obj) return;
   if(!who) return;
   if( find_player(who) != this_player(1) ) return;
   if(!objList) objList = ([ ]);
   if( undefinedp(objList[who]) ) objList += ([ who : ({ obj }) ]);
   else
      objList[who] += ({ obj });
   move_object( obj, this_object() );
   write_file(storeLog, "On "+ctime(time())+", "+TP->QN+" stored "+file_name(obj)+"\n");
   return;
}

int ret(string who){
   int i;
   
   if(!who) return 0;
   if(!objList) return 0;
   if( undefinedp(objList[who]) ) return 0;
   if( (string)this_player(1)->query_real_name() != who ) return 0;
   for(i=0; i<sizeof(objList[who]); i++)
   {
      move_object(objList[who][i], this_player(1));
      write_file(retLog, "On "+ctime(time())+", "+TP->QN+" retrieved "+file_name(objList[who][i])+"\n");
   }
   objList = m_delete(objList, who);
   return 1;
}

mapping qL(){ return objList; }
int clean_up(){ return 0; }
