#include "../backbone.h"
inherit STD_MONSTER;
int booties;
string func, type, match;

void setup(void){
    
   booties = 0;
    
   set_name("mutant");
   set_level(3);
   set_race("mutant");
   set_short("a horrible looking mutant");
   set_long_f("A horrible looking mutant, begging for money.\n");
   func = allocate(1);
   type = allocate(1);
   match = allocate(1);
   func[0] = "give_beggar";
   type[0] = "gives";
   set_match(TO, func, type, match);
   load_chat(2,({
      "Mutant says: Please, give money to a poor mutant!\n",
      "Mutant says: Why can't I find any money ?\n",
      "Mutant says: two dollars please !\n",
   }));
   load_a_chat(10,({
      "Mutant says: Why do you do this to me?\n",
      "Mutant says: Get away from me!\n",
      "Mutant says: Leave me alone!\n",
   }));
}
 
give_beggar(str) {
   int money;
   string who;

   say("Mutant says: Thank you.\n");
   if (sscanf(str, "%s gives you %d dollars.", who, money) != 2)
      return;
    
   if(TO->query_money() >= 20){
      command("west",TO);
      command("buy beer",TO);
      command("east",TO);
      command("drink beer",TO);
   }

   if (TO->query_money() >= 1000 && !booties){
      W("Mutant says: You are so generous... Please take these!\n");
      S("The mutant pulls off his boots and throws them towards "+TP->QN+".\n");
      move_object(clone_object(OBJ+"mark1"),ENV(TO));
      booties = 1;
   }
}
