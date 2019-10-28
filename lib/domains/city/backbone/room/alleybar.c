inherit ROOM+"restaurant";

int toast, burger, pizza, water, juice, coke;
object obj, obj2, obj3;

void setup(void) {
  reset_bar();
    if(!present("buddy",this_object())) {
      obj=clone_object("/std/monster");
      obj->set_name("buddy");
      obj->set_alias("bar keeper");
      obj->set_short("Buddy the barkeeper");
      obj->set_long("Buddy is a large sized man in the middle ages.\n"+
		   "He seems to have been training at a gym for several\n"+
		   "years.\n");
      obj->set_level(15);
      obj->set_hp(280);
      obj->set_ac(8);
      obj->set_ep(50000);
      obj->set_al(-100);
      obj->set_gender(1);
     move_object(obj,this_object());
      
      obj2=clone_object("/std/weapon");
      obj2->set_name("saw");
      obj2->set_short("a meat saw");
      obj2->set_long("A nuclear-driven meat saw ");
      obj2->set_class(10);
      obj2->set_weight(2);
      obj2->set_value(550);

      obj3=clone_object("/std/armor");
      obj3->set_name("apron");
      obj3->set_short("a synthetic leather apron");
      obj3->set_long("The material is almost exactly like leather but\n"+
		    "a lot more protective");
      obj3->set_class(7);
      obj3->set_weight(2);
      obj3->set_type("cloak");
      obj3->set_value(700);
      move_object(obj2,obj);
      move_object(obj3,obj);
      command("wield saw",obj);
      command("wear apron",obj);
    }
   
    set_outdoors(0);
    set_light(1);
    short_desc = "A bar off an alley";
    
  dest_dir = 
        ({
	  ROOM+"darkalley2", "south",
        });
  items_arr = ({ ({"tables","table"}),"Some ordinary tables of wood, standing"+
	       " on the floor",
	       "counter","It's loooong and wet from drinks",
	  });
}

long(str) {
  if (str) return ::long(str);
  write("You are in Buddy's fastfood bar. \n"
        + "A long counter stands along the wall in front\n"
	+ "of you. Some small tables are spread on the floor.\n"
	+ "Type 'menu' to see what you can order.\n");
  if(!pizza&&!burger&&!toast&&!coke&&!juice&&!water) {
    write("A sign says: SOLD OUT!\n");
  }
  write("    There is one obvious exit: south\n");
}

init() {
  ::init();
    add_action("order","order");
    add_action("order","buy");
    add_action("menu","menu");    
  }

menu() {
  write("             -----------------------------------------------\n"+
	"            |                --==> MENU <==--               |\n"+
	"            |        Food:                     Drinks:      |\n"+
	"            |       -------                   ---------     |\n"+
	"            |                                               |\n"+
	"            |   Pizza:        $164       Coke:       $104   |\n"+
	"            |                                               |\n"+
	"            |   Cheeseburger:  $94       Lemon juice  $82   |\n"+
	"            |                                               |\n"+
	"            |   Toast:         $35       Tonic water  $31   |\n"+
	"            |                                               |\n"+
	"             -----------------------------------------------\n");
  return 1;
}
      
  reset_bar() {
  toast = 10;
  burger = 8;
  pizza = 5;
  water = 10;
  juice = 8;
  coke = 5;
}

