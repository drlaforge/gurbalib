inherit "std/room";
#include "../area.h"
#include "/obj/lens_and_pods.h"

object ob,tp;

init ()
{
	::init();
	add_action ("buy",({"order","purchase","buy"}));
	add_action ("buy","order");
	add_action ("menu","list");
	add_action ("menu","menu");
	add_action ("menu","menue");
        add_action ("nofreeze",({"kill","blast","xblast","staff","stun","tama","kyosho"}));
        add_action ("nofreeze",({"sweep","jumpkick","headbutt","elbow","roundkick","uppcut","flipkick","snapkick"}));
        add_action ("nofreeze",({"shoot","fire","engage"}));
	add_action ("bounced",({"smash","break","shatter"}));
}

reset (arg)
{
	 
	set_outdoors (0);
	set_light (1);
	set_short("a Standard Products laser supply store");
	set_long_f("This is the Standard Products laser supply store. "+
		   "All manner of supplies for any laserweapon currently available can be obtained here. "+
		   "The store itself is very spartan in design, the entire structure being "+
		   "manufactured from stainless steel. The walls are lined with stainless steel "+
		   "cases, each labeled and containing different types of laser lenses and energy "+
		   "pods. There is a glass display case, behind which stands a Standard Products "+
		   "merchant droid waiting to help you.\n");
	add_exit("east",ROOM+"s_boul3");

        add_item(({"wall","walls","steel wall","steel walls","stainless steel wall","stainless steel walls"}), "\n"+
                   "The walls are made from stainless steel and are lined with steel cases");
        add_item(({"pods","pod","energy pods","energy pod"}),
                   "The energy pods are stored out of sight in the stainless steel cases\n"+
		   "that line the walls");
        add_item(({"lenses","lens","laser lens","laser lenses"}),
                   "The lenses for all manner of laserweapons are stored out of sight in\n"+
		   "the stainless steel cases that line the walls");
        add_item(({"droid","merchant droid","robot","merchant robot","standard products merchant droid","standard products droid"}),
                  "The Standard Products merchant droid (model I-3) waits behind the display\n"+
		  "case to process your order");
        add_item(({"case"}),
                  "Which case? The display case, or the steel cases?");
        add_item(({"display case","glass case","glass display case"}),
                 "The glass display case contains several models of Standard Products\n"+
		 "laserweapons, reflecting every new development in the technology since\n"+
		 "the birth of Laserweapon Technology. They are here to serve as conversation\n"+
		 "pieces, as well as provide a sort of history lesson on laserweapons");	
   	add_item(({"weapon","weapons","gun","guns","laserweapon","laserweapons","lasergun","laserguns","technology","laserweapon technology"}),
		 "The laserweapons in the display case range in model and design from the first\n"+
		 "bulky weapons with the companion powerpack to the latest handheld burners.\n"+
		 "They all reflect how the technology has changed, evolved, and been refined");
	add_item(({"cases","steel cases","stainless steel cases"}),
		 "The stainless steel cases that line the walls contain all manner of laser\n"+
		 "lenses and energy pods to be sold");
	add_item(({"store","supply store","laser supply store","standard products laser supply store"}),
		 "You stand in the Standard Products laser supply store. The Standard\n"+
		 "Products merchant droid awaits your order");

	load_chat(5,({"The merchant droid beeps: 'Menu' to see what goods are sold here.\n",
		      "The merchant droid whips out a rag and polishes the display case.\n"}));

}

nofreeze(arg)
{
   if(!arg) return 0;
   if(arg!="droid" && arg!="merchant droid" && arg!="standard products merchant droid") return 0;

   writef("Just as you start to take a swing at the merchant droid, it delivers a discrete shock "+
	  "to your system, not enough to kill but enough to jolt you out the door of the shop.\n");
   say(this_player()->query_name()+" is shocked out of the shop by the merchant droid.\n",this_player());
   if(environment(this_player())==this_object())
   {
      writef("You spasm uncomfortably.\n");
      move_object(this_player(),ROOM+"s_boul3");
   }
   return 1;
}

menu ()
{
   int i;
   write("\n");
   for (i=0; i<(sizeof(lens_type_array)+sizeof(energy_type_array)-1); i++)
   {
   if(i<sizeof(energy_type_array))           
   printf("%2d)   %12s energy pod, $%d.\n",(i+1),capitalize(energy_type_array[i][0]),energy_type_array[i][2]);
   else
   printf("%2d)   %12s laser lens, $%d.\n",(i+1),capitalize(lens_type_array[i-sizeof(energy_type_array)][0]),lens_type_array[i-sizeof(energy_type_array)][4]);
   }
   write("\n");
   write("Syntax: Buy <#>\n");
   return 1;
}

buy (str)
{
	int i;
  
	if (!str || !sscanf (str,"%d",i))
	{
		write ("buy #\n");
		return 1;
	}
	if (i<1 ||
i>(sizeof(energy_type_array)+sizeof(lens_type_array)-1))
	{
		write ("Buy what?\n");
		return 1;
	}
        i--;
        if(i<sizeof(energy_type_array))
        {
           if (this_player()->query_money() < energy_type_array[i][2])
	   {
		write ("You don't have enough money.\n");
		return 1;
	   }
	   ob = clone_object ("/obj/energy_pod");
           ob -> set_name ("pod");
           ob -> set_energy (energy_type_array[i][0]);
           ob -> set_short("an energy pod");
  	   if (move_object(ob,this_player()))
	   {
		write ("The merchant droid beeps: 'You cannot carry more!'\n");
		destruct (ob);
		return 1;
	   }
	   this_player()->add_money (- energy_type_array[i][2]);
write("You pay the droid "+energy_type_array[i][2]+" dollars for a "+energy_type_array[i][0]+" energy pod.\n");
	   say (this_player()->query_name()+" buys an energy pod from the merchant droid.\n");
	   return 1;
	}
	else
	{
           i = i - sizeof(energy_type_array);        
           if (this_player()->query_money() < lens_type_array[i][4])
	   {
		write ("You don't have enough money.\n");
		return 1;
	   }
	   ob = clone_object ("/obj/laser_lens");
	   ob -> set_name ("lens");
	   ob -> set_type (lens_type_array[i][0]);
	   ob -> set_short("a laser lens");
	   if (move_object(ob,this_player()))
	   {
		write ("The merchant droid beeps: 'You cannot carry more!'\n");
		destruct (ob);
		return 1;
	   }
	   this_player()->add_money (- lens_type_array[i][4]);
write("You pay the droid "+lens_type_array[i][4]+" dollars for a "+lens_type_array[i][0]+" laser lens.\n");
	   say (this_player()->query_name()+" buys a laser lens from the merchant droid.\n");
	   return 1;
	}
}


bounced(arg)
{
   if(!arg) return 0;
   if(arg!="case" && arg!="display case" && arg!="standard products display case" && arg!="glass display case") return 0;

   writef("Before you can get near the display case, the merchant droid delivers a discrete shock "+
	  "to your system, not enough to kill but enough to jolt you out the door of the shop.\n");
   say(this_player()->query_name()+" is shocked out of the shop by the merchant droid.\n",this_player());
   if(environment(this_player())==this_object())
   {
      writef("You spasm uncomfortably.\n");
      move_object(this_player(),ROOM+"s_boul3");
   }
   return 1;
}







