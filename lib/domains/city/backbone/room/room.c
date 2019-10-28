#pragma strict_types

#define NIGHT_CODE
#define DGD_LIB
#include <newroom.h>
#include <free_kill.h>
 
#include <time.h>

/* Variables.. */
 mixed room_type;
 string   short_desc;
 string   long_desc;
 string   long_func;
 string  *hide_obvious;
 mixed   *chats;
 mixed    property;
 mixed    dest_dir;
 mixed    items;
 mixed   *action_desc; /* ({ ({verb, stris, desc}) }) */
 mixed    sounds;
 mixed    smells;
 string   smell_desc;
 string   sound_desc;
 int 	  light;
 int     planted;
 int     arable;
 int      skip_obvious;
 int  no_boost;
 int      outdoors;
 int      no_clean_up;
 int      ffz;
 int      ok_to_dig;
 int      conditional_lighting;
 int      free_kill_flag;
 object  *affect_objects;
 mapping  Messages;
 mapping  t_obj;
 mapping  objects;
 mixed *  uniques;
 mapping luniques;
 mapping  local_help;
 mapping   readable;

/* Prototypes.. */
int             Enter_room(int brief);
int             check_dir(int num);
int             test_if_any_here();
int             dark(int silent);
int             query_light();
int             do_smell_listen(mixed arr, string str, string verb, string sayverb);


varargs void add_time_object(string fname, int num);
void do_time_obj();

void set_no_boost(int i){ no_boost = i; }
int query_no_boost(){ return no_boost; }

int
id(string str)
{
  if (!items)
    return 0;
  if (!mappingp(items))
    items = FIX_ITEMS(0, items);
  
  if (!items[str])
    return 0;
  return 1;
}

string
real_short(){ return short_desc; }

string
short()
{
  if(dark(1))
    return "Darkness";
  if(!short_desc)
    return "A Room";
  return short_desc;
}

void
long(string str)
{
    string          func;
    int             end;
    
    if (!mappingp(dest_dir))
      dest_dir = FIX_DEST_DIR(0, dest_dir);
    
    if (!str)
    {
      if( stringp(long_desc) )
        write(process_string(long_desc));
      GENERATE_LONG(long_desc, long_func, dest_dir,
		    affect_objects, skip_obvious, hide_obvious);
      return;
    }
    if(dark(0))
      return;
    if (!items)
      return;
    if (!mappingp(items))
      items = FIX_ITEMS(0, items);
    
    if (items[str]) 
    {
      if (sscanf(items[str], "#%s", func))
	call_other(this_object(), func, str);
      else 
      {
	string tmp;
        tmp = process_string(items[str]);
	end = tmp[strlen(tmp) - 1];
	if (end != '.' && end != '!' && end != '?')
	  tmp += ".";
        if ( sizeof(explode(tmp,"\n")) == 1 && strlen(tmp) > 78 ){
          write( break_string(tmp, 78) );
        } else {
	  write(tmp+"\n");
        }
      }
    }
    return;
  }

int
hook_look(string str)
{
  if (str)
    return 0;
/*
    if(!present("undergrounder_coat",this_player()) && dark(0))
      return 1;
*/
  DISPLAY_LOOK(0);
  return 1;
}

int
hook_glance()
{
  DISPLAY_LOOK(1);
  return 1;
}

