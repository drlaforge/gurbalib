#include "../area.h"

inherit "/std/object";
inherit "/std/modules/m_readable";

static int grafitti;

void setup(void) {
	
	set_id("Graffitti Wall");
	set_short("A Graffitti Wall");
	set_gettable(0);
	set_long("Do: 'scribble <text>'\n");
	add_action ("scribble","scribble");
	add_action("read", "read");
}