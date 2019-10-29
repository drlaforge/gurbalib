
#include "convoy.h"

inherit STD_OBJ;

#define Ticker 3
#define Length 2
#define Wait   3

#define Dir0   "East"
#define Dir1   "West"
#define Min    0
#define Max    5

static object SubObj;
static object HoldObj;
static int location;
static int moving;
static int direction;
static mapping Locations;

private int realEnter(object who);

private void load_locations(){
   int *key;
   int i;
   
   key = m_indices(Locations);
   for(i=0; i<sizeof(key); i++)
   (Locations[key[i]])->load_me();
}

private void configure(){
   if(!SubObj) SubObj = clone_object( SubRoom );
   if(!HoldObj) HoldObj = clone_object( HoldRoom );
   if(!location) location = Max;
   moving = 0;
   SubObj->setControl( TO );
   Locations = ([
         0 : Abacus,
	 1 : Convoy+"lighthouse",
         2 : Dragon,
         3 : Convoy+"prison",
         4 : Convoy+"surfers",
         5 : Abacus ]);
   direction = -1;
   
}

int query_location(){ return location; }
int query_moving(){ return moving; }
string query_obs(){ return sprintf("%O\n%O", SubObj, HoldObj); }
mapping query_locations(){ return Locations; }
string query_direction_string(){ return (direction==-1?Dir1:Dir0); }

void tell_sub(string str){
   if(SubObj)
      tell_room(SubObj, str);
}

void setup(){
    
    
   set_name("submarine");
   set_id(({"sub"}),({"black submarine"}),({"black sub"}));
   set_short("A black submarine");
   set_long_f(
        "The submarine is about 15 metres long. It is matte black, "+
        "with very few features. It is almost certainly on automatic, "+
        "constantly ferrying people and cargo to whatever destinations "+
	"remain in the ocean. If you have enough money, \"enter sub\" to "+
	"see where it goes.", 75);
   set_gettable(0);
   set_weight(1002010);
   if( cloned() ) configure();
}

void hook_destruct(){
   if(SubObj) destruct( SubObj );
   if(HoldObj) destruct( HoldObj );
}

void init(){
   ::init();
   add_action("enterSub", "enter");
   add_action("enterSub", "board");
}

int enterSub(string str){

   int money;
   
   if(!SubObj) return !notify_fail("The submarine can't take any more passengers right now.\n");
   if(!str) return !notify_fail("Yes, enter what?\n");
   if(id(str)){
      money = this_player()->query_money();
      if( money < TicketPrice ){
         if( present("ACB_BANK_CARD", TP) ){
            money = TP->query_bank_account();
            if( money < TicketPrice )
               return !notify_fail("The ticket price is $"+TicketPrice+". Come back when you have enough money.\n");
            else {
               write("You scan your bank card through the slot and it deducts $"+TicketPrice+" from your account.\n");
               TP->add_account("checking", -(TicketPrice) );
               return realEnter(TP);
            }
         }
         return !notify_fail("The ticket price is $"+TicketPrice+". Come back when you have enough money.\n");
      }
      write("You drop your $"+TicketPrice+" into a slot.\n");
      TP->add_money(-(TicketPrice));
      return realEnter(TP);
   }
   
   return !notify_fail("Um, don't think you can enter that.\n");
}

int realEnter(object who){
   TP->move_player("into the submarine.", SubObj);
   if( find_call_out("moveMe") == -1 )
      call_out("moveMe", Ticker, Length);
   return 1;
}

int peopleOn(object ob){
   object *obs;
   int i;
   
   obs = all_inventory(ob);
   for(i=0; i<sizeof(obs); i++)
   if( userp(obs[i]) ) return 1;
   
   return 0;
}

void moveMe(int tick){
   if(!tick){
      location += direction;
      if( location == Min ) direction = 1;
      if( location == Max ) direction = -1;
      move_object(TO, Locations[location]);
      tell_sub("The submarine surfaces and the door opens.\n");
      tell_sub("A voice beeps: Arrived at "+ENV(TO)->real_short()+"!\n");
      tell_room( ENV(TO), "A black submarine surfaces and it's door opens.\n");
      moving = 0;
      call_out("moveMe", Ticker*Wait, Length);
      return;
   }
   if( tick == Length )
      {
      tell_sub("The submarine dives into the inky blackness and continues its voyage.\n");
      /*  "Hide" the bus */      tell_room( ENV(TO), "The submarine submerges, leaving nothing more than a few bubbles.\n");
      move_object( TO, HoldObj );
   }
   else
      tell_sub("The submarine continues its voyage through the inky blackness of the ocean.\n");
   call_out("moveMe", Ticker, (tick-1));
   moving = 1;
   return;
}

