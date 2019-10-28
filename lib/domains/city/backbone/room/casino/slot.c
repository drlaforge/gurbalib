/* Darkman */

#include <def.h>
#include "casino.h"
#include "slot.h"


#define TPENV       ENV(TP)
#define MAX_IN		20
#define CHANCE      7000
#define CS(x,y)		colour_string(x, y, 0, this_player())
#define cWin	2
#define bWin	5
#define oWin	10
#define tWin	20
#define sWin	500

inherit "std/obj";

int dollar_in, reel_one, reel_two, reel_thr, winner, won, s;
int pulled;
string *reels;
static object user;

int calc_win();
int check_win();

inherit "std/obj";

void setup(void){
	 
	 
        set_id( ({ "machine", "slot machine",  "vintage gold", "slot" }) );
	set_name("slot machine");
	set_short("a slot machine");
        set_long("This is a vintage gold slot machine. It is pretty typical, a rectangular\n"+
                 "metal box with three huge dials and a big lever on the side. There is a slot\n"+
                 "where you can \"insert\" dollars, and a helpful \"help play\" display.\n");
	set_gettable(0);
	set_weight(1000000);
}

init() {
   ::init();
   add_action("hook_cmds", ({ "pull", "insert", "help" }) );
}

query_user(){ return user; }

filter_slots(ob){
	if( !living(ob) && ob->id("slot machine") ) return 1;
	return 0;
}

hook_cmds(str){
	object *obs;
	object mine;
	string func;
	int i;

	func = query_verb()+"_c";
	obs = filter_array( all_inventory( ENV(TO) ), "filter_slots", TO );
	for(i=0; i<sizeof(obs); i++){
		if( obs[i]->query_user() == TP ){
			mine = obs[i];
			break;
		}
		if(!obs[i]->query_user()){
			mine = obs[i];
		}
	}
	if( mine )
		call_other(mine, func, str);
	else
		write("All the slot machines seem to be in use, you'll have to wait your turn.\n");
	return 1;
}

display(str){
	write("The slot machine displays: "+str);
	return 1;
}

insert_c(str) 
{
	int amnt;
	if( !sscanf( str, "%d dollars", amnt ) && str != "dollar" && str != "money"
		&& str != "1 dollar") {
      write("Insert what?\n");
      return 1;
   }

   if (amnt < 0)
     {
      write("Stop that cheating!\n");
      return 1;
     }
 

   if( !amnt ) amnt = 1;
   if( amnt > MAX_IN ) return display("You can only have "+MAX_IN+" dollars in the slot machine!\n");
   if( (dollar_in+amnt) > MAX_IN)
      return display("You can only have "+MAX_IN+" dollars in the slot machine!\n");
   if( pulled ) return display("You already pulled the handle!\n");
   if( TP->query_money() < amnt ) return display("You don't have enough money.\n");
   TP->add_money(-amnt);
   PATRONS->add_money("slot", TP, -amnt);
   write("You put "+(amnt==1?"a dollar":amnt+" dollars")+" in the slot machine.\n");
   say(TP->QN+" puts "+(amnt==1?"a dollar":amnt+" dollars")+" into the slot machine.\n");
   user = TP;
   dollar_in += amnt;
   return 1;
}

pull_c( string str ) {
   if( str != "lever" && str != "handle" && str != "the handle" ) {
      write("Pull what?\n");
      return 1;
   }
   if(!dollar_in) return display(
         "You're supposed to put money in the machine to play it.\n");
   if(pulled) return display("The wheels on the machine are already spinning.\n");

   write("You pull the big lever on the side of the machine.\n");
   say(TP->QN+" pulls the lever on the side of the slot machine.\n", TPENV, TP);
   pulled = 1;
   calc_win();
   return 1;
}