/*  static int been_here; */void setup()
{
  int i, j;
  string *tmp;
  mixed ret;
  
/* Taken out, causes bugs in set_light /Nedo 980201 
 *  if(!arg && !been_here) 
 *  {
 *    been_here = 1;
 *    this_object()->reset();
 *    been_here = 0;
 *  } 
 */

light = 1;
/* added stuff for arable land - Mycon 270506 */
     if(planted > 0){
          if(arable)
               planted=0;
          else
               planted--;
     }
  /* Do not execute this on creation /Nedo 980201 */
  if(arg) {
    if( t_obj && mappingp(t_obj) )
	  do_time_obj();

    if(mappingp(objects)) 
      for(i=0, tmp=m_indices(objects); i < sizeof(tmp); i++)
        for(j=0; j < sizeof(objects[tmp[i]]); j++)
	  if(!objectp(objects[tmp[i]][j]) || 
	     !present(objects[tmp[i]][j],this_object()))
	    objects[tmp[i]][j] = 
	      move_object(clone_object(tmp[i]),this_object());
  
    if(mappingp(luniques)) 
      for(i=0, tmp=m_indices(luniques); i < sizeof(tmp); i++)
        for(j=0; j < sizeof(luniques[tmp[i]]); j++)
          if(!objectp(luniques[tmp[i]][j]))
            luniques[tmp[i]][j] = 
              move_object(clone_object(tmp[i]),this_object());

   if(pointerp(uniques) && sizeof(uniques))
      {

      for(i=0; i<sizeof(uniques); i++){
         ret = UNIQUE_D->add_unqiue_object(uniques[i][0],
            uniques[i][1], this_object(), uniques[i][2]);
         if( ret == -1 )
            continue;
         if( ret == 0 )
            uniques = exclude_array(uniques, i, i);
         if( pointerp(ret) ){
            for(j=0; j<sizeof(ret); j++)
            if( find_object(ret[j]) )
               move_object( find_object(ret[j]), this_object());
          }
      }
   }
  }
}

/* destroy walking npcs that belong to me */
void hook_destruct(){
int i, j;
mixed *tmp;
    if(mappingp(luniques))
      for(i=0, tmp=m_indices(luniques); i < sizeof(tmp); i++)
        for(j=0; j < sizeof(luniques[tmp[i]]); j++)
          if(objectp(luniques[tmp[i]][j]))
             if( find_object(luniques[tmp[i]][j])->query_npc() )
             destruct(luniques[tmp[i]][j]);
}

void init() {
  int             i, j;
  string         *dests;
  
  if (pointerp(chats))
    if (this_player() && !this_player()->query_npc())
      set_heart_beat(1);
  
  if (items && !mappingp(items))
    items = FIX_ITEMS(0, items);

  add_action("dig_a_hole", "dig");
  add_action("hook_smell", "smell");
  add_action("hook_smell", "sniff");
  add_action("hook_listen", "listen");
  
  if (!mappingp(dest_dir))
    dest_dir = FIX_DEST_DIR(0, dest_dir);
  if (!m_sizeof(dest_dir))
    return;
  dests = m_indices(dest_dir);
  for (i = 0; i < sizeof(dests); i++)
    add_action("qxxc_move", dests[i]);
  if (mappingp(Messages))
    add_action("check_message", m_indices(Messages));
#ifdef HUBBA
  add_action("cmd_hook", "", 1);
#endif
}

void
heart_beat()
{
  string          tmp,tmp_time;

  if (!test_if_any_here() || !pointerp(chats) || !sizeof(chats))
  {
    set_heart_beat(0);
    return;
  }
  if (random(100) > chats[0])
    return;
  tmp = chats[1][random(sizeof(chats[1]))];
  if (sscanf(tmp, "#%s", tmp))
    call_other(this_object(), tmp, 0);
  else if(sscanf(tmp,"%s#light",tmp))
{
    if(query_light()>0)
		tell_room(this_object(),tmp);
}
	else
		tell_room(this_object(), tmp);
}

varargs         status
add_message(string * action, string * arg, string reply, string * other)
{
  int             i;
  
  if (!Messages)
    Messages = ([]);
  if (pointerp(action))
    for (i = 0; i < sizeof(action); i++)
      Messages[action[i]] = ({arg, reply, other});
  else
    Messages[action] = ({arg, reply, other});
  return 1;
}

status 
remove_message(string * action)
{
  int             i;
  
  if (!Messages)
    return 0;
  if (pointerp(action))
    for (i = 0; i < sizeof(action); i++)
      Messages = m_delete(Messages, action[i]);
  else
    Messages = m_delete(Messages, action);
  return 1;
}

