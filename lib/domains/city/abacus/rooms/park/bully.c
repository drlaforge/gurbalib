inherit "std/monster";

object magnum;
int e;

void setup(void){
   
   
  set_level(16);
  set_name("bully");
  set_alt_name("bully");
  set_short("A Big Bully");
  set_long_f(
"This a BIG BULLY you dont want to mess with him."+
" This big fat belly lager guy, reminding you of yourself, is a well built git."+ 
" He wears a string vest and slaggy jeans with black boots and white socks. A"+
" generally sad mean guy.");

  set_male(1);

  
  load_a_chat(20,({
"'Give me you money wimp!' The big bully screams.\n",
"Bully shouts: Where is your money.\n",
  }));
  
  set_chance(20+random(15));
  set_spell_dam(5+random(6));
  set_spell_mess1("The Big Bully takes out his magnum.");
  set_spell_mess2("The Big Bully bashes your skull with the butt of his pistol.\n");
  
  move_object(clone_object(ROOM+"park/g357.c"),this_object());
  init_command("wield magnum");
  init_command("select single on gun");


}

heart_beat () {
  magnum=present ("magnum",this_object());
  if(magnum){
    if(!random(4) && query_attack()) {
      init_command ("shoot");
  }
}
  ::heart_beat();
}
