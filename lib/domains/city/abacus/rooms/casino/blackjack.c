/*			Black Jack V1.2
 *		      -=-=-=-=-=-=-=-=-=-
 *	  This game follows the real rules of black jack as I 
 *	know them. If you find bugs or anything wrong about the rules,
 *	please let me know by mailing me at AbacusMud / NuclearWarMud
 *	or tdi9110@abacus.hgs.se
 *
 *	  Configurate the game as you like in blackjack.h
 *
 *	  This version can take only one player per game and you
 *	you can't split the cards if you get a pair. That might be
 *	added in the future.
 *	  Enjoy !!:)
 *				/ Bigfoot.
 */

#include ROOM+"casino/blackjack.h"

/*-=-=-= Global Variables.. =-=-=-*/
static object busy;		/* Current player.		*/
static mixed colors;		/* Array of colors.		*/
static mixed numbers;		/* Array of numbers.		*/
static mixed *player_cards;	/* Vector of players cards.	*/
static mixed *dealer_cards;	/* Vector of dealers cards.	*/
static status insurance;	/* Insurance flag.		*/
static int bet;			/* The amount bet.		*/
#ifdef BALANCEPATH
int balance;			/* Game balance.		*/ 
#endif

void
reset (int arg)
{
        string foo;

	if (arg)
		return;

#ifdef BALANCEPATH
	restore_object (BALANCEPATH);
#endif
	colors = ({"H","S","D","C" });
	numbers = ({"A","2","3","4","5","6","7","8","9","10","J","Q","K" });
#ifdef USE_DEALER
	if (sscanf (file_name (this_object()), "%s#%s", foo, foo))
	        create_dealer ();
#endif
	reset_game ();
}

void
reset_game ()
{
	bet = busy = insurance = 0;
	player_cards = dealer_cards = ({});
}

string
short ()
{ 
	return "A Black Jack table";
}

void
long (string str)
{
	if (str=="book" || str=="rules" || str=="rulebook")
		return help_game(str);

	write ("It's a green table with several squares for the cards.\n" +
		"There is a rulebook hanging beside the table.\n");
#ifdef BALANCEPATH
	if (this_player()->query_level() >= WIZLEVEL)
		write("As a scientist you can check the total balance\n" +
		      "of this game by typing 'bjbalance'.\n");
#endif
	if (busy)
		write(busy->query_name()+" is busy playing.\n");
}

status
id (string str)
{
	return str == "table" || str=="blackjack table" ||
		str == "book" || str == "rules" || str == "rulebook";
}

void
init()
{
	add_action ("play",		"play");
	add_action ("stay",		"stay");
	add_action ("double",		"double");
	add_action ("bet",		"bet");
	add_action ("more_cards",	"card");
#ifdef BALANCEPATH
	if (this_player()->query_level() >= WIZLEVEL)
		add_action ("show_balance",	"bjbalance");
#endif
	add_action ("cancel_game",	"cancel");
	add_action ("help_game",	"read");
	add_action ("show_hand",	"hand");
}

status
play (string str)
{
	if (!str || (str!="cards" && str!="blackjack" && str!="black jack"))
		return nfail ("Play what?.\n");
#ifdef USE_DEALER
	if (!present ("dealer", environment()))
	{
		write("The dealer isn't here right now.\n");
		return 1;
	}
#endif
	if (busy && (!present (busy, environment()) || !query_ip_number(busy)))
		reset_game();
	if (busy && busy==this_player())
	        return R("You are already playing.\n", 1);
	if (busy)
		return R(busy->query_name() + " is busy playing.\n", 1);
	busy = this_player();
	say (busy -> query_name() + " plays a game of Black Jack.\n");
	return R("Place your bet, " +
			capitalize((string) busy->query_real_name())+".\n", 1);
}

