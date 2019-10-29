inherit "std/monster";
void setup(void){
	 
	if(arg)return;
	set_name("ghost");
	set_alias("holo");
	set_level(10+random(3));
	set_gender(1);
	set_aggressive(0);     
	set_short("A Holo-Ghost");
	set_long("This is a holo-ghost of the ruler of Abacus.\n"+
                 "You have seen everything now a Holo-Ghost, this must have be done as a prank.\n"+ 
                 "He looks very very horrible. Reminds you of the top coder of the club Cederic.\n"+
                 "His facial expresions make you cringe and want basically want to throw up.\n"+
                "As he is a ghost you can see partly through him but hes not that frightening.\n"+ 
                 "He has however a pleasant character and should not be that hard to beat up. \n"+
               "Have a go.\n");

       load_a_chat(15, ({
		"Ghost says: I am the ruler.\n",
		"Ghost says: I can still demote you.\n",
	}));
}

