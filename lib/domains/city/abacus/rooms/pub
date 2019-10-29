
inherit ROOM+"restaurant";

static mapping bought;

query_bought(){ return bought; }


init () {
   ::init();
   if(present("jackson"))
      {
      add_action ("my_order","order");
      add_action ("my_order","buy");
   }
   add_action ("my_menu","menu");
   add_action ("read_list", "read");
   add_action ("check","up");
}

reset (arg) 
{
    
   if(!(present("jackson")))
      {
      move_object(clone_object("/obj/monsters/jackson"),this_object());
   }
   bought = ([ ]);
    
   set_short("In a rebuilt and renovated pub");
   set_long_f
   ("You are in a pub. There is some wooden furniture dotted around. "+
      "A small desk sits in the back of the bar for business. "+
      "Cigarette smoke hangs in the air, and there is bubblegum "+
      "stuck on the floor in places. You also detect the faint "+
      "scent of opium in the air. In the corner closest to the "+
      "counter there is a Wurlitzer jukebox chained to the floor. "+
      "There is an LCD which displays a toplist of players on Nuclear "+
      "War. It is mounted prominently in the middle of the room. "+
      "There is a stairway that goes up to the Veteran pub. "+
/*
      "A banner hangs from the ceiling, that says '"+
      colour_string("Closing Soon!","HIRED")+"'.\n");
*/
"\n");
   set_light (1);
   set_outdoors (0);
   items_arr = ({
         "banner",colour_string("Closing Soon!","HIRED"),
         "pub",
         "The pub looks better now than it did before",
         ({"stair","stairs"}),
         "The stairs leads up the Veteran pub",
         "smoke",
         "This smoke can't be good for your health",
         ({"bubble gum","bubblegum","gum"}),
         "Bubble gum of different flavours and colours is stuck to the floor",
         ({"bar desk","desk"}),
         "A bar desk made of dark wood",
         "furniture", "Furniture made of wood is all over the bar",
         ({"jukebox","wurlitzer"}),
         "A Wurlitzer jukebox in mint condition that plays CDs. It must be\n"+
         "very valuable because it is chained to the ground and a padlock\n"+
         "prevents you from inserting coins in the slot. On the glasswindow\n"+
         "there is a paper saying: 'For use by management only.'",
         "chain",
         "The chain is really sturdy and keeps the jukebox firmly to the floor.\n"
         +"unless you find the key to the padlock that locks the chain together.",
         "padlock",
         "There is a padlock preventing you from inserting coins in\n"
         +"the slot as well as one that locks the chain together.", });
add_item( ({"list","toplist","lcd","screen","lcd device","top player list"}),
"A small device with a LCD screen which lists the top players of the game. Type \"help toplist\" for more information");
   
add_item(({"menu","list"}),"Just type 'menu'.");
   dest_dir = ({ ROOM+"yard", "east", ROOM+"pub_vet","up",});
   dname = ({ "beer", "wine", "whiskey","barrel of ale", "barrel of water", });
   dalias = ({ "cold beer","red wine","finest whiskey","ale","water"});
   dshort = ({ "A cold beer", "A bottle of red wine","A bottle of finest whiskey", "A barrel of ale", "A barrel of water", });
   dmess = ({ "Aaahh! Cold beer!", "Wonderful red wine!", "Aahh! Great whiskey", "You drink some of the ale", "You drink some water.", });
   dstrength = ({ 2,7,12,8,5, });
   dheal = ({ 1,7,12,8,5, });
   dtype = ({ "obj/drink","obj/drink","obj/drink","obj/drink" ,"obj/soft_drink"});
   dportable = ({ 1,1,1,1,1 });
   max_size = ({ 1,1,1,10,10 });
   set_reply ("Jackson says: ");
   set_order_what ("Order what?\n");
   set_menu_table ("...............................: ");
   set_not_enough ("You don't have enough money.\n");
   set_enough_healing ("You've had enough in here!\n");
}

