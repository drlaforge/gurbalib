/* Wishbone Jan2005 */

inherit "/std/object";
int activated;

void setup(void) {
     
    set_name("grease");
    set_short("some bacon grease");
    set_long_f("This is some nasty looking bacon grease. You could "+
	"taste it, but you would probably throw up pretty quickly.\n");
    set_gettable(1);
    set_drop(0);
    set_weight(1);
    set_value(0);
}

init()
{ 
  ::init();
  add_action("cleanseBody","taste"); 
}

cleanseBody(str)  
{
   if(str !="grease") return 0; 
   if(activated) 
    {
      writef("You are aleady tasting the horrible grease.\n"); 
      return 1; 
    }
   writef("You start to taste the grease. It's horrible!\n"); 
   say(this_player()->query_name()+" starts to taste "+
	this_player()->query_possessive()+" bacon grease.\n",this_player()); 
   activated = 1; 
   call_out("cleanseBodyDone",5,this_player()); 
   return 1;  
}

cleanseBodyDone(arg){
   if(arg != environment(this_object())) return 1;
   writef("You suddenly throw up! That bacon grease was disgusting!\n");
   say(this_player()->query_name()+" throws up on the floor.\n");
   this_player()->set_stuffed(this_player()->query_stuffed()/5*4);
   destruct(this_object());
   return 1;
}


