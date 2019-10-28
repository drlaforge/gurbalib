/*  elite Poker dealer     *//*  Author: Shalafi@Genocide *//*  Translation: One */                      
/*  phase 1=original betting *//*  phase 2=draw *//*  phase 3=final betting *//*  phase 4=showing of hands    */ 
inherit "/std/monster";
#include ROOM+"poker/ghost.h"
 
int i;
int amount;
int canante, gameon, turn, totalplayers;
int *playergone, *playerchecks, phase;
object *players, *stillhere;
int *bets, announced, currentbet, pot, betoccured, raises;
mixed *hands; 
string *deck; 
mapping analysis;
int lastbet;
int *discard;
string *test;
 
void setup(void){
   
   
 
   set_short("An elite poker dealer");
   set_name("poker dealer");
   set_alt_name("poker");
   set_alias("dealer");
   set_long(break_string(
"The dealer looks expert in his craft, but enough about him - how about the "
"game?  It's draw poker, six-player max.  Local limits are 2000 dollars "
"opening bets, and 1000 dollars per raise, maximum 4 raises.  Play begins with "
"the deal, followed by a period of betting, which concludes when all players "
"have called or folded.  Then each player can draw 0-3 cards to help his hand, "
"followed by another stage of betting.  Finally, the hands are displayed and "
"the high hand takes the entire pot.  To join a hand, 'ante' when the dealer "
"calls for it.  Other useful commands are:",75)+
"   - hand (show your hand)               - pot (display the current pot)\n"
"   - turn (whose turn is it)             - list (who is still in this hand)\n"
"   - bet <# of chips>                    - raise <# of chips>\n"
"   - check (pass without betting)        - call (add chips without raising)\n"
"   - fold (throw in your hand)           - discard <card# card# card#>\n"
);
 
   canante=1;
   hands=allocate(7);   
   playergone=allocate(7); 
   playerchecks=allocate(7);
   totalplayers=0;
   raises=0;
   turn=1000;
   announced=pot=currentbet=0;
   phase=1;
   lastbet=-1;
   discard=({ 0, 0, 0, 0, 0, 0, 0 });
/*
   analysis=([ "rank": 0;0;0;0;0;0,
               "firstpair": 0;0;0;0;0;0,
               "secondpair": 0;0;0;0;0;0,
      
               "three": 0;0;0;0;0;0,
               "four": 0;0;0;0;0;0,
               "highcard": 0;0;0;0;0;0,
             "2card": 0;0;0;0;0;0,
          "3card":0;0;0;0;0;0,
               "4card":0;0;0;0;0;0,
               "5card":0;0;0;0;0;0
   ]);
*/
   analysis=([ "rank": ({0,0,0,0,0,0}),
               "firstpair": ({0,0,0,0,0,0}),
               "secondpair": ({0,0,0,0,0,0}),
               "three": ({0,0,0,0,0,0}),
               "four": ({0,0,0,0,0,0}),
              "highcard": ({0,0,0,0,0,0}),
               "2card": ({0,0,0,0,0,0}),
               "3card": ({0,0,0,0,0,0}),
               "4card": ({0,0,0,0,0,0}),
               "5card": ({0,0,0,0,0,0}),
            ]);      
   this_object()->new_deck();
   bets=({ 0, 0, 0, 0, 0, 0, 0 });
}
 
init() {
   ::init();
   add_action("bet", "bet");
   add_action("hand", "hand");
   add_action("check", "check");
   add_action("raise", "raise");
   add_action("fold", "fold");   
   add_action("stand", "stand");
   add_action("list", "list");
   add_action("ante", "ante");
   add_action("discard", "discard");
   add_action("call", "call");
   add_action("pot", "pot");
   add_action("turn", "turn");
}         
           
pot() {
   if (!gameon) {
      write("No hand has begun yet.\n");
      return 1;
   }
   write("The pot is currently "+(pot+10*sizeof(players))+" chips.\n");
   return 1;
}

turn() {
   if (!gameon) {
      write("The hand has not started yet.\n");
      return 1;
   }
   if (turn==1000) {
      write("It is no one's turn yet.\n");
      return 1;
   }
   if (phase==4) {
      write("Play has ended.\n");
      return 1;
   }
   if (turn>sizeof(players)-1) 
      write("There seems to be a bug.  Alert One.\n");
   else
      if (players[turn] && interactive(players[turn]))  
         if (players[turn]==this_player())
            write("It is your turn, high roller!\n");
         else
            write("It is "+players[turn]->query_name()+"'s turn.\n");
      else {
         write("You point out that player "+(turn+1)+" is gone.  "+
               "The dealer nods.\n");
         this_object()->next_turn();
      }
   return 1;
}

