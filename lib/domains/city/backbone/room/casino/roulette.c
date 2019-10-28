/* roulette-table by Thorwald ... requires file roulettetoken.c */
/* Modified for style and completeness, Superpimp & Cygnus (05/99) */
/* Cashing in loyalty card added - Wishbone 01/05 */
/* Fixed an issue when cashing out before the ball stops, no winnings */

   
#define TOKEN_FILE ROOM+"casino/roulettetoken"
#include <tune.h>
#include <ansi2.h>
#define RED ESC+ANSICODES[COLOURS["RED"]]
#define BLUE ESC+ANSICODES[COLOURS["BLUE"]]
#define GREEN ESC+ANSICODES[COLOURS["GREEN"]]
#define RE ESC+ANSICODES[COLOURS["RESET"]]
#define CYAN ESC+ANSICODES[COLOURS["CYAN"]]
#define MAG ESC+ANSICODES[COLOURS["MAGENTA"]]
#define BOLD ESC+ANSICODES[COLOURS["BOLD"]]
#define ITALIC ESC+ANSICODES[COLOURS["ITALIC"]]
#define UNDERL ESC+ANSICODES[COLOURS["UNDERLINE"]]
#define FLASH ESC+ANSICODES[COLOURS["FLASH"]]

object ob;
string colors,squares;
string del1,del2,del3,del4;
string antal;
string players,player_color;
string st,st2,st3,curr_col;
int inte,inte2,inte3,inte4;
int prize,rulla,curr_no,antali;

short () {
   return ("a Standard Products roulette table");
}
long () {
   write ("There is a large spinning wheel and a board.\n");
   write ("The board has got 0-36 numbers.\n");
   write ("0 is green, 1 is red, 2 is black, 3 is red etc.\n");
   write ("There are also three squares marked: 1-12, 13-24, 25-36.\n");
   write ("You also see one red square and one black square.\n");
   write ("-------------------------------------------------\n");
   write ("'buy'   <dollars> (each token costs "+prize+" dollars)\n");
   write ("'claim' Cash in a Bacon Shop loyalty card\n");
   write ("'bet'   <tokens> on <0-36, s1-s3, red, black>\n");
   write ("'bets'  Shows the bets so far.\n");
   write ("'cash'  Exchange all tokens for cash.\n");
   write ("-------------------------------------------------\n");
   write ("\n");
   write ("There is a bright green <reset> button underneath the table.\n");
}
id (str) {
   return str=="board" || str=="table" || str == "roulette" || str =="roulette board";
}
init () {
   add_action ("mplay","bet");
   add_action ("mplay","play");
   add_action ("mbuy","buy");
   add_action ("mbets","bets");
   add_action ("mcash","cash");
   add_action ("mclaim","claim");
   add_action ("reset_button",({"initiate"}));
}
reset (arg) {
    
   colors=({ "blue","green","magenta","white","yellow",
         "orange","cyan","purple" });
   squares =({ "0","1","2","3","4","5","6","7","8","9","10","11",
         "12","13","14","15","16","17","18","19","20",
         "21","22","23","24","25","26","27","28","29",
         "30","31","32","33","34","35","36","red","black",
         "s1","s2","s3", });
   players = allocate (sizeof (colors)); /*Player bet where*/
   player_color = allocate (sizeof (colors)); /* Player has personal col.*/
   prize=50;
   rulla=0;
}

reply (str2) {
   write ("The roulette-manager says: "+str2);
}
ret_which_color (plyr) {     /* Check if player got color, if not return -1*/
   int baja;
   baja=0;
   while (baja < sizeof (colors) && plyr != player_color [baja]) {
      baja += 1;
   }
   if (baja ==sizeof (colors)) baja=-1;
   return baja;
}

remove_player_color (plyr) {
   int place;
   place = 0;
   while(place < sizeof(colors) && plyr != player_color[place]) {
      place += 1;
   }
   if(place != sizeof(colors)) player_color[place] = 0;
   return plyr;
}

find_first_empty_color (plyr) {
   int baja2;
   baja2=0;
   while (baja2 < sizeof (colors) && player_color [baja2]) {
      baja2=baja2+1;
   }
   if (baja2 ==sizeof (colors)) baja2=-1;
   else
      player_color [baja2] = plyr;
   return baja2;
}

