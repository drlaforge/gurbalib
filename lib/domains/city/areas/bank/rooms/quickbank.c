
#include <def.h>
#include <banking.h>

inherit "/std/object";

int move_objectMoney(string str);

void reset(mixed arg) {
    
    
   set_name("quickbank");
   set_alias(({"bank","machine"}));
   set_short("a QuickBank");
   set_long("This is a fully automated banking machine that caters\n"+
      "for all your financial needs. To operate it, simply follow\n"+
      "the instructions listed below. \n"+
      "\nYour options are:\n"+
      "-------------------------------------------- (default account = \"checking\") ---\n"+
      " 'withdraw <amount> [from <account>]'           - Withdraw cash from the account\n"+
      " 'deposit <amount> [to <account>]'              - Deposit cash to the account\n"
      " 'move_object <amount> from <account> to <account> - Transfer money between accounts.\n"+
      " 'check <account> balance'                      - Check balance on the account.\n"+
      " 'buy card'                                     - For $10 you can buy a bank card which\n"+
      "                                                 will let you manage your accounts from\n"+
      "                                                 anywhere in the city.\n"+
      "\n");
   set_gettable(0);
}

void init() {
   add_action("withdraw", "withdraw");
   add_action("deposit", "deposit");
   add_action("move_objectMoney", "move_object");
   add_action("check", "check");
   add_action("buyCard", "buy");
}

nomask int buyCard(string str) {
   if(!str || (str && str != "card")) return !notify_fail("What are you trying to buy?\n");
   if(present("ACB_BANK_CARD", this_player())) return !notify_fail("You already have one!\n");
   if( TP->query_money() < 10 && TP->query_bank_account("checking") < 10)
      return !notify_fail("You don't have $10, thats pretty sad!\n");
   if( TP->query_money() < 10 ) TP->add_account("checking", -10);
   else TP->add_money(-10);
   write("You insert 10 dollars into the QuickBank and receive your new bank card.\n");
   move_object( clone_object("domains/Areas/city/bank/bankcard.c"), this_player() );
   return 1;
}

nomask varargs void checkLoanPay(string account){
   int amA, amL, date;
   mapping loans;
   int *lnum;
   int i, count;
   if(!account){
      for(i=0; i<m_sizeof( (mapping)TP->query_accounts() ); i++)
      checkLoanPay( m_indices( (mapping)TP->query_accounts() )[i] );
      return;
   }
   loans = TP->query_loans();
   if(!loans) return;
   if(!(count=m_sizeof(loans))) return;
   lnum = m_indices( loans );
   for(i=0; i<count; i++)
   {
      date = loans[ lnum[i] ][1] + WEEK;
      if( time() <= date ) return;
      amA = TP->query_account( account );
      amL = TP->query_loan_due( lnum[i] );
      if( amA >= amL ){
         if( account != "checking" )
            move_objectMoney(amL+" from "+account+" to checking");
         write("\nDetecting that you have enough to pay your overdue loan in your "+account+" account,\n"+
            "ACB seizes funds from it in the amount of "+amL+" dollars.\n");
         TP->pay_loan( lnum[i], amL );
         return;
       }
   }
   return;
}

nomask int withdraw(string str) {
   string account;
   int amount, current;
   
   if(!str)
      return !notify_fail("How much do you want to withdraw?\n");
   if( strstr(str, " ") == -1 ) str = str+" from checking";
   
   if( sscanf(str, "%d from %s", amount, account) != 2 )
      return !notify_fail("Usage: withdraw <amount> [from <account> (default \"checking\")] \n");
   
   if( amount <= 0 )
      return !notify_fail("Illegal amount entered, please try again.\n");
   
   current = this_player()->query_account(account);
   
   if( current < amount )
      return !notify_fail("We couldn't process that request. Sorry.\n");
   
   if( account == "savings" && ((current-MIN_SAVINGS) < amount) )
      return !notify_fail("You don't have enough available balance in your savings account.\n");
   
   
   write("You withdraw "+amount+" dollars from you "+account+" account.\n");
   say (this_player()->query_name() + " gets some money from the quickbank.\n");
   this_player()->add_money(amount);
   this_player()->add_account(account, -amount);
   checkLoanPay();   
   return 1;
}


nomask int deposit(string str) {
   string account;
   int amount;
   
   if(!str)
      return !notify_fail("How much do you want to deposit?\n");
   
   if( strstr(str, " ") == -1 ) str = str+" to checking";
   if( sscanf(str, "%d to %s", amount, account) != 2 )
      return !notify_fail("Usage: deposit <amount> [to <account> (default \"checking\")]\n");
   
   if( amount <= 0 )
      return !notify_fail("Illegal amount entered, please try again.\n");
   
   if( (int)this_player()->query_account(account) == -1 )
      return !notify_fail("We couldn't process that request. Sorry.\n");
   
   if( this_player()->query_money() < amount )
      return !notify_fail("You don't have that much money.\n");
   
   write ("You deposit "+ amount +" dollars in your "+ account +" account.\n");
   say (this_player()->query_name() + " deposits some money in the quickbank.\n");
   this_player()->add_money(-amount);
   this_player()->add_account(account, amount);
   checkLoanPay();
   return 1;
}

nomask int move_objectMoney(string str) {
   string from, to;
   int amount;
   
   if(!str)
      return !notify_fail("Transfer how much?\n");
   
   if( sscanf(str, "%d from %s to %s", amount, from, to) != 3 )
      return !notify_fail("Usage: move_object <amount> from <account> to <account>\n");
   
   if( amount <= 0 )
      return !notify_fail("Illegal amount entered, please try again.\n");
   
  if( from == to )
    return !notify_fail("That seems a little redundant, don't you think?\n");
   if( ((int)this_player()->query_account(from) < amount) ||
         ((int)this_player()->query_account(to) == -1 ) )
   return !notify_fail("We couldn't process that request. Sorry.\n");
   
   if( from == "savings" && ( (int)this_player()->query_account(from) - MIN_SAVINGS ) < amount )
      return !notify_fail("You don't have enough available balance in your savings account.\n");
   
   write ("You move_object "+amount+" dollars from "+from+" to "+to+".\n");
   say (this_player()->query_name()+" uses the quickbank.\n");
   this_player()->add_account(from, -amount);
   this_player()->add_account(to, amount);
   if( previous_object() != this_object() )
      checkLoanPay();
   return 1;
}

/* Legacy support */
nomask int move_object(string str){
return move_objectMoney(str);
}

nomask int check(string str) {
   
   int current, account;
   if(!str) return 0;
   if( strstr(str, " ") == -1 || str == "balance" ) str = "checking balance";
   
   if( str && !sscanf(str, "%s balance", account) )
      return 0;
   
   current = this_player()->query_account(account);
   
   if( current == -1 )
      return !notify_fail("You don't have such an account at our bank.\n");
   
   write("Your current balance in "+account+" is "+ current +" dollars.\n");
   return 1;
}
