#include <tune.h>
/********************************************************/
/***                      LPC                         ***/
/***                   DRAW POKER                     ***/
/***     written by Scogar AKA: Gary Thonerfelt       ***/
/***                scogar@netcom.com                 ***/
/********************************************************/

#define PBAL     ROOM+"casino/data/pokerbal"
inherit "/std/object";
/*-----------------global-variables-----------------*/
int balance;            /* current game balance     */
int wins;               /* current # of player wins */
int plays;              /* current # of times played*/
int *stats;             /* array holding #'s of wins*/
string tp;              /* current player           */
static mixed *gc;       /* players cards            */
static int bet;         /* players bet              */   
static int win_type;    /* sets win status          */
/*--------------------------------------------------*/
void setup(void)
{
    
    stats=({0,0,0,0,0,0,0,0,0,0});
   tp = 0;
   restore_object(PBAL);
   set_name("poker machine");
   set_alias("machine");
   set_short("a video draw poker machine");
   set_long("\n"
  +" _______________________________________________________________________ \n"
  +"| ____________             VIDEO DRAW POKER                             |\n"
 +"||            |\\      ___________________________   _                   |\n"
  +"||  NUCLEAR   | |    |  ___  ___  ___  ___  ___  | | | <--- Money slot  |\n"
  +"||    ____    | |    | |~  ||~  ||~  ||~  ||~~ | | | |                  |\n"
  +"||  (######)  | |    | | ~ || ~ ||~ ~||~~~|| ~ | | |_|                  |\n"
  +"|| (########) | |    | |~~~||~~~|| ~ || ~ ||~ ~| |      Payoff chute    |\n"
 +"||  (##/\\##)  | |    | |___||___||___||___||___| |      ^   __________  |\n"
  +"||     ||     | |    |       Video Display       |      |  |  Rules   | |\n"
 +"||     ||     | |    |___________________________|  /~~~\\  | Inst, &  | |\n"
  +"||     ||     | |    |  [1]  [2]  [3]  [4]  [5]  | |     | | Payoff % | |\n"
 +"||WAR  || DECK| |    |   |    |    |    |    |   |  \\___/  |  'SIGN'  | |\n"
  +"||____________| |    |  Draw or Discard buttons  |         |__________| |\n"
+"| \\____________\\|    |___________________________|                      |\n"
+"|_______________________________________________________________________|\n");
	if (this_player()->query_level() >= ROOKIE_LEVEL)
		write("As a scientist you can check the total balance\n" +
		      "of this game by typing 'pokerbalance'.\n");
   set_value(0);
   set_weight(1);
} 

init()
{
   add_action ("pdraw","deal");   add_action ("pread","read");
   add_action ("pview","cards");  add_action ("ppress","pb");
   add_action ("ppress","press"); add_action ("ppress","push");
   add_action ("pinsert","insert");
   if (this_player()->query_level() >= ROOKIE_LEVEL)
   add_action ("show_balance",	"pokerbalance");
}
	
pread (str)
{
   if (!str) return 0;
   if (str == "sign")
      write("\n                  ***   VIDEO DRAW POKER   ***\n\n"
      +"To begin, just 'insert <bet> dollars'.\n"
      +"To hold or discard, just 'press <1 to 5>' or 'pb <1 to 5>'.\n"
      +"To view your current hand, just type 'cards'.\n"
      +"To draw when you've finished discarding, just type 'deal'.\n"
      +"\n\nPayoffs (with a 5 dollar bet) are:\n"
      +"\nOne Pair. . . . $5      To play the game:\n"
      +"Two Pairs . . . $10     You must have a pair of\n"
      +"Three of a Kind $15     Jacks or better to win.\n"
      +"Strait. . . . . $20     You will be dealt 5 cards.\n"
      +"Flush . . . . . $30     You may choose to keep\n"
      +"Full House. . . $45     up to all five before \n"
      +"Four of a Kind. $125    pressing 'deal'.\n"
      +"Strait Flush. . $250    The cards will be re-drawn only once.\n"
      +"ROYAL FLUSH . . $1250\n");
return 1;
}