list() {
   int i;
   if (!gameon) {
      write("The hand has not yet begun.\n");
      return 1;
   }
   this_object()->stillhere();
   if (!sizeof(stillhere)) {
      write("No one seems to be left in this hand.\n");
      return 1;
   }
   write("Players still in this hand:\n");
   for (i=0;i<sizeof(stillhere);i++)
      write("   "+stillhere[i]->query_name()+".\n");
   return 1;
}                        
 
bet(str){
   int me;

  if(!str){
      write("Bet what?\n");
      return 1;
  }
  if(!sscanf (str,"%d",amount))
   { 
      write("A number please.\n");
       return 1; }
 
   if (!gameon) {
      write("The hand has not yet begun.\n");
      return 1; 
   }
   me=member_array(this_player(), players);
   if (me==-1) {
      write("You are not in this hand.\n");
      return 1;
   }
   if (phase!=1 && phase!=3) {
      write("It is not time for betting.\n");
      return 1;
   }
   if (turn!=me) {
      write("It is not your turn to bet.\n");
      return 1;
   }                              
   if (betoccured==phase) {
      write("A bet has already been made.  You may <call>, <raise>, or <fold>.\n");        
      return 1;
   }
   if(amount < 1){
       write("Your bet must be more then 0!\n");
       return 1;
   }
   if(amount > 2000){
      write("The maximum bet for this table is 2000 chips.\n");
      return 1;                  
   }                                      
   if (this_player()->query_money() < amount) {
      write("You don't have that much money!\n");
      return 1;
   }
   this_player()->add_money(amount*(-1));
   lastbet=member_array(this_player(), players);
   betoccured=phase;
   currentbet=(int)currentbet+(int)amount;
   pot=(int)pot+(int)amount;
   if (phase==1)
      bets[me]=(int)amount;
   else
      bets[me]=(int)bets[me]+(int)amount;
   if ((int)amount==1)
      write("You bet a single dollar.\n");
   else
       write("You bet "+(int)amount+" dollars.\n");   
   if ((int)amount==1)
      tell_room(environment(this_object()), this_player()->query_name()+
         " bets a single dollar.\n", ({ this_player() }) );    
   else
      tell_room(environment(this_object()), this_player()->query_name()+
         " bets "+(int)amount+" dollars.\n", ({ this_player() }) );    
   this_object()->next_turn();
   return 1;
}    
is_playing(ob){
    if(!players) return 0;
    if(member_array(ob,players) == -1) return 0;
    return 1;
}
 
fold() {   
   int me;
   if (!gameon) {
      write("The hand hasn't even begun yet!\n");
      return 1;
   }
   me=member_array(this_player(), players);
   if (me==-1) {
      write("You aren't even playing this hand.\n");
      return 1;
   }
   if (turn!=me) {
      write("Wait until your turn to fold.\n");
      return 1;
   }
   if (playergone[me]) {
      write("You have already folded your hand.\n");
      return 1;
   }
   playergone[me]=1;
   totalplayers--;
   write("You fold your hand.\n");
   tell_room(environment(this_object()), this_player()->query_name()+ 
      " folds.\n", ({ this_player() }));
   if (this_object()->stillhere()!=2)
      this_object()->next_turn();
   return 1;
} 
 
raise(str){
   int me;
 
   if(!str){
   write("Raise what?\n");
   return 1;
  }
   if(!sscanf(str,"%d",amount)){
      write("A number please!\n");
      return 1;
   }
   if (!gameon) {
      write("The hand has not yet begun.\n");
      return 1; 
   }
   me=member_array(this_player(), players);
   if (me==-1) {
      write("You are not in this hand.\n");
      return 1;
   }
   if (phase!=1 && phase!=3) {
      write("It is not time for betting.\n");
      return 1;
   }
   if (turn!=me) {
      write("It is not your turn to bet.\n");
      return 1;
   }                              
   if (betoccured!=phase) {
      write("No bet has been made yet.  You may <check>, <bet>, or <fold>.\n");        
      return 1;
   }                    
   if (raises>3) {
      write("The maximum number of raises for this table, 4, has been reached.\n");   
      return 1;
   }
   if ((int)amount < (int)1 || (int)amount > (int)1000) {
      write("The maximum raise for this table is 1000 chips.\n");
      return 1;                  
   }             
   if (this_player()->query_money() < 
       ((int)currentbet-(int)bets[me]+(int)amount)) {
      write("You don't have enough money!\n");
      return 1;
   }
   this_player()->add_money(-(currentbet-bets[me]+amount));
   lastbet=member_array(this_player(), players);
   pot=(int)pot+(int)currentbet-(int)bets[me]+(int)amount;
   bets[me]=(int)currentbet+(int)amount;
   currentbet=(int)currentbet+(int)amount;
   raises++;
   if ((int)amount==1)
      write("You raise the bet a single dollar.\n");
   else
      write("You raise the bet "+(int)amount+" dollars.\n"); 
   if ((int)amount==1)
      tell_room(environment(this_object()), this_player()->query_name()+
         " raises the bet a single dollar.\n", ({ this_player() }));  
   else
      tell_room(environment(this_object()), this_player()->query_name()+
         " raises the bet "+(int)amount+" dollars.\n",({this_player()})); 
   this_object()->next_turn();
   return 1;
}
 
