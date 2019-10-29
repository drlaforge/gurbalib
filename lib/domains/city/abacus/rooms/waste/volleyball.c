inherit "std/room";
#include "../area.h"
string str,ro,rt,lo,lt;
int ro_pos,rt_pos,lt_pos,lo_pos;
int i;
int diff_level;
int reset_call;
int who_blocking,this_blocker;
int real_block;
int block_here,block_there;
int blocking_array,first_blocker,second_blocker,n_block_fr,n_block_fl;
int first_time;
int block_array;
int lscore,rscore;
int from_pos;
string pos_nom;
object ron,rtn,ltn,lon;
int number_hits;
int start_game;
int team_mate;
int where_array;
int last_touch,in_game,player_number;
int over,last_hit;

string nom;
int rdm;
int rnd,ball_pos,in_play,timer,real_time;
int coin_flip,who_serve;
string service_array;
int server_ok;
string this_server;
int countr,countl;
int all_present;
int play_ok;

void setup(void) {
   
  set_light(1);
  set_outdoors(0);
  if(!first_time){
  countr=0;
  countl=0;
  diff_level=2;
  ro="-";
  lo="-";
  rt="-";
  lt="-";
  first_time=1;
  }
  short_desc = "A Volleyball Court";
  set_long_f("A volleyball court is set up here "+
	"with a net stretched between two poles. A sign is near one of the "+
	"poles and has some important writing on it.\n");
dest_dir = ({});
add_item(({"sand"}),"It's a quartz sand common on many beaches");
add_item(({"court","volleyball court"}),"A volleyball game.\nTo see the rules, read the sign.");
add_exit("south",ROOM+"convoy/wasteland");
add_item(({"sign"}),"Rules of the game:\n"+
"    The game is played on a 2x2 grid on each side of the net.\n"+
"You move around by moving to the corners and typing fr, fl, br, or bl.\n"+
"(Front Right, Back Left, etc) To hit the ball, you type the command\n"+
"followed by where you want to aim (spike fr , bump bl, etc).\n"+
"You will not always hit the ball where you are aiming. When a ball is hit,\n"+
"There will be an unknown time for the players to move and react before\n"+
"the ball hits the ground.\n"+
"    You can only block when standing in the front row (fr or fl).\n"+
"And when you do so, you remain in the air attempting a block for a short\n"+
"time during which you cannot move or hit the ball.\n\n"+
"For more information type 'commands'.");
add_item(({"water","ocean"}),"The ocean is a nice inviting blue.\n"+
  "Waves are crashing in toward shore");
add_item(({"waves","wave"}),"The waves are really big.\n"+
  "If only you had some way to get out there.");
add_item(({"net"}),"A standard volleyball net hung between 2 poles");
add_item(({"pole","poles"}),"Two poles with a volleyball net between them.\n"+
"There is a sign on one of the poles.");
add_item(({"shore"}),"A sandy shore against which the waves come rolling in.");
add_item(({"beach"}),"A sandy beach.");
}