status
bet (string amount)
{
	if (this_player() != busy)
		return 0;
	if (bet)
		return R("You have already placed your bet.\n", 1);
	if (!amount)
		amount = "0";
	if (!sscanf (amount, "%d", bet))
		return nfail ("Usage: bet <amount>.\n");
	if (bet < 10 || bet > MAXBET)
	{
		bet = 0;
		return R("You may only bet between 10 and " +
				MAXBET+" "+MONEYTYPE+".\n", 1);
	}
	if (!pay_money (bet))
	{
	        bet = 0;
		return  R("Place your bet.\n", 1);
	}
	R("Ok, your bet is "+bet+".\n"+
			"The dealer start dealing the cards.\n", 1);
	deal ();
	return 1;
}

status
more_cards ()
{
	if (this_player() != busy)
		return 0;
	if (!bet)
		return R("You better place your bet first.\n", 1);
	player_cards += get_cards (1);
	show_cards (player_cards);
	if (test_too_much(player_cards))
		return 1;
	card_help();
	return 1;
}

status
double ()
{
	if (this_player() != busy)
		return 0;
	if (!valid_double())
		return R("You can't do that now.\n",1);
	if (!pay_money(bet))
		return 1;
	bet *= 2;
	R("Ok, your bet is now "+bet+" "+MONEYTYPE+". You will now\n" +
		"only be able to receive one more card.\n", 0);
	player_cards += get_cards (1);
	show_cards (player_cards);
	if (test_too_much (player_cards))
		return 1;
	dealer_draws ();
	return 1;
}

status
stay ()
{
	if (this_player() != busy)
		return 0;
	if (!sizeof (player_cards))
		return R("But you haven't started yet..\n", 1);
	R("Ok, as you wish.\n", 0);
	if (valid_insurance())
		return 1;
	dealer_draws ();
	return 1;
}

void
deal ()
{
	player_cards += get_cards (2); 	
	dealer_cards += get_cards (1);
	show_cards (dealer_cards);
	show_cards (player_cards);
	if (calculate_points (player_cards)[1] == 21)
		return score (1, 1);
	if (valid_double())
		R("Now you can double your bet if you like.\n",0);
	card_help ();
	return;
}

void
insurance (string str)
{
	if (!str || (str[0]!='n' && str[0]!='y'))
	{
		write ("[y/n] : ");
		input_to ("insurance");
		return;
	}
	if (str[0]=='n')
		R("Ok, no insurance then.\n", 0);
	else
	{
		R("The insurance costs "+bet/2+" "+MONEYTYPE+".\n", 0);
		if (!pay_money (bet/2))
		{
			insurance (0);
			return;
		}
		insurance = 1;
	}
	dealer_draws ();
	return;
}
		

int *
calculate_points (mixed cards)
{
	status aceflag;
	int i, points;

	for (i=aceflag=points=0; i < sizeof (cards); i++)
	{
		if (cards[i][0] == 1)
			aceflag = 1;
		points += cards[i][0];
		if (cards[i][0] > 10) 
			points -= cards[i][0] % 10;
		if (aceflag && points+10 > 21)
			aceflag = 0;
	}
	if (aceflag)
		return ({ points, points+10 });
	return ({ points, 0 });
}	


mixed *
get_cards (int how_many)
{
	int *tmp;

	for (tmp = ({}); sizeof (tmp) < how_many; )
		tmp += ({({ random (13)+1 ,random (4) })}); 
	return tmp;
}

void
show_cards (mixed *cards)
{
	int i, j, *points;

	if (cards == player_cards)
		write ("Your hand:\n");
	else if (cards == dealer_cards)
		write ("My hand:\n");	
	for (i=0; i < sizeof (cards)/7+1; i++)	
	{
		for (j=0; j < 7 && j < sizeof(cards); j++)
			write(" .--------. ");
		write ("\n");
		for (j=0; j < 7 && j < sizeof(cards); j++)
			write(extract(" | " + numbers[cards[i+j][0]-1] +
				colors[cards[i+j][1]] + "     ",0,9) + "| ");
		write("\n");
		for (j=0; j < 7 && j < sizeof(cards); j++)
			write(" |        | ");
		write("\n");
	}
	points = calculate_points (cards);
	if (cards == player_cards)
		write ("You have ");
	else if (cards == dealer_cards)
		write ("I have ");
	write (points[0]);
	if (points[1])
		write (" or " + points[1]);
	write (".\n\n");
}

