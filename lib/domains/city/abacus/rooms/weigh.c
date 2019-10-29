#define COST 100

inherit "/std/room"

create()
{
    set_light(1);
    set_short("A market");
    set_long("This area was probably a fruit market long ago,\n" +
	     "but was totally demolished by the nuclear blast.\n" +
             "All that remains are a few broken tables and an\n" +
	     "old brass scale.\n");

    add_exit("north", ROOM+"darkalley1");

    add_item(({"few broken tables", "broken tables", "broken table", "tables", "table"}),
	     "A few broken tables that held fruit once upon a time");
    add_item(({"old brass scale", "brass scale", "old scale", "scale"}),
	     "An old brass scale that used to weigh fruit. It still\n" +
             "seems in good shape, you might even be able to weigh\n" +
	     "things with it. While the weight marks have worn off,\n" +
             "you could probably get a general idea of the weight.\n" +
	     "There is a slot in the base");
    add_item(({"slot", "slot in the base"}),
	     "This seems to be a slot where you place money. A little\n" +
	     "sign is attached below the slot");
    add_item(({"little sign", "sign"}),
	     "A small sign with some writing. Maybe you should read it");
    add_message("read", ({"sign", "little sign"}),
		"It reads: Weight [item] to weigh your item. Cost is $100.\n",
	        "reads the sign."); 
}

init()
{
    ::init();
    add_action("weigh", "weigh");
}

weigh(arg)
{
    object ob;

    if (!arg) return 0;
   
    if (!(ob = present(arg, this_player())))
    {
	write("You can't weigh it if you don't have it!\n");
	return 1;
    }


    if (this_player()->query_money() < COST)
    {
	write("But you don't have enough money!\n");
	return 1;
    }
               
    this_player()->add_money(-COST);
    say(this_player()->query_name() + " weighs something on the scale.\n");
    write("You place the " + arg + " on the scale.\n");
    call_out("weight1", 2, ob);
    return 1;
}

weight1(ob)
{
    write("The scale bumps up and down for a bit then comes to rest...\n");
    call_out("weight2", 2, ob);
    return 1;
}

weight2(ob)
{
    int i;
    string str;

    i = ob->query_weight();

    str = ob->short();

    if (!str) str = "Something";
    else str = capitalize(str);
    
    if (i == 0)
    	write(str + " looks as light as a feather.\n");
    else if (i == 1)
	write(str + " doesn't look like it weighs much at all.\n");
    else if (i == 2)
	write(str + " doesn't look too heavy.\n");
    else if (i == 3)
	write(str + " looks a bit heavy.\n");
    else if (i == 4)
	write(str + " appears somewhat heavy.\n");
    else if (i == 5)
	write(str + " looks quite heavy.\n");
    else if (i >= 6)
	write(str + " looks very heavy indeed.\n");
    return 1;
}  