calc_win() {
   write("The three reels of the machine have started spinning.\n");
   reels = ({ "orange", "cherry", "blank", "blank", "Super 7", "triple bar", "bell" });
   s = sizeof(reels);
   winner = random(CHANCE);
   switch( winner ) {  /*  Percentage it'll be this one in avg 10000 pulls - no error correction */      case 1..1000 :			/*  ~ 15.47% */		  reel_one = "cherry";
		  reel_two = "cherry";
		  reel_thr = "cherry";
		  won = cWin; break;
      case 1001..1500 :			/*  ~ 7.83% */		  reel_one = "bell";
		  reel_two = "bell";
		  reel_thr = "bell";
		  won = bWin; break;
      case 1501..1900 :			/*  ~ 6.29% */		  reel_one = "orange";
		  reel_two = "orange";
		  reel_thr = "orange";
		  won = oWin; break;
      case 1901..1990 :			/*  ~ 1.56% */		  reel_one = "triple bar";
		  reel_two = "triple bar";
		  reel_thr = "triple bar";
		  won = tWin; break;
      case 4444 :				/*  ~ 0.02 % */		  reel_one = "Super 7";
		  reel_two = "Super 7";
		  reel_thr = "Super 7";
		  won = sWin; break;
      default :					/*  ~ 70.07 % */		  reel_one = reels[random(s)];
		  reel_two = reels[random(s)];
		  reel_thr = reels[random(s)];
		  won = 0; break;
   }
   call_out("show_pics", 4, 1);
   return 1;
}

show_pics(int flag){
	string *one, *two, *three;
	int i;
	string delim;
	delim = " || ";
	if( flag == 1 ){
		write("The first wheel stops on "+reel_one+".\n");
		write( picMap[reel_one] );
		call_out("show_pics", 4, 2);
	}
	else if( flag == 2 ){
		write("The second wheel stops on "+reel_two+".\n");
		one = explode( picMap[reel_one], "\n" );
		two = explode( picMap[reel_two], "\n" );
		for(i=0; i<sizeof(one); i++)
			write( one[i]+delim+two[i]+"\n" );
		call_out("show_pics", 4, 3);
	}
	else if( flag == 3 ){
		if(reel_thr == reel_two && reel_thr == reel_one && !won)
			reel_thr = "blank";
		write("The third wheel stops on a "+reel_thr+".\n");
		one = explode( picMap[reel_one], "\n" );
		two = explode( picMap[reel_two], "\n" );
		three = explode( picMap[reel_thr], "\n" );
		for(i=0; i<sizeof(one); i++)
			write( one[i]+delim+two[i]+delim+three[i]+"\n" );
		check_win();
	}
	return 1;
}

check_win() {
   pulled = 0;
   user = 0;
   if(!won) {
      display("Sorry, better luck next time.\n");
      write("As you walk away, you think...come on, insert another dollar, I can win!\n");
	  say(TP->QN+" frowns sadly, loser.\n");
      dollar_in = 0;
      PATRONS->add_lost("slot", TP);
      return 1;
   }
   won = won*dollar_in;
   if( won > 200 )
	   write_file("/open/darkman/who.won",
	   sprintf("%s won %d dollars.\n", TP->QN, won) );
if( won < 0 ){
write_file("/open/darkman/slot.error",
TP->QN +" ("+won+") - Error on "+ctime(time())+"\n" );
}


   TP->add_money(won);
   PATRONS->add_money("slot", TP, won);
   PATRONS->add_won("slot", TP);
   display("Congratulations "+TP->QN+", you have won "+won+" dollars.\n");
   write("Some dollars drop out into the slot, you quickly scoop them up.\n"+
      "You feel lucky, insert another dollar to win again!\n");
   say(TP->QN+" smiles happily, "+TP->QPR+" just won "+won+" dollars!\n");
   dollar_in = 0;
   return 1;
}

help_c(str) {
   if(str == "play") {
      write(
         "In order to play simply <insert dollar or insert x dollar(s)>\n"+
		 "and pull the handle.\n"+
         " \n"+ 
         "The machine pays out as follows:\n"+
         " \n"+
         "cherry        cherry       cherry       "+cWin+"   dollar\n"+
         "bell          bell         bell         "+bWin+"   dollars\n"+
         "orange        orange       orange       "+oWin+"  dollars\n"+
         "triple bar    triple bar   triple bar   "+tWin+"  dollars\n"+
         "Super 7       Super 7      Super 7      "+sWin+" dollars  *JACKPOT*\n"+
         " \n"+
         "You can play up to "+MAX_IN+" dollars at a time. To find out home\n"+
         "many dollars you have won, just multiply the number of \n"+
         "dollars you played by the payouts above to determine your \n"+
         "winnings.\n\n"+
         "For example:  Three Super 7's with "+MAX_IN+" dollars in play\n"+
         "will pay 25,000 dollars.\n");
      return 1;
   }
   return call_other("/obj/bin/mortal/help", "main", str);
}