void
dealer_draws ()
{
	int stop, player_points, *tmp;

	write ("The dealer draws..\n");
	tmp = calculate_points (player_cards);
	player_points = tmp[0];
	if (tmp[1])
		player_points = tmp[1];
	while (!(stop = check_break(dealer_cards, player_points)))
		dealer_cards += get_cards (1);
	show_cards (dealer_cards);
	switch (stop)
	{
		case 1: R("I have too much.\n",0);
			score (1, 0);
			break;
		case 2: R("I have black jack!\n",0);
			if (insurance)
			{
				R("But since you have an insurance, you'll keep your money.\n",0);
				this_player()->add_money (bet);
				reset_game();
				break;			
			}
		case 3: score (0, 0);
			break;
		case 4: score (1, 0);
			break;
	}		
	return;
}

status				
check_break (mixed *cards, int player_points)
{
	int *points, point;

	points = calculate_points (cards);
	point = points[0];
	if (points[1])
		point = points[1];
	if (point < 17)
		return 0;
	if (point > 21)
		return 1;
	if (point >= 17)
	{
		if (sizeof(cards) == 2 && point == 21)
			return 2;
		if (point < player_points)
		{
			if (point == points[1] && points[0] < 17)
					return 0;
			return 4;
		}
		if (point >= player_points)
			return 3;
	}
}

void
score (status win, status black_jack){
   int draw;
/*     tell_room(environment(this_object()),"Player[0]="+calculate_points(player_cards)[0]+" Player[1]="+calculate_points(player_cards)[1]+" Dealer[0]="+calculate_points(dealer_cards)[0]+" Dealer[1]="+calculate_points(dealer_cards)[1]+"\n"); */	if (win)
	{
		int win_amount;
		win_amount = bet;
		if (black_jack)
		{
			write ("You have Black Jack!!\n");
			busy->add_money (bet/2);
			add_balance (bet/2);
			win_amount += bet/2;
		}
		R("Congratulations "+busy->query_name()+"!\n"+
			"                 You win "+win_amount+" "+MONEYTYPE+".\n",0);
		busy->add_money (bet*2);
		add_balance (bet);
		say(busy->query_name()+" wins "+win_amount+" "+MONEYTYPE+" on black jack.\n");
	}
	else
	{
       /*  Added that you get your stake back on a draw (push) - Mycon 08-10-2008 */       if(calculate_points(player_cards)[0] == calculate_points(dealer_cards)[0]){
          R("Draw 1\n",0);
          draw=1;
       }
       if(calculate_points(player_cards)[0] == calculate_points(dealer_cards)[1]){
          R("Draw 2\n",0);
          draw=1;
       }
       if(calculate_points(player_cards)[1] == calculate_points(dealer_cards)[0]){
          R("Draw 3\n",0);
          draw=1;
       }
       if(calculate_points(player_cards)[1] > 0 && calculate_points(player_cards)[1] > 0 && (calculate_points(player_cards)[1] == calculate_points(dealer_cards)[1])){
          R("Draw 4\n",0);
          draw=1;
       }
       if(draw){
          R("Draw! You get your stake back.\n",0);
          busy->add_money(bet);
       }
       else {
          R("Sorry, you lose your "+bet+" "+MONEYTYPE+".\n",0);
          add_balance (-bet);
          say(busy->query_name()+" loses "+bet+" "+MONEYTYPE+" on black jack.\n");
       }
	}
	reset_game();
	return;
}

void
add_balance (int amount)
{
#ifdef BALANCEPATH
	if (this_player()->query_level() >= WIZLEVEL)
                return;
	balance += amount;
        save_object(BALANCEPATH);
#endif
}

status
test_too_much (mixed *cards)
{
	if (calculate_points (cards)[0] <= 21)
		return 0;
	if (cards != player_cards)
		return 1;
	write("You have too much.\n");
	score (0, 0);
	return 1;
}



