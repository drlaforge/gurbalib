#pragma strict_types
#define MAX_LIST 25
#include <tune.h>

/* Variables... */

object *living_list;		/* Array of living objects.		*/
object *dead_list;		/* Array of dead objects.		*/
mixed numbers;			/* Mapping of words for numbers.	*/
mixed dirs;			/* Mapping of shorts for dirsections	*/

/* Prototypes... */

void show_dead_list (mixed *dead_list, int overflow);	/* Show dead objects */
void show_living_list (mixed *living_list);		/* Show livings.     */
string get_list_name (object ob, int num);	        /* Dead item(s) name */
string brief_desc (object room);			/* Room in brief mode*/
string convert_direction (string dir);		        /* Short form of dir */
string get_exits_string (mixed dest_dir, string *hide_obv); /* Exit string.*/
string add_decimal (int array_size, int index);		/* put ',' into lists*/
mixed fix_pair_map (mixed map, mixed new);		/* array to mapping  */

void
reset (int arg)
{
	if (arg)
		return;

	living_list = dead_list = ({});		/* Make empty arrays. */
}

void
display_look (int brief, int dark)			/* Display room. */
{
	object room;
	object inv;
	int cnt;

	room = environment (this_player());	

	if (this_player()->query_level() >= APP_LEVEL)
	        write ("[" + file_name(room) + "]\n");
	if (brief)
		write(brief_desc (room) + "\n");
	else
            {
		room->long();
            }

	inv = first_inventory(room);
	while(inv && cnt <= MAX_LIST)
	{
	        string sh;
	    
		sh = (string) inv->short();
		if (inv == this_player() || !sh || !strlen(sh))
		{
			inv = next_inventory(inv);
			continue;
		}
		if(!living(inv) || (!query_ip_number(inv)&&!inv->query_npc()))
		{
			dead_list += ({ inv });
			cnt++;
		}
		else
		{
		        living_list += ({ inv });
			cnt++;
		}
		inv = next_inventory(inv);
	}

	if (sizeof (dead_list))
	        show_dead_list(dead_list, cnt >= MAX_LIST);
	if (sizeof (living_list))
	        show_living_list(living_list);

	living_list = dead_list = ({});		/* Clear arrays. */
	return;
}

void
show_dead_list (mixed *dead_list, int indent)	/* Display dead items. */
{
	string str;
	int i;
		
	if (indent)
	        write ("Wow, what a lot of things.\n");
	str = indent ? "Among them you see " : "You see ";
	indent = indent ? 19 : 8;

	dead_list = unique_array (dead_list, "short");
	for (i=0; i < sizeof(dead_list); i++)
		str += get_list_name (dead_list[i][0], sizeof(dead_list[i]))
				+ add_decimal (sizeof(dead_list), i);
	write (break_string (str + ".", 79, indent));
	return;
}

void
show_living_list (mixed *living_list)		/* Display livings. */
{
	int i;
	string str;

	living_list = unique_array (living_list, "short");
	for (str="", i=0; i < sizeof(living_list); i++)
	{
	        str += get_list_name(living_list[i][0],sizeof(living_list[i]));
		str += add_decimal (sizeof(living_list), i);
	}
	str += (sizeof(living_list) > 1 || sizeof(living_list[0]) > 1) ? " are here." : " is here.";
	write (break_string (capitalize(str), 79, 0));
	return;
}

string
add_decimal (int array_size, int index)
{
	if (index == array_size - 2)
		return " and ";
	else if (index != array_size - 1)
		return ", ";	

	return "";
}

string
get_list_name (object ob, int num)	/* Fix list name of item. */
{
	string name;
	string pl_name;

	name = (string) ob->short(interactive(ob));
	if(name[strlen(name)-1] == '.')
		name = name[0..strlen(name)-2];

            name = capitalize(name);
	if (num <= 1)
	        return name =
		  (sscanf(name, "A %s", name) ? "a "+name :
		     (sscanf(name, "An %s", name) ? "an "+name : name));

	if (pl_name = (string) ob->plural_short())
		return convert_number (num) + " " + pl_name;
	return convert_number (num) + " " + pluralize(name);
}		

void
generate_long		/* Write the long description. */
(string ldesc, string lfunc, string *dests, object *aff_ob, int skip_obv, string *hide_obv)
{
    int i;

    if (stringp (lfunc))
        call_other (previous_object(), lfunc, 0);
    if (pointerp (aff_ob))
        for (i=0; i < sizeof (aff_ob); i++)
	    if(objectp(aff_ob[i]) && present(aff_ob[i],previous_object()))
	        aff_ob[i]->affect_environment();
    if (mappingp (dests) && !skip_obv)
        write (colour_string(get_exits_string(dests, hide_obv),"GREY","EXITS"));
}

string
brief_desc (object room)		/* Display the brief description. */
{
	int i;
	string str;
	string *hide_obv;
	mixed dirs;
        int size;

        str = capitalize ((string) room->short());
	if ((int) room->query_skip_obvious())
	        return str;
	dirs = (mixed) room->query_real_dest_dir();
	if (!mappingp (dirs))
		return (str + " (none)");
	hide_obv = (string *) room->query_hide_obvious();
	if (pointerp(hide_obv))
	        for (i=0; i < sizeof(hide_obv); i++)
		        dirs = m_delete(dirs, hide_obv[i]);
	if (!m_sizeof (dirs))
		return (str + " (none)");
	dirs = m_indices(dirs);
          dirs = map_array( dirs, "convert_direction", this_object() );
       str += " (";
      size = sizeof(dirs);
     for(i=0; i<size; i++) str += colour_string( dirs[i]+add_decimal( size, i ), "GREY", "EXITS" );
	return str + ")";
}

