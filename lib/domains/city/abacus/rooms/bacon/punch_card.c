/* Wishbone Jan 2005 - card aquired and holes punched in bacon shop */
/* Completed cards traded for chips in the casino. Ideas by Mishra */

inherit "std/obj";
int holes,max,count,spent,paid;

void setup(void) {
  
  
 set_short("A loyalty card");
 set_long_f("This is a bacon shop loyalty card. The more you buy, the more holes "+
	  "get punched in it. The bacon shop has some kinda deal with the casino "+
	  "where you can claim free chips at the roulette table with every completed card.");
 set_name("card");
 set_alias("lunch_punch_card");
 set_gettable(1);
 set_drop(1);
 set_value(0);
 set_weight(0);
 set_spent(0);
 max = 10;
}

init_arg(arg){
 sscanf(arg,"%d#%d",count,paid);
 holes=count;
 spent=paid;
}

long() 
{
 ::long();
 if((max-holes)<1)
  {
   write("This card is complete and can be traded in at the casino.\n");
   return 1;
  }
  write("You have $"+spent+" worth of bacon on this card.\n");
 write("You need "+(max-holes)+" more holes to complete the card.\n");
 return 1;
}

set_holes(arg)
{
 return holes = arg;
}

set_spent(arg)
{
 return spent = arg;
}

query_holes()
{
 return holes;
}

query_spent()
{
 return spent;
}

query_auto_load()
{
return source_file_name(this_object())+":"+holes+"#"+spent; 
}

