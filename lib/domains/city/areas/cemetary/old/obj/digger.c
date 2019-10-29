inherit "obj/monster";
int step;
string helper;
int digged;
reset(arg)          {
	step = 0;
	digged = 0;
	helper = 0;
          ::reset(arg);
          if(arg) return;
          set_level(4);
          set_name("grave digger");
          set_alias("digger");
          set_alt_name("man");
          set_short("an old grave digger");
	  set_gender(1);
          set_long(
          "This old man looks very fragile. \n"+
          "He is trying to dig with his shovel, but is too weak.\n");
          load_chat(25,({
          "Old man says: I am too weak for this!\n",
          "Old man sniffs.\n",
          "Old man tries to dig some, but fails and falls to the ground.\n",
          "Old man says: Can you help me? Nod if you think you can.\n",
          "Old man says: Can you help me? Just nod if you think you can.\n",
          "Old man says: Can you help me to dig? If you can, just nod.\n",
          "Old man says: Please help me. Nod if you will.\n",
          }));
	set_chance(20);
}
init(){
	::init();
	add_action("nod","nod");
	add_action("killa","kill");
	add_action("dig","dig");
}
nod(str){
        object shovel;

	if(str=="man"||str=="digger"||!str){
if(helper && find_player(lower_case(helper))){
write("Old man says: "+helper+" is helping me already. Thanks anyway.\n");
return 1;
}
	write("Old man says: Really? Thanks!\n");
	write("Old man gives you his shovel.\n");
/*
	move_object(clone_object("/obj/obj/shovel"),this_player());
*/
        if(transfer(shovel=clone_object("obj/obj/shovel"),this_player())) {
                write("You can't carry the shovel.  The old man places the shovel on the ground.\n");
                move_object(shovel,environment());
        }
	step = 1;
	helper = this_player()->query_name();
load_chat(20,({
	"Old man says: Now "+helper+" will do some digging!\n",
	"Old man says: "+helper+" promised me to help me dig.\n",
	"Old man twiddle his thumbs.\n",
	"Old man smiles at you.\n",
	"Old man smiles happily.\n",
	}));
	return 1;
}
}
killa(){
	write("Old man says: Please dont hurt me!\n");
	return 1;
}
dig(){
object statue;
	if(digged){ write("Its already dug up.\n"); return 1; }
	if(!helper){ write("Old man says: Use my shovel instead!\n"); return 1;
			}
	if(this_player()->query_name()!=helper){
	write("Old man says: "+helper+" promised to help me. Dont bother.\n");
	return 1;
	}
	write("Old man says: No! Dont dig there! Dig here instead.\n");
	write("You dig on the location the man says for awhile.\n");
	write("You found a statue.\n");
	statue = clone_object("/obj/cemetary/statue");
	move_object(statue,environment(this_object()));
	digged = 1;
	write("Old man says: Woah! The ancient buddha statue!\n");
	write("Old man says: I heard you can meditate with that!\n");
load_chat(20,({
	"Old man says: "+helper+" found something in here. And I helped.\n",
	"Old man struts proudly.\n",
	"Old man whistles on a merry tune.\n",
	"Old man describes a statue that "+helper+" found.\n",
	}));
	return 1;
	}