order(str) {
  string empty_name, consumer_mess, consuming_mess, name;
  string alias, short, long, type;
  int full_value, value, weight, heal, strength;
  object buddy, healing;
  buddy = present("buddy",this_object());
  if (!buddy) {
    write("Buddy the barkeeper isn't here right now.\n");
    return 1;
  }
  if((buddy->query_attack() && buddy->query_attack() == this_player()) ||
     (buddy->query_alt_attack() && buddy->query_alt_attack() == this_player()))
    {
      write("Buddy says: I don't sell anything to my enemies, you motherfucker.\n");
      return 1;
    }
  if(str == "toast") {
    if(!toast) { 
      sold_out_mess();
      return 1;
    }
    name = "toast";
    alias = str;
    short = "a small toast";
    long = "a very small meal";
    type = "food";
    consumer_mess = "Mmm.. not bad. You wish you had another one";
    consuming_mess = " eats "+short;
    weight = 1;
    heal = 5;
    strength = 4;
    full_value = get_full_value(strength,heal);
    if (!test_weight(weight))
      return 1;
    toast -= 1;
} else 
  if(str == "cheeseburger" || str == "burger") {
    if(!burger) {
      sold_out_mess();
      return 1;
    }
    name = "cheeseburger";
    alias = str;
    short = "a greasy cheeseburger";
    long = "It contains a lot of fat";
    type = "food";
    consuming_mess = " eats "+short;
    consumer_mess = "You feel the fat keep building up your beautiful stomach";
    weight = 1;
    heal = 12;
    strength = 7;
    full_value = get_full_value(strength,heal);
    if (!test_weight(weight))
      return 1;
    burger -= 1;
  } else 
if(str == "pizza") {
  if(!pizza) {
    sold_out_mess();
    return 1;
  }
  name = "pizza";
  alias = str;
  short = "a huge pizza";
  long = "It seems very nourishing and delicious";
  type = "food";
  consuming_mess = " feasts on "+short;
  consumer_mess = "Mums mums!";
  weight = 1;
  heal = 20;
  strength = 10;
  full_value = get_full_value(strength,heal);
  if (!test_weight(weight))
    return 1;
  pizza -= 1;
} else 
  if(str == "coke" || str == "cola" || str == "coca cola") {
    if(!coke) {
      sold_out_mess();
      return 1;
    }
    name = "coke";
    alias = str;
    short = "a glass of cold coke";
    long = "It's really ice cold";
    type = "soft_drink";
    consuming_mess = " drinks "+short;
    consumer_mess = "Aahh! Can't beat the feeling";
    empty_name = "glass";
    value = 10;
    weight = 1;
    heal = 15;
    strength = 12;
    full_value = get_full_value(strength,heal);
    if (!test_weight(weight))
      return 1;
    coke -= 1;
  } else 
    if(str == "lemon juice" || str == "lemon" || str == "juice") {
      if(!juice) {
	sold_out_mess();
	return 1;
      }
      name = "juice";
      alias = str;
      short = "a jug of fresh lemon juice";
      long = "It seems very nourishing and delicious";
      type = "soft_drink";
      consuming_mess = " drinks "+short;
      consumer_mess = "Oh, I like it!";
      empty_name = "jug";
      value = 10;
      weight = 1;
      heal = 12;
      strength = 10;
      full_value = get_full_value(strength,heal);
      if (!test_weight(weight))
	return 1;
      juice -= 1;
    } else 
      if(str == "water") {
	if(!water) {
	  sold_out_mess();
	  return 1;
	}
	name = "water";
	alias = str;
	short = "a glass of tonic water";
	long = "It's sparkles lively";
	type = "soft_drink";
	consuming_mess = " drinks "+short;
	consumer_mess = "Very refreshing indeed!";
	empty_name = "glass"; 
	value = 10;
	weight = 1;
	heal = 5;
	strength = 5;
	full_value = get_full_value(strength,heal);
	if (!test_weight(weight))
	  return 1;
	water -= 1;
      } else 
	return 0;
  if (this_player()->query_money() < full_value) {
    write("That'll cost you "+full_value+" which you don't have.\n");
    return 1;
  }
  healing=clone_object("obj/"+type);
  healing->set_name(name);
  healing->set_alias(alias);
  healing->set_short(short);
  healing->set_long(long);
  healing->set_consumer_mess(consumer_mess);
  healing->set_consuming_mess(consuming_mess);
  if(type == "soft_drink") 
    healing->set_empty_container(empty_name);
  healing->set_value(value);
  healing->set_full_value(full_value);
  healing->set_weight(weight);
  healing->set_strength(strength);
  healing->set_heal(heal);
  healing->set_portable(0);
  move_object(healing,this_player());
  this_player()->add_money(-full_value);
  write("You pay Buddy "+full_value+" for "+short+".\n");
  say(this_player()->query_name()+" orders "+short+".\n");
  return 1;
}

sold_out_mess() {
  write("Buddy says: Sorry, I've run out of that.\n");
  return 1;
}

test_weight(w)
{
  if (!this_player()->add_weight(w))
    {
      write("Buddy says: You can't carry anymore.\n");
      return 0;
    }
  return 1;
}

get_full_value(str,heal)
{
  return ((10*heal+(heal^2)/5)-4*str);
}
