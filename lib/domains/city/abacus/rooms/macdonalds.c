#define TP this_player()
inherit ROOM+"restaurant";

object bertha;
int fries,sand,burger,meal,shake,coke;

init() {
   ::init();
   add_action ("my_order","order");
   add_action ("my_order","buy");
   add_action ("my_menu","menu");
}

reset (arg) {
  bar_reset();
   
  if (!arg) {
    short_desc = "an old McDonald's restaurant";
    set_long_f("Around you is whats left of an old torn up McDonalds's "+
    "restaurant. By the looks of the graffiti-scrawled walls, the local punks "+
    "have been busy. Despite the obvious abuse, everything in here seems "+
    "quite functional. There is a menu above the counter, type 'menu' to "+
    "review it.\n");
    set_light (1);
    set_outdoors (0);
    items_arr = ({
        "menu", "#my_menu",
	({"counter","steel counter"}), "A large steel counter.",
	"graffiti","Mindless graffiti on the wall.",
	"walls","Walls covered in graffiti.",
	"floor","A solid well worn floor.",
	({"ceiling","roof"}),"The ceiling still looks like an old style McDonald's restaurant.",
           });
    dest_dir = ({ ROOM+"adam_street3", "east",
              });
    dname = ({ "small fries","turkey sandwich","buster burger",
        "square meal","macmilkshake","maccoke"});
    dalias = ({ "fries","sandwich","burger","meal","milkshake","coke"});
   
    dshort = ({ "a small fries", "a turkey sandwich", "a Buster Burger",
        "a Square Meal", "a MacMilkshake", "a MacCoke" });
    dmess = ({ "Yum!","You are what you eat!","Yum! Yum! Yum!","Gad, that's a bellyload.","Schlourp! scchlurp!","You can't beat the feeling..." });
    dstrength = ({ 2,4,10,15,5,6 });
    dheal = ({ 2,10,15,25,4,10 });
    dtype = ({ "obj/food","obj/food","obj/food","obj/food", "obj/soft_drink", "obj/soft_drink" });
    dportable = ({ 1,1,1,0,1,1 });
    set_reply ("Bertha says: ");
    set_order_what ("Order what?\n");
    set_menu_table ("                               ");
    set_not_enough ("You don't have enough money, Mac.\n");
    set_enough_healing ("You've had enough, shove off.\n");
  } 

  if(!bertha) {
    bertha = clone_object("obj/mean_monster");
    bertha->set_name("bertha");
    bertha->set_alias("bertha");
    bertha->set_gender(2);
    bertha->set_level(18);
    bertha->set_hp(625);
    bertha->set_wc(23);
    bertha->set_ac(10);
    bertha->set_short("Bertha");
    bertha->set_long(
      "Bertha is a stern looking woman standing behind the counter ready to take\n"+
      "your order. If you are ready to order just type 'order' and what you want.\n");
    bertha->set_chance(40);
    bertha->set_spell_dam(20);
    bertha->set_spell_mess1("Panggg.....");
    bertha->set_spell_mess2("Panggg, Bertha hits you with a big iron skillet.");
    move_object(bertha,this_object());
  }
}

my_order (str) {
  if(!present("bertha",this_object()))
     return write("Bertha is not here to cook anything for you.\n");
  if(present("bertha",this_object())->query_attack())
    return write("Bertha says: I'm too busy fighting!\n");
if(str == "fries" || str == "small fries" || str == "a small fries"){
	if(!fries){
		sold_out_mess();
		return 1;
	}
	fries -= 1;
}

if(str == "burger" || str == "buster burger" || str == "a Buster Burger"){
	if(!burger){
		sold_out_mess();
		return 1;
		}
	burger -= 1;
	}

if(str == "milkshake" || str == "macmilkshake" || str == "a MacMilkshake"){
	if(!shake){
		sold_out_mess();
		return 1;
		}
	shake -= 1;
	}

if(str == "meal" || str == "square meal" || str == "a Square Meal"){
	if(!meal){
		sold_out_mess();
		return 1;
		}
	meal -= 1;
	}

if(str == "sandwich" || str == "turkey sandwich" || str == "a turkey sandwich"){
	if(!sand){
		sold_out_mess();
		return 1;
		}
	sand -= 1;
	}

if(str == "coke" || str == "maccoke" || str == "a MacCoke"){
	if(!coke){
		sold_out_mess();
		return 1;
		}
	coke -= 1;
	}


   restaurant_order (str);
   /* ^ this will return 1 if success 0 if not success */
   return 1;
}

my_menu () {
   write ("=-- Grease Pit Homestyle Foods --=\n");
   query_menu();
   write ("=-------Bertha: Proprietor-------=\n");
   return 1;
}

bar_reset(){
	fries = 12;
	burger = 10;
	sand = 10;
	meal = 5;
	shake = 12;
	coke = 8;
}

sold_out_mess(){
	writef("Bertha says: Jesus! Bunch of damn lardasses! Eat me outta my whole stock! DAMN! Get the hell outta here!");
	say(this_player()->query_name()+" is rudely rebuffed from ordering by Bertha.\n");
	return 1;
}
	
