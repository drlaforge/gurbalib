/* Wishbone Jan 2005 - added grease, bits and loyalty card stuff */

inherit ROOM+"restaurant";
int rand,mcheck,grease,bits,value,money;
object ob1,ob2,ob3,lcard;

init()
{
   ::init();
   add_action ("my_order","order");
   add_action ("my_order","buy");
   add_action ("my_menu","menu");
   add_action ("read","read");
   add_action ("punch_me","punch");
}

void setup(void)
{
   bits = 10;
   grease = 10;
    
    
   set_light(1);
   set_outdoors(0);
   set_short("Mishra's Makin' Bacon");
   set_long_f("This is THE bacon place with a prominent sign on the wall. "+
      "Step on up and order yourself some "+
      "mouth watering, crispy, artery blocking bacon. There is a menu "+
      "which has a thin layer of bacon fat on it. Guess the bastards "+
      "who run this place aren't big on clean up. Bastards!");
   items_arr = ({"bacon","It's bacon!",
         "menu","Use the 'menu' command bastard!",
         ({"prominent sign","sign"}),"You should read the sign",
         "bastards","Fat bastards like yourself",
         "wall","There is a prominent sign on the wall that you should read",
         });
   dest_dir = ({ROOM+"eve_street1", "west"});
   dname = ({"bacon",
         "smoked",
         "slab",
         "turkey",
         "baconleros"});
   dalias = ({"original bacon",
         "smoked bacon",
         "slab bacon",
         "bacon turkey",
         "huevos baconleros"});
   dshort = ({"An order of original bacon",
         "An order of smoked bacon",
         "Some slab bacon",
         "An order of bacon covered turkey",
         "An order of huevos baconleros"});
   dmess = ({"Crispy.",
         "Smokin' bacon.",
         "You suddenly get fatter!",
         "You stuff a bacon covered turkey down your throat!",
         "Cholesterol and animal fat. A winning combination ya fat bastard!"});
   dstrength = ({2,3,4,8,6,8});
   dheal = ({5,6,7,24,12,16});
   dtype = ({"obj/food",
         "obj/food",
         "obj/food",
         "obj/food",
         "obj/food",});
   dportable = ({1,1,1,0,1,1});
   set_reply("The fat bastard says: ");
   set_order_what("Order what?\n");
   set_menu_table("                               ");
   set_not_enough("You don't have enough money, bastard.\n");
   set_enough_healing("You've had enough in here, ya fat bastard!\n");
}

my_order(str)
{
   lcard = present("lunch_punch_card",this_player());
   
   if(str == "grease" || str == "bacon grease") 
      {
      if(!grease)
         {
         write("The fat bastard says: We're sold out, fucker!\n");
         return 1;
      }
      if(move_object(ob1 = clone_object(ROOM+"bacon/grease"),this_player()))
         {
         writef("The fat bastard says: You can't carry any more!\n");
         return !destruct(ob1);
      }
      if(!this_player()->add_money(-300))
         {
         writef("The fat bastard says: You don't got enough cash!\n");
         return !destruct(ob1);
      }
      if(lcard)
         {
         lcard->set_spent(lcard->query_spent()+300);
      } 
      grease--;
      writef("You buy some bacon grease.\n");
      say(this_player()->query_name() + " buys some bacon grease.\n");
      return 1;
   }
   
   if(str == "bits" || str == "bacon bits") 
      {
      if(!bits)
         {
         write("The fat bastard says: We're sold out, fucker!\n");
         return 1;
      }
      if(move_object(ob2 = clone_object(ROOM+"bacon/bits"),this_player()))
         {
         writef("The fat bastard says: You can't carry anymore!\n");
         return !destruct(ob2);
      }
      if(!this_player()->add_money(-300))
         {
         writef("The fat bastard says: You don't got enough cash!\n");
         return !destruct(ob2);
      }
      if(lcard)
         {
         lcard->set_spent(lcard->query_spent()+300);
      }
      bits--;
      writef("You buy some bacon bits.\n");
      say(this_player()->query_name() + " buys some bacon bits.\n");
      return 1;
   }
   
   if(str == "card" || str == "loyalty card") 
      {
      if(present("lunch_punch_card",this_player()))
         return writef("The fat bastard says: You already have one!\n");
      
      writef("You grab a loyalty card.\n");
      say(this_player()->query_name() + " grabs a loyalty card.\n");
      move_object(ob3 = clone_object(ROOM+"bacon/punch_card"),this_player());
      return 1;
   }
   
   money = this_player()->query_money();
   restaurant_order (str);
   if(lcard)
      {
      lcard->set_spent(lcard->query_spent()+(money-this_player()->query_money()));
   }
   return 1;
}

my_menu()
{
   write("------=*=*=*=*=* Makin' Bacon *=*=*=*=*=------\n\n");
   write("Loyalty Card\t\t\tFree\n");
   write("Original Bacon\t\t\t$ 47\n");
   write("Smoked Bacon\t\t\t$ 55\n");
   write("Texas Slab Bacon\t\t$ 63\n");
   write("Huevos Baconleros\t\t$124\n");
   write("Bacon Covered Turkey\t\t$275\n");
   write("Mishra's Bacon Bits\t\t$300\n");
   write("Bacon Grease\t\t\t$300\n\n");
   write("-------=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=------\n");
   return 1;
}

read(str)
{
   if(str == "sign")
      {
      write("\nThe sign reads: "+colour_string("Mishra's Makin Bacon!","HIRED")+"\n\n");
      write("   -------=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=------\n");
      write("    Buy a loyalty card and for every $5000 worth \n");
      write("    of delicious products you buy here, you are  \n");
      write("    entitled to 'punch' one hole in the card.    \n");
      write("    When the card is complete, it can be traded  \n");
      write("    in for free roulette chips in Andre's casino!\n");
      write("   -------=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=------\n");
      return 1;
   }
   return 0;
}

punch_me(str)
{
   lcard = present("lunch_punch_card",this_player());
   
   if(str == "me" || str == "face")
      {
      writef("The fat bastard punches you hard in the face!\n");
      say(this_player()->query_name()+" is punched hard in the face!\n");
      return 1;
   }
   
   if(str == "card" || str == "loyalty card")
      {
      if(!lcard)
         return write("The fat bastard says: You don't have a loyatly card, you dick!\n");
      
      if(lcard->query_spent() < 5000)
         return write("The fat bastard says: You've spent $"+
         lcard->query_spent()+" recently, which ain't enough!\n");
      
      if(lcard->query_holes()==10)
         return write("The fat bastard says: That card is already full!\n");
      
      lcard->set_spent(lcard->query_spent()-5000);
      lcard->set_holes(lcard->query_holes()+1);
      return write("The fat bastard takes your loyalty card and punches another hole in it.\n");
   }
   return write("The fat bastard says: What was it you wanted to get punched..?\n");
}

