init(){
	add_action("move","move");
	add_action("move","push");
	add_action("move","lift");
	add_action("move","remove");
	add_action("bury","bury");
	add_action("exa","exa");
	add_action("exa","look");
	add_action("exa","examine");
	add_action("put","put");
	add_action("put","place");
	add_action("lime","lime");
	add_action("dro","drop");
}
int moved;
int sour;
short(){
if(moved==1){
        return "a white stone moved aside revealing a hole in the ground";
	}
else	{
        return "a white stone in the middle of the pentagram";
	}
}
get(){
	write("The stone is to heavy. Maybe you can move it.\n");
	return 0;
}
id(str){
	if(str=="stone"||str=="white stone") return 1;
	else return 0;
}
long(){
	write("The stone looks movable.\n");
}
move(str){
	if(str=="stone"||str=="white stone"){
	write("You move the white stone.\n");
	if(moved==1){
	moved = 0;
	write("The stone is back in position again.\n");
	return 1;
	}
	else	{
		write("You move the stone from the middle of the pentagram.\n");
		moved = 1;
		return 1;
		}
	}
}
int kitten;
bury(str){
object corp;
	if(str=="corpse"||str=="corpse of cat"){
	if(moved==0){
	write("You cant bury any corpse. The stone blocks the hole.\n");
	return 1;
	}
	if(!present("corpse",this_player())){
	write("What corpse ?\n");
	return 1;
	}
	if(!present("corpse of a white cat",this_player())){
	write("The corpse is to big.\n");
	return 1;
	}
	write("You bury the corpse of a cat and the stone magically slide back on the hole.\n");
	say(this_player()->query_name()+" buries a corpse and the stone suddenly moves.\n");
corp = present("corpse of a white cat",this_player());
destruct(corp);
	moved = 0;
	call_out("kitten",10);
	return 1;
	}
}
exa(str){
	if(str=="hole"||str=="at hole"){
	if(moved==0){
	write("What hole ?\n");
	return 1;
	}
	write("The hole is not very big.\n");
	return 1;
	}
}
put(str){
	if(str=="corpse in hole"||str=="corpse of cat in hole"){
	write("You mean bury ?\n");
	return 1;
	}
}
kitten(){
	write("Suddenly the stone moves and a cat comes from the hole.\n");
say("The stones moves and a cat comes from the hole.\n");
moved = 1;
if(sour==0)
move_object(clone_object("/obj/cemetary/icat"),environment());
else
move_object(clone_object("/obj/cemetary/scat"),environment());
return 1;
}
int end;
lime(str){
	lime_d();
	if(end==1) return 1;
	if(str=="ground"){
	write("You lime the ground. It's not sour anymore.\n");
	sour = 1;
	say(this_player()->query_name()+" limes the ground.\n");
	des_lime();
	return 1;
	}
	write("Lime what? The ground?\n");
	return 1;
}
dro(str){
	if(str=="lime"){
	lime_d();
	if(end==1)
	return 1;
	write("You lime the ground.\n");
	sour = 1;
	say(this_player()->query_name()+" limes the ground.\n");
	des_lime();
	return 1;
	}
}
lime_d(){
	if(!present("lime",this_player())){
	write("You got no lime.\n");
	end = 1;
	return 1;
	}
	end = 0;
	return 1;
}
des_lime(){
object vict;
	vict = present("lime",this_player());
	destruct(vict);
	return 1;
}
