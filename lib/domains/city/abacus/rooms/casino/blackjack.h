
#include <tune.h>

/* To keep track of the game balance,  define the filename where to save it.
 */
#define BALANCEPATH ROOM+"casino/data/blackjackbalance"

/* The filename to the room where the table shall be.
 */
#define GAMEROOM      ROOM+"casino/bRoom.c"

/* What type of money do the game use. "dollars", "gold coins" or whatever.
 */
#define MONEYTYPE	"dollars"

/* How much will the players be able to bet.
 */
#define MAXBET		10000

/* The lowest level of a wizard. Normally 21.
 */ 
#ifdef SCI_LEVEL
#define	WIZLEVEL	SCI_LEVEL
#else
#define WIZLEVEL ROOKIE_LEVEL
#endif
/* If you want a dealer to be cloned, define this.
 */
/*#define USE_DEALER
*/
 
/* End of configuration */

/*-=-=-= Declarations.. =-=-=-*/
void deal ();
void show_cards (mixed *cards);
void reset_game ();
void dealer_draws ();
void create_dealer ();
void help_game (string str);
object find_gameroom ();
void add_balance (int amount);
void score (status win, status black_jack);
status card_help ();
status nfail (string str);
status valid_insurance ();
status valid_double ();
status pay_money (int amount);
status reply(string str, status ret);
status test_too_much (mixed *cards);
int *get_cards (int how_many);
int check_break (mixed *dealer_cards, int player_points);
mixed *calculate_points (mixed *cards);

#define R(XX,YY)	reply(XX,YY)

