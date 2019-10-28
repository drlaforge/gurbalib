/* Wishbone 18Mar00 - updated to be a little more in theme than a guild adventurers book... */

#include <ansi2.h>
#define B ESC+ANSICODES[COLOURS["HICYAN"]]
#define G ESC+ANSICODES[COLOURS["HIGREEN"]]
#define X ESC+ANSICODES[COLOURS["RESET"]]

#define DEBUG 0

id(str) { return str == "pamphlet" || str == "chain" || str =="history pamphlet"; }


query_value()
{
	return 0;
}
int current_page;
void setup(void)
{
    current_page = 0;
}

short()
{
    return "a "+colour_string("history pamphlet","HICYAN")+" attached to a chain";
}

long(str)
{
    if (str == "chain") {
        write("A strong chain secured to the wall.\n");
        return;
    }


    write("There is a pamphlet hanging on a chain attached to the wall.\n");
    write("The title is: '"+colour_string("A HISTORY OF NUCLEAR WAR","HICYAN")+"'.\n");
    write("You can '"+colour_string("read pamphlet","HIGREEN")+"' and '"+colour_string("open pamphlet","HIGREEN")+"' too if necessary.\n");
}


init()
{
	add_action("read_pamphlet", "read");
	add_action("open", "open");
	add_action("close", "close");


}

read_pamphlet(str)
{
    int i;
    string info;
    string mat;


if((str == "pamphlet")  && (current_page == 0)) {
        write("The pamphlet is closed.\n");
        return 1;

	
	}

        info = ({ "/doc/guildbook" });
	if(!str) return;
	if (str == 0)
	{
	notify_fail("read what ?\n");
#if DEBUG
        write("Info dirs:\n");
 	while (i < sizeof(info))
 	{
 		write(info[i] + " ");
 		i += 1;
 	}
 	write("\n");
 	return 1;
#endif
	}

        str = lowercase(str);
	if(id(str))
		str = "/";

        while (sscanf(str, "%s %s", str, mat));
	str = "/" + str;
	while(i < sizeof(info))
	{
		if (file_size(info[i] + str) == -2)
		{
   write ("\t\t\t\t CONTENTS PAGE\n");
   write ("\t\t\t\t =============\n");
   write("Chapters:\n");
   write("---------\n");
			ls(info[i] + str);
write(
"\n               To read something type 'read <chapter>'\n");
			return 1;
		}
		if (file_size(info[i] + str) > 0)
		{
			this_player()->more(info[i] + lowercase(str));
			return 1;
		}
		i += 1;
	}
        notify_fail("You leaf furiously through the pages but fail to find what\n"+
                    "you were looking for. Perhaps you should look at the contents page.\n");
         return 0;
	write("You leaf furiously through the pages but fail to find what\n"+
              "you were looking for. Perhaps you should look at the contents page.\n");

	return 1;
}


open(str)
{
    if (!id(str))
	return 0;
    if (current_page) {
	write("The pamphlet is already open.\n");
	return 1;
    }
    current_page = 1;
    write("Ok.\n");
    say(call_other(this_player(), "query_name", 0) +
	" opens the pamphlet.\n");
    return 1;
}

close(str)
{
    if (!id(str))
	return 0;
    if (current_page == 0) {
	write("It is already closed.\n");
	return 1;
    }
    current_page = 0;
    write("Ok.\n");
    say(call_other(this_player(), "query_name", 0) +
	" closed the pamphlet.\n");
    return 1;
}

#define BLANKS "                    "
ls(path)
{
    int i, j;

    path = this_player()->mk_path(path);
    if (!this_player()->valid_read(path))
    {
#if DEBUG
        write("Access denied: " + path + "\n");
#endif
        return;
    }
    path = get_dir(path + "/");
    if (!pointerp(path) || !sizeof(path))
    {
#if DEBUG
        write("No such directory.\n");
#endif
        return;
    }
#if DEBUG
    write("Sizeof directory: " + sizeof(path) + ".\n");
#endif
    for (i=j=0; i < sizeof(path); i++)
    {
        path[i] = capitalize(path[i]);
        write(j < 3 ? (path[i] + BLANKS)[0..18] : path[i] + "\n");
        j = j < 3 ? j + 1 : 0;
    }
    if(j)
         write("\n");
}

get() {
  write("You try and grab this priceless artifact but despite your mighty\n"+
	"strength the chain remains attached to the pamphlet.\n");
  return 0;
}
