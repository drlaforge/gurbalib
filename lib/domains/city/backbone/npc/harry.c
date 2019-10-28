#include "../backbone.h"
inherit STD_MONSTER;
string func, type, match;
int not_following;

void setup(void){
    
    
   add_object(OBJ+"ledtorch",1);
   set_match(TO,func,type,match);
   set_name("harry");
   set_alias(({"mutant","pimp","bastard"}));
   set_surname("Bastard the Mutant Pimp");
   set_short("Harry Bastard the mutant pimp");
   set_long_f("Harry Bastard the mutant pimp. He is looking for all his little mutant bitches.\n");
   set_level(5+random(6));
   set_aggressive(0);
   set_gender(1);
   add_money(random(500));
   load_chat(2,({
      "Harry says: What are you waiting for?\n",
      "Harry says: Hello there!\n",
      "Harry says: I don't like nuclear winter.\n",
      "Harry says: Who am I?\n",
      "Harry says: I don't like acid rain.\n",
      "Harry says: Who are you?\n",
      "Harry says: Why do you look so stupid?\n",
      "Harry says: What are you doing here?\n",
      "Harry says: Bad weather, isn't it?\n",
      "Harry grins.\n",
      "Harry says: Where did you all go for a week?\n",

   }));
   load_a_chat(10,({
      "Harry says: Don't hit me!\n",
      "Harry says: That hurt!\n",
      "Harry says: Help, someone!\n",
      "Harry says: Why can't you go bullying elsewhere?\n",
      "Harry says: Aooooo\n",
      "Harry says: I hate bashers!\n",
      "Harry says: Bastard!\n",
      "Harry says: You big brute!\n",
   }));      
   func = allocate(13);
   type = allocate(13);
   match = allocate(13);
   func[0] = "why_did";
   type[0] = "sells";
   type[1] = "attack";
   type[2] = "left";
   match[2] = "the game";
   type[3] = "takes";
   type[4] = "drops";
   func[5] = "how_does_it_feel";
   type[5] = "is now level";
   func[6] = "smiles";
   type[6] = "smiles";
   match[6] = " happily.";
   func[7] = "say_hello";
   type[7] = "arrives";
   func[8] = "test_say";
   type[8] = "says:";
   func[9] = "telling";
   type[9] = "tells you:";
   func[10] = "follow";
   type[10] = "leaves";
   func[11] = "gives";
   type[11] = "gives";
   func[12] = "test_ask";
   type[12] = "asks you:";

}

why_did(str){
   string who, what;
   sscanf(str, "%s %s", who, what);
   if(who == "harry" || who == "Harry")
      return;
   if (sscanf(str, "%s sells %s.", who, what) == 2)
      notify("Harry says: Why did you sell " + what + "\n");
   if (sscanf(str, "%s attacks %s.", who, what) == 2)
      notify("Harry says: Why does " + who + " attack " + what + "?\n");
   if (sscanf(str, "%s left the game.", who) == 1)
      notify("Harry says: Why did " + who + " quit the game ?\n");
   if (sscanf(str, "%s takes %s.\n", who, what) == 2)
      notify("Harry says: Why did " + who + " take " + what + " ?\n");
   if (sscanf(str, "%s drops %s.\n", who, what) == 2) 
      notify("Harry says: Why did " + who + " drop " + what + " ?\n");
}

notify(str){
   say(str);
   W(str);
}

how_does_it_feel(str){
   string who, what;
   sscanf(str, "%s %s", who, what);
   if(who == "harry" || who == "Harry")
      return;
   if (sscanf(str, "%s is now level %s.\n", who, what) == 2) 
      notify("Harry says: How does it feel, being level "+ what +" ?\n");
}

smiles(str) {
   string who, what;
   sscanf(str, "%s %s", who, what);
   if(who == "harry" || who == "Harry")
      return;
   if (sscanf(str, "%s smiles happily", who) == 1 && who != "Harry")
      notify("Harry smiles happily.\n");
}

say_hello(str){
   string who;
   if (sscanf(str, "%s arrives.", who) == 1)
      notify( "Harry says: Hi " + who + ", nice to see you !\n");
}

