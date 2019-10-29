
#include "convoy.h"

inherit STD_OBJ;

#define Ticker 2
#define Length 1
#define Wait   3

#define Dir0   "north"
#define Dir1   "south"
#define Min    -2
#define Max    3

static object BusObj;
static object HoldObj;
static int location;
static int moving;
static int direction;
static mapping Locations;
static mapping Lengths;

private int realEnter(object who);

private int getLength(int location){
   int ord;
   ord = direction;
   if( direction == -1 ) ord = 0;
   return Lengths[location+direction][ord];
}


private void load_locations(){
   int *key;
   int i;
   
   key = m_indices(Locations);
   for(i=0; i<sizeof(key); i++)
   (Locations[key[i]])->load_me();
   
}

private void configure(){
   if(!BusObj) BusObj = clone_object( BusRoom );
   if(!HoldObj) HoldObj = clone_object( HoldRoom );
   if(!location) location = 0;
   moving = 0;
   BusObj->setControl( TO );
   Locations = ([
        -2 : Convoy+"ded_gates",
         -1 : Convoy+"wasteland",
         0 : Abacus,
         1 : Carnival,
         2 : Convoy+"fieldmount",
         3 : Convoy+"jungle" ]);
   
   Lengths = ([
         3 : ({ Length+1, Length+1 }),
         2 : ({ Length+1, Length+1 }),
         1 : ({ Length+1, Length }),
         0 : ({ Length, Length+2 }),
         -1 : ({ Length+2, Length+2 }),
         -2 : ({ Length+2, Length+2 }) ]);
   
   
   direction = 1;
   
}

int query_location(){ return location; }
string query_location_desc(){ return (string)(Locations[query_location()]->short()); }
int query_moving(){ return moving; }
string query_obs(){ return sprintf("%O\n%O", BusObj, HoldObj); }
mapping query_locations(){ return Locations; }
string query_direction_string(){ return (direction==-1?Dir1:Dir0); }

void tell_bus(string str){
   if(BusObj)
      tell_room(BusObj, str);
}

void setup(){
    
    
   set_name("apc");
   set_alias(({"APC","battered APC","bus"}));
   set_short("a battered APC");
   set_long_f("The APC is quite battered with a lot of it's paint removed by battle scars. "+
		"The APC fairly large and could hold quite a few people. These days the driver uses it "+
		"as a bus to shuttle people around the region. If you have enough money 'enter apc' for "+
		"a ride.\n");
   set_gettable(0);
   set_weight(1002010);
   if( cloned() ) configure();
}

void hook_destruct(){
   if(BusObj) destruct( BusObj );
   if(HoldObj) destruct( HoldObj );
}

void init(){
   ::init();
   add_action("enterBus", "enter");
   add_action("enterBus", "board");
}

int enterBus(string str){
   int money;
   
   if(!BusObj) return !notify_fail("The driver isn't taking any more passengers right now.\n");
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
      write("You hand over $"+TicketPrice+" to the driver and enter the APC.\n");
      TP->add_money(-(TicketPrice));
      return realEnter(TP);
   }
   
   return !notify_fail("Um, don't think you can enter that.\n");
}

int realEnter(object who){
   TP->move_player("into the APC.", BusObj);
   if( find_call_out("moveMe") == -1 )
      call_out("moveMe", Ticker, getLength(location));
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
      tell_bus("The APC grinds to a halt and the pneumatic doors open.\n");
      tell_bus("The APC driver yells: We're at the "+ENV(TO)->real_short()+"!\n");
      tell_room( ENV(TO), "An APC arrives and grinds to a halt, it's heading "+query_direction_string()+".\n");
      moving = 0;
      call_out("moveMe", Ticker*Wait, getLength(location));
      return;
   }
   if( tick == getLength(location) )
      {
      tell_bus("The APC jolts to a start and races along the road to the "+query_direction_string()+".\n");
      /*  "Hide" the bus */      tell_room( ENV(TO), "The APC races off to the "+query_direction_string()+".\n");
      move_object( TO, HoldObj );
   }
   else
      tell_bus("The APC continues at a very quick pace to the "+query_direction_string()+".\n");
   call_out("moveMe", Ticker, (tick-1));
   moving = 1;
   return;
}

