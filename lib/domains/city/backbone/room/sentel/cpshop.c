inherit "/std/room";

#define CPPRICE "$1200"
#define CPPRICEINT 1200
#define SUBPRICE "$500"
#define SUBPRICEINT 500
#define CELLPHONE present("cell phone",this_player())
#define SENTELDIR ROOM+"sentel/"

void setup(void)
{
 
room 

/*
    if(!present("witch",this_object()))
     {
      move_object(clone_object("/players/wishbone/halloween/witch"),this_object());
     }
*/

set_light(1);
set_outdoors(0);
set_short("SenTel Shop");

set_long_f(
"This is a small, cube-shaped room.  The walls are made of "+
"gleaming silver.  They are all featureless except for the west "+
"one, embedded in which are two slots, a molded indentation, and a screen.  "+
"There is an empty doorway leading east.\n" );

add_exit("east",ROOM+"shop");

items_arr = ({
  ({"walls","silver","gleaming silver"}),
    "Gleaming silver.",
  ({"wall","west wall"}),
    "Gleaming silver. On the wall are two slots, a molded indentation, "+
    "and a screen.",
  ({"slots","two slots","slot"}),
    "There is a big one and a small one.",
  ({"small slot"}),
    "Money sized.",
  ({"big slot"}),
    "About 20cm times 5cm.",
  ({"indentation","molded indentation"}),
    "The outline of the indentation looks stunningly like that "+
    "of the front of a cell phone.",
  ({"screen"}),
    "In the upper left corner are three Japanese characters.  In "+
    "the upper right corner is the text \"SenTel\".  The rest contains "+
    "some readable text.",
  ({"text","readable text"}),
    "Readable text.",
  ({"doorway","empty doorway"}),
    "It's empty and big enough to be an obvious exit."
  });
}

init()
{
::init();
add_action("read","read");
add_action("buy","buy");
add_action("renew","renew");
}

read(str)
{
if(str=="text" || str=="screen")
  {
  writef(
  "The screen reads: \"Welcome to the SenTel shop.  Here you can buy our "+
  "products or subscribe to our services.  Everything is self-automated.  Below "+
  "is what we have to offer:\n" );
  write("\n"+
  "  Personal Cell Phone: "+CPPRICE+".  \['buy cell phone'\]\n"+
  "  100 Reset Cell Phone Subscription: "+SUBPRICE+".  \['renew cell phone'\]\"\n");
  }
else
  {
  writef("Read what?\n" );
  }
return 1;
}

buy(str)
{
object ob;
if(str=="phone" || str=="cell phone")
  {
  ob = clone_object(SENTELDIR+"cellphone");
  if(this_player()->query_money() < CPPRICEINT)
    {
    writef("You don't have enough money.\n" );
    destruct(ob);
    }
  else
    {
    if(CELLPHONE)
      {
      writef("You already have a cell phone.\n" );
      destruct(ob);
      }
    else
      {
      if(move_object(ob,this_player()))
        {
        writef("You are carrying too much shit.\n" );
        destruct(ob);
        }
      else
        {
        writef("You slip "+CPPRICE+" into the money slot.\n");
        say(this_player()->query_name()+" slips "+CPPRICE+" into the money slot.\n");
        this_player()->add_money(-CPPRICEINT);
        tell_room(environment(this_player()),
        "A cell phone slides gently out of the larger slot.\n");
        writef("You pick it up.\n");
        say(this_player()->query_name()+" picks it up.\n");
        }
      }
    }
  }
else
  {
  writef("Buy what?\n" );
  }
return 1;
}

renew(str)
{
if(str=="cell phone" || str=="phone")
  {
  if(CELLPHONE)
    {
    writef("You slip "+SUBPRICE+" into the money slot.\n");
    say(this_player()->query_name()+" slips "+SUBPRICE+" into the money slot.\n");
    this_player()->add_money(-SUBPRICEINT);
    writef(
    "You snap your cell phone into the indentation on the wall.\n");
    say(
    this_player()->query_name()+" snaps "+this_player()->query_possessive()+
    " cell phone into the indentation on the wall.\n");
    tell_room(environment(this_player()),
    "The cell phone glows so brilliantly for a few moments you have to "+
    "squint your eyes.\n");
    present("cell phone",this_player())->set_time(100);
    writef(
    "You unsnap the cell phone from the indentation on the wall.\n");
    say(
    this_player()->query_name()+" unsnaps "+this_player()->query_possessive()+
    " cell phone from the indentation on the wall.\n");

    if(CELLPHONE->query_phone_status()==0 || CELLPHONE->query_phone_status()==1)
      {
      CELLPHONE->set_phone_status(1);
      CELLPHONE->set_led("\"Ready.\"");
      }
    }
  else
    {
    writef(
    "You don't have a cell phone to renew.\n" );
    }
  }
else
  {
  writef(
  "Renew what?\n" );
  }
return 1;
}