test_ask(str){
   string a, b, msg;
   string c;
   int money;
   if( sscanf( str, "%s asks you: %s\n", a, b) != 2 )
      return;
   str = b;
   if( str == "clean the statue" || str == "clean statue" ){
      if( find_player( lowercase(a) )->query_money() < 100 ){
         msg = "Harry snickers and says: I'll do it for $100!\n";
         notify(msg);
      }
      else {
         msg = "Harry takes your $100 and runs off to clean the statue!\n";
         notify(msg);
         find_player(lowercase(a))->add_money(-100);
         move_object(TO, ROOM+"central_square" );
         notify("Harry cleans up the statue.\n");
         present("statue",ENV(TO))->cleanPoop();
      }
   }
   return;
}

test_say(str){
   string a, b, message;
   sscanf(str, "%s %s", a, b);
   if(a == "harry" || a == "Harry")
      return;
   if(!sscanf(str, "%s says: %s\n", a, b) == 2) 
      return;
   str = b;
   if(str == "hello" || str == "hi" || str == "hello everybody") 
      message = "Harry says: Hello there! What's your name?\n";
   if(lowercase(str) == lowercase(a)) 
      message = "Harry says: Beautiful name, "+a+".\n";
   if(str == "shut up") 
      message = "Harry says: Shut up yourself!\n";
   if(str=="stop" || str=="stay" || str=="halt" || str=="sod off" || str=="stay here" || str =="don't follow" || str =="get lost" || str=="piss off"){
      if(random (2)==1) {
         say ("Harry says: Ok then.\n");
         not_following=1;
      }
      else {
         say ("Harry says: WHAT?!? Are you being rude?\n");
         TO->attack_object (find_player(lowercase(a)));
      }
   }
   if (message)
      notify(message);
}

telling (str) {
   string who,what;
   object o;
   if(sscanf (str,"%s tells you: %s",who,what)!=2)
      return;
   o=find_player(lowercase(who));
   if(!o) return;
      tell_object (o,"Harry tells you: Howdy howdy hoo..\n");
   return 1;
}

follow(str){
   int i;
   string who, where;
   if (not_following) not_following-=1;
   else
   if(sscanf(str, "%s leaves %s.\n", who, where) == 2){
      switch(where){
         case "south": 
         case "north": 
         case "west": 
         case "east": 
         case "down": 
         case "up": 
         call_other(TO, "init_command", where);
         if(random(3)==1){
            i=random (4);
            if(i==0) say("Harry says: Hey wait!\n");
            if(i==1) say("Harry says: Why are you running away from me!?\n");
            if(i==2) say("Harry says: Are you in a hurry?\n");
            if(i==3) say("Harry says: Stop running around!\n");
         }
         default:
      }
   }
}

gives(str) {
   string who, what, whom;
   int rand;
   object obj, next_obj;
   if(sscanf(str, "%s gives you %s.\n", who, what) != 2)
      return;
   if(what == "firebreather" || what == "special" || what == "beer" || what == "bottle") {
      rand = random(4);
      if(rand == 0) {
         if(random(10) > 6) {
            notify("Harry sighs and says: I guess you're gonna kill me now.\n");
            obj = first_inventory(TO);
            while(obj) {
               next_obj = next_inventory(TO);
               move_object(obj, ENV(TO));
               notify("Harry drops " + call_other(obj, "short") + ".\n");
               obj = next_obj;
            }
            call_other(TO, "init_command", "west");
         }
      }
      if(rand == 1) 
         call_other(TO, "init_command", "drink " + what);
      if(rand == 2){
         obj = first_inventory(TO);
         while(!call_other(obj, "id", what))
            obj = next_inventory(obj);
         move_object(obj, ENV(TO));
         notify("Harry drops the " + what + ".\n");
      }
      if(rand == 3) {
         obj = first_inventory(TO);
         while(!call_other(obj, "id", what))
            obj = next_inventory(obj);
         move_object(obj, find_living(lowercase(who)));
         notify("Harry returned the " + what + " to " + who + ".\n");
      }
   } 
   else if(what == "corpse") {
      notify("Harry says: HEY, bury your corpses yourself, asshole.\n");
      obj = first_inventory(TO);
      while(!call_other(obj, "id", what))
         obj = next_inventory(obj);
      move_object(obj, find_living(lowercase(who)));
      notify("Harry returned the " + what + " to " + who + ".\n");
   }
   else { 
      notify("Harry says: Thank you very much, sir.\n");
   }
}

monster_died(){
   object obj, b;
   int num;
   obj = first_inventory(TO);
   while(obj){
      b = next_inventory(TO);
      if(call_other(obj, "id", "bottle")){
         destruct(obj);
         num = 1;
      }
      obj = b;
   }
   if(num)
      notify("There is a crushing sound of bottles breaking, as the body falls.\n");
}
