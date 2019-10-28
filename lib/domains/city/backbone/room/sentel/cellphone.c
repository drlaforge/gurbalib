#include <tune.h>
#include <ansi2.h>
inherit "/std/object";

int i;
object owner;
string colour;
string ansicolour;
string led;
int time;
int phone_status;
 /*
 * 0 : unsubscribed
 * 1 : inactive phone
 * 2 : phone ringing on their end
 * 3 : phone ringing on your end
 * 4 : on the phone with someone
 */
object tomodachi;

#define DEFAULTCOLOUR "GREY"
#define SENTELDIR ROOM+"sentel/"

/* Messages */
#define LEDdisplay "The LED display reads: "
#define LEDflicker "The LED display on your cell phone flickers.\n"
#define DIALING "You push somes keys on the keypad.\n"
#define DIALINGSAY this_player()->query_name()+" pushes some keys on "+this_player()->query_possessive()+" cell phone.\n"
#define NOSUBSCRIBE "You must subscribe to SenTel's service first.\n"
#define HANGUPLED "\"Call disconnected.\""
#define CLICK "Your phone clicks.\n"

query_phone_status() { return phone_status; }
query_ansicolour() { return ansicolour; }
set_led(x) { led=x; }
set_phone_status(x) { phone_status=x; }
set_time(x) { time=x; }
set_tomodachi(x) { tomodachi=x; }
call_out_removal() { remove_call_out("ring1"); }

disconnected()
{
if(phone_status>1)
  {
  writef(CLICK);
  writef(LEDflicker);
  say(this_player()->query_name()+" hangsup "+
  this_player()->query_possessive()+" cell phone.\n");
  led=HANGUPLED;
  tell_object(tomodachi,CLICK);
  tell_object(tomodachi,LEDflicker);
  present("cell phone",tomodachi)->set_led(HANGUPLED);
  present("cell phone",tomodachi)->set_phone_status(1);
  phone_status=1;
  if(phone_status==2)
    call_out_removal();
  if(phone_status==3)
    present("cell phone",tomodachi)->call_out_removal();
  }
}


query_auto_load()
{
save_phone();
if(environment() && environment() == this_player()) 
  return SENTELDIR+"cellphone:"+this_player()->query_real_name();
if(environment())
  return SENTELDIR+"cellphone:"+environment()->query_real_name();
}

init_arg(name)
{
if(!restore_object(SENTELDIR+"user/"+name))
  destruct(this_object());
save_phone(name);
}

save_phone(name)
{
if(!name && environment())
  name = environment()->query_real_name();
else
  return;
save_object(SENTELDIR+"user/"+name);
}

quit(){ save_phone(); }

restore_phone()
{
if(!restore_object(SENTELDIR+"user/"+this_player()->query_real_name()))
  return 0;
return 1;
}

drop()
{
disconnected();
return 1;
}