pinsert (str)
{
   int i, i2; string ts;
   if (!str) return 0;
   if (tp!=0)                /* checks for player present or player linkdead */
   {
       if(present(tp->query_name(),environment(this_object())))
       {
          if (!(interactive(tp))) {tp->add_money(bet); tp=0; }
       }
       if(tp!=0){
       if(!(present(tp->query_name(),environment(this_object())))) {tp=0;} 
           }
                     /* resets machine if player isn't present or if player is linkdead */
                     /* or if machine was left alone it resets */
   if (tp!=0 && tp==this_player()) /*if machine is already being used by player..*/
        {
      	    write("You have to finish the game you are playing first !\n");
            return 1;
        }
        if (tp!=0 && tp!=this_player())
        {
           write("Sorry... You will have to wait till "+tp->query_name());
           write(" is finished playing "+tp->query_possessive()+" hand.\n");
            return 1;
        }
   }
   if (sscanf (str,"%d %s",bet,ts)!=2)
   {                               /*if player didn't type 3 seperate args...*/
      write ("Please type 'insert <amount> dollars'"); write ("\n");
      return 1;
   }
   if (ts!="dollars" && ts!="dollar" && ts!="$") 
   {                                          /*if money arg isn't dollars...*/
      write ("This machine accepts only dollars...\n"); return 1;
   }
   if (bet < 2 )                   /*if amount bet was less than 2 dollars...*/
   {
      write ("The Machine buzzes zzZZZTTTttt...  \n");
      write("Sorry, The minimum bet is 2 dollars.\n");
      return 1;
   }
   if (this_player()->query_level() < ROOKIE_LEVEL && bet > 20000 )                 /* if amount bet was over 20000 dollars...*/
   {
      write ("The Machine buzzes zzZZZTTTttt...  \n");
      write ("Sorry, The maximum bet is 20000 dollars.\n");
      return 1;
   }
   if (this_player()->query_money() < bet) /*if bet is more than player has..*/
   {
      write ("You don't have that much money.\n");
      return 1;
   }
   tp=this_player();   /* tp is now the player that is playing till finished */
   write ("Clink! Rattle! Rattle! Rattle! You put $"+bet);
   write(" into the poker machine.\n");
   say (tp->query_name());
   say(" put some money into the draw poker machine.\n");
   this_player()->add_money (-bet); /* player made bet...subtract bet amount */
   write("                          These are your cards.\n     "); 
   write("(#1)           (#2)          (#3)           (#4)           (#5)\n");
   gc=({({0,1,1,1,1,1}),({0,0,0,0,0,0,0,0,0,0,0}),({0,0,0,0,0,0,0,0,0,0,0})});
   win_type=0;         /*reset arrays at initialization of program execution */
   gc[1][1]=random(13)+1;gc[2][1]=random(4)+1;
   for(i2=2;i2<11;i2++){check(i2);}                  /* get 10 unlike cards  */      
    cardproc();wributton();
   return 1;
}

