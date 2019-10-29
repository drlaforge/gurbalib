inherit "std/monster";
object mother;
int called;
int id(string str){return str == "child";} 
void setup(void){
	 
	called=0;
	set_name("child");
	set_level(4);
	set_gender(2);
	set_aggressive(0);
	add_money(random(5));
	set_short("A child");
	set_long("A child playing in the park\n"+ 
                 "She is about 5 years old but still looks older. Like any kid of her age she\n"+
                 "is very mucky and has chocolate all around her face. She has a sorry\n"+ 
                                "looking expression on her face, it looks as if she's lost something \n"+"or someone.\n");

	load_chat(15, ({
		"A child says: I want my mummy\n"}));
	/* Whats this? A monster in the area not carrying anything? */
}


attacked_by(who){
	call_out ("kill",2);
}

kill(){
	if(!this_object()->query_attack()) remove_call_out("kill");
	if(this_object()->query_hp()<100){
	if(called) return;
		if(!present("mother",this_object())){
			say("The child calls for her mummy");
			mother=clone_object(ROOM+"park/mother");
			move_object(mother,environment(this_object()));
			remove_call_out ("kill");
			called=1;
			return;
		}
	}
	call_out ("kill",2);
	return;
}