status 
check_message(string arg)
{
  string         *mess, action;
  int             i, pos;
  string         *tmp;
  
  if (!Messages || !Messages[action = query_verb()])
    return 0;
  if(!pointerp(Messages[action][0]))
    tmp = explode(Messages[action][0],"");
  else
    tmp = Messages[action][0];
  if (member_array(arg, Messages[action][0]) > -1) 
  {
    if(Messages[action][1][0] == '#')
      call_other(this_object(),Messages[action][1][1..-1]);
    else 
      writef(Messages[action][1], 78, 0);
    if (sizeof(Messages[action]) >= 2)
    {
      if (!pointerp(Messages[action][2]))
#ifdef MUDOS
        tmp = ({Messages[action][2]});
#else
      tmp = explode(Messages[action][2],"");
#endif
      else
	tmp = Messages[action][2];
      if(tmp[0] && (tmp[0][0] == '#'))
	call_other(this_object(),tmp[0][1..-1]);
      else
	say(break_string(this_player()->query_name() + " " +
			 tmp[random(sizeof(tmp))], 78, 0));
    }
    return 1;
  } 
  else
    return 0;
}

mapping 
query_messages(mixed arg)
{
  if (!Messages)
    Messages = ([]);
  return arg ? Messages[arg] : Messages;
}
#ifdef DGD_LIB
varargs void add_exit(string dir, string where, string my_func)
#else
void add_exit(string dir, string where, string my_func)
#endif
{
  if (pointerp(dest_dir))
    dest_dir = FIX_DEST_DIR(0, dest_dir);
  dest_dir = FIX_DEST_DIR(dest_dir, ({where, dir, my_func}));
}

#ifdef DGD_LIB
varargs void add_item(mixed what, string desc, string arg1, string arg2)
#else
void add_item(mixed what, string desc, string arg1, string arg2)
#endif
{
  items = FIX_ITEMS(items, ({what, desc, arg1, arg2}));
}

varargs void add_item_f(mixed what, string desc, string arg1, string arg2)
{
  if( !desc ) desc = "";
  desc = implode( explode( break_string( desc, 78, 0 ), "\n" ), "\n" );
   add_item( what, desc, arg1, arg2 );
}

void do_time_obj(){
	int i, j;
	string *tmp;
	
	if(mappingp(t_obj)) {
		tmp = m_indices(t_obj);

		for(i=0; i < sizeof(tmp); i++){
			for(j=0; j < sizeof(t_obj[tmp[i]]); j++){
				if(!objectp(t_obj[tmp[i]][j]))
					if(tmp[i]->check_time(1) )
						t_obj[tmp[i]][j] = move_object(clone_object(tmp[i]),this_object());
			}
		}
	}
}

void add_time_object(string fname, int num){

  int cnt;
  if(!stringp(fname))
    return;
  if(!mappingp(t_obj))
	  t_obj = ([ ]);
  if(t_obj[fname])
    return;
  
  t_obj[fname] = allocate(!num ? 1 : num);
  if( !(fname->check_time( ({1,0}) )) )
	  return;
  
  for(cnt=0;cnt<(num?num:1);cnt++)
    t_obj[fname][cnt] = move_object(clone_object(fname),this_object());
}
        
varargs void add_object(string fname, int num, int time)
{
	int cnt;

  if(!stringp(fname))
    return;
  if(!num) num = 1;
  if(time){
	  add_time_object(fname, num);
	  return ;
  }
  if(!mappingp(objects))
    objects = ([]);
  if(objects[fname])
    return;
  objects[fname] = allocate(!num ? 1 : num);
  
  /* Clone the item here instead, only reset it in reset /Nedo 980201 */
  for(cnt=0;cnt<(num?num:1);cnt++)
    objects[fname][cnt] = move_object(clone_object(fname),this_object());
}