check() {
   int me;
   if (!gameon) {
      write("The hand has not yet begun.\n");
      return 1; 
   }
   me=member_array(this_player(), players);
   if (me==-1) {
      write("You are not in this hand.\n");
      return 1;
   }
   if (phase!=1 && phase!=3) {
      write("It is not time for betting.\n");
      return 1;
   }
   if (turn!=me) {
      write("It is not your turn to bet.\n");
      return 1;
   }                              
   if (betoccured==phase) {
      write("A bet has already been made.  You may <call>, <raise>, or <fold>.\n");        
      return 1;
   }
   write("You check.\n");
   tell_room(environment(this_object()), this_player()->query_name()+
      " checks.\n", ({ this_player() }));
   playerchecks[me]=1;
   this_object()->next_turn();
   return 1;
}               
 
call(string arg) {
   int me;
 
   if(!gameon){
      write("The game has not yet begun.\n");
      return 1;
   }
   me=member_array(this_player(),players);
   if (me==-1) {
      write("You are not in this hand.\n");
      return 1;
   }
   if (phase!=1 && phase!=3) {
      write("It is not time for betting.\n");
      return 1;
   }
   if (turn!=me) {
      write("It is not your turn to bet.\n");
      return 1;
   }                              
   if (betoccured!=phase) {
      write("No bet has been made yet.  You may <check>, <bet>, or <fold>.\n");        
      return 1;
   }
   if (this_player()->query_money() < (currentbet-bets[me])) {
      write("The house covers your bet.\n");
      this_player()->add_money(this_player()->query_money()*(-1));
   }
   else
      this_player()->add_money(-(currentbet-bets[me]));
   write("You call.\n");
   tell_room(environment(this_object()), this_player()->query_name()+
      " calls.\n", ({ this_player() }));
   pot=(int)pot+(int)currentbet-(int)bets[me];
   bets[me]=(int)currentbet;
   playerchecks[me]=1;
   this_object()->next_turn();
   return 1;
}                                                           
                            
