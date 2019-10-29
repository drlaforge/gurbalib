/* room/elevator.c  by Thorwald
 * inherit this file for making elevators!
 * Check /doc/examples/elevat.c to see how to use it
 * You should also do a "filename"->foo(); in your
 * area.c file, to load the elevator at reboot.
 */

inherit "std/room";
#include "../area.h"
#include <newroom.h>
mixed dests,obv_exit;
string levels;
int where,to;
int SPEED,LLENGTH;
int hide;
object ob;
string items2;

init()
{
::init();
   add_action ("mpress","press");
   add_action ("mpress","push");
   add_action ("mleave","out");
   add_action ("mleave","leave");
   add_action ("mleave","exit");
}

void setup(void)
{
    
     
/* who used this? */
/*  ("/players/darkman/compatlog.c")->used_it("/open/darkman/elev.compat", this_object()); */    /* defaults: */
    no_clean_up = 1;  /* Important!!! */
    short_desc ="In an elevator";
    long_desc = "You stand in an elevator.\n"+
	"There is a panel with buttons here.\n"+
	    "";
    set_light (1);
    set_outdoors(0);
    skip_obvious=1;
    where=0; /* 0 = Ground level */
    to=0;
    items_arr = ({ "panel",
		   "#panel",
		   "buttons",
		   "The buttons are red.\ntry 'exa panel'",
	   });
add_item(({"elevator doors","elevator door","door","doors"}), "#doors");
    set_speed(2);
    set_length(4);
}

set_start (str) 
{
    int i;

    where=(str-1)*LLENGTH;
    to=where;
    if (dests) 
    {
	i=0;
	while (i<sizeof(dests)) 
	{
	    if (!find_object(dests[i])) 
		dests[i]->force_load();
	    ob = present ("panel",find_object(dests[i]));
	    if (ob)
		destruct (ob); /* if already exist a panel! */
	    ob = clone_object ("obj/elevatorpanel"); /* put a panel in each room*/
	    if (obv_exit)
		ob -> set_exit (obv_exit); /* set alt. entr into elev */
	    if (hide)
		ob -> set_hide (hide); /* invisible panel */
	    ob -> set_elevator (this_object());
	    ob -> set_where (i*LLENGTH);
	    move_object (ob, find_object(dests[i]));
	    i++;
	}
	return 1;
    }
    return 0;
}

panel() 
{
    int i;
    write ("There are "+sizeof(dests)+" buttons labeled 1-"+sizeof(dests));
    write ("\n");
    write ("A display shows: "+((where / LLENGTH)+1));
    write ("\n");
    if (!levels) 
	return 1;
    i=sizeof(levels)-1;
    while (i>=0)
    {
	if ((where/LLENGTH)+1 == i+1) 
	    write ("* ");
	else
	    write ("  ");
	write ((i+1)+") "+levels[i]+".\n");
	i--;
    }
}

set_to (str)
{
    if (to!=where)
	return 0; /* elev already moving can't press! */
    tell_room (dests[where/LLENGTH], "The elevator door suddenly closes.\n");
    to=str;
    return 1;
}

set_enter (s) { obv_exit=s; }    /* extra direction if not 'enter elevator' */
set_hide (i) { hide=i; }         /* invisible panels ? */
query_speed() { return SPEED; }
query_length () { return LLENGTH; }
set_speed(s) { SPEED=s; }
set_length (l) { LLENGTH=l; }
set_dests(l) { dests=l; }
set_levels (l) { levels=l; }
query_destinations () { return sizeof (dests); }
query_to () { return to; }
query_where () { return where; }
query_dests () { return dests; }
query_dest (str) { return dests[str]; }

add_dests (str) 
{
   if (!dests)
       dests=str;
   else 
       dests=dests + ({ str });
   return 1;
}

mpress(str) 
{
    string s;
    int i;
    
    if (!str)
	return 0;
    if (!dests) 
	return 0;
    if (sscanf (str,"%s %d",s,i)!=2)
	if (!sscanf (str,"%d",i))
	{ 
	    write (capitalize(query_verb())+" what button?\n"); 
	    return 1; 
	}
    if (i>sizeof(dests) || i < 1)
    {
	write ("You can't find that button.\n"); 
	return 1; 
    }
   if (((i-1)*LLENGTH)==where) 
   {
       write ("You are already there.\n"); 
       return 1; 
   }
   if (!set_to((i-1)*LLENGTH)) 
   {
       write ("But the elevator is already moving.\n"); 
       return 1; 
   }
   write ("You "+query_verb()+" button "+str+".\n");
   say (this_player()->query_name()+" "+query_verb()+"ed button "+str+".\n");
   start_elevator();
   return 1;
}

doors(){
write("Simple elevator doors, which are current "+(where!=to?"closed":"open")+".\n");
}

mleave() 
{   /* leave elevator */
   if (where!=to)
   { 
       write ("You can't do that while the elevator is moving.\n");
       return 1;
   }
   this_player()->move_player("out of the elevator#"+dests[(where/LLENGTH)]);
   return 1;
}

to_room (str) 
{
   tell_room (this_object(),str);
   return 1;
}

/* ------- Elevator moving routines: (call outs) ------- */

start_elevator() 
{
    if (where < to) 
    {
	where+=1;
	to_room ("The elevator starts moving upwards.\n");
    }
    if (where > to)
    {
	where-=1; 
	to_room ("The elevator starts moving downwards.\n");
    }
    call_out ("move_elevator",SPEED);

}

move_elevator () 
{
    if (where!=to) 
    {
	if (where < to) 
	    where+=1;
	if (where > to) 
	    where-=1;
	if ((where/LLENGTH)*LLENGTH==where)
	{
	    to_room ("A display shows: "+((where/LLENGTH)+1)+".\n");
	}
	else
	    to_room ("The elevator continues...\n");
	call_out ("move_elevator",SPEED);
    }
    if (where==to) 
    {
	to_room ("Ping! \nThe elevator door opens.\n");
	tell_room (dests[where / LLENGTH],"Ping! \nSuddenly the elevator door opens.\n");
	remove_call_out ("move_elevator");
    }
}

query_escape_proof(){
        if(where != to)
		return "Not while the elevator doors are closed!\n";
}