varargs
void add_unique_object(string uname, mixed fname, int num, int rand){
   int i;
   mixed ret;
   object obj;
   string *cmds;

   if(!num) num = 1;
   if(!uname) return;
   if(intp(fname)){ num = fname; fname = 0; }
   if(!rand) rand = 0;

   ret = UNIQUE_D->add_unique_object(uname, num, this_object(), rand);

   /* ret = -1 (random fail), 0 (exists or fail), array (success) */
   if(ret == -1){
      if(!uniques) uniques = ({});
      uniques += ({ ({ uname, num, rand }) });
   }
   else if( pointerp(ret) ){
      for(i=0; i<sizeof(ret); i++)
      if( find_object(ret[i]) )
         move_object( find_object(ret[i]), this_object());
   }
   else {
      if(stringp(fname))
         add_object(fname, num);
   }

   return;
}

void add_local_unique(string fname, int num){
  int cnt;
  if(!stringp(fname)) return;
  if(!mappingp(luniques)) luniques=([]);
  if(luniques[fname]) return;
  luniques[fname] = allocate(!num?1:num);
  no_clean_up = 1;

  for(cnt=0;cnt<(num?num:1);cnt++)
    luniques[fname][cnt] = move_object(clone_object(fname),this_object());
}

void
set_smell(string smell)
{
  smell_desc = smell;
}

void
add_smell(mixed what, string desc)
{
 int last;
  last = strlen(desc) - 1;
  if( desc[last] != '.' || desc[last] != '?' || desc[last] != '!' ) desc += ".";
  smells = FIX_SMELLS(smells, ({what, desc}));
}

void set_sound(string sound){ sound_desc = sound; }
void
add_sound(mixed what, string desc)
{
  sounds = FIX_SOUNDS(sounds, ({what, desc}));
}

mixed
query_chats()
{
  return chats;
}

void
load_chat(int chance, mixed strs)
{
  if (!chance)
    return;
  if (stringp(strs))
    strs = ({strs});
  chats = ({chance, strs});
}

void
set_dig(int arg)
{
  ok_to_dig = arg;
}

void
set_no_clean_up(int arg)
{
  no_clean_up=arg;
}

int
query_no_clean_up() { return no_clean_up; }

int
dig_a_hole(string str)
{
  object          hole;
  
  if (!outdoors && !ok_to_dig) 
  {
    notify_fail("You can't dig here.\n");
    return 0;
  }
  if (present("ROOMHOLE", this_object()))
    return 0;
  move_object(hole = clone_object("obj/hole"), this_object());
  this_object()->affect_long(hole);
  return (int) hole->dig(str);
}

int
hook_smell(string str)
{
    if (!str) 
    {
      notify_fail("You don't smell anything special.\n");
      if (!smell_desc)
	return 0;
      write(smell_desc + "\n");
      return 1;
    }
    if (!mappingp(smells))
      smells = FIX_SMELLS(0, smells);
    return do_smell_listen(smells, str, "smell", "smells at");
  }

int
hook_listen(string str)
{
  if (!str) 
  {
    notify_fail("You hear nothing special.\n");
    if (!sound_desc)
      return 0;
    write(sound_desc + "\n");
    return 1;
  }
  if (!mappingp(sounds))
    sounds = FIX_SOUNDS(0, sounds);
  return do_smell_listen(sounds, str, "hear", "listens to");
}

int
do_smell_listen(mixed map, string str, string verb, string sayverb)
{
  if (!str)
    return 0;
  
  sscanf(str, "at %s", str);
  sscanf(str, "on %s", str);
  sscanf(str, "to %s", str);
  if (!map[str]) {
    notify_fail("You don't " + verb + " anything special.\n");
    return 0;
  }
  if (this_player()->short())
    say(this_player()->query_name() + " " + sayverb + " the " + str + ".\n");
  if (sscanf(map[str], "#%s", str))
    return (int) call_other(this_object(), str, 0);
  write(map[str] + "\n");
  return 1;
}

int
Enter_room(int brief)
{
  if (!this_player())
    return 0;
  if(!present("undergrounder_coat",this_player()) && dark(0))
    return 1;
  DISPLAY_LOOK(brief);
  return 1;
}

int
dark(int silent)
{
  if(query_light()>0)
    return 0;
  if(this_player() && !silent)
    write("Darkness.\n");
  return 1;
}

