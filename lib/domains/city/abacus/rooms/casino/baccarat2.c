#include <tune.h>
#include <def.h>
#include "casino.h"
inherit "std/obj";
#define SAVEFILE    ROOM+"casino/baccarat2"
int totalBets;
int totalPayout;
int countDealer;
int countPlayer;
int countTie;
#define suits ({"S","H","D","C"})
#define values ({" A"," 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9","10"," J"," Q"," K"})

string *cards;
int *points;
void setup(void){
    
    
   set_name("baccarat table");
   set_alias(({"table","baccarat"}));
   set_short("a baccarat table");
   set_long("This is a baccarat table.\n" +
      "The dealer and player are dealt two cards each.\n" +
      "Cards Ace to Nine are worth their face value in points.\n" +
      "Cards Ten and higher are worth zero points.\n" +
      "The winner is the player with a modulus points total closest to nine.\n" +
      "You can bet on either your hand, the dealers hand or a tie.\n" +
      "A win pays evens and a tie pays 8 to 1.\n" +
      "If you bet on a player and the cards tie, your bet is refunded.\n" +
      "The house takes 5% of winnings on dealer.\n\n" +
      "To play 'bet xxx dollars on player/dealer/tie'\n" +
      "All bets must be in multiples of 100 dollars.\n");
   restore_object(SAVEFILE);
}

init(){
   ::init();
   add_action("playit", "bet");
}

