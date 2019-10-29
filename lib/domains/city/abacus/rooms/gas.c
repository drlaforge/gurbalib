/* gas station.
 * object must have:   query_tank()   -  size of tank
 *                     query_fuel()   - how much in it now
 *                     set_fuel ()    - fill fuel
 *
 * Changed it a bit, just because I could. - Darkman 09-22-01
 */

#include <global.h>

#define GAS_BASE 5
#define MIN_GAS 3
#define MAX_GAS 8

inherit STD_ROOM; 
#include "../area.h"

static int gas;

void get_gas_price(){
	int temp, mod;

	temp = gas;
	if(!temp) 
		temp = GAS_BASE;

	/* some stupid random formula */
        mod = ceil( random(10)*0.3 );

	/* 50% chance of price going down */
	if( random(2) == 1 )
		mod = mod * -1;

	temp += mod;
	if( temp < MIN_GAS ) temp = MIN_GAS;
	if( temp > MAX_GAS ) temp = MAX_GAS;

	gas = temp;
	return;
}

int query_gas_price(){
	if(!gas)
		get_gas_price();
	return gas;
}

void setup() {

	 
	get_gas_price();
	set_long(
		"A large neon \"StormTech Gas\" flickers annoyingly to your right,\n"+
		"in front of you stand about six gas pumps. Much like the ancient\n"+
		"ones, a pump, with an added computer interface. As you walk up to\n"+
		"one of the pumps, the screen displays: \n\n"+
		"Welcome to StormTech Gas! Thank you for your business!\n"+
		"Here you can fill up all your fuel dependent things.\n"+
		"Type 'fill up <object>' to fill it completely.\n"+
		"Type 'fill <object> <liters>' to fill it with <liters> liters.\n"+
                "The price is "+gas+" dollars/liter.\n\n");
	 
	set_outdoors(1);
	set_light(1);
	set_short("Gas station in dark alley");
	add_item( ({ "gas pump", "pump", "new gasp pump", "old style gas pump" }),
		"A simple gas pump, you do know how to use this, right?");
	add_item( ({ "screen", "computer", "computer interface" }),
		"Welcome to StormTech Gas! Thank you for your business!\n"+
		"Here you can fill up all your fuel dependent things.\n"+
		"Type 'fill up <object>' to fill it completely.\n"+
		"Type 'fill <object> <liters>' to fill it with <liters> liters.");
	add_item( ({ "flickering sign", "flickering neon sign", "neon sign", "sign" }),
		"A large sign high above you that read: StormTech Gas");

	add_exit("west",ROOM+"south_alley2","");
 
}

init() {
	::init();
    add_action("fill_it","fill");
}

fill_it(str) {
  int max,req;
  string what;
  object tank;
  if(!str) 
    return 0;

  if(sscanf(str,"up %s",what) == 1) {
    tank = present(what,this_player());
    if(!tank) 
        tank = present(what,environment(this_player()));
    if(!tank) {
      write("You don't have a " + what + ".\n");
      return 1;
    }
    if(!tank->query_tank()) {
      write("You can't put any fuel in your " + what + ".\n");
      return 1;
    }
    write("Your tank can hold " + tank->query_tank() + " liters.\n");
    max = (tank->query_tank() - tank->query_fuel()) * gas;
    if(this_player()->query_money() < max) {
      write("And that will cost you "+max+" dollars, which you don't have.\n");
      return 1;
    }
    /* Added full-check here.  --Thorwald */
    if (tank->query_fuel() >= tank->query_tank()) {
        write ("The "+what+" is already full!\n"); return 1;
    }
    write("You pay " + max + " dollars to fill your " + what + " up.\n");
    this_player()->add_money(-max);
    tank->set_fuel(tank->query_tank());
    return 1;
  }

  if(sscanf(str,"%s %d",what,req) == 2) {
    tank = present(what,this_player());
    if(!tank) 
        tank = present(what,environment(this_player()));
    if(!tank) {
      write("You don't have a " + what + ".\n");
      return 1;
    }
    if(!tank->query_tank()) {
      write("You cannot put any fuel in your " + what + ".\n");
      return 1;
    }
    if(req < 1) {
      write("Chucks! Are you trying to cheat?\n");
      return 1;
    }
    max = tank->query_tank() - tank->query_fuel();
    if(this_player()->query_money() < (req * gas)) {
      write("To fill your " + what + " with " + req + " liter"+(req>1?"s":"")+",\n");
      write("would cost you " + req*gas + " dollars, which you don't have.\n");
      return 1;
    }
    if(max < req) {
      write("Your " + what + " can't hold that much.\n");
      write("But you fill it as much as you can.\n");
      req = max;
    }
      write("You fill your " + what + " with " + req + " liter"+(req>1?"s":"")+",\n");
    write("and pay " + req*gas + " dollars for it.\n");
    this_player()->add_money(-req*gas);
    tank->set_fuel(tank->query_fuel() + req);
    return 1;
  }
}