mbuy (str) {
   if (!str) return 0;
   if (!sscanf (str,"%d",inte)) return 0;
   if (inte < 0) return 0;
   if (inte<prize) { write ("Each costs "+prize+" dollars.\n"); return 1;}
   if (this_player()->query_money() < inte) {
      reply ("We don't sell tokens on credits. Get the cash somewhere first, bub.\n");
      return 1;
   }
   inte2=ret_which_color (this_player()->query_real_name());
   if (inte2==-1) {
      inte2=find_first_empty_color (this_player()->query_real_name());
      if (inte2==-1) {
         reply ("Sorry, no more bettors on this game just now.\n");
         return 1;
       }
   }
   write ("The roulette-manager gives you "+(inte/prize)+" "+colors [inte2]+" tokens.\n");
   inte3 = inte-((inte/prize)*prize);
   if (inte3>0) {
      reply ("And here is "+inte3+" dollars back in change.\n");
      this_player()->add_money(inte3);
   }
   this_player()->add_money (- inte);
   say (this_player()->query_name()+" gives "+inte+" dollars to the roulette-manager.\n",this_player());
   say (this_player()->query_name()+" receives "+inte/prize+" "+colors [inte2]+" tokens.\n");
   inte=inte/prize;
   add_tokens (this_player(),inte,colors [inte2]);
   return 1;   
}

/* This is for cashing in Bacon Shop loyalty cards only - Wishbone */

mclaim()
{
 if(!present("lunch_punch_card",this_player()))
  { 
   write ("You don't have a loyalty card.\n");
   return 1;
  }
 if(present("lunch_punch_card",this_player())->query_holes() < 10)
  { 
   write ("That loyalty card isn't complete.\n");
   return 1;
  }
 inte2=ret_which_color(this_player()->query_real_name());
 if (inte2==-1) 
  {
   inte2=find_first_empty_color(this_player()->query_real_name());
   if (inte2==-1)
    {
     reply ("Sorry, no more bettors on this game just now.\n");
     return 1;
    }
  }
 write ("The roulette-manager gives you 250 "+colors [inte2]+" tokens.\n");
 write ("Your completed loyalty card is unceremoniously torn up and thrown away!\n");
 destruct(present("lunch_punch_card",this_player()));
 say (this_player()->query_name()+" gives a loyalty card to the roulette-manager.\n",this_player());
 say (this_player()->query_name()+" receives 250 "+colors [inte2]+" tokens.\n");
 add_tokens (this_player(),250,colors [inte2]);
 return 1;   
}

/* Wasn't that exciting? */

mcash () {
   inte2=ret_which_color (this_player()->query_real_name());
   if (rulla > 0 || players[inte2] != 0) {
      reply ("Please wait for the ball to stop before trying to claim your prize!\n");
      return 1;
   }
   ob=present ("roulettetoken",this_player());
   if (!ob || ob->query_tokens() < 1) {
      reply ("You can't cash in what you didn't win. Take a seat.\n");
      return 1;
   }
   this_player()->add_money(ob->query_tokens()*prize);
   remove_player_color(this_player()->query_real_name());
   reply ("You got "+ob->query_tokens()*prize+" dollars for "+ob->query_tokens()+" tokens.\n");
   say (this_player()->query_name()+" cashes in "+this_player()->query_possessive()+" "+ob->query_tokens()+" tokens.\n");
   if (this_player()->query_level() <SCI_LEVEL) {
      log_file ("pub.roulette",capitalize(this_player()->query_real_name())+"  ("+this_player()->query_level()+")  sold "+ob->query_tokens()+" tokens  "+ctime(time())+"\n");
   }
   
   destruct (ob);
   return 1;
}

mbets () { query_bets(); return 1; }

mplay (str) {
   if (!str) return 0;
   if (sscanf (str,"%s",del2) !=1) { return 0; }
   if (sscanf (del2,"%s on %s",antal,del3)!=2) { antal="1"; del3=del2; }
   if (sscanf (antal,"%d",antali)!=1) { write ("Bet how many?\n"); }
   if (antali < 0) return 0;
   /* Start of play */
   inte=0;
   while (inte < sizeof(squares) && del3!=squares[inte]) {
      inte=inte+1;
   }
   if (inte == sizeof(squares)) { write ("Bet on "); return 0; }
   ob = present ("roulettetoken",this_player());
   if (!ob) {
      reply ("Baha, there ain't no credit in this joint, chief. Get yourself some tokens.\n");
      return 1;
   }
   inte2=ret_which_color (this_player()->query_real_name());
   if (inte2==-1 || colors [inte2] != ob->query_color()) {
      reply ("We don't accept competitors' tokens.\n");
      return 1;
   }
   if (ob->query_tokens() < antali) {
      reply ("We don't let players ride on credit here, why don't you bet what you can cover.\n");
      return 1;
   }
   if (!ob->query_tokens()) {
      reply ("You're flat busted, buddy. Take a seat.\n");
      remove_player_color(ob->query_real_name());
      return 1;
   }
   if (players [inte2] ==0) players [inte2]="";
   players [inte2]=players [inte2] + antal +","+squares [inte] + ",";
   write (CYAN+"You play "+antal+" "+colors [inte2]+" tokens on "+squares[inte]+".\n"+RE);
   say (CYAN+this_player()->query_name()+" plays "+antal+" "+colors[inte2]+" tokens on "+squares [inte]+".\n"+RE);
   ob->add_tokens (-antali);
   ob->set_color (colors [inte2]);
   if (ob->query_tokens () <1) {
      destruct (ob);
   }
   if( rulla == 0 && find_call_out("rollit") == -1 ) call_out("rollit", 3);
   return 1;
}

