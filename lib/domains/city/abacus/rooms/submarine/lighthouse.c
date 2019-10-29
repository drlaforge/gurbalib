inherit "/std/room";

void setup(void) {
      set_light(1);
      set_outdoors(1);
      short_desc = "abacus lighthouse";
      set_long_f("This is a jetty on some barren rocks. "+
		  "The Abacus lighthouse towers above you covering most of the rocks, "+
		  "with just a small area cleared as a helipad.\n");
      items_arr=({
	({"helipad","small helipad","area","small area"}),
	"A small area for a helicopter to land when bringing supplies to the lighthouse",
        "jetty", "A jetty.",
	({"rocks","barren rocks","rock"}),"The rocks are totally barren",
	({"abacus lighthouse","lighthouse"}),
	"The lighthouse juts upwards from the barren rocks",
	"abacus","You can just make out the city of Abacus in the distance",
	});
   }
