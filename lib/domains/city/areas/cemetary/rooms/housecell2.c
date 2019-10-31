/* ROOMMAKER..  Modified by Thorwald. */

inherit "room/room";

int sbook;
int batteries;
object key;

reset(arg) {
  sbook = 1;
  batteries = 0;
  if (arg) return;
  set_outdoors(0);
  set_light(0);
  short_desc = "a cellar in the house in the cemetary";
    
  long_desc = 
    "The cellar comes to a dead end here. At one corner stands a desk with\n"+
    "a small chair in front of it. The walls look damp and you see mildew\n"+
    "everywhere.\n";
  items = ({
    "desk", "#desk",
    ({"slot","narrow slot"}),"Looks like the batteries go in here.",
    ({"system","control system","control"}),
    "There is no indication what the system actually does.",
    "chair","It's a very small chair, and it looks uncomfortable.",
    "book","#book",
  });
  dest_dir = 
    ({
      "/domains/areas/city/cemetary/room/housecell", "south",
    });
}

desk(){
  writef("The desk is made of wood and looks like it is starting to "+
	"to rot.  There is a slot to one side.\n");
  if(sbook)
    write("In the centre sits a book.\n");
  return 1;
}

init(){
  ::init();
    add_action("get","get");
    add_action("get","take");
    add_action("stick_it_in","insert");
}

get(str){
  object book;
  if(str!="book") return 0;
  if(!sbook) return 0;
  sbook = 0;
  write("You take the book from the table.\n");
  book = clone_object("/obj/treasure");
  book->set_short("a small black book");
  book->set_long(
	 "It is a very small book with a black cover. Looking closer, you\n"+
         "see that it is entitled 'Nightbreeders'.\n"+
         "It looks readable.\n");
  book->set_alias("book");
  book->set_weight(1);
  book->set_value(20);
  book->set_read(
       "The book is about the nightbreeders and how they came to being.\n"+
       "On one page, there is a map:\n"+
		 "  X     X\n"+
		 "  |     |\n"+
		 "  # # # #\n"+
		 "  | | | |\n"+
		 "X-#-#-#-#-#\n"+
		 "        |\n"+
		 "      #-O\n\n"+
		 "X = way down.\n"+
                 "O = way up.\n");
  if(transfer(book,this_player())) {
    write("You try to pick up the book, but cannot hold the extra weight.\n");
    say(this_player()->query_name()+" tried, but could not pick up the book from the desk.\n");
   move_object(book,this_object());
    return 1;
  }
  write("Ok.\n");
  say(this_player()->query_name()+" takes a book from the desk.\n");
  return 1;
}

book() {
  if(sbook) {
    write("It is a book on the desk. Why don't you pick it up?\n");
    return 1;
  } else {
    write("You see where a book was, but is no more.\n");
    return 1;
  }
}

stick_it_in(str)
{
 int have_some;
 have_some = (present("batteries",this_player()));
  if(have_some)
   {
    write("You insert the batteries into the slot.\n");
    destruct(have_some);
    batteries=1;
   writef("The desk starts to vibrate (weird...). A key is "+
      "shaken loose and falls to the floor.\n");
   key= clone_object("/domains/areas/city/cemetary/obj/bloodkey.c");
   move_object(key,this_object());
    return 1;
   }
  else
   {
    write("You don't have any batteries!\n");
    return 1;
   }
}

