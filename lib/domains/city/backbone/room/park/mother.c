inherit "std/monster";
object handbag;
void setup(void){
	 
	if(arg)return;
	set_name("mother");
	set_alias(({"mother","mummy"}));
	set_level(10+random(3));
	set_gender(2);
	set_aggressive(1);     
	add_money(random(500)+200);
	set_short("The childs mother");
	set_long("This is the childs mother. She looks really cross with you.\n");
	load_a_chat(15, ({
		"The mother says: You stay away from my baby.\n",
		"The mother says: You big bully.\n",
	}));
	set_dead_ob(this_object());
	handbag=clone_object(ROOM+"park/handbag");
	move_object(handbag,this_object());
	command("wield handbag",this_object());
}

