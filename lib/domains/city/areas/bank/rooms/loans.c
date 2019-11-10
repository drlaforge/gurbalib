#include <def.h>
#include <banking.h>

inherit STD_ROOM;
void setup(){
    
    
   set_long_f("This new addition to the ACB building houses the Loans Department "+
      "of the bank. Expecting to see people sitting behind desks, you are a bit "+
      "suprised to see just booths along the wall with video screens. The whole "+
      "process seems to be automated these days. The bank lobby is to your south.\n", 78);
   add_item( ({ "booth", "booths", "video booths", "screens", "screen","video screens", "video screen" }),
      "Simple screens, you walk up to one of them and it only has one line displayed:\n\n"+
      "\t\tType: \"help loans\" for information");
   set_short("ACB Loan Dept.");
   set_light(1);
   set_outdoors(0);
   add_exit("south", "/domains/Areas/city/bank/lobby.c");
   add_help("loans", 
      sprintf("%:'=-'77s\n%|77s\n%:'-'77s\n\n%s\n%:'=-'77s\n",
         "","ACB Loans Help","",
         "Welcome to the Abacus Central Bank Loans Department. It is our\n"+
         "goal here to help you meet all your financial needs. Currently we\n"+
         "offer very affordable loans to all citizens of Abacus City. Below\n"+
         "you will find the specifics of what we offer:\n\n"+
         " 1) Any member of ACB can have up to two (2) loans at one time from ACB. \n"+
         " 2) Currently the interest rate is: "+LOAN_RATE+"%*\n"+
         " 3) ALL loans are due one (1) week from day of approval.\n"+
         " 4) If payment of loan plus interest incurred is not paid in full, a per diem\n"+
         "    fee of "+LOAN_OVER_RATE+"% interest is charged PER DAY to the remaining\n"+
         "    balance of your loan.\n"+
         " 5) Please make your payments on time, else we will be forced to seize funds\n"+
         "    from your checking account as available to us.\n\n"+
         "\nIf you understand and agree to these terms, please \"applyloan\" for a loan!\n\n"+
         " * Given rate assumes you have average credit history.\n"+
         "   Type \"checkrate\" to see what we can offer you.\n",
         "") );
}

void init(){
   ::init();
   add_action("checkRate", "checkrate");
   add_action("applyLoan", "applyloan");
}

int checkRate(){
   if( TP->query_history("late") >= HIGH_RISK )
      return !notify_fail("We can't give you a loan, you've been late on payments too many times!\n");
   write("Right now we can offer you a great rate of: "+TP->query_rate()+"%!\n");
   return 1;
}

int applyLoan(string am){
   int amount;
   
   if(!am) return !notify_fail("How much would you like to apply for? Syntax: \"applyloan <amount>\"\n");
   amount = atoi(am);
   if(!amount || (amount && amount <= 0) ) return !notify_fail("Please try again.\n");
   if(amount < MIN_LOAN) return !notify_fail("We only lend in amounts of $"+MIN_LOAN+" or more.\n");
   this_player()->add_loan(amount);
   if( !present("ACB_BANK_CARD", this_player()) ){
      move_object( clone_object("/domains/Areas/city/bank/bankcard.c"), this_player() );
      write("You have been given the new ACB Bank Card for your patronage.\n");
   }
   write("Thank you for using ACB Loan Services.\n");
   return 1;
}