analyze(int player) {
   int *same, *rank;
   string *suit, handsuit; 
   int samesuit, straighttest;  
   string comment;
   int i, j;
   string fuck, this;
                             
   rank=allocate(5);
   suit=allocate(5); 
   same=allocate(5);
 
   analysis["rank"][player]=0;
   analysis["firstpair"][player]=0;
   analysis["secondpair"][ player]=0;
   analysis["three"][player]=0;
   analysis["four"][player]=0;
   analysis["highcard"][player]=0;
   analysis["2card"][player]=0;
   analysis["3card"][player]=0;
   analysis["4card"][player]=0;
   analysis["5card"][player]=0;
                
   samesuit=0;
   for (i=0;i<5;i++) { 
      sscanf(hands[player][i], "%d %s", rank[i], suit[i]); 
      if (rank[i]==1)
         rank[i]=14;
   }
   for (i=0;i<5;i++) {
      for (j=0;j<5;j++)    
         if (i==j) continue;
         else if (rank[i] == rank[j])
            same[i]++; 
      }
   for (i=0;i<5;i++) {
      if (same[i]==3) 
         analysis["four"][player]=rank[i]; 
      else if (same[i]==2)
         analysis["three"][player]=rank[i];
      else if (same[i]==1) 
         if (analysis["firstpair"][player]>0 &&
             analysis["firstpair"][player]!=rank[i])
            analysis["secondpair"][player]=rank[i];
         else
            analysis["firstpair"][player]=rank[i];   
      if (i==0) handsuit=suit[i];  
      else if (suit[i]==handsuit)
         samesuit++;
   }                     
   rank=sort_array(rank, "sort_high", this_object());
   analysis["highcard"][player]=rank[0];
   analysis["2card"][player]=rank[1];
   analysis["3card"][player]=rank[2];
   analysis["4card"][player]=rank[3];
   analysis["5card"][player]=rank[4]; 
   
   straighttest=1;
   for (i=0;i<4;i++) 
      if ( (rank[i] != rank[i+1]+1) && !(i==0 && rank[i]==14 && 
                                         rank[i+1]==5) )
         straighttest=0;
   if (straighttest==1 && (int)analysis["highcard"][player]==14 &&
       (int)analysis["2card", player]==5) analysis["highcard"][player]=5;
 
   if (analysis["firstpair"][player]!=0)
      analysis["rank"][player]=1;
   if (analysis["secondpair"][player]!=0)
      analysis["rank"][player]=2;
   if (analysis["three"][player]!=0) {
      analysis["rank"][player]=3;     
      if (analysis["firstpair"][player]!=0)
         analysis["rank"][player]=6;
   }
   if (straighttest)
      analysis["rank"][player]=4;
   if (samesuit==4)
      analysis["rank"][player]=5;
   if (analysis["four"][player]!=0)
      analysis["rank"][player]=7;
   if (straighttest && samesuit==4) { 
      analysis["rank"][player]=8;    
      if (analysis["highcard"][player]==14)
         analysis["rank"][player]=9;
   }
                                                     
   switch(analysis["rank"][player]) {
      case 0:
         comment=HAND->rank_card(analysis["highcard"][player])+" high";
         break;
      case 1:
         if (HAND->rank_card(analysis["firstpair"][player])=="Six")
            comment="a pair of Sixes";
         else
            comment="a pair of "+
                HAND->rank_card(analysis["firstpair"][player])+
 
            "s";
         break;
      case 2:
         fuck=HAND->rank_card(analysis["firstpair"][player]);
         this=HAND->rank_card(analysis["secondpair"][player]);
         if (fuck=="Six") fuck="Sixe";
         if (this=="Six") this="Sixe";
         comment="two pair, "+fuck+
            "s and "+this+"s";
         break;
      case 3:
         if (HAND->rank_card(analysis["three"][player])=="Six")
            comment="three Sixes";
         else
            comment="three "+
               HAND->rank_card(analysis["three"][player])+"s";
         break;
      case 4:
         comment="a straight, "+
             HAND->rank_card(analysis["highcard"][player])+
            " high";
         break;
      case 5:
         comment="a flush, "+
            HAND->rank_card(analysis["highcard"][player])+
            " high"; 
         break;
      case 6:
          fuck=HAND->rank_card(analysis["three"][player]);
          this=HAND->rank_card(analysis["firstpair"][player]);
          if (fuck=="Six") fuck="Sixe";
          if (this=="Six") this="Sixe";
            comment="a full house, "+fuck+
             "s over "+this+"s";
         break;
      case 7:
         if (HAND->rank_card(analysis["four"][player])=="Six")
            comment="four Sixes";
         else
            comment="four "+HAND->rank_card(analysis["four"][player])+"s";
         break;
      case 8:
          comment="a straight flush, "+HAND->rank_card(
             analysis["highcard"][player])+" high";
          break;
      case 9:
          comment="a royal flush";
          break;                       
   } 
   tell_room(environment(this_object()), players[player]->query_name()+
      " has "+comment+".\n");
   return 1;
}
                                  
