#include <def.h>
#include <banking.h>


inherit STD_AUTO;
inherit STD_OBJ;

string tFrom, tTo;
int tAm;

void setup(){
    
    
   set_short("ACB bank card");
   set_id( ({ "ACB_BANK_CARD", "bank card", "card", "acb card", "check card" }) );
   set_long_f("Introduced in early 2491, the ACB bank card allows "+
      "you to keep up to date with all your dealings with the Abacus Central "+
      "Bank. Programmed to respond only to your commands, this card will allow you to "+
      "check your accounts, loans and even submit payments. Simply type \"commands\" "+
      "to view a list of available commands.\n", 78);
   set_gettable(1);
   set_drop(1);
   set_weight(0);
}

void init(){
   ::init();
   add_action("showCmds", "commands");
   add_action("checkBal", "balances");
   add_action("checkLoan", "loans");
   add_action("checkAll", "printout");
   add_action("payLoan", "pay");
   add_action("iniTransfer", "move_object");
}

private void prHeader(string title){
/*     printf("%:'-'77s\n%|77s\n%|77s\n\n", "", title, sprintf("%:'-'"+strlen(title)+"s", "") ); */    printf("\n%|77s\n%|77s\n\n", title, sprintf("%:'-'"+strlen(title)+"s", "") );
}

private void prFooter(){
   printf("%-:'-'77s\n", "");
}

int showCmds(){
   prHeader("ACB Bank Card Command List");
   printf("%-15s%-62s\n%-15s%-62s\n\n%-15s%-62s\n%-15s%-62s\n\n%-15s%-62s\n%-15s%-62s\n\n",
      "balances", "Check your account balances.",
      "move_object", "Initiate a move_object of money.",
      "loans", "Check you loan balances and due dates.",
      "pay <X> <$Y>", "Pays $Y on loan X.",
      "printout", "Comrehensive printout of your finances with ACB.",
      "commands", "List of commands available via the bank card.");
   prFooter();
   return 1;
}

int checkBal(){
   mapping foo;
   string out;
   int i;
   string name;
   
   out = "";
   
   foo = TP->query_accounts();
   if(!foo || !mappingp(foo)) out = "You have no bank accounts at ACB.";
   else {
      for(i=0; i<m_sizeof(foo); i++)
      {
         name = m_indices(foo)[i];
         out += sprintf("%-15s", capitalize(name));
         if( name == "savings" )
            out += sprintf("%-40s%-30s\n", "$ "+TP->query_account(name)+" (Available: $ "+
              ((int)TP->query_account(name)-MIN_SAVINGS)+")",
            "Interest Earned: "+((int)TP->query_account(name) - foo[name][0]) );
         else
            out += sprintf("%-62s\n", "$ "+foo[name]);
      }
   }
   
   prHeader("ACB Balances");
   write(out+"\n");
   prFooter();
   return 1;
}

int checkLoan(string which){
   int wh;
   mapping foo;
   string out;
   int duet, due, i;
   int borrowed;
   float rate;
   
   if( which ) wh = atoi(which);
   foo = TP->query_loans();
   if(!foo || (foo && !m_sizeof(foo)))
      out = "You have no loans from ACB, we have great rates, come in and get one now!\n";
   else if( wh && pointerp(foo[wh]) ){
      out = "Information for Loan "+which+":\n\n";
      due = foo[wh][0];
      duet = foo[wh][1];
      duet += 604800;
      rate = foo[wh][2];
      borrowed = foo[wh][3];
      out += "\tAmount Borrowed:\t$ "+borrowed+"\n";
      out += "\tRate:\t\t\t"+rate+"%\n";
      out += "\tRemaining Balance:\t$ "+TP->query_loan_due(wh)+"\n";
      out += "\tDue on:\t\t\t"+(time() > duet?"This account is overdue!":ctime(duet))+"\n";
   }
   else 
      {
      out = "(Type: loans <number> to see detail on the loan)\n\n";
      for(i=0; i<m_sizeof(foo); i++){
         out += sprintf("%-20s%-52s\n", "Loan #: "+m_indices(foo)[i], "Due: $ "+TP->query_loan_due(m_indices(foo)[i])+
            " by: "+ctime(foo[m_indices(foo)[i]][1]+(604800)) );
      }
   }
   
   prHeader("ACB Loans");
   write(out+"\n");
   prFooter();
   return 1;
}

int checkAll(){
   int x;
   int i;
   
   i = TP->query_loans() ? m_sizeof( (mapping)TP->query_loans() ) : 0;
   checkBal();
   if( i > 0 ){
      for(x=0; x<i; x++)
      checkLoan(""+(x+1));
   }
   else
      checkLoan(0);
   return 1;
}

int payLoan(string which){
   mixed wh, am;
   if(!which) return !notify_fail("Pay which loan? Check the \"loans\" command for the right number.\n");
   if( sscanf( which, "%s $%s", wh, am) != 2 && sscanf( which, "%s %s dollars", wh, am) != 2 )
      return !notify_fail("Syntax: pay <loan #> $<amount> or pay <loan #> <amount> dollars\n");
   TP->pay_loan( atoi(wh), atoi(am) );
   return 1;
}

int iniTransfer(){
   write("From what account do you wish to move_object? ");
   input_to("getTranFrom");
   return 1;
}

int getTranFrom(string str){
   if(!str || strlen(str) < 1) return !notify_fail("You must enter an account, move_object terminated.\n");
   str = lowercase(str);
   if( member_array( str, m_indices( (mapping)TP->query_accounts() ) ) == -1 ){
      write("You have no such account. Try again: ");
      input_to("getTranFrom");
      return 1;
   }
   
   tFrom = str;
   write("To which account do you wish to move_object? ");
   input_to("getTranTo");
   return 1;
}

int getTranTo(string str){
   if(!str || strlen(str) < 1) return notify_fail("You must enter an account, move_object ended.\n");
   str = lowercase(str);
   if( member_array( str, m_indices( (mapping)TP->query_accounts() ) ) == -1 ){
      write("You have no such account. Try again: ");
      input_to("getTranTo");
      return 1;
   }
   
   if( str == tFrom ){
      write("Same account. Try again: ");
      input_to("getTranTo");
      return 1;
   }
   
   tTo = str;
   write("How much would you like to move_object: ");
   input_to("getTranAm");
   return 1;
}

int getTranAm(string str){
   if(!str || strlen(str) < 2) return notify_fail("Nothing entered, move_object ended.\n");
   if( !sscanf(str, "$%d", tAm) && !sscanf(str, "%d$", tAm) )
      tAm = atoi(str);
   
   if(!tAm) return notify_fail("Nothing entered, move_object ended.\n");
   if(tAm < 0 ) return notify_fail("Invalid amount, move_object ended.\n");
   ("/domains/Areas/city/bank/quickbank.c")->move_objectMoney( tAm+" from "+tFrom+" to "+tTo );
   tAm = 0;
   tFrom = 0;
   tTo = 0;
   return 1;
}