add_tokens (whom,numb,kulor) {
   ob=present ("roulettetoken",whom);
   if (!ob) {
      ob=clone_object (TOKEN_FILE);
      move_object (ob,whom);
   }
   ob->add_tokens (numb);
   ob->set_color (kulor);
}
rollit () {
   remove_call_out ("rollit");
   tell_room (environment (this_object()),RED+"The ball bounces around.\n"+RE);
   rulla=rulla+1;
   if (rulla < 8) { call_out ("rollit",3); return 1; }
   tell_room (environment (this_object()),RED+"The ball finally stops at number...\n"+RE);
   call_out ("ballstop",3);
   return 1;
}
ballstop () {
   int vunnit_antal;
   int snurra;
   string s,s2,s3;
   object obj;
   curr_no = random (sizeof (squares)-5);
   snurra = curr_no-((curr_no/2)*2);
   if (snurra==1) curr_col="red"; else curr_col="black";
   if (curr_no==0) curr_col ="green";
   tell_room (environment (this_object()),"..."+curr_no+", "+curr_col+".\n");
   snurra=0;
   while (snurra < sizeof (colors)) {
      if (player_color[snurra]) {
         vunnit_antal=0;
         obj=present (player_color [snurra],environment (this_object()));
         while (players[snurra] && sscanf (players[snurra],"%s,%s,%s",s,s2,s3) > 1 && obj) {
            players [snurra]=s3;
            if (sscanf(s,"%d",antali)!=1) { antali=1; }
            if (squares[curr_no]==s2) {
               vunnit_antal=vunnit_antal+35*antali;
               tell_room (environment (this_object()),GREEN+capitalize(player_color [snurra])+" wins "+(35*antali)+" tokens for number "+s2+".\n"+RE);
                }
            if (curr_no >0 && curr_no <13 && s2=="s1") {
               vunnit_antal=vunnit_antal+3*antali;
               tell_room (environment (this_object()),GREEN+capitalize(player_color [snurra])+" wins "+(3*antali)+" tokens for numbers between 1-12.\n"+RE);
                }
            if (curr_no >12 && curr_no <25 && s2=="s2") {
               vunnit_antal=vunnit_antal+3*antali;
               tell_room (environment (this_object()),GREEN+capitalize(player_color [snurra])+" wins "+(3*antali)+" tokens for numbers between 13-24.\n"+RE);
                }
            if (curr_no >24 && curr_no <37 && s2=="s3") {
               vunnit_antal=vunnit_antal+3*antali;
               tell_room (environment (this_object()),GREEN+capitalize(player_color [snurra])+" wins "+(3*antali)+" tokens for numbers between 25-36.\n"+RE);
                }
            if (s2==curr_col) {
               vunnit_antal=vunnit_antal+2*antali;
               tell_room (environment (this_object()),capitalize(player_color [snurra])+" wins "+(2*antali)+" tokens for "+s2+".\n");
                }
          }
         if (vunnit_antal>0) add_tokens (obj,vunnit_antal, colors [snurra]);
          }
      snurra=snurra+1;
   }
   players = allocate (sizeof (colors)); /*Player bet where*/
   rulla=0;
   return 1;
}
query_bets () {
   int integer;
   integer=0;
   write ("\n");
   while (integer<sizeof (colors) ) {
      if (player_color [integer]) {
         write (player_color [integer]+" ("+colors [integer]+") \nBet: (<how many>,<number>,): "+players [integer]+".\n");
         }
      integer=integer+1;
   }
}
query_weight () {return 200;}
query_value () {return 0;}
get () {return 0;}
query_plyr(){ return players; }
query_plyrcol(){ return player_color; }

/* Added reset button because it still doesn't clear like it should.  --cygnus 05/99  */

reset_button(str)  
{
   
   object ob;
   
   if(!str || (str != "reset button" && str != "green button" && str != "green reset button")) 
      {
      notify_fail(capitalize(query_verb())+" what?\n");
      return 0;
   }
   
   if(this_player()->query_level() < 82) return write("The roulette-manager slaps your hand away from there, mumbling something\n"+
         "about killing you, your family, and everyone they know if you try to touch\n"+
      "that again.\n");
   write("You initiate the reset button on the roulette table. The game resets.\n");
   tell_room(environment(this_object()),break_string(this_player()->query_name()+" resets the roulette table.\n",78),({this_player()}));
   ob = clone_object(ROOM+"casino/roulette");
   move_object(ob,environment(this_object()));
   destruct(this_object());
   return 1;
}