discard(string nog) { 
   int *which, *temp;
   int i, j, pl;
   string junk;
   int *woo, acerank;
   string ace, junksuit;  
 
   if (!gameon) {
      write("The hand has not begun yet!\n");
      return 1;
   }  
   if (!sizeof(players) || member_array(this_player(), players)==-1) {
      write("You are not playing this hand.\n");
      return 1;
   }
   if (member_array(this_player(), players)!=turn) {
      write("It is not your turn.\n");
      return 1;
   }
   if (phase!=2) {
      write("It is not time to discard yet.\n");
      return 1;
   }
   if (!nog) {
      write("Usage: discard card# card# card#...\n");
      return 1;
   }
   test=explode(nog, " ");
  which=allocate(sizeof(test));
   i = sizeof(test);
   while(i){
      i--;
      if(!sscanf(test[i],"%d",which[i])){write("bah\n");}
      }
   for (i=0;i<sizeof(which);i++)      
      if (!sizeof(temp)) temp=({ which[i] });
      else if (member_array(which[i], temp)==-1)
         temp+=({ which[i] });
   for (i=0; i<sizeof(which); i++) 
       if ( ((int)which[i] < (int)1) || ( (int)which[i] > (int)5) ) 
          temp-= ({ which[i] });   
   which=temp;
   if (sizeof(which)==4) {
      woo=({ 1, 2, 3, 4, 5 });
      for (i=0;i<4;i++)
         woo-=({ (int)which[i] }); 
      ace=hands[member_array(this_player(), players)][(int)woo[0]-1];   
      sscanf(ace, "%d %s", acerank, junksuit);
      if (acerank!=14) {
         write("You must hold an ace to discard 4 cards.\n");
         return 1;
      }                 
      write("You show everyone your "+HAND->id_card(ace)+".\n");
      tell_room(environment(this_object()), this_player()->query_name()+
         " shows everyone "+this_player()->query_possessive()+" "+
         HAND->id_card(ace)+".\n");
   }                                     
   else if (!sizeof(which) || sizeof(which) > (int)3) {
      write("You must discard 1-3 cards.\n");
      return 1;
   } 
   pl=member_array(this_player(), players);
   for (i=0;i<sizeof(which);i++)
      this_object()->replace_card(member_array(this_player(), players), 
         which[i]);
   if ((int)sizeof(which)==1)
      write("You draw one card.\n");
   else
      write("You take "+sizeof(which)+" cards.\n");
   if ((int)sizeof(which)==1)
      tell_room(environment(this_object()), this_player()->query_name()+
         " draws 1 card.  Fear.\n", ({ this_player() })); 
   else
       tell_room(environment(this_object()), this_player()->query_name()+
          " takes "+sizeof(which)+" cards.\n", ({ this_player() }));  
   junk="";
   for (j=0;j<sizeof(hands[pl]);j++)
      junk+=hands[pl][j]+",";
   junk=junk[0..(strlen(junk)-2)];
   HAND->show_hand(junk, players[pl], 1);  
   discard[pl]=1;
   this_object()->next_turn();
   return 1;
}   
 
stand() {
   int me;
 
   if (!gameon) {
      write("The hand has not begun yet.\n");
      return 1;
   }
   if (phase!=2) {
      write("This is not the time to discard or stand.\n");
      return 1;
   }
   me=member_array(this_player(), players);
   if (me==-1) {
      write("You are not playing this hand.\n");
      return 1;
   }
   if (playergone[me]) {
      write("You have already folded your hand.\n");
      return 1;
   }
   write("You stand pat.\n");
   tell_room(environment(this_object()), this_player()->query_name()+
      " stands pat.  Jesus Christ.\n", ({ this_player() }));
   discard[member_array(this_player(), players)]=1;
   this_object()->next_turn();
   return 1;
} 
   
int sort_high(int a, int b) {
   return a<b;
}
 
next_turn() {
   int loop;
                    
   while (remove_call_out("too_long")!=-1) continue;
   loop=0;
   if (this_object()->stillhere()==2)
      return 1;
   if (turn==100) turn=-1;
   turn++;
   while( (playergone[turn]==1 || turn==sizeof(players) ||
          ((playerchecks[turn]==1 || lastbet==turn) && bets[turn]==(currentbet) &&
          (phase==1 || phase==3)) || ((discard[turn]==1 &&
           phase==2)) ) && loop<10) {    
      loop++;
      if (turn>=sizeof(players)-1) turn=0;              
      else turn++;
   }        
   if (loop>8) {
      phase++;
      if (phase==2) 
         tell_room(environment(this_object()),
"Initial betting is over, and the dealer begins to ask for draws.\n");
      if (phase==3) {
         tell_room(environment(this_object()),   
"Drawing is over, and the dealer opens the table to betting again.\n");
         lastbet=-1;
         playerchecks=({ 0, 0, 0, 0, 0, 0 });
         raises=0;
      }
      if (phase==4) {
         this_object()->end_this();  
         return 1;
      }
      else turn=100;   
      this_object()->next_turn();
      return 1;
   }
   tell_room(environment(this_object()),
      "The dealer looks toward "+players[turn]->query_name()+".\n",
      ({ players[turn] })); 
   if(bets[turn] < currentbet) {
      if (((int)currentbet-(int)bets[turn])==1) 
         tell_object(players[turn], "If you wish to remain in the hand, you "
            "owe the pot 1 dollar.\n");
      else
         tell_object(players[turn], "If you wish to remain in the hand, you "
            "owe the pot "+((int)currentbet-(int)bets[turn])+
            " dollars.\n");
   }
   if (phase==1) {
      if (betoccured!=1)
         tell_object(players[turn], "The dealer asks whether you would like to "
            "<bet>, <check>, or <fold>.\n");    
      else
         tell_object(players[turn], "The dealer asks whether you would like to "  
            "<raise>, <call>, or <fold>.\n");        
   }
   else if (phase==2) {
     tell_object(players[turn], "The dealer asks which cards "+
          "you would like to <discard>,\n"+
          "or whether you would like to <stand>.\n");
   }
   else if (phase==3) { 
      if (betoccured!=3)
         tell_object(players[turn], "The dealer asks whether you would like to "
            "<bet>, <check>, or <fold>.\n");    
      else
         tell_object(players[turn], "The dealer asks whether you would like to "  
            "<raise>, <call>, or <fold>.\n");   
   }
      call_out("too_long", 60, turn);
   return 1;
}
 