int
test_if_any_here()
{
  object         *inventory;
  int             i;
  
  if (!sizeof(inventory = all_inventory()))
    return 0;
  for (i = 0; i < sizeof(inventory); i++)
    if (living(inventory[i]) && !inventory[i]->query_npc())
      return 1;
  return 0;
}

int user_check(){ return test_if_any_here(); }

int
affect_long(object ob)
{
  object         *tmp;
  tmp = (object *) DESC->register_aff_ob(ob, affect_objects);
  if (sizeof(tmp) && tmp != affect_objects) 
  {
    affect_objects = tmp;
    return 1;
  }
  return 0;
}

int
add_obvious(string dir)
{
  if (!mappingp(dest_dir))
    return 0;
  if (dest_dir[dir])
    return 0;
  
  add_exit(dir, file_name(previous_object()), 0);
  update_actions();
  return 1;
}

int
remove_obvious(string dir)
{
    if (!mappingp(dest_dir))
      return 0;
    dest_dir = m_delete(dest_dir, dir);
    update_actions();
    return 1;
  }

void
update_actions()
{
  filter_array(all_inventory(), "update_init", this_object());
}

void
update_init(object ob)
{
  if (living(ob))
    move_object(ob, this_object());
}

int
qxxc_move()
{
  string          verb;
  if (dest_dir && !mappingp(dest_dir)) 
  {
    FIX_DEST_DIR(0, dest_dir);
    filter_array(all_inventory(this_object()), "update_init", this_object());
  }
  verb = query_verb();
  if (!dest_dir[verb])
    return 0;
  if( this_player()->query_guest() )
    if((dirname( dest_dir[verb][0] ) != ROOM+"" && dirname( dest_dir[verb][0] ) != "/room") &&
   strstr( dirname( dest_dir[verb][0] ), "domains/Gangs/TG/room" ) == -1 ) {
    write("A security guard quickly appears and says: For your own safety, we insist you stay in the\n"+
     "patroled areas of the city.\n");
    return 1;
   }
  if (dest_dir[verb][1] &&
      call_other(this_object(), dest_dir[verb][1], dest_dir[verb][0]))
	return 1;
  this_player()->move_player(verb, dest_dir[verb][0]);
  return 1;
}

mixed
query_property(string str)
{
  if (!str)
    return property;
  if (!property)
    return 0;
  if (stringp(property))
    return str == property;
  if (member_array(str, property) >= 0)
    return 1;
  return 0;
}

int
clean_up()
{
  object *inv;
  if (no_clean_up)
    return 0;
  if(inv=all_inventory())
    filter_array(inv,"clean_up_filter",this_object());
  if (first_inventory())
    return 1;
  
#if 0
  log_file("CLEAN_UP", ROOM+" " + extract(ctime(time()), 4, 19) + " : " +
	   file_name(this_object()) + ".\n");
#endif
  
    destruct(this_object());
  return 0;
}

void 
clean_up_filter(object ob)
{
    if(ob->id("empty_container"))
      destruct(ob);
  }

string         *
query_smells()
{
  return QUERY_SMELLS;
}

mixed
query_real_smells()
{
  return QUERY_REAL_SMELLS;
}

string         *
query_sounds()
{
  return QUERY_SOUNDS;
}

mixed
query_real_sounds()
{
  return QUERY_REAL_SOUNDS;
}

string         *
query_items()
{
  return QUERY_ITEMS;
}

mixed
query_real_items()
{
  return QUERY_REAL_ITEMS;
}

string         *
query_dest_dir()
{
  return QUERY_DEST_DIR;
}

mixed
query_real_dest_dir()
{
  if (!mappingp(dest_dir))
    dest_dir = FIX_DEST_DIR(0, dest_dir);
  return QUERY_REAL_DEST_DIR;
}

string         *
query_exits() 
{
  mixed i;

  i = query_real_dest_dir();
  if(!mappingp(i)) return 0;
  return m_indices(i);
}

string
query_long()
{
  return long_desc;
}

string
query_short()
{
  return short_desc;
}

