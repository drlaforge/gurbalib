/* randomized storage added, the shop WILL sell out once in a while...
 And the prices are raised as well!			 Turbo 980527 */ 
/* Fuck you, Turbo. */
/* added 'show <weapon>' just for fun.. Thorwald 921023 */

inherit "std/room";
#include "../area.h"

#define INFORM_COST 300
#define FRANK   present("frank", this_object())

int ammo, items, i;
object ob, tp, dev;
int *ammo_sold;

init () {
	::init();
	add_action ("buy", ({ "buy", "order" }) );
	add_action ("menu", ({ "list", "menu" }) );
	add_action ("show", ({ "show", "calibre" }) );
}

reset (arg) {
    int x;
	ammo = ({"300", 100,
	         "500", 500,
	         "556", 500,
	         "762", 100,
	         "810", 100,
	         "840", 100,
	         "900", 100,
	         "965", 100,
	         "1000", 100,
	         "1140", 100,
	         "1270", 100,
	         "1400", 50,
	         "1700", 50,
	         "1727", 50,
	         "2000", 25,
	        });
            
	/*  Total amount of ammo sold per reset, randomized between 1 and 50 for each type */
    x = sizeof(ammo)/2;
	if( !sizeof(ammo_sold) ) ammo_sold = allocate(x);
	for (i = 0; i < x; i++) {
		ammo_sold[i] = random(50);
	}
	 
	if (arg)
		return ;
	set_outdoors (0);
	set_light (1);
	set_short("Tyson & Kid's Ammunition Shop");
	set_long_f("You stand in the Tyson & Kid's ammo shop. Your one stop shop of all your favorite " +
	           "ammunition for your favorite guns! There are shelves with packets all over the walls. The " +
	           "packets consist of ammo for sale, if you type \"list\" you can see a list of the current " +
	           "inventory. A large sign has been posted on wall behind the counter.\n");
	add_exit( "east", ROOM+"boul5" );
        add_object("/std/object/unjam_device.c", 1);
        add_object("/obj/monsters/frank.c", 1);
        add_object("domains/NG/Areas/merc/npc/frank_guard.c", 1);
	add_item(({"large counter", "counter"}), "A simple counter, behind which the sales clerk does his work.");
	add_item("shelves", "Shelves with packets of ammunition on them.");
	add_item(({ "packets", "packet", "packets of ammo"}), "Just simple packets of ammo for your purchasing pleasure.");
	add_readable(({"large sign", "sign"}), "WARNING: DO NOT STEAL. WE WILL KICK YOUR ASS.");
}

ammo_sold(){ return ammo_sold; }
menu () {
	int number;

	for (number = 0; number < sizeof(ammo); number += 2) {
		printf("%2d)   %3d rounds, calibre %3.2f mm (%3.2f inches) $%d%s.\n",
		       (number / 2 + 1), ammo[number + 1], (atoi(ammo[number]) * 1.0 / 100),
		       (atoi(ammo[number]) * 1.0 / 100 / 25.4), price(number), (ammo_sold[(number/2)] < 1 ? " -- SOLD OUT --" : "") );
	}
	return 1;
}

price (number) {
	return (2*(ammo[number + 1]*2) + (atoi(ammo[number]) / 25));
}

buy (str) {
	int number;
	int my_sold_number;

	if ( !FRANK ) {
		write("There doesn't appear to be anyone here to help you.\n");
		return 1;
	}

	if (!str || !sscanf (str, "%d", number)) {
		write ("Frank says: buy #\n");
		return 1;
	}
	if (number < 1 || number > (sizeof (ammo) / 2)) {
		write ("Frank asks: buy what?\n");
		return 1;
	}
	my_sold_number = number - 1;
	number = ((number - 1) * 2);
	if (this_player()->query_money() < price(number)) {
		write ("Frank slaps you.\nFrank says: You don't have enough money.\n");
		return 1;
	}
	if (ammo_sold[my_sold_number] < 1) {
		write("Frank says: I don't have that calibre ammo right now -- tough shit!\n");
		return 1;
	}
	ob = clone_object ("/obj/new_ammobox");
	ob -> set_name ("packet");
	ob -> set_calibre (ammo[number]);
	ob -> set_short(sprintf("A packet of %3.2f mm calibre bullets", (atoi(ammo[number])*1.0 / 100)));
	ob -> set_ammo (ammo[number + 1]);
	if (move_object(ob, this_player())) {
		write ("Frank says: You cannot carry more, idiot - pick it up when you figure out how this works!\n");
		move_object(ob, this_object());
		return 1;
	}
	this_player()->add_money ( - price(number));
	ammo_sold[my_sold_number] = ammo_sold[my_sold_number] - 1;
	write ("You pay " + price(number) + " dollars for a packet of ammo.\n");
	say (this_player()->query_name() + " buys a packet of ammo.\n");
	return 1;
}

show(str) {
	if (!str || !(ob = present (str, this_player())))
		return 0;
	if ( !FRANK ) {
		write("There doesn't appear to be anyone here to help you.\n");
		return 1;
	}

	write ("Frank studies " + ob->short() + ".\n");
	say ( this_player()->query_name() + " shows Frank the " + ob->short() + ".\n" );
	tp = this_player();
	call_out ("frank_result", 2);
	return 1;
}

frank_result() {
	if ( !FRANK ) {
		return 1;
	}

	if (!ob || !ob->query_calibre()) {
		tell_room (this_object(), "Frank says: That's no shootweapon!\n");
		return 1;
	}
	if (!tp->add_money( -INFORM_COST)) {
		write ("Frank says: I know exactly what you need. But, you don't have enough money - hahahaha.\n");
		return 1;
	}
	printf("Frank says: That's a %3.2f mm calibre weapon.\n",
	       (ob->query_calibre() / 100.0));
	if (ob->query_type()) {
		tell_room (this_object(), "Frank says: But this weapon needs extra ammunition, which I don't have.\n");
		return 1;
	}
	return 1;
}