too_long(int num) {
   if (playergone[num]==0) {
      playergone[num]=1;
      totalplayers--;
   }
   if (players[num])
      tell_object(players[num],
         "You have taken too long, and the dealer takes your cards.\n");
   tell_room(environment(this_object()),
"Player "+(num+1)+" seems to have left.  His hand is thrown in.\n"); 
   if (this_object()->stillhere()!=2) 
      this_object()->next_turn();
      return 1;
}
 
hand() {
   string junk;
   int j, player;
   object him;
 
   if (!gameon) {
      write("No hand has begun yet.\n");
      return 1;
   }
   player = member_array(this_player(), players);
 
   if (player==-1) {
      write("You aren't in this hand!\n");
      return 1;
   }  
   if (playergone[player]==1) {
      write("Your hand has been thrown in already.\n");
      return 1;
   }
   junk="";
   for (j=0;j<sizeof(hands[player]);j++)
      junk+=hands[player][j]+",";
   junk=junk[0..(strlen(junk)-2)];
   write("Your hand:\n");
   HAND->show_hand(junk, players[player], 1);
   return 1;
}
 
ante() {       
   if (sizeof(players) && member_array(this_player(), players)!=-1) {   
      write("You have already anted.\n");
      return 1;
   }
   if (!canante) {
      write("It is too late to join this hand, wait a few minutes.\n");
      return 1;
   }
   if (sizeof(players)>5) {
      write("The dealer shakes his head.  Six players is his max.\n");
      return 1;
   }
   if (this_player()->query_money()<10) {
      write("You don't even have enough money to ante, pauper!\n");
      return 1;
   }
   if (!sizeof(players)) {
      players=({ this_player() });   
      if (!announced) {
         tell_room(environment(this_object()),
         "The dealer announces that a new hand will start in 15 seconds.\n");
         call_out("begin_game", 15);
         announced=1;
      }
   }
   else players+=({ this_player() });      
   totalplayers++;
   write("You pound down 10 dollars and join the hand.\n");
   this_player()->add_money(-10);
   tell_room(environment(this_object()),
      this_player()->query_name()+" antes 10 dollars "+
          "and enters the hand.\n", ({ this_player() }) );
   return 1;
}  
 
begin_game() {
   int i, j, pl;
   string junk;
   
   this_object()->ensure_ante();
   pl=sizeof(players);
   if (!pl) {
      tell_room(environment(this_object()),
   "No one has anted--the dealer decides not to begin the hand yet.\n");
      announced=0;
      players=0;
      return 1;
   }
   if (pl==1) {
      tell_room(environment(this_object()),
   "Not enough players for a hand--try again when you have at least 2.\n");
      if (players[0])
         this_player()->add_money(10);
      pot=0;
      totalplayers=0;
      players=0;
      announced=0;
      return 1;
   }
   this_object()->new_deck();
   gameon=1;
   canante=0;
   tell_room(environment(this_object()),
      "The hand of poker begins, with "+pl+" players.\n");
   tell_room(environment(this_object()),
      "The dealer deals every player five cards.\n");
   for (i=0;i<pl;i++) {     
      this_object()->first_cards(i);
      junk="";
      for (j=0;j<sizeof(hands[i]);j++)
         junk+=hands[i][j]+",";
      junk=junk[0..(strlen(junk)-2)];
      tell_object(players[i], "Your hand:\n");          
      HAND->show_hand(junk, players[i], 1);      
   }               
   call_out("next_turn", 5);
   return 1;
}
             
ensure_ante() {
   object *pls;
   int i;
 
   if (!sizeof(players)) return 1;
   pls=players;
   for (i=0;i<sizeof(players);i++)
      if (!players[i] || !interactive(players[i])) {
          pls-=({ players[i] });
          totalplayers--;
      }
   players=pls;
   return 1;
}              