string
convert_direction (string dir)		/* Shorter form of direction. */
{
	if (!dirs)
		dirs = (["north":"n","south":"s","west":"w","east":"e",
			"northeast":"ne","northwest":"nw","southeast":"se",
			"southwest":"sw"]);
	if (dirs[dir])
		return dirs[dir];
	return dir;
}

mixed
fix_items (mixed items, mixed *new_item)	/* Fix the item mapping. */
{
	int i;
	int j;
	string desc;

	if (pointerp (items))
	{
	        if (!pointerp (new_item))
		         new_item = ({});
		new_item += items;
	}
	if (!mappingp (items))
		items = ([]);
	if (!pointerp (new_item))
		return items;

	if (sizeof (new_item) < 3)
		new_item += ({ 0 });
	for (i=0; i < sizeof (new_item); i++)
	{
		if (stringp (new_item[i]) && sscanf (new_item[i], "@%s", desc))
		{
		        previous_object() -> add_smell (new_item[i-2], desc);
			new_item = exclude_array (new_item, i, 0);
			i--;
		}
		if (stringp (new_item[i]) && sscanf (new_item[i], "&%s", desc))
		{
		        previous_object()->add_sound (new_item[i-2], desc);
			new_item = exclude_array (new_item, i, 0);
		        i--;
		}
/*
                if (stringp(new_item[i]) && sscanf(new_item[i], "!%s", desc))
                {
                        previous_object()->add_readable( new_item[i-2], desc );
                        new_item = exclude_array( new_item, i, 0 );
                        i--;
                }
*/
	}
	return fix_pair_map (items, new_item);
}

mixed
fix_dest_dir (mixed dest_dir, string *new_exit)	/* Fix the dest_dir mapping. */
{
	string foo;
	int jmp;
	int i;

	if (!mappingp (dest_dir))
		dest_dir = ([]);
	if (!pointerp (new_exit) || !sizeof(new_exit))
		return dest_dir;

	if (sizeof (new_exit) < 3)
		return dest_dir += ([new_exit[1]:({ new_exit[0], 0 })]);
	jmp=2;
	if (!new_exit[2] || sscanf (new_exit[2], "#%s", foo))
		jmp=3;
	for (i=1; i < sizeof(new_exit); foo=0, i+=jmp)
	        if (jmp==2)
			dest_dir[new_exit[i]] = ({new_exit[i-1],0});
		else
		{
		        if (stringp(new_exit[i+1]))
			          sscanf (new_exit[i+1],"#%s",foo);
			dest_dir[new_exit[i]] = ({new_exit[i-1], foo});
		 }
	return dest_dir;
}

mixed
fix_pair_map (mixed map, mixed new)	/* Convert array to mapping. */
{
	int i;
	int j;

	if (pointerp (map))
	{
	        if (!pointerp (new))
		        new = ({});
		new += map;
	}
	if (!mappingp (map))
		map = ([]);
	if (!pointerp (new))
		return map;
	for (i=0; i < sizeof (new); i+=2)	
		if (pointerp (new[i]))
			for (j=0; j < sizeof(new[i]); j++)
				map[new[i][j]] = new[i+1];
		else if (stringp (new[i]))
			map[new[i]] = new[i+1];
	return map;
}	

object *		 /* Add affecting objects. */
register_aff_ob (object new_ob, object *affect_objects)
{
	int i;

	if (!pointerp (affect_objects))
		affect_objects = ({});
	if (!new_ob)
		return affect_objects;
	if (member_array (new_ob, affect_objects) >= 0)
		return affect_objects;
	return affect_objects += ({ new_ob });
}

string         	/* Returns the string of exits. */
get_exits_string (mixed dest_dir, string *hide_obv)
{
	string ret;
	mixed dests;
	int len;
	int i;	
	
	if (pointerp(hide_obv))
	        for (i=0; i < sizeof(hide_obv); i++)
		        dest_dir = m_delete(dest_dir, hide_obv[i]);

	dests = m_indices(dest_dir);
	if (!sizeof(dests))
		return "    There are no obvious exits.\n";
	ret = (sizeof(dests)==1 ? "There is one obvious exit: " :
	       "There are "+convert_number(sizeof(dests))+" obvious exits: ");
	len = strlen(ret)+4;		
	for (i=0; i < sizeof(dests); i++)
		ret += (dests[i] + add_decimal (sizeof (dests), i));
	return "    " + break_string (ret + ".", 78 , len);
}

string *
query_dest_dir (mixed dest_dir)
{
	int i;
	string *dirs;
	string *tmp_arr;
	
	if (!mappingp (dest_dir))
		dest_dir = fix_dest_dir (0, dest_dir);
	if (!m_sizeof (dest_dir))
		return 0;
	dirs = m_indices (dest_dir);
	for (tmp_arr = ({}), i=0; i < sizeof (dirs); i++)
		tmp_arr+=({dest_dir[dirs[i]][0],dirs[i],dest_dir[dirs[i]][1]});
	return tmp_arr;
}

string *
query_pair_map (mixed map)
{
	int i;
	string *tmp_arr;
	string *indices;

	if (!mappingp (map))
		map = fix_pair_map (0, map);
	if (!m_sizeof (map))
		return 0;
	indices = m_indices (map);
	for (tmp_arr=({}), i=0; i < sizeof (indices); i++)
		tmp_arr += ({ indices[i], map[indices[i]] });
	return tmp_arr;
}

mixed
query_real_map (mixed map)
{
	if (!mappingp (map))
		map = fix_pair_map (0, map);
	if (!m_sizeof (map))
		return 0;
	return map;
}

