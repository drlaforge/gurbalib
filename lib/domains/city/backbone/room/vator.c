
/* vator std 
 * Darkman
 *
 * This vator works more like rl vators, you can push as many floors 
 * as you like and it will go to all of them.
 * like a real vator, if its originally going down, then it will
 * continue going down till at lowest stop, then go back up.
 * and vice-versa.
 *
 * Enjoy, lemme know if anything bugs =)
 *
 * inherit this room, and add the following functions:
 * 
 * add_floor( floor#, file_name, (optional)length to floor )
 * set_current_floor( floor# );
 * set_push_verb( array|string );           /*  optional, default: push, press */ * set_order( asceding = 0, decending = 1); /*  optional, default: 1 */ * set_speed( seconds );                    /*  optional, default: 3 */ * set_door_pause( seconds );               /*  optional, default: 4 */ * set_length( len );                       /*  optional, default: 1 */ * set_enter( dir );                         /*  optional, "enter" (for rooms w/ panel) */ *
 */

#include <def.h>

#define ELE_MOVE     3
#define DOOR_PAUSE   4
#define STD_LENGTH   1

#define FLOOR        0
#define LEN          1

inherit STD_ROOM; 
#include "../area.h"

/* local vars */

nomask mapping floors;

int current_floor;          
int is_moving;
int order;
int door_pause;
int *stop_floor;
int hide;
int delay;
int door_delay;
int length;
int extern_tick;
int num;

mapping t_stop;

string id_key;
string out_dir;
string *push_verbs;
string base_direction;
string enter;

/* local funcs */
void set_button_verb(mixed input);
int add_stop(int i);

void set_hide(int i) { hide = i; }
void set_order(int i) { order = (!i ? 0 : 1); }
void set_speed(int i) { delay = i; }
void set_door_pause(int i) { door_delay = i; }
void set_enter(string where) { enter = where; }
void set_length(int i) { length = i; }

int is_moving() { return is_moving; }
int query_door_pause() { return door_pause; }
int *query_stops() { return stop_floor; }

mapping query_floors() { return floors; }
mapping query_t_stop(){ return t_stop; }

string query_direction() { return base_direction; }
string query_where(int i){ return floors[i][FLOOR]; }
int query_length(int i) {
	if(!length)	length = STD_LENGTH;
	if( !i ) return -1;
	if( i<1 && i > m_sizeof(floors) ) return length;
	if(!floors[i][LEN]) return length;

	return floors[i][LEN];
}

void setup() {
	 
	 

	no_clean_up = 1;
	set_light(1);
	set_outdoors(0);

	set_short("An Elevator");
	set_long("You're in an elevator, there is a panel here.\n");

	/* vator stuff */
	add_item( ({ "panel", "elevator panel" }), "#panel_desc", 0, 0);
	add_item( ({ "display", "display panel" }), "#display_desc", 0, 0);

	add_exit( "out", "whatever", "");

	set_button_verb( ({ "push", "press" }) );

	if(!t_stop) t_stop = ([ "up" : ({ }), "down" : ({ }) ]);
	if(!floors) floors = ([ ]);
	if(!stop_floor) stop_floor = ({ });
	if(!current_floor) current_floor = 1;
	if(!id_key) id_key = "ElevPanel";

	order = 1;
}

/* Set the verbs for the push function */
void set_button_verb( mixed input ) {
	if( !pointerp(input) ) 
		push_verbs = ({ input });
	else
		push_verbs = input;

	return;
}

void init() {
	::init();
	add_action("push", push_verbs);
	add_action("out", "out");
}

/* going out? */
int out() {
	if(!out_dir)
		out_dir = query_where(current_floor);

	if(!out_dir){
		write("Something seems to have broken. You're stuck in here!\n");
		return 1;
	}

	if(is_moving){
		write("The doors are closed, obviously, since the elevator is moveing.\n");
		return 1;
	}

	TP->move_player("out the elevator#"+out_dir);
	return 1;
}

