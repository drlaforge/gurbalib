inherit "/std/room";

void setup(void) {
 set_light(1);
 set_outdoors(1);
 short_desc = "on a jetty";
 set_long_f("You stand on a small jetty protruding out into the ocean. You "+
	    "realize from careful examination of the lifeless ocean that you "+
	    "would certainly perish from swimming in its waters. The jetty "+
            "countinues to the west and east from here.");
 dest_dir = ({
	ROOM+"submarine/jetty3", "west",
	ROOM+"submarine/jetty", "east", });
 items_arr=({"waters",
        "The water is so polluted that nothing could live in it.",
	"slim",
	"You do not know what it is, but it sure looks gross.",
	"green slim",
	"You do not know what it is, but it sure looks gross.",
        "jetty",
	"The jetty extends out over the ocean.",
	"water",
	"The ocean water.",
        "small jetty",
	"The jetty extends out over the ocean.",
	"ocean",
	"A large and lifeless ocean.",
	"lifeless ocean",
	"A large and lifeless ocean.",});
  }
