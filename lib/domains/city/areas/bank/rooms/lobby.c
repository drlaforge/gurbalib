#include <banking.h>
#include "../area.h"

inherit STD_ROOM;

void setup(void){
   
    
    
   set_light(1);
   set_short("Abacus Central Bank");
   set_long("You stand in the Abacus Central Bank's central office.\n"+
      "The walls are bare and cold, and the room is empty with the\n"+
      "exception of a series of monitors that hang from the roof. A\n"+
      "fully automated multi-user Quickbank supercomputer runs along\n"+
       "the length of the east wall.");
   add_item("sign", "As you suspected, it says \"LOANS!\"");
   add_item("door", "north door", "open door", "A simple open door");
   add_item("computer","supercomputer","computers","super computer", "It's a computer. It's super. A supercomputer");
   add_item("rods", "A collection of long metallic rods which support the banks information monitors");
   add_item("roof", "A number of monitors are atrached to the high vaulted roof, via\n"+
      "a number of long steel rods\n");
   add_item("east wall", "The east wall is partially covered by a huge Quickbank AMT\n"+
      "which represents the latest form of hi-tech banking\n");
   add_item("rod", "A collection of long metallic rods which support the banks information monitors");
   add_item("monitors","monitor", "The monitor reads:\n"+
      "\n"+
      "Welcome to ACB's central banking office. We offer a wide range\n"+
      "of financial services. If you would like a bank account simply\n"+
      "examine the fully automated Quickbank machine in front of you,\n"+
      "where full instructions are given.\n"+
      "\n"+
      "\n"+
      "ACB - 'YOU CAN BANK ON US!'\n");
   add_item("vaulted roof", "A number of monitors are atrached to the high vaulted roof, via\n"+
      "a number of long steel rods\n");
   add_item("long steel rods", "A collection of long metallic rods which support the banks information monitors");
   add_item("walls", "The walls are whitewashed and plain in appearance, with the\n"+
      "exception of a large multi-user Quickbank attached to the\n"+
      "east wall.\n");
   add_item("wall", "The walls are whitewashed and plain in appearance, with the\n"+
      "exception of a large multi-user Quickbank attached to the\n"+
      "east wall.\n");
   add_item("steel rods", "A collection of long metallic rods which support the banks information monitors");
   add_item("information monitor", "The monitor reads:\n"+
      "\n"+
      "Welcome to ACB's central banking office. We offer a wide range\n"+
      "of financial services. If you would like a bank account simply\n"+
      "examine the fully automated Quickbank machine in front of you,\n"+
      "where a full instructions are given.\n"+
      "\n"+
      "\n"+
      "ACB - 'YOU CAN BANK ON US!!'\n");
   add_item("information monitors", "The monitor reads:\n"+
      "\n"+
      "Welcome to ACB's central banking office. We offer a wide range\n"+
      "of financial services. If you would like a bank account simply\n"+
      "examine the fully automated Quickbank machine in front of you,\n"+
      "where a full instructions are given.\n"+
      "\n"+
      "\n"+
      "ACB - 'YOU CAN BANK ON US!!'\n");
   add_object("domains/city/areas/bank/quickbank", 1);
   add_exit("west", "room/eden1");
   
}

/*void init(){
   ::init();
 Not Yet
   add_action("openAcc", "open");

}*/

int openAcc(string str){
   int frPock, frCheck;
   
   if(!str) return !notify_fail("Open what? A savings account?\n");
   if( str == "account" ) return !notify_fail("Do you mean a savings account?\n");
   if(str != "savings" && str != "savings account" ) return !notify_fail("Do you mean a savings account?\n");
   if( (int)TP->query_account("savings") > 0 ) return !notify_fail("It seems you already have a savings account.\n");
   frPock = TP->query_money();
   frCheck = TP->query_account("checking");
   
   if( frPock < 100 && frCheck < 100 ) return !notify_fail("You need $"+MIN_SAVINGS+" to open a savings account.\n");
   
   if( frPock >= 100 ){
      write("You insert $100 into the slot. The screen reads: \"Thank you, Savings Account Opened.\"\n");
      TP->add_money(-100);
   }
   else
      {
      write("The bank draws $100 from your checking account. The screen reads: \"Thank you, Savings Account Opened.\"\n");
      TP->add_account("checking", -100);
   }
   TP->add_new_account("savings", 100);
   return 1;
}