pdraw(str)
{
   int i, i2, match, pairs, three_kind, high_card, flush, paymult, temp, cflag;
   int *ca;
   if (str);
   if (tp==0)        /* if not busy or player isnt player playing */
   {  
       write("You need to place a bet first.\n");
       return 1;
   }
   if(this_player()->query_name()!=tp->query_name()) 
   {
        write("Sorry... You will have to wait till "+tp->query_name());
        write(" has finished playing.\n");
        return 1;
   }
   say("\n"+tp->query_name()+" pressed the deal button.\n");
   i2 = 6;                /* this loop tosses discards and gets replacements */
   for(i=1;i < 6;i++)
   {
      if (gc[0][i] == 1)
      {
       gc[1][i] = gc[1][i2]; gc[2][i] = gc[2][i2]; i2++;}
   }
   cardproc();
   ca=({0,0,0,0,0,0,0});
   /*-------------win-condition-sorting-and-checking-routines----------------*/ 
   for(i=1;i<6;i++) {ca[i]=gc[1][i];}         /*loads temp arry from gc[1]*/
   high_card=temp=pairs=three_kind=0;
   for(i2=1;i2<6;i2++)                            
   {                           /* this loop finds how many card values match,*/
                               /* when matches are found, matched cards in   */ 
      for(i=1;i<6;i++)         /* the ca[array] are set to zero, and the     */
      {                        /* sort is continued with remaining >0 values.*/
         if (ca[i2]!=0 && i2!=i)
         {
            if(gc[1][i2]==gc[1][i]) { temp++; high_card=gc[1][i2]; ca[i] = 0; }
         }
      }
      if (temp == 1) { pairs++;  temp = 0; }
      if (temp == 2) { three_kind=1;  temp = 0; }
      if (temp == 3) { win_type=7;}      /* if 3 matches, win = 4 of a kind */
   }
   if (win_type != 7)              /* if four of a kind, skip rest of checks */
   {
      if (pairs==1)
      {                    /* if value of pair = jacks or better, win = pair.*/  
          if(high_card>10 || high_card==1) { win_type = 1; }
      } 
      if (pairs==2) {win_type = 2;}      /* if 2 pairs,      win = 2 pairs   */
      if (three_kind==1)                 /* if 3 of a kind , win = 3 of kind */ 
      {                                  /* if 3kind & pair, win = fullhouse */
         win_type = 3; if (pairs ==1) {win_type = 6;}
      }
      if (pairs==0)        /*if hand has a pair, skip flush and strait checks*/
      {
         i2 = 1;                                   /* flush checking routine */
         for(i=2;i < 6;i++)
         {
            if (gc[2][1] == gc[2][i]){i2++;}
         }                                         /* if 5 match , win=flush */
         if (i2 == 5) { win_type = 5; flush=1;}  
         for(i=1;i<6;i++) 
         {                          /*loads temp array with plyr card values */
             ca[i]=gc[1][i]; gc[2][i]=0;
         }
         gc[1][6]=0; ca[6]=0;       /* forces card #6 for a low-compare dummy*/
         for(i2=1;i2<7;i2++)        /* this set of loops sorts card values   */
         {                          /* and stores the cards highest-to-lowest*/
            temp=ca[i2];            /* into the gc[2] array for comparison   */
            cflag=i2;               /* from the ca array, then the highest   */
            for(i=1;i<7;i++)        /* value in *ca is changed to 0->loop..  */ 
            {                       /* The resulting sorted gc[2] array is   */
               if(ca[i] > temp)     /* prepared for sequencial check         */ 
               {                    /*  for a possible strait                */
               	  temp=ca[i];
               	  cflag=i;
               }
            }
            gc[2][i2]=temp;ca[cflag]=0;
         }
         if(gc[2][5]==1 && gc[2][1]==13) {gc[2][5]=gc[2][4];gc[2][4]=gc[2][3];gc[2][3]=gc[2][2];gc[2][2]=gc[2][1];gc[2][1]=14;}
         i2 = 1;                             /*this loop checks cards to be  */
         for(i=1;i<5;i++)                    /*only 1 apart in value and     */
         {                                   /*increments i2 for flush count */
            if(gc[2][i]-gc[2][(i + 1)]==1)
            {
                i2++;
            }
         }
         if(i2 == 5){ win_type = 4;}         /* If flush count is 5 then,    */
         if(win_type == 4)                   /* set win as strait.           */
         {                                   /*If win is strait and flush was*/
            if(flush==1){win_type = 8;}       /* set,then set win as strtflush*/
         }
         if(win_type == 8)
         {                                   /*If win is strtflush and card #*/
            if (gc[2][2] == 13)              /* 2 is king,win = royal flush  */ 
            {
               win_type = 9;
            }
         }
      }
   }
   /*----------finished-sorting-and-checking-win-conditions------------------*/
   plays++;
   gc=({({"nothing","One pair","Two pairs","Three of a Kind",
   	   "a Strait","a Flush","a Full House","Four of a Kind",
   	   "A Strait Flush","A ROYAL FLUSH"}),({1,1,2,3,4,6,9,25,50,250})});
   if (win_type==0)                                     /* if player lost... */
   {
      write("You lost "+bet+" dollars.\n"); balance += bet;
      say("You hear a scream of frustration from "+(this_player()->query_name())+"\nas "+(this_player()->query_pronoun())+" just lost "+(bet)+" dollars playing poker.\n");
   save_object(PBAL);
      tp=0;
      return 1; 
   }
   paymult = (bet * gc[1][win_type]);  /*if player won,calculate payoff,etc..*/
   write("You have "+(gc[0][win_type])+" !\nYou have won "+(paymult-bet)+" dollars!\n");
   say(tp->query_name()+" just got "+(gc[0][win_type])+" playing poker!\nAnd "+(this_player()->query_pronoun())+" won "+(paymult-bet)+" dollars!\n");
   this_player()->add_money(paymult); wins++; stats[win_type]++; balance -= (paymult-bet);
   save_object(PBAL);
   tp=0;
return 1;
}

pview(str)
{
    int i;
    if (str);
    if (tp==0) 
    {                   /* if machine is already being used... fail & return */
    	write("You need to place a bet first.\n");
    	return 1;
    }
    if(this_player()->query_name()!=tp->query_name())
    {           /* if player not playing tries to view cards...fail & return */
       write("Sorry... You will have to wait till "+tp->query_name());
       write(" has finished playing.\n");
       return 1;
    }
    cardproc();
    wributton();
    return 1;        
}      

ppress(str)
{
   int *ga;
   int i;
   ga=({({"NUCLEAR","Ace","2","3","4","5","6","7","8","9","10","Jack",
   "Queen","King","Ace"}),({"suits","Hearts","Spades","Diamonds","Clubs"})});
   if(!str) return 0;
    if (tp==0)
   {         /* if machine is not *tp* and player tries to press a button... */
       write("You need to place a bet first.\n");
       return 1;
   }
   if(this_player()->query_name()!=tp->query_name()) 
   {                            /* if machine is in use by another player... */
       write("Sorry... You will have to wait till "+tp->query_name());
       write(" has finished playing.\n");
       return 1;
   }
   if (str!="1" && str!="2" && str!="3" && str!="4" && str!="5"){return 0;}
   sscanf(str,"%d",i);                /* makes i the # of the button pressed */
   if (gc[0][i] == 1)  
   {             /* if/else loop is for (discard or keep) toggles &  message */
      write("OK... Keeping the "+ga[0][gc[1][i]]+" of "+ga[1][gc[2][i]]);
      write(".\n"); gc[0][i] = 0;
   }
   else  
   {
      write ("OK... Discarding the "+ga[0][gc[1][i]]+" of "+ga[1][gc[2][i]]);
      write(".\n"); gc[0][i] = 1;
   }
return 1;
}                                                

