inherit "std/monster";

object coat;
int e;

void setup(void){
   
   
  set_level(2);
  set_name("wimp");
  set_alt_name("wimp");
  set_short("A wimp");
  set_long_f(
"This a wimp I would not bother fighting him.\n"+
"He reminds you of the class pet and with his pitiful actions. He actually "+
"looks to need a good kicking");

load_chat(4,({
"The wimp bleeds all over the floor.\n",
"The wimp mumbles: ... fuck you... bully...\n",
})),

  reduce_hit_point(45);  
  set_male(1);

if(!coat){
  coat=clone_object("/std/armor");
  coat->set_name("coat");
  coat->set_short("A coat");
  coat->set_long_f(
  "A boring coat stolen from a wimp. It reminds you of a duffle coat your "+
  "mother set you to school in. The only thing this would protect you from"+
  " would be a dog pissing on you.");
  coat->set_weight(1);
  coat->set_ac(3);
  coat->set_value(100);
  coat->set_type("cloak");
  move_object(coat,this_object());
  command("wear coat",this_object());}

  }

