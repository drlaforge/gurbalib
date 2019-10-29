#include <def.h>
inherit STD_OBJ;
int is_lighted;

void setup(void){
    
   set_name("torch");
   set_alias("led torch");
   set_short("an LED torch");
   set_long_f("It's a bright yellow torch that uses powerful LEDs. This torch however is "+
      "extra special as it has a self sufficient powersupply so the batteries should never run out.\n");
   set_weight(1);
   set_gettable(1);
   set_value(200);
}

short(){
   if(is_lighted)
      return ::short()+" (lit)";
   return ::short();
}

long(){
   ::long();
   write("It is currently switched "+(is_lighted?"on":"off")+".\n");
}

init(){
   ::init();
   add_action("light_it_up",({"turn","switch"}));
}

light_it_up(str){
   string tmp;
   if(!str)
      return 0;
   if(sscanf(str,"on %s",tmp) && id(tmp)){
      if(is_lighted)
         write("The "+tmp+" is already on.\n");
      else{
         is_lighted=1;
         write("You "+query_verb()+" on the "+tmp+".\n");
         if(set_light(1)==1)
            write("You can see again.\n");
      }
      return 1;
   }
   if(sscanf(str,"off %s",tmp) && id(tmp)){
      if(!is_lighted)
         write("The "+tmp+" is already off.\n");
      else{
         is_lighted=0;
         write("You "+query_verb()+" off the "+tmp+".\n");
         if(set_light(-1)==0)
            write("It becomes dark.\n");
      }
      return 1;
   }
   return 0;
}