status
pay_money (int amount)
{
	if (this_player()->query_money() < amount)
		return R("You can't afford that!\n", 0);
	this_player()->add_money (-amount);
	return 1;
}

status
reply (string str, status ret)
{
	write ("The dealer says: " + str);
	return ret;
}

status
nfail (string str)
{
        notify_fail (str);
	return 0;
}

status
valid_double ()
{
	int points;
	if (sizeof(player_cards)!=2)
		return 0;
	points = calculate_points(player_cards)[0];
	if (points < 10 || points > 11)
		return 0;
	return 1;
}

status
valid_insurance ()
{
	if (sizeof (dealer_cards) != 1 || dealer_cards[0][0] != 1)
		return 0;
	input_to ("insurance");
	return R("I have an ace. Do you want insurance ?\n[y/n] : ",1);
}

void
create_dealer ()
{
	object dealer;

	if (environment() && present ("dealer", environment()))
		return;
	dealer = clone_object("/std/monster");
	dealer -> set_short ("a dealer");
	dealer -> set_name("A dealer");
	dealer -> set_alias("dealer");
	dealer -> set_long ("He's the guy dealing the cards. He looks like\n" +
			"he enjoys fooling people.\n");
	dealer -> set_level (12);
	dealer -> set_al (200);
	dealer -> set_ep (39000);
	dealer -> set_hp (140);
	dealer -> set_wc (13);
	dealer -> set_ac (4);
	dealer -> load_chat (4, ({
			"The dealer says: Money to win here!\n",
			"The dealer says: Insurance pays 2 to 1.\n",
			"The dealer says: A new deal right now just for you.\n"
			}));
	move_object (dealer, find_gameroom());
}

object
find_gameroom ()
{
	if (find_object (GAMEROOM))
		GAMEROOM -> force_load();
	return find_object (GAMEROOM);
}


status
card_help ()
{
	return R("If you want another card, type 'card', else 'stay'.\n", 1);
}

status
help_game (string str)
{
	if (!str)
		return 0;
	
	if (str != "book" && str != "rulebook" && str != "rules")
		return 0;
	write("Some rules:\n" +
	  "You should get as close to 21 as you can. Ace can be 1 or 11.\n"+
	  "10, jacks, queens and kings is all ten points. If you have\n"+
	  "more points than the dealer after the game, you'll win the pot.\n"+
	  "If you get 21 right after the deal, you have got a Black Jack,\n"+
	  "and wins 1.5 times your bet. If you have 10 or 11 right after\n"+
	  "the deal, you can double your bet if you want to. You bet must\n"+
	  "be 10-"+MAXBET+" "+MONEYTYPE+". The dealer must stay on 17 and more, and must\n"+
	  "take more cards on less than 17. If the dealer has an ace right\n"+
	  "after the deal, he will ask you fi you want to buy an insurance\n"+
	  "for half the bet. If you do, you'll keep your bet if the dealer\n"+
	  "get Black Jack. If you get more than 21 you have to much, and\n"+
          "lose the deal. If you for any reason can't play the game to its\n"+
          "end, you can cancel, but then you will lose all your bet money.\n"+
	  "        Good Luck!\n"+
	  "Commands:\n"+
	  " * Start playing the game...   -   'play cards'.\n"+
	  " * Place your bet...           -   'bet <amount>'.\n"+
	  " * More cards...               -   'card'.\n"+
	  " * Stay...                     -   'stay'.\n"+
	  " * Double your bet...          -   'double'.\n"+
	  " * Cancel...                   -   'cancel'.\n"+
	  " * Show your current cards...  -   'hand'.\n");
	return 1;
}

status
show_balance ()
{
	write("The game has given the players "+balance+" "+MONEYTYPE+".\n");
	return 1;
}

status
show_hand ()
{
        if (this_player() != busy)
	        return 0;
        if (!sizeof (player_cards))
	{
	        write ("You don't have any cards yet.\n");
		return 1;
	}
        show_cards (player_cards);
	return 1;
}

status
cancel_game ()
{
        if (this_player() != busy)
	        return 0;
        reset_game();
	return R("Ok, welcome back another time.\n", 1);
 }
 
