

#include <def.h>

inherit STD_ROOM; 
#include "../area.h"

int casino_room(){ return 1; }

void setup(){
    
    
}

int plyrs(object o){ return userp(o); }

void securityCheck(){
   object *o;
   object *fighting;
   int i;
   
   fighting = ({ });
   o = filter_array(all_inventory( TO ), "plyrs", TO);
   if( !sizeof(o) ) return;
   for(i=0; i<sizeof(o); i++)
   {
      if( member_array( o[i], fighting ) == -1 )
         if( o[i]->query_attack() )
         if( ENV((object)(o[i]->query_attack()))->casino_room() )
         fighting += ({ o[i], o[i]->query_attack() });
   }
   
   for(i=0; i<sizeof(fighting); i++) {
      if( environment(fighting[i])->casino_room() ){
         tell_object( fighting[i], "Three men arrive, grab you and throw you out of the casino.\n"+
            "They leave you, laughing and saying: \"We said NO FIGHTING! Get lost!\"\n" );
         fighting[i]->move_player("thrown out of the casino#room/casino/lobby");
       }
   }
   tell_room(TO, "Three very large men walk through the room, keeping the peace.\n" );
   if( find_call_out("securityCheck") == -1 )
      call_out("securityCheck", 120);
   return;
}

void init(){
   ::init();
   if( find_call_out("securityCheck") == -1 )
      call_out("securityCheck", 120);
}