int
query_light()
{
int mod;
#ifdef NIGHT_CODE
  if((int)NTIME->query_time_of_day()==NIGHT)
    {
   if( set_light(0) == 0 ) /* already dark */
     mod = 0;
   else
   mod = 1;
    if(outdoors && conditional_lighting!=2)
      return set_light(0)-mod;
    if(!outdoors && conditional_lighting==1)
      return set_light(0)-mod;
    }
#endif
  return set_light(0);
}

int
query_skip_obvious()
{
  return skip_obvious;
}

string         *
query_hide_obvious()
{
  return hide_obvious;
}

int
query_outdoors()
{
  return outdoors;
}

mixed *
query_uniques() 
{ 
  return uniques; 
}

string throw(string obj,string dest) { return dest; }

mapping query_t_obj(){ return t_obj; }

mapping
query_objects() 
{
  return objects; 
}

int
query_conditional_lighting()
{
return conditional_lighting;
}

void
set_outdoors(int arg)
{
  outdoors = arg;
  ok_to_dig = outdoors;
}

void
set_conditional_lighting(string str)
{
conditional_lighting=str;
}

void
set_long(string str)
{
  long_desc = str;
}

varargs void
set_long_f(string str, int len)
{
  long_desc = break_string(str, len ? len : 78, 0);
}

void
set_short(string str)
{
  short_desc = str;
}

int
fix_light(int light) 
{
  return set_light(light);
}

void
debug()
{
  DEBUG;
}


void save_me(string file)
{
  if (!stringp(file))
    file = source_file_name(this_object());
  if (!this_player(1)->valid_write("/"+file))
    return;
  light = set_light(0);
  save_object(file);
}

void restore_me(string file)
{
  restore_object(file);
  set_light(light);
  reset(1);
}

void set_free_kill(int i){ free_kill_flag = i; }
int query_free_kill(){ return (free_kill_flag || FREE_KILL); }

/* Darkman - 000509 */
int query_local_help(string str) {
	if(!local_help) return 0;
	if(!m_sizeof(local_help)) return 0;
	if(undefinedp(local_help[str])) return 0;
	write( local_help[str] );
	return 1;
}

void add_help(mixed what, string descrip) {
        int i;
	if(!what) return;
	if(!descrip) return;

        if(pointerp(what)){
           for(i=0; i<sizeof(what); i++) add_help(what[i], descrip);
         }
	if(!local_help)
		local_help = ([ ]);

	if( undefinedp( local_help[what] ) )
		local_help += ([ what : descrip ]);
	else
		local_help[what] = descrip;

	return ;
}

varargs mixed query_readable(string key){
   if(!readable) return -1;
   if(!key) return readable;
   if(undefinedp(readable[key])) return -1;
   return readable[key];
}

varargs
void add_readable(mixed what, mixed desc){
   int i;
   if(!what) return;
   if(!desc) desc = 0;
   if( pointerp(what) ){
     for(i=0; i<sizeof(what); i++) add_readable(what[i], desc);
   }
   if(!readable) readable = ([ what : desc ]);
   else readable[what] = desc;
  if( !id( what ) ) add_item( what, desc );
   return;
}


void set_type(mixed type) {
  int i;

  if(!type) return;
  if( pointerp(type) ) {
    i = 0;
    while(type[i]){
      set_type(type[i]);
      i++;
    }
    room_type = type;
    return;
  }

  room_type = type;
  switch(type) {
   case "street" : add_object(ENV_OBJ+"/streetlamp.c");
      break;
    default: break;
  }
  return;
}

string query_type(){ return room_type; }

void set_arable(int i){ arable=i; }
void set_planted(int i){ planted=i; }
void add_planted(){ planted++; }
int query_planted(){ return planted; }
int query_arable(){ return arable; }

string query_city(){
  string fname;

  fname = file_name(this_object());
  if( strstr( fname, "domains/NG" ) != -1 ) return "new genesis";
  if( strstr( fname, "domains/Barleymow" ) != -1 ) return "barleymow";
  return "abacus";
}

/* EOF */