replace_card(int pl, int crd) {  
   int j;            
   string card, junk;
   int bog;
 
   if (sizeof(deck)==0) {
      tell_room(environment(this_object()),
         "The dealer shuffles the deck.\n");
      this_object()->new_deck();
   }
   card=deck[random(sizeof(deck))];
   deck-=({ card });
   bog=(int)crd-(int)1;
   hands[pl][bog]=card;
   return 1;
}
 
stillhere() {
   int i;
 
   stillhere=0;
   for (i=0;i<sizeof(players);i++)
      if (playergone[i]==0 && (!players[i] || !interactive(players[i])
           || !environment(players[i]) )) {
         tell_room(environment(this_object()),
   "Player "+(i+1)+" seems to have wandered off.  The dealer collects his cards.\n"); 
         playergone[i]=1;
         totalplayers--;
      }
   for (i=0;i<sizeof(players);i++)
      if (!playergone[i] && players[i])
         if (!sizeof(stillhere))
            stillhere=({ players[i] });
         else
            stillhere+=({ players[i] });   
                                             
   if (totalplayers<2) {
     if (sizeof(stillhere)==0 || !stillhere[0]) {
         tell_room(environment(this_object()), "No one left.  Game over, bog.\n");
         call_out("game_over", 2);
         return 2;
      }
      if (pot!=0) {
         tell_room(environment(this_object()),
         "As the only player left, "+stillhere[0]->query_name()+
         " wins the pot: "+(pot+10*sizeof(players))+" chips.\n");
         stillhere[0]->add_money(pot+10*sizeof(players));
         pot=0;
      }
      call_out("game_over", 2);
      return 2;
   }
 
   return 1;
}                                            

first_cards(int hi) {
   int i;
   string card;
           
   for (i=0;i<5;i++) {
      if (sizeof(deck)==0) {
         tell_room(environment(this_object()),
            "The dealer shuffles the deck.\n");
         this_object()->new_deck();
      }                       
      card=deck[random(sizeof(deck))];   
      deck-=({ card });            
      if (!sizeof(hands[hi]))
         hands[hi]=({ card }); 
      else
         hands[hi]+=({ card });
   }      
   return 1;
}
 
new_deck() {  
   int j, k;
 
   deck=({
"2 s", "3 s", "4 s", "5 s", "6 s", "7 s", "8 s", "9 s", "10 s", 
   "11 s", "12 s", "13 s", "14 s",
"2 c", "3 c", "4 c", "5 c", "6 c", "7 c", "8 c", "9 c", "10 c", 
   "11 c", "12 c", "13 c", "14 c",
"2 h", "3 h", "4 h", "5 h", "6 h", "7 h", "8 h", "9 h", "10 h",
   "11 h", "12 h", "13 h", "14 h",
"2 d", "3 d", "4 d", "5 d", "6 d", "7 d", "8 d", "9 d", "10 d", 
   "11 d", "12 d", "13 d", "14 d",
        });            
   for(j=0;j<6;j++) 
      if (sizeof(hands[j])) 
         for (k=0;k<sizeof(hands[j]);k++)
            deck-=({ hands[j][k] });
   return 1;
}                                     
 
game_over() {
   players=0;
   bets=({ 0, 0, 0, 0, 0, 0, 0 });
   discard=({ 0, 0, 0, 0, 0, 0, 0 });
   playergone=allocate(7); 
   playerchecks=allocate(7);
   canante=1;
   gameon=pot=currentbet=0;
   stillhere=0;
   hands=allocate(7);
   turn=100;
   totalplayers=betoccured=0;
   raises=currentbet=0;
   phase=1;
   lastbet=-1;
   while (remove_call_out("begin_game")!=-1) continue;
   while (remove_call_out("too_long")!=-1) continue;
   while(remove_call_out("end_this")!=-1) continue; 
   while(remove_call_out("next_turn")!=-1) continue;
   while(remove_call_out("game_over")!=-1) continue;
   tell_room(environment(this_object()),
"The dealer calls for new bets.  A fresh hand will start in 15 seconds.\n");
   call_out("begin_game", 15);
   return 1;
}
 
end_this() {
   int i; 
 
   tell_room(environment(this_object()), "All betting is complete, and the "
      "players show their hands...\n");
   this_object()->stillhere();
   for (i=0;i<sizeof(stillhere);i++)
      call_out("reveal_hand", 5*(i+1), member_array(stillhere[i], players));
   call_out("award_pot", 4*(i+1)+2);
   call_out("game_over", 5*(i+i));
   return 1;
}    
 