init() {
  ::init();
  add_action("play","play");
  add_action("spike","spike");
  add_action("show_score","score");
  add_action("endgame_check","endgame");
  add_action("stopend","stopend");
  add_action("choose","choose");
  add_action("serve","serve");
  add_action("jserve","jserve");
  add_action("bump","bump");
  add_action("set","set");
  add_action("read","read");
  add_action("general_stuff","general");
  add_action("who_is_serving","whoserve");
  add_action("start","start");
  add_action("where","where");
  add_action("players","players");
  add_action("commands","commands");
  add_action("block","block");
  add_action("fr","fr");
  add_action("fl","fl");
  add_action("br","br");
  add_action("bl","bl");
  add_action("help_starting","starting");
  add_action("emote","emote");
  add_action("difficulty","difficulty");
  add_action("hit","hit");
}
emote(str) {
  notify_fail("Emote what?\n");
  write("You emote: "+this_player()->query_name()+" "+str+"\n");
  say(this_player()->query_name()+" "+str+"\n");
  return 1;
}
start() {
  if(start_game==1){
    write("Game is already in progress.\n");
    return 1;
  }
  write("Time to choose teams. Choose either the 'r' or the 'l' side.\n");
  say("Time to choose teams. Choose either the 'r' or the 'l' side.\n");
  countl=0;
  countr=0;
  ro="-";
  lo="-";
  rt="-";
  lt="-";
  rscore=0;
  lscore=0;
  all_present=0;
  return 1;
}
choose(str){
  if(this_player()->query_name()==ro ||
      this_player()->query_name()==lo ||
      this_player()->query_name()==rt ||
      this_player()->query_name()==lt){
         write("You are already in the game.\n");
        return 1;
  }
  if(str=="l"){
    if(countl==2){
      write("There are already 2 players on that team!\n");
      return 1;
    }
    else {
      write("You stand over with the team on the left.\n");
      say(this_player()->query_name()+" walks over to join "+
        "the team on the left.\n");
      countl=countl+1;
      if(countl==1){
        lo=this_player()->query_name();
        lon=this_player();
      return 1;
    }
     else if(countl==2){
        lt=this_player()->query_name();
        ltn=this_player();
      return 1;
    }
}
}
  if(str=="r"){
    if(countr==2){
      write("There are already 2 players on that team!\n");
      return 1;
    }
    else {
      write("You stand over with the team on the right.\n");
}
      say(this_player()->query_name()+" walks over to join "+
        "the team on the right.\n");
      countr=countr+1;
      if(countr==1){
        ro=this_player()->query_name();
        ron=this_player();
      return 1;
    }
       else if(countr==2){
        rt=this_player()->query_name();
        rtn=this_player();
         return 1;
      }
  else write("Please choose either the 'r' or the 'l' teams!\n");
  return 1;
}
}
play() {
  if(start_game==1){
     write("Game is already in progress.\n");
     return 1;
}
          if(countr==2){
     if(countl==2){
              play_ok=1;
              lscore=0;
              rscore=0;
              block_array=({0,0,0,0});
             real_block=({0,0,0,0});
              who_blocking=({});
              start_game=1;
              coin_flip=random(2);
                 if(coin_flip==1){
                    who_serve=1;
                    service_array=({ro,lo,rt,lt});
                    say(lo+" will serve first.\n");
                    write(lo+" will serve first.\n");
                    return 1;
                 }
                 if(coin_flip==0){
                     who_serve=0;
                     service_array=({ro,lo,rt,lt});
                     say(ro+" will serve first.\n");
                     write(ro+" will serve first.\n");
                     return 1;
                 }
    }
    write("The left team doesn't have 2 players yet.\n");
    say("The left team doesn't have 2 players yet.\n");
    return 1;
    }
  write("The right team doesn't have 2 players yet.\n");
  say("The right team doesn't have 2 players yet.\n");
  return 1;
}
serve(str){
  if(play_ok<1){
    say("You can't serve until there are enough people on each team.\n");
    write("Please finish choosing teams.\n");
    return 1;
  }
  this_server=this_player()->query_name();
  ready();
  if(all_present==0){
    say("Make sure all players are present.\n");
    write("Make sure all players are present.\n");
    return 1;
  }
  if(reset_call==1){
    write("You cannot do that while game is being reset.\n");
    return 1;
  }
  if(in_play==1){
    write("You can't serve while the ball is in play.\n");
    return 1;
  }
  if(server_ok==0){
    write("It is not your turn to serve.\n");
  return 1;
  }
  where_array=({3,3,4,4});
  if(!str){
  write("Serve where? (br,bl,fr,fl)\n");
  return 1;
  }
  if(str!="fr" && str!="br" && str!="fl" && str!="bl"){
    write("Serve the ball to br,bl,fr,fl.\n");
    return 1;
  }
  write("Players are in their starting positions.\n");
  say("Players are in their starting positions.\n");
  where_start();
  write("You serve the ball.\n");
  say(this_player()->query_name()+" serves the ball.\n");
    rdm=random(100);
    last_hit=1;
    last_touch=who_serve;
    number_hits=0;
    over=1;
    in_play=1;
     serve_time();
  if(rdm<50){
    if(str=="fr"){
      write("You serve the ball to fr.\n");
      say(this_server+" serves the ball to fr.\n");
      ball_pos=1;
      call_out("no_touch",real_time);
      return 1;
    }
    if(str=="fl"){
      write("You serve the ball to fl.\n");
      say(this_server+" serves the ball to fl.\n");
      ball_pos=2;
      call_out("no_touch",real_time);
      return 1;
    }
    if(str=="br"){
      write("You serve the ball to br.\n");
      say(this_server+" serves the ball to br.\n");
      ball_pos=3;
      call_out("no_touch",real_time);
      return 1;
    }
      write("You serve the ball to bl.\n");
      say(this_server+" serves the ball to bl.\n");
      ball_pos=4;
      call_out("no_touch",real_time);
      return 1;
  }
  if(rdm<60){
    write("You serve the ball to fr.\n");
    say(this_server+" serves the ball to fr.\n");
    ball_pos=1;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rdm<70){
    write("You serve the ball to fl.\n");
    say(this_server+" serves the ball to fl\n");
    ball_pos=2;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rdm<80){
    write("You serve the ball to br.\n");
    say(this_server+" serves the ball to br.\n");
    ball_pos=3;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rdm<90){
    write("You serve the ball to bl.\n");
    say(this_server+" serves the ball to bl.\n");
    ball_pos=4;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rdm<95){
    write("You serve the ball into the net.\n");
    say(this_server+" serves the ball into the net.\n");
    change();
    return 1;
  }
    write("You serve the ball out of bounds.\n");
    say(this_server+" serves the ball out of bounds.\n");
    change();
    return 1;
}
ready(){
  if(present(lon, this_object())){
      if(present(ltn, this_object())){
       if(present(ron, this_object())){
          if(present(rtn, this_object())){
          all_present=1;
          right_server();
          return 1;
        }
       write(rt+" is not here.\n");
       all_present=0;
       say(rt+" is not here.\n");
       return 1;
       }
     else write(ro+" is not here.\n");
     say(ro+" is not here.\n");
     all_present=0;
     return 1;
   }
   else write(lt+" is not here.\n");
   say(lt+"is not here.\n");
   all_present=0;
   return 1;
  }
 else write(lo+" is not here.\n");
 say(lo+" is not here.\n");
 all_present=0;
 return 1;
}
right_server(){
  if(this_server==service_array[who_serve]){
    server_ok=1;
    return 1;
    }
  server_ok=0;
  return 1;
}
br(){
  if(play_ok<1){
    write("Wait for the game to begin.\n");
    return 1;
  }
  check_player(this_player());
  if(in_game<1){
    write("You are not in the game.\n");
    return 1;
  }
  if(in_play<0){
    write("You can't move until the ball is served.\n");
    return 1;
  }
  what_number(this_player());
  if(block_array[player_number]==1){
    write("You cannot move while blocking.\n");
    return 1;
  }
  if(where_array[player_number]==3){
    write("You are already at br.\n");
    return 1;
  }
  where_array[player_number]=3;
  write("You move to br.\n");
  say(this_player()->query_name()+" moves to br.\n");
  return 1;
}
check_player(ob){
  nom=ob->query_name();
  if(nom==ro || nom==rt || nom==lo || nom==lt){
    in_game=1;
    return 1;
  }
  in_game=0;
  return 1;
}
what_number(ob){
  player_number=member_array(ob->query_name(),service_array);
  return 1;
}
bl(){
  if(play_ok<1){
    write("Wait for the game to begin.\n");
    return 1;
  }
  check_player(this_player());
  if(in_game<1){
    write("You are not in the game.\n");
    return 1;
  }
  if(in_play<0){
    write("You can't move until the ball is served.\n");
    return 1;
  }
  what_number(this_player());
  if(block_array[player_number]==1){
    write("You cannot move while blocking.\n");
    return 1;
  }
  if(where_array[player_number]==4){
    write("You are already at bl.\n");
    return 1;
  }
  where_array[player_number]=4;
  write("You move to bl.\n");
  say(this_player()->query_name()+" moves to bl.\n");
  return 1;
}
fl(){
  if(play_ok<1){
    write("Wait for the game to begin.\n");
    return 1;
  }
  check_player(this_player());
  if(in_game<1){
    write("You are not in the game.\n");
    return 1;
  }
  if(in_play<0){
    write("You can't move until the ball is served.\n");
    return 1;
  }
  what_number(this_player());
  if(block_array[player_number]==1){
    write("You cannot move while blocking.\n");
    return 1;
  }
  if(where_array[player_number]==2){
    write("You are already at fl.\n");
    return 1;
  }
  where_array[player_number]=2;
  write("You move to fl.\n");
  say(this_player()->query_name()+" moves to fl.\n");
  where_array[player_number]=2;
  return 1;
}
fr(){
  if(play_ok<1){
    write("Wait for the game to begin.\n");
    return 1;
  }
  check_player(this_player());
  if(in_game<1){
    write("You are not in the game.\n");
    return 1;
  }
  if(in_play<0){
    write("You can't move until the ball is served.\n");
    return 1;
  }
  what_number(this_player());
  if(block_array[player_number]==1){
    write("You cannot move while blocking.\n");
    return 1;
  }
  if(where_array[player_number]==1){
    write("You are already at fr.\n");
    return 1;
  }
  where_array[player_number]=1;
  write("You move to fr.\n");
  say(this_player()->query_name()+" moves to fr.\n");
  where_array[player_number]=1;
  return 1;
}
bump(str){
  check_player(this_player());
  if(in_game<1){
    write("You are not in the game.\n");
    return 1;
  }
  if(in_play<1){
    write("The ball hasn't been served yet.\n");
    return 1;
  }
  if(!str){
    write("Bump where? (fl,fr,bl,br)\n");
    return 1;
  }
  what_number(this_player());
  if(where_array[player_number]!=ball_pos){
    write("The ball is not here.\n");
    return 1;
  }
  if(block_array[player_number]==1){
    write("You cannot bump while blocking.\n");
    return 1;
  }
  right_team(this_player());
  if(team_mate==0){
    write("The ball is on the other side of the net.\n");
    return 1;
  }
  if(last_touch==player_number){
    remove_call_out("no_touch");
    write("You cannot hit the ball twice in a row.\n");
    say(this_player()->query_name()+" hit the ball twice in a row.\n");
    whoops();
    return 1;
  }
  if(number_hits>2){
    remove_call_out("no_touch");
    write("Your side took too many hits.\n");
    say(this_player()->query_name()+"'s side took too many hits.\n");
    whoops();
    return 1;
  }
  if(str!="fr" && str!="fl" && str!="br" && str!="bl"){
  write("Please bump to either fr,fl,br,bl.\n");
  return 1;
  }
  rdm=random(100);
  adjust_bump();
  last_hit=3;
  number_hits=number_hits+1;
  last_touch=player_number;
  bump_time();
  remove_call_out("no_touch");
  if(rnd<50){
    if(str=="fl"){
        write("You bump the ball to fl.\n");
        say(this_player()->query_name()+" bumps the ball to fl.\n");
        ball_pos=2;
        call_out("no_touch",real_time);
        return 1;
      }
      if(str=="fr"){
        write("You bump the ball to fr.\n");
        say(this_player()->query_name()+" bumps the ball to fr.\n");
        ball_pos=1;
        call_out("no_touch",real_time);
        return 1;
      }
      if(str=="bl"){
        write("You bump the ball to bl.\n");
        say(this_player()->query_name()+" bumps the ball to bl.\n");
        ball_pos=4;
        call_out("no_touch",real_time);
        return 1;
      }
        write("You bump the ball to br.\n");
      say(this_player()->query_name()+" bumps the ball to br.\n");
        ball_pos=3;
        call_out("no_touch",real_time);
        return 1;
    }
  if(rnd<60){
    write("You bump the ball to fr.\n");
    say(this_player()->query_name()+" bumps the ball to fr.\n");
    ball_pos=1;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rnd<70){
    write("You bump the ball to fl.\n");
    say(this_player()->query_name()+" bumps the ball to fl.\n");
    ball_pos=2;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rnd<80){
    write("You bump the ball to br.\n");
    say(this_player()->query_name()+" bumps the ball to br.\n");
    ball_pos=3;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rnd<90){
    write("You bump the ball to bl.\n");
    say(this_player()->query_name()+" bumps the ball to bl.\n");
    ball_pos=4;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rnd<100){
    write("You bump the ball out of bounds.\n");
    say(this_player()->query_name()+" bumps the ball out of bounds.\n");
    whoops();
    return 1;
  }
    write("You bump the ball into the net.\n");
    say(this_player()->query_name()+" bumps the ball into the net.\n");
    whoops();
    return 1;
}
adjust_bump(){
  if(last_hit==1 || last_hit==3 || last_hit==7){
    rnd=rdm;
    return 1;
  }
  if(last_hit==2 || last_hit==5 || last_hit==8){
    rnd=rdm+10;
    return 1;
  }
  rnd=rdm-10;
  return 1;
}
right_team(ob){
  nom=ob->query_name();
  if(who_serve==1 || who_serve==3){
    if(nom==service_array[1] || nom==service_array[3]){
      if(over==0){
       team_mate=1;
      return 1;
      }
      team_mate=0;
      return 1;
    }
      if(over==1){
        team_mate=1;
        return 1;
      }
    team_mate=0;
    return 1;
    }
    if(nom==service_array[2] || nom==service_array[0]){
      if(over==0){
      team_mate=1;
      return 1;
    }
      team_mate=0;
       return 1;
     }
    if(over==1){
      team_mate=1;
      return 1;
      }
    team_mate=0;
    return 1;
}
set(str){
  check_player(this_player());
  if(in_game<1){
    write("You are not in the game.\n");
    return 1;
  }
  if(in_play<1){
    write("The ball has not been served yet.\n");
    return 1;
  }
  if(!str){
    write("Set where? (fl,fr,bl,br)\n");
    return 1;
  }
  what_number(this_player());
  if(where_array[player_number]!=ball_pos){
    write("The ball is not here.\n");
    return 1;
  }
  if(block_array[player_number]==1){
    write("You cannot set while blocking.\n");
    return 1;
  }
  right_team(this_player());
  if(team_mate==0){
    write("The ball is on the other side of the net.\n");
    return 1;
  }
  if(last_touch==player_number){
    remove_call_out("no_touch");
    write("You cannot hit the ball twice in a row.\n");
    say(this_player()->query_name()+" hit the ball twice in a row.");
    whoops();
    return 1;
  }
  if(number_hits>2){
    remove_call_out("no_touch");
    write("Your side took too many hits.\n");
    say(this_player()->query_name()+"'s side took too many hits.\n");
    whoops();
    return 1;
  }
  if(str!="fl" && str!="fr" && str!="bl" && str!="br"){
    write("Please set to either fr,fl,br,bl.\n");
    return 1;
  }
  rdm=random(100);
  adjust_set();
  last_hit=4;
  number_hits=number_hits+1;
  last_touch=player_number;
  set_time();
  remove_call_out("no_touch");
  if(rnd<50){
    if(str=="fl"){
      write("You set the ball to fl.\n");
      say(this_player()->query_name()+" sets the ball to fl.\n");
      ball_pos=2;
      call_out("no_touch",real_time);
      return 1;
    }
    if(str=="fr"){
      write("You set the ball to fr.\n");
      say(this_player()->query_name()+" sets the ball to fr.\n");
      ball_pos=1;
      call_out("no_touch",real_time);
      return 1;
    }
    if(str=="br"){
      write("You set the ball to br.\n");
      say(this_player()->query_name()+" sets the ball to br.\n");
      ball_pos=3;
      call_out("no_touch",real_time);
      return 1;
    }
    write("You set the ball to bl.\n");
    say(this_player()->query_name()+" sets the ball to bl.\n");
    ball_pos=4;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rnd<60){
    write("You set the ball to fr.\n");
    say(this_player()->query_name()+" sets the ball to fr.\n");
    ball_pos=1;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rnd<70){
    write("You set the ball to fl.\n");
    say(this_player()->query_name()+" sets the ball to fl.\n");
    ball_pos=2;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rnd<80){
    write("You set the ball to br.\n");
    say(this_player()->query_name()+" sets the ball to br.\n");
    ball_pos=3;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rnd<90){
    write("You set the ball to bl.\n");
    say(this_player()->query_name()+" sets the ball to bl.\n");
    ball_pos=4;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rnd<100){
    write("You set the ball into the net.\n");
    say(this_player()->query_name()+" sets the ball into the net.\n");
    whoops();
    return 1;
  }
    write("You set the ball out of bounds.\n");
    say(this_player()->query_name()+" sets the ball out of bounds.\n");
    whoops();
    return 1;
}
adjust_set(){
  if(last_hit==1){
    rnd=rdm+30;
    return 1;
  }
  if(last_hit==2 || last_hit==5){
    rnd=rdm+40;
    return 1;
  }
  if(last_hit==3 || last_hit==6){
    rnd=rdm;
    return 1;
  }
  if(last_hit==4){
    rnd=rdm-10;
    return 1;
  }
  rnd=rdm+10;
  return 1;
}
jserve(str){
  if(play_ok<1){
    say("You can't serve until there are enough people on each team.\n");
    write("Please finish choosing teams.\n");
    return 1;
  }
  this_server=this_player()->query_name();
  ready();
  if(all_present==0){
    say("Make sure all players are present.\n");
    write("Make sure all players are present.\n");
    return 1;
  }
  if(in_play==1){
    write("You can't serve while the ball is in play.\n");
    return 1;
  }
  if(reset_call==1){
    write("You cannot do that while the game is being reset.\n");
    return 1;
  }
  if(server_ok==0){
    write("It is not your turn to serve.\n");
    return 1;
  }
  where_array=({3,3,4,4});
  if(!str){
    write("Serve where? (br,bl,fr,fl)\n");
    return 1;
  }
  if(str!="fr" && str!="fl" && str!="br" && str!="bl"){
    write("Serve the ball to br,bl,fr,fl.\n");
    return 1;
  }
  write("Players are in their starting positions.\n");
  say("Players are in their starting positions.\n");
  where_start();
  write("You jump serve the ball.\n");
  say(this_player()->query_name()+" jump serves the ball.\n");
    rdm=random(100);
    last_hit=2;
    last_touch=who_serve;
    number_hits=0;
    over=1;
    jserve_time();
  if(rdm<10){
    if(str=="br"){
      write("You jump serve the ball to br.\n");
      say(this_player()->query_name()+" jump serves the ball to br.\n");
      ball_pos=3;
      in_play=1;
      call_out("no_touch",real_time);
      return 1;
    }
    if(str=="fr"){
      write("You jump serve the ball to fr.\n");
      say(this_player()->query_name()+" jump serves the ball to fr.\n");
      ball_pos=1;
      in_play=1;
      call_out("no_touch",real_time);
      return 1;
    }
    if(str=="fl"){
      write("You jump serve the ball to fl.\n");
      say(this_player()->query_name()+" jump serves the ball to fl.\n");
      ball_pos=2;
      in_play=1;
      call_out("no_touch",real_time);
      return 1;
    }
      write("You jump serve the ball to bl.\n");
      say(this_player()->query_name()+" jump serves the ball to bl.\n");
      in_play=1;
      ball_pos=4;
      call_out("no_touch",real_time);
      return 1;
  }
  if(rdm<20){
    write("You jump serve the ball to fr.\n");
    say(this_player()->query_name()+" jump serves the ball to fr.\n");
    ball_pos=1;
    in_play=1;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rdm<30){
    write("You jump serve the ball to fl.\n");
    say(this_player()->query_name()+" jump serves the ball to fl.\n");
    ball_pos=2;
    in_play=1;
    call_out("no_touch",real_time);
    return 1;
  }
if(rdm<40){
    write("You jump serve the ball to br.\n");
    say(this_player()->query_name()+" jump serves the ball to br.\n");
    ball_pos=3;
    in_play=1;
    call_out("no_touch",real_time);
    return 1;
  }
    if(rdm<50){
    write("You jump serve the ball to bl.\n");
    say(this_player()->query_name()+" jump serves the ball to bl.\n");
    ball_pos=4;
    in_play=1;
    call_out("no_touch",real_time);
    return 1;
  }
  if(rdm<80){
    write("You jump serve the ball into the net.\n");
    say(this_player()->query_name()+" jump serves the ball into the net.\n");
    change();
    return 1;
  }
    write("You jump serve the ball out of bounds.\n");
    say(this_player()->query_name()+" jump serves the ball out of bounds.\n");
    change();
    return 1;
}
where(){
  if(play_ok<1){
    write("Wait for the game to begin.\n");
    return 1;
  }
  pos_name(ron);
  write(ro+" is at "+pos_nom+".\n");
  pos_name(rtn);
  write(rt+" is at "+pos_nom+".\n");
  pos_name(lon);
  write(lo+" is at "+pos_nom+".\n");
  pos_name(ltn);
  write(lt+" is at "+pos_nom+".\n");
  ball_pos_name();
  write("Ball is at "+pos_nom+".\n");
  which_side_other();
  return 1;
}
pos_name(ob){
  what_number(ob);
  if(where_array[player_number]==1){
    pos_nom="fr";
    return 1;
  }
  if(where_array[player_number]==2){
    pos_nom="fl";
    return 1;
  }
  if(where_array[player_number]==3){
    pos_nom="br";
    return 1;
  }
  if(where_array[player_number]==4){
    pos_nom="bl";
    return 1;
  }
  pos_nom="some other place";
  return 1;
}
spike(str){
  check_player(this_player());
  if(in_game<1){
    write("You are not in the game.\n");
    return 1;
  }
  if(in_play<1){
    write("The ball hasn't been served yet.\n");
    return 1;
  }
  if(!str){
    write("Spike where? (fr,fl,br,fl)\n");
    return 1;
  }
  what_number(this_player());
  if(where_array[player_number]!=ball_pos){
    write("The ball is not here.\n");
    return 1;
  }
  if(block_array[player_number]==1){
    write("You cannot spike while blocking.\n");
    return 1;
  }
  right_team(this_player());
  if(team_mate==0){
    write("The ball is on the other side of the net.\n");
    return 1;
  }
  if(last_touch==player_number){
    remove_call_out("no_touch");
    write("You cannot hit the ball twice in a row.\n");
    say(this_player()->query_name()+" hit the ball twice in a row.\n");
    whoops();
    return 1;
  }
  if(number_hits>2){
    remove_call_out("no_touch");
    write("Your side took too many hits.\n");
    say(this_player()->query_name()+"'s side took too many hits.\n");
    whoops();
    return 1;
  }
  if(str!="fr" && str!="fl" && str!="br" && str!="bl"){
    write("Please spike to either fr,fl,br,bl.\n");
    return 1;
  }
  rdm=random(100);
  adjust_spike();
  last_hit=5;
  from_pos=ball_pos;
  number_hits=number_hits+1;
  last_touch=player_number;
  spike_time();
  remove_call_out("no_touch");
  if(rnd<40){
    if(str=="fr"){
      write("You spike the ball to fr.\n");
      say(this_player()->query_name()+" spikes the ball to fr.\n");
      over_net();
      ball_pos=1;
      call_out("no_touch",real_time);
      check_block();
      real_block=({0,0,0,0});
      return 1;
    }
    if(str=="fl"){
      write("You spike the ball to fl.\n");
      say(this_player()->query_name()+" spikes the ball to fl.\n");
      over_net();
      ball_pos=2;
      call_out("no_touch",real_time);
      check_block();
      real_block=({0,0,0,0});
      return 1;
    }
    if(str=="br"){
      write("You spike the ball to br.\n");
      say(this_player()->query_name()+" spikes the ball to br.\n");
      over_net();
      ball_pos=3;
      call_out("no_touch",real_time);
      check_block();
      real_block=({0,0,0,0});
      return 1;
    }
      write("You spike the ball to bl.\n");
      say(this_player()->query_name()+" spikes the ball to bl.\n");
      over_net();
      ball_pos=4;
      call_out("no_touch",real_time);
      check_block();
      real_block=({0,0,0,0});
      return 1;
  }
  if(rnd<50){
    write("You spike the ball to fr.\n");
    say(this_player()->query_name()+" spikes the ball to fr.\n");
    over_net();
    ball_pos=1;
    call_out("no_touch",real_time);
    check_block();
    real_block=({0,0,0,0});
    return 1;
  }
  if(rnd<60){
    write("You spike the ball to fl.\n");
    say(this_player()->query_name()+" spikes the ball to fl.\n");
    over_net();
    ball_pos=2;
    call_out("no_touch",real_time);
    check_block();
    real_block=({0,0,0,0});
    return 1;
  }
  if(rnd<70){
    write("You spike the ball to br.\n");
    say(this_player()->query_name()+" spikes the ball to br.\n");
    over_net();
    ball_pos=3;
    call_out("no_touch",real_time);
    check_block();
    real_block=({0,0,0,0});
    return 1;
  }
  if(rnd<80){
    write("You spike the ball to bl.\n");
    say(this_player()->query_name()+" spikes the ball to bl.\n");
    over_net();
    ball_pos=4;
    call_out("no_touch",real_time);
    check_block();
    real_block=({0,0,0,0});
    return 1;
  }
  if(rnd<90){
    write("You spike the ball out of bounds.\n");
    say(this_player()->query_name()+" spikes the ball out of bounds.\n");
    whoops();
    return 1;
  }
    write("You spike the ball into the net.\n");
    say(this_player()->query_name()+" spikes the ball into the net.\n");
    whoops();
    return 1;
}
adjust_spike(){
  if(last_hit==1){
    rnd=rdm+60;
    adjust_spike_more();
    return 1;
  }
  if(last_hit==2 || last_hit==5){
    rnd=rdm+80;
    adjust_spike_more();
    return 1;
  }
  if(last_hit==3 || last_hit==7){
  rnd=rdm+20;
  adjust_spike_more();
    return 1;
  }
  if(last_hit==4 || last_hit==6){
    rnd=rdm;
    adjust_spike_more();
    return 1;
  }
    rnd=rdm+40;
    adjust_spike_more();
    return 1;
}
adjust_spike_more(){
 if(ball_pos==3 || ball_pos==4){
    rnd=rnd+20;
    return 1;
  }
  return 1;
}
over_net(){
  write("The ball goes over the net.\n");
  say("The ball goes over the net.\n");
  number_hits=0;
  if(over==1){
    over=0;
    which_side();
    return 1;
  }
  over=1;
  which_side();
  return 1;
}
no_touch(){
  say("The ball hits the ground.\n");
  write("The ball hits the ground.\n");
  whoops();
  return 1;
}
whoops(){
  in_play=0;
  ball_pos=5;
  block_remove();
  if(over==1){
    if(who_serve==1 || who_serve==3){
      lscore=lscore+1;
      say("The left team gets a point.\n");
      write("The left team gets a point.\n");
      score();
      check_end();
      if(start_game==0) return 1;
      write("It is still "+service_array[who_serve]+"'s turn to serve.\n");
      say("It is still "+service_array[who_serve]+"'s turn to serve.\n");
      over=2;
      return 1;
    }
      rscore=rscore+1;
      say("The right team gets a point.\n");
      write("The right team gets a point.\n");
      score();
      check_end();
      if(start_game==0) return 1;
      write("It is still "+service_array[who_serve]+"'s turn to serve.\n");
      say("It is still "+service_array[who_serve]+"'s turn to serve.\n");
      over=2;
      return 1;
  }
  change();
  return 1;
}
change(){
  in_play=0;
  ball_pos=5;
  over=2;
  if(who_serve<3){
    who_serve=who_serve+1;
    write("It is now "+service_array[who_serve]+"'s turn to serve.\n");
    say("It is now "+service_array[who_serve]+"'s turn to serve.\n");
    score();
    return 1;
  }
    who_serve=0;
  write("It is now "+service_array[who_serve]+"'s turn to serve.\n");
    say("It is now "+service_array[who_serve]+"'s turn to serve.\n");
    score();
    return 1;
}
score(){
  write("Right side: "+rscore+"      Left side: "+lscore+"\n");
  say("Right side: "+rscore+"      Left side: "+lscore+"\n");
  return 1;
}
where_start(){
  pos_name(ron);
  write(ro+" is at "+pos_nom+".\n");
  say(ro+" is at "+pos_nom+".\n");
  pos_name(rtn);
  write(rt+" is at "+pos_nom+".\n");
  say(rt+" is at "+pos_nom+".\n");
  pos_name(lon);
  write(lo+" is at "+pos_nom+".\n");
  say(lo+" is at "+pos_nom+".\n");
  pos_name(ltn);
  write(lt+" is at "+pos_nom+".\n");
  say(lt+" is at "+pos_nom+".\n");
  write("********************\n");
  say("********************\n");
  return 1;
}
ball_pos_name(){
  if(ball_pos==1){
    pos_nom="fr";
    return 1;
  }
  if(ball_pos==2){
    pos_nom="fl";
    return 1;
  }
  if(ball_pos==3){
    pos_nom="br";
    return 1;
  }
  if(ball_pos==4){
    pos_nom="bl";
    return 1;
  }
    pos_nom="some other place (at the server's feet)";
    return 1;
}
hit(str){
  check_player(this_player());
  if(in_game<1){
    write("You are not in the game.\n");
    return 1;
  }
  if(in_play<1){
    write("The ball hasn't been served yet.\n");
    return 1;
  }
  if(!str){
    write("Hit where? (fr,fl,br,bl)\n");
    return 1;
  }
  what_number(this_player());
  if(where_array[player_number]!=ball_pos){
    write("The ball is not here.\n");
    return 1;
  }
  if(block_array[player_number]==1){
    write("You cannot hit while blocking.\n");
    return 1;
  }
  right_team(this_player());
  if(team_mate==0){
    write("The ball is on the other side of the net.\n");
    return 1;
  }
  if(last_touch==player_number){
    remove_call_out("no_touch");
    write("You cannot hit the ball twice in a row.\n");
    say(this_player()->query_name()+" hit the ball twice in a row.\n");
    whoops();
    return 1;
  }
  if(number_hits>2){
    remove_call_out("no_touch");
    write("Your side took too many hits.\n");
    say(this_player()->query_name()+"'s side took too many hits.\n");
    whoops();
    return 1;
   }
  if(str!="fr" && str!="fl" && str!="br" && str!="bl"){
     write("Please hit to either fr,fl,br,bl.\n");
    return 1;
  }
  rdm=random(100);
  adjust_hit();
  last_hit=7;
  from_pos=ball_pos;
  number_hits=number_hits+1;
  last_touch=player_number;
  hit_time();
  remove_call_out("no_touch");
  if(rnd<40){
    if(str=="fr"){
      write("You hit the ball to fr.\n");
      say(this_player()->query_name()+" hits the ball to fr.\n");
      over_net();
      ball_pos=1;
      call_out("no_touch",real_time);
      check_block();
      real_block=({0,0,0,0});
      return 1;
    }
    if(str=="fl"){
      write("You hit the ball to fl.\n");
      say(this_player()->query_name()+" hits the ball to fl.\n");
      over_net();
      ball_pos=2;
      call_out("no_touch",real_time);
      check_block();
      real_block=({0,0,0,0});
      return 1;
    }
    if(str=="br"){
      write("You hit the ball to br.\n");
      say(this_player()->query_name()+" hits the ball to br.\n");
      over_net();
      ball_pos=3;
      call_out("no_touch",real_time);
      check_block();
      real_block=({0,0,0,0});
      return 1;
    }
      write("You hit the ball to bl.\n");
      say(this_player()->query_name()+" hits the ball to bl.\n");
      over_net();
      ball_pos=4;
      call_out("no_touch",real_time);
      check_block();
      real_block=({0,0,0,0});
      return 1;
  }
  if(rnd<50){
      write("You hit the ball to fr.\n");
      say(this_player()->query_name()+" hits the ball to fr.\n");
      over_net();
      ball_pos=1;
      call_out("no_touch",real_time);
      check_block();
      real_block=({0,0,0,0});
      return 1;
  }
  if(rnd<60){
    write("You hit the ball to fl.\n");
    say(this_player()->query_name()+" hits the ball to fl.\n");
    over_net();
    ball_pos=2;
    call_out("no_touch",real_time);
    check_block();
    real_block=({0,0,0,0});
    return 1;
  }
  if(rnd<70){
    write("You hit the ball to br.\n");
    say(this_player()->query_name()+" hits the ball to br.\n");
    over_net();
    ball_pos=3;
    call_out("no_touch",real_time);
    check_block();
    real_block=({0,0,0,0});
    return 1;
  }
  if(rnd<80){
    write("You hit the ball to bl.\n");
    say(this_player()->query_name()+" hits the ball to bl.\n");
    over_net();
    ball_pos=4;
    call_out("no_touch",real_time);
    check_block();
    real_block=({0,0,0,0});
    return 1;
  }
  if(rnd<90){
    write("You hit the ball into the net.\n");
    say(this_player()->query_name()+" hits the ball into the net.\n");
    whoops();
    return 1;
  }
    write("You hit the ball out of bounds.\n");
    say(this_player()->query_name()+" hits the ball out of bounds.\n");
    whoops();
    return 1;
}
adjust_hit(){
  if(last_hit==2 || last_hit==5){
    rnd=rdm+30;
    return 1;
  }
  if(last_hit==4 || last_hit==6){
    rnd=rdm;
    return 1;
  }
    rnd=rdm+10;
    return 1;
}
block(){
  check_player(this_player());
  if(in_game<1){
    write("You are not in the game.\n");
    return 1;
  }
  if(in_play<1){
    write("The ball has not been served yet.\n");
    return 1;
  }
  right_team(this_player());
  if(team_mate==1){
    write("The ball is on your side of the net.\n");
    return 1;
  }
  what_number(this_player());
  if(block_array[player_number]==1){
    write("You are already attempting a block.\n");
    return 1;
  }
  if(where_array[player_number]==3 || where_array[player_number]==4){
    write("You cannot block from the back row.\n");
    return 1;
  }
  block_array[player_number]=1;
  real_block[player_number]=1;
  who_blocking=add_array(who_blocking,player_number);
  call_out("end_blocking",8,this_player());
  if(where_array[player_number]==1){
    write("You are attempting to block the ball at fr.\n");
    say(this_player()->query_name()+" is attempting to block at fr.\n");
    return 1;
  }
    write("You are attempting to block the ball at fl.\n");
    say(this_player()->query_name()+" is attempting to block at fl.\n");
    return 1;
}
check_block(){
  if(member_array(1,block_array)<0){
    return 1;
  }
  first_blocker=member_array(1,real_block);
  blocking_array=real_block;
  blocking_array[first_blocker]=0;
  second_blocker=member_array(1,blocking_array);
  pos_blockers();
  if(last_hit==5){
    block_spike();
    return 1;
  }
  if(last_hit==6){
    block_dink();
    return 1;
  }
  if(last_hit==7){
    block_hit();
    return 1;
  }
    return 1;
}
pos_blockers(){
  n_block_fr=0;
  n_block_fl=0;
  if(where_array[first_blocker]==1){
    if(second_blocker<0){
      n_block_fr=1;
      return 1;
    }
    if(where_array[second_blocker]==1){
      n_block_fr=2;
      return 1;
    }
      n_block_fr=1;
      n_block_fl=1;
      return 1;
  }
  if(member_array(1,blocking_array)<1){
    n_block_fl=1;
    return 1;
  }
  if(where_array[second_blocker]==2){
      n_block_fl=2;
      return 1;
    }
      n_block_fr=1;
      n_block_fl=1;
      return 1;
}
block_hit(){
  rnd=random(100);
  if(from_pos==1){
    block_here=n_block_fr;
    block_there=n_block_fl;
    if(ball_pos==1){
      hit_block_same();
      return 1;
    }
    if(ball_pos==2){
      hit_block_front_diagnol();
      return 1;
    }
    if(ball_pos=3){
      hit_block_behind();
      return 1;
    }
      hit_block_back_diagnol();
      return 1;
  }
  if(from_pos==2){
    block_here=n_block_fl;
    block_there=n_block_fr;
    if(ball_pos==2){
      hit_block_same();
      return 1;
    }
    if(ball_pos==1){
      hit_block_front_diagnol();
      return 1;
    }
    if(ball_pos==4){
      hit_block_behind();
      return 1;
    }
      hit_block_back_diagnol();
      return 1;
  }
  if(ball_pos==1){
    block_here=n_block_fr;
    hit_block_behind();
    return 1;
  }
  if(ball_pos==2){
    block_here=n_block_fl;
    hit_block_behind();
    return 1;
  }
  return 1;
}
hit_block_same(){
      if(block_here==1){
        if(rnd<45){
          block_back();
          return 1;
        }
        if(rnd<60){
          off_block();
          return 1;
        }
        if(rnd<90){
          no_block();
          return 1;
        }
          off_block_ob();
          return 1;
      }
      if(block_here==2){
          if(rnd<65){
          block_back();
          return 1;
        }
        if(rnd<75){
          off_block();
          return 1;
        }
         if(rnd<95){
          no_block();
          return 1;
        }
          off_block_ob();
          return 1;
        }
       return 1;
}
hit_block_behind(){
  if(block_here==1){
      if(rnd<30){
      block_back();
       return 1;
     }
     if(rnd<35){
      off_block();
      return 1;
    }
    if(rnd<95){
      no_block();
      return 1;
    }
      off_block_ob();
      return 1;
  }
  if(block_here==2){
    if(rnd<35){
      block_back();
      return 1;
    }
    if(rnd<50){
       off_block();
      return 1;
    }
    if(rnd<90){
    no_block();
      return 1;
    }
      off_block_ob();
       return 1;
   }
    return 1;
}
hit_block_back_diagnol(){
  if(block_here==1){
    if(rnd<15){
      block_back();
      return 1;
    }
     if(rnd<20){
      off_block();
      return 1;
    }
    if(rnd<95){
      no_block();
      return 1;
    }
      off_block_ob();
      return 1;
  }
  if(block_here==2){
    if(rnd<30){
      block_back();
      return 1;
    }
    if(rnd<40){
      off_block();
      return 1;
    }
    if(rnd<95){
      no_block();
      return 1;
    }
      off_block_ob();
      return 1;
  }
    return 1;
}
hit_block_front_diagnol(){
  if(block_here==2){
    if(rnd<40){
       block_back();
      return 1;
    }
    if(rnd<55){
      off_block();
      return 1;
    }
    if(rnd<60){
       off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  if(block_here==1){
    if(block_there==1){
      if(rnd<45){
        block_back();
        return 1;
      }
      if(rnd<65){
         off_block();
         return 1;
      }
      if(rnd<70){
        off_block_ob();
        return 1;
      }
        no_block();
        return 1;
    }
      if(rnd<30){
        block_back();
        return 1;
      }
      if(rnd<45){
        off_block();
        return 1;
      }
      if(rnd<55){
        off_block_ob();
        return 1;
      }
        no_block();
        return 1;
  }
  if(block_there==2){
    if(rnd<35){
      block_back();
      return 1;
     }
    if(rnd<50){
       off_block();
      return 1;
     }
    if(rnd<55){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
    }
  if(rnd<20){
    block_back();
    return 1;
  }
  if(rnd<30){
    off_block();
    return 1;
  }
  if(rnd<40){
    off_block_ob();
    return 1;
  }
    no_block();
  return 1;
}
no_block(){
  write("The ball goes by the block.\n");
  say("The ball goes by the block.\n");
  return 1;
}
off_block_ob(){
  write("The ball is blocked!!!\n");
  say("The ball is blocked!!!\n");
  remove_call_out("no_touch");
     write("The blocked ball goes out of bounds.\n");
    say("The blocked ball goes out of bounds.\n");
    whoops();
    return 1;
}
off_block(){
  write("The ball has been deflected by the block.\n");
  say("The ball has been deflected by the block.\n");
  remove_call_out("no_touch");
  call_out("no_touch",real_time);
  rnd=random(4);
  last_hit=8;
  if(rnd==0){
    write("The ball is now heading for fr.\n");
     say("The ball is now headed for fr.\n");
    ball_pos=1;
    return 1;
  }
  if(rnd==1){
    write("The ball is now heading for fl.\n");
    say("The ball is now heading for fl.\n");
    ball_pos=2;
    return 1;
  }
  if(rnd==2){
    write("The ball is now heading for br.\n");
    say("The ball is now heading for br.\n");
    ball_pos=3;
    return 1;
  }
     write("The ball is now heading for bl.\n");
    say("The ball is now heading for bl.\n");
    ball_pos=4;
    return 1;
}
block_spike(){
  rnd=random(100);
  if(from_pos==1){
  block_here=n_block_fr;
  block_there=n_block_fl;
  if(ball_pos==1){
      spike_block_same();
      return 1;
  }
  if(ball_pos==2){
      spike_block_front_diagnol();
      return 1;
    }
    if(ball_pos==3){
      spike_block_behind();
      return 1;
    }
      spike_block_back_diagnol();
      return 1;
  }
  if(from_pos==2){
    if(ball_pos==1){
      spike_block_front_diagnol();
      return 1;
    }
    if(ball_pos==2){
      spike_block_same();
      return 1;
    }
    if(ball_pos==3){
      spike_block_back_diagnol();
      return 1;
    }
      spike_block_behind();
      return 1;
  }
  if(from_pos==3){
    if(ball_pos==1){
      spike_back_block_same();
      return 1;
    }
    if(ball_pos==2){
      spike_back_block_opposite();
      return 1;
    }
    if(ball_pos==3){
      spike_back_block_behind();
      return 1;
    }
      spike_back_block_back_diagnol();
      return 1;
  }
  if(ball_pos==1){
    spike_back_block_opposite();
    return 1;
  }
  if(ball_pos==2){
    spike_back_block_same();
    return 1;
  }
  if(ball_pos==3){
    spike_back_block_back_diagnol();
    return 1;
  }
    spike_back_block_behind();
    return 1;
}
spike_block_same(){
  if(block_here==1){
    if(rnd<45){
      block_back();
      return 1;
    }
    if(rnd<65){
      off_block();
      return 1;
    }
    if(rnd<85){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  if(block_here==2){
  if(rnd<60){
    block_back();
    return 1;
  }
  if(rnd<75){
    off_block();
    return 1;
  }
  if(rnd<90){
    off_block_ob();
    return 1;
  }
    no_block();
    return 1;
}
return 1;
}
spike_block_behind(){
  if(block_here==1){
    if(rnd<30){
      block_back();
      return 1;
    }
    if(rnd<50){
      off_block();
      return 1;
    }
    if(rnd<75){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
   }
  if(block_here==2){
  if(rnd<45){
    block_back();
    return 1;
  }
  if(rnd<65){
    off_block();
    return 1;
  }
  if(rnd<85){
    off_block_ob();
    return 1;
  }
    no_block();
    return 1;
}
return 1;
}
spike_block_back_diagnol(){
  if(block_here==1){
    if(rnd<25){
      block_back();
      return 1;
    }
    if(rnd<45){
      off_block();
      return 1;
    }
    if(rnd<60){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  if(block_here==2){
    if(rnd<40){
      block_back();
      return 1;
    }
    if(rnd<60){
      off_block();
      return 1;
    }
    if(rnd<75){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
    return 1;
}
spike_block_front_diagnol(){
  if(block_here==2){
    if(rnd<50){
      block_back();
      return 1;
    }
    if(rnd<70){
      off_block();
      return 1;
    }
     if(rnd<80){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  if(block_here==1){
    if(block_there==1){
      if(rnd<60){
        block_back();
        return 1;
      }
      if(rnd<75){
        off_block();
        return 1;
      }
      if(rnd<85){
        off_block_ob();
        return 1;
      }
        no_block();
        return 1;
    }
    if(rnd<30){
      block_back();
      return 1;
    }
    if(rnd<50){
      off_block();
      return 1;
    }
    if(rnd<70){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  if(block_there==2){
    if(rnd<45){
      block_back();
       return 1;
    }
      if(rnd<60){
      off_block();
      return 1;
    }
    if(rnd<80){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  if(rnd<30){
    block_back();
    return 1;
  }
  if(rnd<50){
    off_block();
    return 1;
  }
  if(rnd<70){
    off_block_ob();
    return 1;
  }
    no_block();
    return 1;
}
spike_back_block_same(){
  if(block_here==1){
    if(rnd<45){
      block_back();
      return 1;
    }
    if(rnd<70){
      off_block();
      return 1;
    }
    if(rnd<80){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  if(block_here==2){
    if(rnd<70){
      block_back();
      return 1;
    }
    if(rnd<85){
      off_block();
      return 1;
    }
    if(rnd<90){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  return 1;
}
spike_back_block_behind(){
  if(block_here==1){
    if(rnd<40){
      block_back();
      return 1;
    }
    if(rnd<60){
      off_block();
      return 1;
    }
    if(rnd<80){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  if(block_here==2){
    if(rnd<60){
      block_back();
      return 1;
    }
    if(rnd<75){
      off_block();
      return 1;
    }
    if(rnd<90){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  return 1;
}
spike_back_block_opposite(){
  if(block_there==1){
    if(rnd<60){
      block_back();
      return 1;
    }
    if(rnd<70){
      off_block();
       return 1;
    }
    if(rnd<75){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  if(block_there==2){
    if(rnd<70){
      block_back();
      return 1;
    }
    if(rnd<80){
      off_block();
      return 1;
    }
    if(rnd<85){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  return 1;
}
spike_back_block_back_diagnol(){
  if(block_here==2){
    if(rnd<35){
      block_back();
      off_block();
     }
    if(rnd<55){
      off_block();
      return 1;
    }
    if(rnd<65){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  if(block_here==1){
    if(block_there==1){
      if(rnd<40){
        block_back();
        return 1;
      }
      if(rnd<60){
        off_block();
        return 1;
      }
      if(rnd<70){
        off_block_ob();
        return 1;
      }
        no_block();
        return 1;
    }
    if(rnd<25){
      block_back();
      return 1;
    }
    if(rnd<45){
      off_block();
      return 1;
    }
    if(rnd<65){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
  if(block_there==2){
    if(rnd<35){
      block_back();
      return 1;
    }
    if(rnd<55){
      off_block();
      return 1;
    }
    if(rnd<65){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
  }
    if(rnd<25){
      block_back();
      return 1;
    }
    if(rnd<45){
      off_block();
      return 1;
    }
    if(rnd<65){
      off_block_ob();
      return 1;
    }
      no_block();
      return 1;
}
block_back(){
  write("The ball is blocked!!!\n");
  say("The ball is blocked!!!\n");
  remove_call_out("no_touch");
  call_out("no_touch",real_time);
  last_hit=8;
  last_touch=5;
  rnd=random(4);
  if(rnd==0){
    write("The ball is blocked to fr.\n");
    say("The ball is blocked to fr.\n");
    ball_pos=1;
    over_net();
    return 1;
  }
  if(rnd==1){
    write("The ball is blocked to fl.\n");
    say("The ball is blocked to fl.\n");
    ball_pos=2;
    over_net();
    return 1;
  }
  if(rnd==2){
    write("The ball is blocked to br.\n");
    say("The ball is blocked to br.\n");
    ball_pos=3;
    over_net();
    return 1;
  }
    write("The ball is blocked to bl.\n");
    say("The ball is blocked to bl.\n");
    ball_pos=4;
    over_net();
    return 1;
}
which_side(){
  if(over==2){
    write("The ball is not in play.\n");
    say("The ball is not in play.\n");
  }
  if(who_serve==0 || who_serve==2){
    if(over==1){
      write("The ball is on the LEFT TEAM'S side.\n");
      say("The ball is on the LEFT TEAM'S side.\n");
      return 1;
    }
      write("The ball is on the RIGHT TEAM'S side.\n");
      say("The ball is on the RIGHT TEAM'S side.\n");
      return 1;
  }
    if(over==1){
      write("The ball is on the RIGHT TEAM'S side.\n");
      say("The ball is on the RIGHT TEAM'S side.\n");
      return 1;
  }
    write("The ball is on the LEFT TEAM'S side.\n");
    say("The ball is on the LEFT TEAM'S side.\n");
    return 1;
}
end_blocking(ob){
  this_blocker=who_blocking[0];
  block_array[this_blocker]=0;
  real_block[this_blocker]=0;
  who_blocking=exclude_array(who_blocking,0);
  write("You stop blocking.\n");
  say(ob->query_name()+" stops blocking.\n");
  return 1;
}
block_remove(){
  if(!sizeof(who_blocking)){
    return 1;
  }
  remove_call_out("end_blocking");
  this_blocker=who_blocking[0];
  block_array[this_blocker]=0;
  real_block[this_blocker]=0;
  who_blocking=exclude_array(who_blocking,0);
  block_remove();
  return 1;
}
commands(){
  write("Commands for movement:\n");
  write("        fr , fl , br , bl\n");
  write("\n");
  write("Commands for serving:\n");
  write("         serve <aim> , jserve <aim>\n");
  write("\n");
  write("Commands for hitting ball:\n");
  write("  To keep ball on own side:\n");
  write("          bump <aim> , set <aim>\n");
  write("\n");
  write("  To hit the ball over the net:\n");
  write("           spike <aim> , hit <aim>\n");
  write("\n");
  write("Defensive commands:\n");
  write("           block\n");
  write("\n");
  write("General purpose commands:\n");
  write("           type 'general' for a detailed list\n");
  return 1;
}
show_score(){
  write("RIGHT TEAM : "+rscore+"      LEFT TEAM : "+lscore+"\n");
  return 1;
}
check_end(){
  if(rscore<15 && lscore<15){
    return 1;
  }
  if(rscore>14){
    if(lscore<14){
    end_game();
    return 1;
    }
       if((rscore - lscore)>1){
    end_game();
    return 1;
    }
    return 1;
  }
  if(rscore<14){
    end_game();
    return 1;
  }
  if((lscore - rscore)>1){
    end_game();
    return 1;
  }
  return 1;
}
end_game(){
  start_game=0;
  play_ok=0;
  if(rscore>lscore){
  write("The RIGHT TEAM wins!!!!\n");
    say("The RIGHT TEAM wins!!!!\n");
    return 1;
  }
  write("The LEFT TEAM wins!!!!\n");
    say("The LEFT TEAM wins!!!!\n");
  return 1;
}
players(){
  write("Left Team");
  for(i=0;i<36;i++) write(" ");
  write("Right Team\n");
  write(lo);
  for(i=0;i<(45-strlen(lo));i++) write(" ");
  write(ro+"\n");
  write(lt);
  for(i=0;i<(45-strlen(lt));i++) write(" ");
  write(rt+"\n");
  return 1;
}
endgame_check(){
  if(start_game!=1){
    write("There is no game to reset.\n");
    return 1;
  }
  if(!present(lon,this_object()) && !present(ltn,this_object()) &&
     !present(ron,this_object()) && !present(rtn,this_object())){
      write("Game is reset.\n");
      say("Game is reset.\n");
      reset_me_baby();
      return 1;
  }
  if(in_play==1){
    write("You cannot reset the game in the middle of action!\n");
    return 1;
  }
  write("You call for a reset of the game.\n"+
  "To stop the call for a reset type 'stopend'.\n");
  say(this_player()->query_name()+" calls for a game reset to begin.\n"+
    "To stop the call for the game reset type 'stopend'.\n");
  reset_call=1;
  call_out("reset_warning1",5);
  return 1;
}
reset_warning1(){
  write("60 seconds until game is reset.\n"+
    "To stop reset type 'stopend'.\n");
  say("60 seconds until game is reset.\n"+
    "To stop reset type 'stopend'.\n");
  call_out("reset_warning2",15);
  return 1;
}
reset_warning2(){
   write("30 seconds until game is reset.\n"+
    "To stop reset type 'stopend'.\n");
  say("30 seconds until game is reset.\n"+
    "To stop reset type 'stopend'.\n");
  call_out("reset_warning3",10);
  return 1;
}
reset_warning3(){
  write("10 seconds until game is reset.\n"+
    "To stop reset type 'stopend'.\n");
  say("10 seconds until game is reset.\n"+
    "To stop reset type 'stopend'.\n");
  call_out("reset_me_baby",5);
  return 1;
}
reset_me_baby(){
  all_present=0;
  start_game=0;
  lscore=0;
  rscore=0;
  play_ok=0;
  ro="-";
  rt="-";
  lo="-";
  lt="-";
  reset_call=0;
  start();
  return 1;
}
stopend(){
  if(reset_call==0){
    write("There is no game reset in progress.\n");
    return 1;
  }
  write("You stop the reset.\n");
  say(this_player()->query_name()+" stops the reset.\n");
  reset_call=0;
  if(find_call_out("reset_warning1")) remove_call_out("reset_warning1");
  if(find_call_out("reset_warning2")) remove_call_out("reset_warning2");
  if(find_call_out("reset_warning3")) remove_call_out("reset_warning3");
  if(find_call_out("reset_me_baby")) remove_call_out("reset_me_baby");
  return 1;
}
difficulty(str){
  if(in_play==1){
    write("You cannot change difficulty levels in the middle of a game.\n");
    return 1;
  }
  if(!str){
    write("Difficulty ratings are as follows:\n"+
      "\t\t1 : Beginner\n\t\t2 : Intermediate\n\t\t3 : Advanced\n"+
    "Input 'difficulty #'\n");
  if(diff_level==1){
    write("Difficulty is set to Advanced.\n");
    return 1;
  }
  if(diff_level==2){
    write("Difficulty is set to Intermediate.\n");
    return 1;
  }
  write("Difficulty is set to Beginner.\n");
    return 1;
  }
  if(str!="1" && str!="2" && str!="3"){
    write("Difficulty levels are 1, 2, or 3.\n");
    return 1;
  }
  if(str=="1"){
    write("You set the difficulty level to Beginner.\n");
    say(this_player()->query_name()+
      " sets the difficulty level to Beginner.\n");
    diff_level=3;
     return 1;
  }
  if(str=="2"){
    write("You set the difficulty level to Intermediate.\n");
    say(this_player()->query_name()+
      " sets the difficulty level to Intermediate.\n");
    diff_level=2;
    return 1;
  }
  write("You set the difficulty level to Advanced.\n");
  say(this_player()->query_name()+
    " sets the difficulty level to Advanced.\n");
  diff_level=1;
  return 1;
}
serve_time(){
  real_time= (diff_level*2)+6;
  return 1;
}
jserve_time(){
  real_time= (diff_level*2)+4;
  return 1;
}
spike_time(){
  real_time=(diff_level*2)+4;
  return 1;
}
hit_time(){
  real_time=(diff_level*4)+4;
  return 1;
}
bump_time(){
  real_time=(diff_level*4)+4;
  return 1;
}
set_time(){
  if(diff_level==1){
    real_time=10;
    return 1;
  }
  if(diff_level==2){
    real_time=14;
    return 1;
  }
  real_time=20;
  return 1;
}
who_is_serving(){
  if(play_ok<1){
    write("Game is not in progress.\n");
    return 1;
  }
  write("It is "+service_array[who_serve]+"'s turn to serve.\n");
  return 1;
}
block_time(){
  if(diff_level==1){
    real_time=(rnd(4)+1)*2+2;
    return 1;
  }
  if(diff_level==2){
    real_time=(rnd(3)+1)*2+6;
    return 1;
  }
  real_time=(rnd(5)+1)*2+8;
  return 1;
}
general_stuff(){
write("General Purpose Commands:\n");
write("\tcommands\tlists important game commands\n");
write("\twhere\t\tshows player and ball positions\n");
write("\tscore\t\tshows score\n");
write("\tendgame\t\tto end current game\n");
write("\tstopend\t\tto end game reset sequence\n");
write("\tplayers\t\tshows who is in the game and on what team\n");
write("\temote\t\temotion command\n");
write("\twhoserve\tshows current server\n");
write("\tdifficulty\tchanges difficulty of the game\n");
write("\tstarting\tgives a little help on starting the game\n");
return 1;
}
read(str){
  notify_fail("Read what?\n");
  if(str=="sign"){
write("Rules of the game:\n"+
"    The game is played on a 2x2 grid on each side of the net.\n"+
"You move around by moving to the corners and typing fr, fl, br, bl.\n"+
"(Front Right, Back Left, etc) To hit the ball you type the command\n"+
"followed by where you want to aim (spike fr , bump bl , etc).\n"+
"You will not always hit the ball where you are aiming. When a ball is hit,\n"+
"there will be an unknown time for the players to move and react before\n"+
"the ball hits the ground.\n"+
"    You can only block when standing in the front row (fr or fl).\n"+
"And when you do so, you remain in the air attempting to block for a short\n"+
"time during which you cannot move or hit the ball.\n\n"+
"For more information type 'commands'.\n");
  return 1;
  }
return 0;
}
help_starting(){
  write("Help for starting the game:\n"+
" 1) start --  Type this game when a game has just been played to reset\n"+
"\t\t\ta few variables. It will also tell others in\n"+
"\t\t\tthe same room to choose teams.\n"+
"\n"+
" 2) choose <r or l>  --  This command lets you pick what team\n"+
"\t\t\tyou want to play on. Either the r team or the l team.\n"+
"\n"+
" 3) play  --  Once everyone has picked a team and there are 2 people on\n"+
"\t\t\teach side, 'play' will let you get on with the game.\n"+
"\n"+
"  You are now ready to play the game. The server will be decided randomly.\n"+
"Make sure you know the rules and commands before serving. A little\n"+
"practice may help a lot (Just start a game and 'endgame' when ready for\n"+
"the real one.\n");
  return 1;
}
which_side_other(){
  if(over==2){
    write("The ball is not in play.\n");
    return 1;
  }
  if(who_serve==0 || who_serve==2){
    if(over==1){
      write("The ball is on the LEFT TEAM'S side.\n");
      return 1;
    }
      write("The ball is on the RIGHT TEAM'S side.\n");
      return 1;
  }
      if(over==1){
      write("The ball is on the RIGHT TEAM'S side.\n");
      return 1;
  }
    write("The ball is on the LEFT TEAM'S side.\n");
  return 1;
}
query_peace(){return 1; }