/* make sure we're going the right direction */
void direction_check() {
     /* WTF!? */
    if(!sizeof(stop_floor)) return ;
	/* what direction? */
	if(!base_direction)
		if( stop_floor[0] > current_floor )
			base_direction = "up";
		else
			base_direction = "down";

	/* Going up? Keep going up till we have no more 'up' stops */
	if( base_direction == "up" && current_floor > stop_floor[0] )
	{
		base_direction = "down";
		stop_floor += t_stop["down"];
		t_stop["down"] = ({ });
	}

	/* Going down? Keep going down till we have no more 'down' stops */
	if( base_direction == "down" && current_floor < stop_floor[sizeof(stop_floor)-1] )
	{
		base_direction = "up";
		stop_floor += t_stop["up"];
		t_stop["up"] = ({ });
	}

	return ;
}

/* Proper floor movement (depending on length) */
void tick_floor() {
	int foo;
	
	if( !extern_tick ) extern_tick = 1;
	foo = (base_direction == "up" ? current_floor+1 : current_floor-1);
	foo = query_length(foo);

	if( extern_tick == foo ){
		current_floor = (base_direction == "up" ? current_floor+1 : current_floor-1);
		tell_room( this_object(), "The "+current_floor+" lights up on the display.\n" );
		call_other(this_object(), "move_me");
		extern_tick = 1;
		return ;
	} else {
		call_out( "move_me", delay);
	}

	extern_tick++;
}

/* push the button to go out */
int push(string where) {
	int floor, counter;
	string file, direction;

	if( !where )
		return !notify_fail("Push what?\n");

	floor = atoi(where);
	file = query_where(current_floor);

	if( undefinedp( file ) )
		return !notify_fail("Thats not a valid floor.\n");

	if( is_moving || door_pause ){
		/*  add the stop, and move on ... */		if(!add_stop( floor ))
			return !notify_fail("That floor has already been selected.\n");
		else
		{
			write( "You push the button for floor "+floor+".\n");
			say( TP->QN+" pushes the button for floor "+floor+".\n");
		}
		return 1;
	}

	if( floor == current_floor )
		return !notify_fail("You're already on that floor.\n");

	/* what direction? */
	if( floor > current_floor )
		base_direction = "up";
	else
		base_direction = "down";

	add_stop( floor );
	is_moving = 1;

	if(!delay) delay = ELE_MOVE;

	write( "You push the button for floor "+floor+".\n");
	say( TP->QN+" pushes the button for floor "+floor+".\n");
	tell_room( this_object(), "The elevator starts going "+base_direction+".\n");
    tick_floor();
	return 1;
}

void move_me() {

	if(!sizeof(stop_floor)) {
		/* make sure it's ok */
		is_moving = 0;
		door_pause = 0;
		out_dir = query_where(current_floor);
		return ;
	}

	if(member_array(current_floor, stop_floor) != -1) {
		out_dir = query_where(current_floor);

		tell_room( this_object(), "Ping!\nThe elevator slows to a halt and the doors open.\n");
		tell_room( find_object( out_dir ), "The elevator doors open.\n");

		stop_floor = stop_floor - ({ current_floor });

		if(!door_delay)
			door_delay = DOOR_PAUSE;

		call_out("door_pause", door_delay);

		door_pause = 1;
		is_moving = 0;
	} else {
		tell_room( this_object(), "The elevator continues to move "+base_direction+"...\n");
		tick_floor();
		direction_check();
	}
	return ;
}

void door_pause() {

	if(!sizeof(stop_floor))	{
		door_pause = 0;
		is_moving = 0;
		return ;
	}

	door_pause = 0;
	is_moving = 1;
	direction_check();	

	tell_room( this_object(), "The doors close as the elevator starts to move again.\n" );
	tell_room( find_object( out_dir ), "The doors of the elevator close.\n" );
	tick_floor();

	return ;
}

/* manage the floors to stop on */
int add_stop(int i) {
	/* the check if i is a valid floor should already have been done .. */

	if( member_array(i, stop_floor) == -1 ){
		stop_floor += ({ i });
		stop_floor = sort_array(stop_floor, "order_stops", this_object());
		return 1;
	}
	/* The floor is already on stop list */
	return 0;
}

