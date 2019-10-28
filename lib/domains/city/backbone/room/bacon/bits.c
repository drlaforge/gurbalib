/* Wishbone Jan 2005 */

inherit"/obj/food.c";
int doses;

void setup(void) 
{
  
  
 set_name("packet");                           
 set_alias("bits");
 set_short("a packet of bacon bits");
 set_long("This is a packet of delicious bacon bits. They're pretty tasty and improve "+
   	  "most foods that you sprinkle them on to. You feel hungry just thinking about it");                
 set_strength(1);
 set_heal(5);
 set_consumer_mess("You pour the bacon bits into your mouth, yum!\n");
 set_consuming_mess(" eats some bacon bits.\n");
 doses = 3;
}

long() 
{
 ::long();
 write("There are "+doses+" helpings of bacon bits left.\n");
 return 1;
}

init() 
{
 ::init();
 add_action("sprinkle","sprinkle");
}

sprinkle(str) 
{
 string what,what2,temp,temp_short,temp_name;
 object spam,with_ob; 
 int temp_str,temp_heal,temp_weight;

 if(!str) return 0;

 if(!sscanf(str,"%s with bits",what)==1) 
  return write("Sprinkle what with bits?\n");

 spam = present(what,environment(this_object()));

 if(!spam)
  return write("You don't have any "+what+"!\n");
 
 if(!spam->query_food())
  return write("You can only sprinkle bacon bits on food!\n");

 if(spam->query_enhanced())
  return write("The food already has a topping.\n");

 if(sscanf(spam->short(),"%s sprinkled with lots of bacon bits",what)==1)
  return write(what+" doesn't have room for any more bacon bits.\n");

 temp_str = spam->query_strength();
 temp_heal = spam->query_heal();
 temp_weight = spam->query_weight();
 temp_short = spam->short();
 temp_name = spam->query_name();
 destruct(spam);

 move_object(with_ob = clone_object("/obj/food"),this_player());
 with_ob->set_strength(temp_str);
 with_ob->set_heal(temp_heal+10);
 with_ob->set_weight(temp_weight);
 with_ob->set_name(temp_name);
 with_ob->set_enhanced(1);

 if(!sscanf(temp_short,"%s sprinkled with bacon bits",what)==1 
	&& !sscanf(temp_short,"%s sprinkled with lots of bacon bits",what)==1) 
  with_ob->set_short(temp_short+" sprinkled with bacon bits");
 else if(sscanf(temp_short,"%s sprinkled with bacon bits",what)==1) 
  with_ob->set_short(what +" sprinkled with lots of bacon bits");
 else if(sscanf(temp_short,"%s sprinkled with lots of bacon bits",what)==1)
  with_ob->set_short(temp_short);

 with_ob->set_consumer_mess("You wolf down the food and savour the tasty bacon bits");
 write("You sprinkle some bacon bits onto your "+temp_name+".\n");
 say(this_player()->query_name()+" sprinkles some bacon bits onto some "+temp_name+".\n");
 doses--;
 if(doses < 1) 
  {
   write("That was the last of the bacon bits. You toss the empty packet away.\n");
   destruct(this_object());
  }
 return 1;
}