my_order(str) 
{
   string name,item;
   mapping current;
   
   name = this_player()->query_real_name();
   if(present("jackson"))
      {
      if(present("jackson") && (present("jackson")->query_attack()))
         {
         if(present("jackson") && (present("jackson")->query_attack()==this_player()))
            {
            present("jackson")->init_command("shoot");
            write("Jackson says: Eat lead!\n");
            return 1;
         }
         write("Jackson says: I am busy defending my business here, can't help you right now.\n");
         return 1;
      }
      if( str == "beer" || str == "cold beer" )
         if( !undefinedp(bought[name]) )
         if( !undefinedp(bought[name]["beer"]) )
         if( bought[name]["beer"] > 9 ){
         write("Jackson says: I think you've had enough, eh?\n");
         return 1;
      }
      
      if( restaurant_order(str) ) {
         
         /* right now, just restricts beer */
         if( str == "beer" || str == "cold beer" ){
            item="beer";
            
            if(undefinedp(bought[name]))
               bought += ([ name : ([ ]) ]);
            
            current = bought[name];
            if(undefinedp(current[item]))
               current += ([ item : 0 ]);
            
            current[item] += 1;
            bought[name] = current;
         }
      }
      /* ^ this will return 1 if success 0 if not success */
         return 1;
   }
   write("But Jackson isn't here to serve you.\n");
   return(1);
}

my_menu() 
{
   write("------- THE MENU: -------\n");
   query_menu();
   write("-------------------------\n");
   return 1;
}

read_list(str)
{
   int from;
   
   if (!str)
      return err();
   
   
   if(str == "list")
      from = 3;
   else 
      {
      int i;
      string tmp, file, name;
      
      if( sscanf(str, "list %d", i) ){
         from = i;
      } else {  
         if(!sscanf(str, "list %s", name))
            return err();
         name = capitalize (name);
         for(i=tmp=0; file = read_file("/etc/toplist.new",i,500); i+=500)
         if(sscanf(file,"%s"+name+" ",tmp))
            break;
         if(!tmp)
            return write (capitalize (name) + " isn't on the toplist. Read 'help toplist' if you're confused.\n");
         tmp = tmp[-5..-1];
         if(!sscanf(tmp,"%d",from))
            return write("Failed to extract position number.\n");
         write("\n"+capitalize(name)+" is number "+from+" on the toplist.\n");
      }
      if((from -= 6) < 3)
         from = 3;
   }
printf("%|53s\n%|53s\n%|53s\n",
"=Nuclear War MUD Top Player List=",
"=Last Updated: "+ctime(file_time("/etc/toplist.new"))+"=",
"Read 'help toplist' for more information.");
   /*
   write("Pos === Name === Lvl ==== TotExp ==== Age ==\n");
   */
   write("Pos === Name === Lvl ==== Gang ============= Age ====\n");
   cat("/etc/toplist.new", from, 20);
   return 1;
}  

err()
{
   notify_fail("Usage: read list <name> or real list <position number>.\n");
}

check()
{
   if("/obj/daemons/timed"->query_hour() > 1 && "/obj/daemons/timed"->query_hour() < 4)
      {
      write("As you climb the stairs, someone punches you in the face and you tumble backwards!\n"
         +"A voice snarls: We're closed for cleaning from 2am to 4pm, so piss off!\n"); 
      return 1;
   }
   if(this_player()->query_level() < 20) 
      {
      write("As you climb the stairs, someone punches you in the face and you tumble backwards!\n"
         +"A voice snarls: Piss off, Wimp!\n"); 
      say(this_player()->query_name()+
         " climbs the stairs to the Veteran's pub.\n"+
         "There is a THWAP and "+this_player()->query_name()+
         " tumbles back down the stairs.\n"+
         "A voice snarls: Piss off, Wimp!\n"+
         this_player()->query_name()+" blushes hotly.\n"); 
      return 1; 
   }
   return 0;  
}