int order_stops( int one, int two ) {
	return ( one < two );
}

void add_waiting(string dir, int f) {
	if(!t_stop)
		t_stop = ([ "up" : ({ }), "down" : ({ }) ]);

	if(dir != "up" && dir != "down")
		return ;

	t_stop[dir] += ({ f });
	return ;
}

/* add floors to the mapping */
varargs int add_floor(mixed file, int meters) {
	int i;

	/* We need proper input */
	if(!file) return 0;
	if(!num) num = 1;
        if(!meters) meters = 0;

	if( pointerp(file) ) {
		for(i=0; i<sizeof(file); i++){
			add_floor(file[i], meters);
		}
		return 1;
	}

	if( !stringp(file) ) return 0;
	if( !undefinedp(floors[num]) ) /* floor num is there already, skip it */
		return 0;

	floors += ([ num : ({ file, meters }) ]);
	num++;
	
	return 1;
}

nomask int init_vator() {
	object ob, panel;
	string file;
	int i;

	for(i=1; i<=m_sizeof(floors); i++) {

		floors[i][LEN] = query_length(i);
		file = query_where( i );
		
		file->foo();
		ob = find_object(file);

		if(!ob)
			continue;

		if( panel = present(id_key, ob) )
			destruct(panel);
		
		panel = clone_object(PANEL);

		panel->set_floor(i);
		panel->set_alias(id_key);
		panel->set_vator(this_object());
		panel->set_hide(hide);

		if(enter)
			panel->set_enter(enter);
		move_object( panel, ob );
	}

	out_dir = query_where( current_floor );
	return 1;
}

/* where are we?? */
int set_current_floor(int num) {

	if(num < 0) return 0;
	if( undefinedp( floors[num] ) ) return 0;

	current_floor = num;
	init_vator();
	return 1;
}

int query_current_floor() {	return current_floor; }


/* Panel description*/
void panel_desc() {
	string output, tmp, line;
	int i, max_len;

	output = "\n";
	line = "";

	if( !order )
	{
		for(i=0; i<m_sizeof(floors); i++) {
			tmp = query_where( (i+1) );
			if(file_size(tmp) > 0)
				tmp = tmp->short();
			else
				tmp = "Floor "+(i+1);

			line += sprintf("|%' ':2s%d%' ':4s%s\n", 
				( member_array(i+1, stop_floor) != -1 ? "*" : "" ), (i+1), 
				( ((i+1) == current_floor) ? ">" : "" ), tmp+" |");
			
			if( strlen(line) > max_len )
				max_len = strlen(line);

			output += line;
			line = "";
		}
	} else {
		for(i=m_sizeof(floors); i>0; i--) {
			tmp = query_where( (i) );
			if(file_size(tmp) > 0)
				tmp = tmp->short();
			else
				tmp = "Floor "+(i);

			tmp = explode(tmp, "\n")[0];

			line += sprintf("|%' ':2s%d%' ':4s%s\n", 
				( member_array(i, stop_floor) != -1 ? "*" : "" ), (i), 
				( ((i) == current_floor) ? ">" : "" ), tmp+" |");
			
			if( strlen(line) > max_len )
				max_len = strlen(line);

			output += line;
			line = "";
		}
	}

	output = sprintf("%'-':"+max_len+"s\n%s\n%'-':"+max_len+"s\n", "",
		output, "");

	write(output);
	return ;
}

void display_desc() {
	int i, max, line;
    string output;

	max = 0;
	line = ((m_sizeof(floors)*9)-m_sizeof(floors));
	line += 9;

	output = sprintf("%'-':"+line+"s\n|", "");
	for(i=0; i<m_sizeof(floors); i++) {
		max ++;
		output += "\t"+
		(current_floor == (i+1) ? colour_string((i+1), "BROWN", "env", this_player()) : (i+1) );
		if( max > 7 ) output += "\t|\n";
	}

	output += sprintf("\t|\n%'-':"+line+"s\n", "");
	write(output);

	return ;
}

/* Eof - Darkman Obeer 000505 */