check(int i2)        /* this routine checks for a duplicate card and fetches */
                                  /* another till it has a new, unique card  */
{
   int i;
   gc[1][i2] = (random(13)+1);
   gc[2][i2] = (random(4)+1);
   for(i=1;i<i2;i++)
   {
      if (i2 != i)
      {
         if (gc[1][i2] == gc[1][i])
         {
            if(gc[2][i2]==gc[2][i])  
               check(i2);
   }  }  }
return 1;    
}

cardproc()                       /* This function makes the card pictures    */
{                                /*each array element of ca[][] is a fragment*/ 
   string *ca; int i, i2;        /* of a card picture...                     */
   ca=({({"","Ace  ","2    ","3    ","4    ","5    ","6    ","7    ","8    ","9    ","10   ","Jack ","Queen","King "}),
   ({"Hearts","|            |","|  /~\\  /~\\  |","|  \\  \\/  /  |","|   \\    /   |","|    \\  /    |","|     \\/     |","|            |"}),    
   ({"Spades","|            |","|    /~\\     |","|   /   \\    |","|  /     \\   |","|  \\_/|\\_/   |","|     |      |","|            |"}),
   ({"Diamonds","|     /\\     |","|    /  \\    |","|   /    \\   |","|   \\    /   |","|    \\  /    |","|     \\/     |","|            |"}),     
   ({"Clubs","|            |","|    /~\\     |","|    \\ /     |","|  /~~ ~~\\   |","|  \\_/|\\_/   |","|     |      |","|            |"})});     
   write ("\n ____________   ____________   ____________   ____________   ____________  \n");
   write ("|            | |            | |            | |            | |            | \n");            /*the card values */  
   for(i=1;i < 6;i++)     
   {
       write("| "+ca[0][gc[1][i]]+"      | ");
   } 
    write("\n");
   for(i2=1;i2<8;i2++)
   {
       for(i=1;i < 6;i++)
       {
          write(ca[gc[2][i]][i2]+" ");
       }  
    write("\n");
   }
   write("|____________| |____________| |____________| |____________| |____________| \n");           /*ca[2][spades]...  */
   return 1; 
} 

wributton()
{                  /* this function generates the buttons that are displayed */
 int i,i2;
   write("   ________       ________       ________       ________"
        +"       ________    \n");
       for(i=1;i<6;i++){if(gc[0][i]==0)
       {write("  |  HOLD  |   ");} else { write("  | DISCRD |   ");}}
   write("\n   ~~~~~~~~       ~~~~~~~~       ~~~~~~~~       ~~~~~~~~"
        +"       ~~~~~~~~    \n");
   return 1;
}

show_balance()
{
   int i, i2;
       if (tp != 0)
       {
       	   write("\nSorry, while the machine is busy, It cannont give you a gamebalance,\n"
       	        +"as that would interfere with arrays needed by the players.\n");
       	   return 1;
       }
   restore_object(PBAL);
       gc=({"nothing........","one pair.......","two pairs......",
       	       "three of a kind","a strait.......","a flush........",
       	       "a full house...","four of a kind.","a strait flush.",
       	       "a royal flush.."});
       if (plays==0){plays=1;}
       write("The game has been played "+plays+" times .\nNumber of wins = "+wins+" : Number of losses = "+(plays-wins)+"\n");
       write("Average win/loss = "+((100*wins)/(plays-wins))+"%\n");
       if (balance < 0){write("The game has lost "+(-balance)+" dollars to the players.\n");} 
       else {write("The players have lost "+balance+" dollars to the machine.\n");}
       write("\n* number of hands won and win/loss precentage *\n\n");
       for(i=1;i<10;i++)
       {                             /* loop to write independent hand stats */
          i2 = (100*stats[i])/(plays-stats[i]);
          if (stats[i]<10) write(" "); else if (stats[i]<100) write(" ");
          if (i2 < 1)
          {
              i2 = (100000*stats[i])/(plays-stats[i]);
              write(stats[i]+" player(s) had "+gc[i]+"...win/loss = 0."+i2+" %\n");
          } 
          else write(stats[i]+" player(s) had "+gc[i]+"...win/loss = "+i2+" %\n");
       }
       return 1;
}
	
