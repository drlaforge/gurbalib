
#include <def.h>

#define SF ROOM+"casino/patrons_"
#define SO save_object(SF)
#define RO restore_object(SF)

static int * me;
mapping Patrons;

int *init_map(string game, object who){
   string name;
   name = who->query_real_name();
   restore_object(SF+game);
   if(!Patrons) Patrons = ([ ]);
   if( undefinedp(Patrons[name]) ){
      Patrons += ([ name : ({ 0, 0, 0 }) ]);
      save_object(SF+game);
   }
   return Patrons[name];
}

void add_won(string game, object player, int fl){
   if(!player) return;
   if(!userp(player)) return;
   me = init_map(game, player);
   if( fl ) me[1] = me[1] + 1;
   else me[0] = me[0] + 1; /* won */   Patrons[player->query_real_name()]=me;
   save_object(SF+game);
}

void add_lost(string game, object player){
   add_won(game, player, 1);
}

void add_money(string game, object player, int amt){
   if(!player) return;
   if(!userp(player)) return;
   me = init_map(game, player);
   me[2] = me[2] + amt;
   Patrons[player->query_real_name()]=me;
   save_object(SF+game);
}

mixed query_player(string game, string name, int fl){
   restore_object(SF+game);
   name = lowercase(name);
   if( undefinedp(Patrons[name]) ) return 0;
   if( fl ){
      fl -= 1;
      return Patrons[name][fl];
   }
   return Patrons[name];
}


