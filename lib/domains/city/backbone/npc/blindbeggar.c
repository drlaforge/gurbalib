#include "../backbone.h"
inherit STD_MONSTER;
int cloakie;
string func, type, match;

void setup(void){
    
   cloakie = 0;
    
   set_name("beggar");
   set_level(8);
   set_short("a blind beggar");
   set_long_f("The beggar has a long robe, covering his eyes. "+
      "He is down on his luck and in desperate need of some money.\n");
   func = allocate(1);
   type = allocate(1);
   match = allocate(1);
   func[0] = "give_beggar";
   type[0] = "gives";
   set_match(TO, func, type, match);
   load_chat(2,({
      "Beggar says: Please, give some money!\n",
      "Beggar says: I just need a little money...\n",
      "Beggar says: Can't you help me?\n",
   }));
   load_a_chat(10,({
      "Beggar says: Please leave me alone!\n",
      "Beggar says: I can't see, what are you doing!\n",
      "Beggar screams: I only wanted a bit of spare change!\n",
   }));
}

give_beggar(str) {
   int money;
   string who;
   object weapon;

   S("Beggar says: Thank you so much.\n");
   if (sscanf(str, "%s gives you %d dollars.", who, money) != 2)
      return;
    
   if (TO->query_money() >= 1000 && !cloakie) {
      S("Beggar says: You are so kind. I must repay you!\n");
      S("The beggar pulls off his dark glasses and throws them towards you.\n");
      move_object(clone_object(OBJ+"mark2"),ENV(TO));
      cloakie = 1;
   }
}