reveal_hand(int who) { 
   int i, j;
   string junk;
 
   tell_object(players[who], "You lay your hand on the table.\n");
   tell_room(environment(this_object()), players[who]->query_name()+
      " lays "+players[who]->query_possessive()+" cards on "
      "the table.\n");              
   this_object()->stillhere(); 
   junk="";
   for (j=0;j<sizeof(hands[who]);j++)     
      junk+=hands[who][j]+",";
   junk=junk[0..(strlen(junk)-2)];               
   for (i=0;i<sizeof(stillhere);i++) {
      tell_object(stillhere[i], players[who]->query_name()+"'s hand:\n");
      HAND->show_hand(junk, stillhere[i], 0);
   }
   this_object()->analyze(who);
   return 1;
}                                       
 
award_pot() {
   int *slots;
   int i, who, done, j;
   int temp, winner;
 
   done=0;
   this_object()->stillhere();
   for (i=0;i<sizeof(stillhere);i++) {   
      who=member_array(stillhere[i], players);
      if (!sizeof(slots)) 
         slots=({ who });
      else
         slots+=({ who });
   }
    if (sizeof(slots)!=1)
      while(!done) { 
         done=1;
         for(j=0;j<sizeof(slots)-1;j++)
         if (this_object()->firsthigher(slots[j+1], slots[j])) { 
            temp=slots[j];
            slots[j]=slots[j+1];
            slots[j+1]=temp;
            done=0;     
         } 
      }  
   winner=slots[0]; 
   tell_object(players[winner], "You win the pot: "+
      (pot+10*sizeof(players))+" dollars!\n");
   tell_room(environment(this_object()), players[winner]->query_name()+
      " wins the pot: "+(pot+10*sizeof(players))+" dollars!\n",
      ({ players[winner] }));
   players[winner]->add_money(pot+10*sizeof(players));
   return 1;
}
 
firsthigher(int one, int two) { 
   int onehighpair, onelowpair;
   int twohighpair, twolowpair;
 
   if ((int)analysis["rank"][one] != (int)analysis["rank"][two])
      return ((int)analysis["rank"][one] > (int)analysis["rank"][two]);
   switch ((int)analysis["rank"][one]) {
      case 0: 
         return this_object()->firsthighcard(one, two);
         break;
      case 1:
         if ((int)analysis["firstpair"][one] !=    
             (int)analysis["firstpair"][two]) 
            return ((int)analysis["firstpair"][one] >
                    (int)analysis["firstpair"][two]);
         return this_object()->firsthighcard(one, two);
         break;       
      case 2:
         if ((int)analysis["firstpair"][one] >   
              (int)analysis["secondpair"][one]) {
            onehighpair=(int)analysis["firstpair"][one];
            onelowpair=(int)analysis["secondpair"][one];
         }                                            
         else {
            onelowpair=(int)analysis["firstpair"][one];
            onehighpair=(int)analysis["secondpair"][one];     
         }              
         if ((int)analysis["firstpair"][two] > 
             (int)analysis["secondpair"][two]) {
            twohighpair=(int)analysis["firstpair"][two];
            twolowpair=(int)analysis["secondpair"][two];
         }                                            
         else {
            twolowpair=(int)analysis["firstpair"][two];
            twohighpair=(int)analysis["secondpair"][two];     
         }   
         if ((int)onehighpair != (int)twohighpair) 
            return ((int)onehighpair > (int)twohighpair);
         if ((int)onelowpair != (int)twolowpair)
            return ((int)onelowpair > (int)twolowpair);
         return this_object()->firsthighcard(one, two);
         break;                                            
      case 3:
      case 6:         
         return ((int)analysis["three"][one] > 
                 (int)analysis["three"][two]);
         break;                               
      case 4:
      case 5:  
      case 8:
      case 9:                                         
         return this_object()->firsthighcard(one, two); 
         break; 
      case 7:
         return ((int)analysis["four"][one] > (int)analysis["four"][two]);
         break; 
   }                                          
}
 
firsthighcard(int one, int two) {
   if ((int)analysis["highcard"][one] != (int)analysis["highcard"][two])
      return ((int)analysis["highcard"][one] > 
             (int)analysis["highcard"][two]);   
   if ((int)analysis["2card"][one] != (int)analysis["2card"][two])
      return ((int)analysis["2card"][one] > (int)analysis["2card"][two]);     
   if ((int)analysis["3card"][one] != (int)analysis["3card"][two])
      return ((int)analysis["3card"][one] > (int)analysis["3card"][two]);       
   if ((int)analysis["4card"][one] != (int)analysis["4card"][two])
      return ((int)analysis["4card"][one] > (int)analysis["4card"][two]);                 
   return ((int)analysis["5card"][one] > (int)analysis["5card"][two]);   
}                                              