void setup(void) {
  {
  set_name("phone");
  set_value(0);
  set_weight(0);
  set_gettable(1);
  i=0;
  colour="white";
  ansicolour=DEFAULTCOLOUR;
  owner=this_player();
  if(this_player()->query_level()<ROOKIE_LEVEL)
    {
    time=0;
    led="\"Subscribe now to SenTel's service!\"";
    phone_status=0;
    }
  else
    {
    time=-1;
    led="\"Ready.\"";
    phone_status=1;
    }
  save_phone();

if(arg)
  {
  if(time>0)
    time--;
  if(time==0)
    {
    disconnected();
    phone_status=0;
    led="\"Your service has expired. Renew at the SenTel shop.\"";
    }
  if(time<0)
    {
    if(owner->query_level()<ROOKIE_LEVEL)
      tell_object(owner,"You cheating bastaad, you're using your cell phone for free.\n");
    }
  return;
  }
}

id(str)
{
return 
str=="phone" ||
str=="cell phone" ||
str==colour+" cell phone" ||
str==environment()->query_name()+"'s "+colour+" cell phone";
}

short()
{
return owner->query_name()+"'s "+colour+" cell phone";
}

extra_look()
{
if(phone_status==2 || phone_status==4)
  return environment()->query_name()+" is on the phone";
else
  return 0;
}

long()
{
writef(
"This is your own personal cell phone.  It fits easily in the palm of your "+
"hand.  The outer shell glows a "+colour+" colour and is transparent so as "+
"you can see the small, intricate circuitry within.  Centred at the top is "+
"a one line LED display. A keypad with small rubber keys covers most of the rest of "+
"the front.  Three Japanese characters are at the bottom of the front, below "+
"which is the smaller text: \"SenTel\".  "+
"Do 'cphelp' for information on its usage.\n", );
writef("You have "+time+" resets left until your subscription expires.\n");
}

init()
{
::init();

add_action("help","cphelp");
add_action("colour","cpcolour");
add_action("ansi","cpansi");
add_action("led","cpled");
add_action("dial","cpdial");
add_action("answer","cpanswer");
add_action("speak","cpspeak");
add_action("hangup","cphangup");

owner=environment();
if(time>0)
  {
  phone_status=1;
  led="\"Ready.\"";
  }
if(time==0)
  {
  phone_status=0;
  led="\"Subscribe now to SenTel's service!\"";
  }
if(time<0)
  {
  phone_status=1;
  led="\"Ready.\"";
  }
i=0;
if(find_call_out("ring1")>-1)
  call_out_removal();
}

help(str)
{
write(
"'cphelp'          : This help file.\n"+
"'cpcolour (str)'  : Have your phone change colour to (str).\n"+
"'cpansi (colour)' : Set the ansi colour.  Choose (colour) from 'help ansicol'.\n"+
"'cpled'           : Read the LED display.\n"+
"'cpdial (player)' : Dial up (player).\n"+
"'cpanswer'        : Answer your phone.\n"+
"'cpspeak (str)'   : Say (str) through the phone.\n"+
"'cphangup'        : Hang up the phone.\n"+
"\n"+
"Your service can be renewed at the SenTel shop.\n");
return 1;
}

colour(str)
{
if(str)
  {
  if(strlen(str)>20)
    writef("There isn't a colour out there with that many letters.\n");
  if(strlen(str)<21)
    {
    writef("The subtle glow of your cell phone shifts to a "+str+" colour.\n");
    say(
    "The subtle glow of "+this_player()->query_name()+"'s cell phone shifts to a "+
    str+" colour.\n");
    colour=str;
    }
  }
if(!str)
  {
  if(phone_status>1)
    {
    tell_object(tomodachi,CLICK);
    tell_object(tomodachi,LEDflicker);
    present("cell phone",tomodachi)->set_led(HANGUPLED);
    present("cell phone",tomodachi)->set_phone_status(1);
    }
  writef("The subtle glow of your cell phone fades as it turns invisible.\n");
  say(
  "The subtle glow of "+this_player()->query_name()+"'s cell phone fades as "+
  "it turns invisible.\n");
  destruct(this_object());
  }
return 1;
}

ansi(str)
{
if(str)
  {
  ansicolour=upper_case(str);
  writef("Ok.\n");
  }
if(!str)
  writef("You failed to change the ansi colour.\n");
return 1;
}

led(str)
{
writef(LEDdisplay+led+"\n");
return 1;
}

dial(str)
{
if(!str)
  writef("Dial who?\n");
if(phone_status==2 || phone_status==3 || phone_status==4)
  writef("You are already in a call.\n");
if(phone_status==1 && str)
  {
  if(find_player(str))
    {
    tomodachi=find_player(str);
    if(present("cell phone",tomodachi))
      {
      if(present("cell phone",tomodachi)->query_phone_status()==0)
        {
        writef(DIALING);
        writef(LEDflicker);
        say(DIALINGSAY);
        led="\"That person is not subscribed.\"";
        }
      if(present("cell phone",tomodachi)->query_phone_status()>1)
        {
        writef(DIALING);
        writef(LEDflicker);
        say(DIALINGSAY);
        led="\"The line is busy.\"";
        tell_object(tomodachi,"Your phone beeps.\n");
        tell_object(tomodachi,LEDflicker);
        present("cell phone",tomodachi)->set_led("\""+
        this_player()->query_name()+" tryed to call you.\"");
        }
      if(tomodachi==this_player())
        {
        writef(DIALING);
        writef(LEDflicker);
        say(DIALINGSAY);
        led="\"The line is busy.\"";
        }
      if(present("cell phone",tomodachi)->query_phone_status()==1)
        {
        if(!(tomodachi==this_player()))
          {
          phone_status=2;
          writef(DIALING);
          writef(LEDflicker);
          say(DIALINGSAY);
          led="\"Ringing up "+tomodachi->query_name()+".\"";
          call_out("ring1",5);
          present("cell phone",tomodachi)->set_phone_status(3);
          present("cell phone",tomodachi)->set_led("\""+
          this_player()->query_name()+" is calling you.\"");
          tell_object(tomodachi,LEDflicker);
          present("cell phone",tomodachi)->set_tomodachi(this_player());
          }
        }
      }
    else
      {
      writef(DIALING);
      writef(LEDflicker);
      led="\"That person is not registered with SenTel.\"";
      }
    }
  else
    writef("Dial who?\n");
  }
if(phone_status==0)
  writef(NOSUBSCRIBE);
return 1;
}

ring1()
{
i++;
if(i<6)
  {
  if(tomodachi)
    {
    writef("The phone rings on the other end.\n");
    tell_room(environment(tomodachi),tomodachi->query_name()+
    "'s cell phone is ringing.\n",({tomodachi}));
    tell_object(tomodachi,"Your phone is ringing!\n");
    call_out("ring1",10);
    }
  if(!tomodachi)
    {
    writef(LEDflicker);
    led="\"Could not establish a connection with "+tomodachi->query_name()+".\"";
    phone_status=1;
    i=0;
    }
  }
if(i==6)
  {
  writef(LEDflicker);
  led="\"Could not establish a connection with "+tomodachi->query_name()+".\"";
  phone_status=1;
  i=0;
  if(tomodachi)
    {
    present("cell phone",tomodachi)->set_led("\"Ready.\"");
    present("cell phone",tomodachi)->set_phone_status(1);
    tell_object(tomodachi,LEDflicker);
    }
  }
}

answer(str)
{
if(phone_status==3)
  {
  writef("You press a button the keypad and the phone clicks.\n");
  say(this_player()->query_name()+" answers "+this_player()->query_possessive()+
  " cell phone.\n");
  writef(LEDflicker);
  led="\"Connected with "+tomodachi->query_name()+".\"";
  present("cell phone",tomodachi)->call_out_removal();
  tell_object(tomodachi,CLICK+LEDflicker);
  present("cell phone",tomodachi)->set_led("\"Connected with "+
  this_player()->query_name()+".\"");
  phone_status=4;
  present("cell phone",tomodachi)->set_phone_status(4);
  }
else
  writef("Your phone isn't ringing.\n");
return 1;
}

speak(str)
{
if(str)
  {
  if(phone_status==4)
    {
    if(this_player()->query_ansi())
      {
      writef(
      ESC+ANSICODES[COLOURS[ansicolour]]+
      "\[CellPhone\]: "+str+"\n"+
      ESC+ANSICODES[COLOURS["RESET"]]);
      }
    if(!(this_player()->query_ansi()))
      writef("\[CellPhone\]: "+str+"\n");
    if(tomodachi->query_ansi())
      {
      tell_object(tomodachi,
      ESC+ANSICODES[COLOURS[present("cell phone",tomodachi)->query_ansicolour()]]+
      "\[CellPhone\]"+this_player()->query_name()+": "+str+"\n"+
      ESC+ANSICODES[COLOURS["RESET"]]);
      }
    if(!(tomodachi->query_ansi()))
      tell_object(tomodachi,"\[CellPhone\]"+this_player()->query_name()+": "+str+"\n");
    say(
    this_player()->query_name()+" speaks into "+this_player()->query_possessive()+
    " phone: "+str+"\n");
    }
  else
    writef("You speak into your inactive phone: "+str+"\n");
  }
if(!str)
  {
  writef("You drool silently onto your cell phone.\n");
  say(
  this_player()->query_name()+" drools silently onto "+
  this_player()->query_possessive()+" cell phone.\n");
  }
return 1;
}

hangup(str)
{
if(phone_status==0 || phone_status==1)
  writef("The phone is already hung up.\n");
disconnected();
return 1;
}

/*
* Other phones:
* /players/menta/std/phone.c
* /players/recon/stuff/obj/phone.c
*/
