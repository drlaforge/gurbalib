#include "tune.h"
inherit "/std/room";

void setup(void){
    
   set_short("Questroom");
   set_light(1);
   set_long_f("This is the room of quests. Every scientist can make as many "+
      "quests he like. When he has made a quest, he should have it "+
      "approved by an arch scientist. When it is approved, put a "+
      "permanent object in this room, wich has as short description "+
      "the name of the scientist. All objects in this room will be "+
      "checked when a player wants to become a scientist. The player "+
      "must have solved ALL quests. To mark that a quest is solved, "+
      "call 'set_quest(\"name\")' in the player object. The objects "+
      "must all accept the id 'quest' and the name of the scientist. "+
      "The objects must also define a function hint(), that should "+
      "return a message giving a hint of where to start the quest. "+
      "also have a function query_qp that returns how many "+
      "quest_points the quest is worth. Note that players never can "+
      "come here. set_quest(str) will return 1 if this is the first "+
      "time it was solved by this player, otherwise 0.\n");
   add_exit("south",ROOM+"adv_inner");
}

check_for_duplicates(){
   object ob;
   int i;
   
   ob = all_inventory(this_object());
   for(i=0;i<sizeof(ob);i++)
   if(ob[i] && ob[i]->id("quest"))
      while(present(ob[i]->short()+" 2",this_object()))
   destruct(present(ob[i]->short()+" 2",this_object()));
}

count(silently){
   object ob;
   int i,j, all_qp,sum_qp,all,sum;
   
   check_for_duplicates();
   ob = sort_array(all_inventory(this_object()),"sort",this_object());
   for(i=0;i<sizeof(ob);i++) {
      if(this_player()->query_quests(ob[i]->short())) {
         sum_qp += ob[i]->query_qp();
         sum++;
       }
      all_qp += ob[i]->query_qp();
      if(ob[i]->id("quest"))
         all++;
   }
   if(!all_qp)
      return write("I can't make any scientists today as there are no quests "+
      "in store.\n");
   if(!silently) {
      printf("You have collected %d out of %d quest points (%d%%)\n",
         sum_qp, all_qp, (sum_qp*100/all_qp));
      if(sum_qp*100/all_qp < QUESTS_PERCENTAGE)
         printf("You need %d (%d%%) quest points",
         ((all_qp*QUESTS_PERCENTAGE)/100), QUESTS_PERCENTAGE);
      else
         write("You have the "+QUESTS_PERCENTAGE+"% that you need");
      write(" to become a scientist.\n");
      write("This is a list of the quests : ('*' solved by you)\n");
      for(j=1,i=0;i<sizeof(ob);i++)
      if(ob[i]->id("quest")) {
         printf(" %2d%s%s %3d points.",
            j,(this_player()->query_quests(ob[i]->short()) ? " * " : "   "),
            ("\""+capitalize(ob[i]->short())+"\"......................."+
               "............")[0..30], ob[i]->query_qp());
/*
See arch board, 1003:  [8] Quests .... Mycon
         if(this_player()->query_level() >SCI_LEVEL) 
            if(creator(ob[i])) write (" ("+creator(ob[i])+")");
*/
         write("\n");
         j++;
      }
   }
   return QUESTS_PERCENTAGE-((sum_qp*100)/all_qp);
}

list(i)
{
   object ob;
   check_for_duplicates();
   ob = sort_array(all_inventory(this_object()),"sort",this_object());
   if(sizeof(ob) >= i && i > 0)
      write(ob[i-1]->hint());
}

sort(a,b){
   return (a->query_qp() > b->query_qp());
}