playit(arg){
        int i;
        int dealerPoints;
        int playerPoints;
        int dealerThird;
        int playerThird;
        int ammount;
        string bet;
        if (!arg || sscanf (arg,"%d dollars on %s",ammount,bet)!=2) return write("Bet xx dollars on player/dealer/tie\n");
        if (bet != "player" && bet != "dealer" && bet != "tie")  return write("Bet xx dollars on player/dealer/tie\n");
        if (this_player()->query_money() < ammount) return write ("You don't have that much money.\n");
        if (ammount == 0 || (ammount-((ammount/100)*100)) > 0) return write("Bets must be in multiples of 100 dollars.\n");
 
       /* Wishbone 16Feb05 - winnings number too big for the mud to cope above here! */
        if(ammount > 10000000) return write("Maximum bet is $10,000,000.\n");
        if(ammount < 0)
         {
          write("Try betting a real amount of dollars!\n");
          return 1;
         }
          
        
        this_player()->add_money (-ammount);
        PATRONS->add_money("baccarat2", this_player(), -ammount);
        totalBets += ammount;
        points = ({0, 0, 0, 0, 0, 0});
        cards = ({"", "", "", "", "", ""});
        while(!checkcards())
        {
                for(i = 0; i < 6; i++)
                {
                        points[i] = random(13);
                        cards[i] = values[points[i]] + suits[random(4)];
                        points[i]++;
                        if(points[i] > 9) points[i] = 0;
                }
        }
        playerPoints = points[0] + points[2];
        if(playerPoints >= 10) playerPoints -= 10;

        dealerPoints = points[1] + points[3];
        if(dealerPoints >= 10) dealerPoints -= 10;

        playerThird = 0;
        dealerThird = 0;

        if(playerPoints < 8 && dealerPoints < 8)
        {
                if(playerPoints < 6)
                {
                        playerThird = 1;
                        playerPoints += points[4];
                        if(playerPoints >= 10) playerPoints -= 10;
                }

                if(playerThird == 0)
                {
                        if(dealerPoints < 6)
                        {
                                dealerThird = 1;
                                dealerPoints += points[5];
                                if(dealerPoints >= 10) dealerPoints -= 10;
                        }
                }
                else
                {
                        switch(points[4])
                        {
                                case 0..1:
                                        if(dealerPoints < 4)
                                        {
                                                dealerThird = 1;
                                                dealerPoints += points[5];
                                                if(dealerPoints >= 10) dealerPoints -= 10;
                                        }
                                        break;
                                case 2..3:
                                        if(dealerPoints < 5)
                                        {
                                                dealerThird = 1;
                                                dealerPoints += points[5];
                                                if(dealerPoints >= 10) dealerPoints -= 10;
                                        }
                                        break;
                                case 4..5:
                                        if(dealerPoints < 6)
                                        {
                                                dealerThird = 1;
                                                dealerPoints += points[5];
                                                if(dealerPoints >= 10) dealerPoints -= 10;
                                        }
                                        break;
                                case 6..7:
                                        if(dealerPoints < 7)
                                        {
                                                dealerThird = 1;
                                                dealerPoints += points[5];
                                                if(dealerPoints >= 10) dealerPoints -= 10;
                                        }
                                        break;
                                case 8:
                                        if(dealerPoints < 3)
                                        {
                                                dealerThird = 1;
                                                dealerPoints += points[5];
                                                if(dealerPoints >= 10) dealerPoints -= 10;
                                        }
                                        break;
                                case 9:
                                        if(dealerPoints < 4)
                                        {
                                                dealerThird = 1;
                                                dealerPoints += points[5];
                                                if(dealerPoints >= 10) dealerPoints -= 10;
                                        }
                                        break;
                        }
                }
        }
        if(this_player()->query_level() >= SCI_LEVEL && 1==2)
        {
                write("\n");
                write("DEBUG INFO:\n");
                for(i = 0; i < 6; i++)
                {
                        write("Card " + i + " : " + cards[i] + " : " + points[i] + "\n");
                }
                write("PlayerPoints: " + playerPoints + "\n");
                write("PlayerThird: " + playerThird + "\n");
                write("DealerPoints: " + dealerPoints + "\n");
                write("DealerThird: " + dealerThird + "\n");
        }
        write("\n");
        write("Your hand\n");
        if(playerThird == 0)
        {
                write(" .--------.  .--------. \n");
                write(" | " + cards[0] + "    |  | " + cards[2] + "    | \n");
                write(" |        |  |        | \n");
        }
        else
        {
                write(" .--------.  .--------.  .--------. \n");
                write(" | " + cards[0] + "    |  | " + cards[2] + "    |  | " + cards[4] + "    | \n");
                write(" |        |  |        |  |        | \n");
        }
        write("Worth " + playerPoints + " points.\n");
        write("\n");
        write("Dealers hand\n");
        if(dealerThird == 0)
        {
                write(" .--------.  .--------. \n");
                write(" | " + cards[1] + "    |  | " + cards[3] + "    | \n");
                write(" |        |  |        | \n");
        }
        else
        {
                write(" .--------.  .--------.  .--------. \n");
                write(" | " + cards[1] + "    |  | " + cards[3] + "    |  | " + cards[5] + "    | \n");
                write(" |        |  |        |  |        | \n");
        }
        write("Worth " + dealerPoints + " points.\n");
        write("\n");
        if(playerPoints > dealerPoints)
        {
                write("Players hand wins!\n");
                countPlayer++;
                if(bet == "player")
                {
                        action("#NA ## " + (ammount * 2) + " dollars on player.", "win-wins");
                        this_player()->add_money (ammount * 2);
                        PATRONS->add_money("baccarat2", this_player(), ammount * 2);
                        PATRONS->add_won("baccarat2", this_player());
                        totalPayout+=ammount * 2;
                        log_file("baccarat",TP->QN+" won $"+ammount*2+" at "+ctime(time())+".\n");
                }
                else
                {
                        action("#NA ## " + ammount + " dollars.", "lose-loses");
                        PATRONS->add_lost("baccarat2", this_player());
                        log_file("baccarat",TP->QN+" lost $"+ammount+" at "+ctime(time())+".\n");
                }
        }
        if(playerPoints < dealerPoints)
        {
                write("Dealers hand wins!\n");
                countDealer++;
                if(bet == "dealer")
                {
                        action("#NA ## " + (ammount * 195 / 100) + " dollars on dealer.", "win-wins");
                        this_player()->add_money (ammount * 195 / 100);
                        PATRONS->add_money("baccarat2", this_player(), ammount * 195 / 100);
                        PATRONS->add_won("baccarat2", this_player());
                        totalPayout+=ammount * 195 / 100;
                        log_file("baccarat",TP->QN+" won $"+(ammount*195)/100+" at "+ctime(time())+".\n");
                }
                else
                {
                        action("#NA ## " + ammount + " dollars.", "lose-loses");
                        PATRONS->add_lost("baccarat2", this_player());
                        log_file("baccarat",TP->QN+" lost $"+ammount+" at "+ctime(time())+".\n");
                }
        }
        if(playerPoints == dealerPoints)
        {
                write("Both hands tie!\n");
                countTie++;
                if(bet == "tie")
                {
                        action("#NA ## " + (ammount * 9) + " dollars for a tie.", "win-wins");
                        this_player()->add_money (ammount * 9);
                        PATRONS->add_money("baccarat2", this_player(), ammount * 9);
                        PATRONS->add_won("baccarat2", this_player());
                        totalPayout+=ammount * 9;
                        log_file("baccarat",TP->QN+" won $"+ammount*9+" at "+ctime(time())+".\n");
                }
                else
                {
                        action("#NA ## #PO money back for a tie.", "get-gets");
                        this_player() -> add_money (ammount);
                        PATRONS->add_money("baccarat2", this_player(), ammount);
                        totalPayout+=ammount;
                        log_file("baccarat",TP->QN+" tied for $"+ammount+" at "+ctime(time())+".\n");
                }
        }
        
        save_object(SAVEFILE);
        return 1;
}

checkcards(){
        int i;
        int j;
        for(i = 0; i < 5; i++)
        {
                for(j = i + 1; j < 6; j++)
                {
                        if(cards[i] == cards[j]) return 0;
                }
        }
        return 1;
}
