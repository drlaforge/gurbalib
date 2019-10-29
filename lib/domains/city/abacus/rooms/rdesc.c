/*

  rdesc.c  Ver 3.0  1991-01-18

  General routines for room description. 
  This is the central object called from all rooms to handle 
  a diversity of things. 

  The idea with this central object is to avoid needing to update all
  rooms when something must be changed.

*/

#define GAMEADMIN_WIZ "draconian"  /* Errors in backbone is logged to this sci */
#define MAX_LIST 50         /* Maximum number of objects described in a room */

/* #define MAX_AFFECT 10  Obsolete: Max objs that can affect the long desc. */


/* To avoid allocating these every time we do a look in empty rooms
   we make them global and allocate them in reset().
*/
int *live_list, *dead_list;


id(str) { return str == "rdesc"; }

void setup(void)
{ 
   

  live_list = allocate(MAX_LIST);
  dead_list = allocate(MAX_LIST);
}

short() { return 0; }

init() {}

/* This replaces the "look" routine in player.c for looking in rooms
*/
rdesc_look(pr_brief)
{
  object ob, myself,current_room;
  string item,stmp,t1,t2;
  int max,cntl,cntd;
  
  myself=this_player(); 
  current_room = environment(myself);
  
  /* Look in the room we are in
  */
  if (pr_brief) write(current_room->short() + "\n");
  else current_room->long();

  /* Check what else is in the room
  */
  ob = first_inventory(current_room);
  if (!ob) return 1;
  if (!next_inventory(ob)) return 1;     /* Only me in room => ready */

  /* Make two lists, living objects and other objects
  */
  max = MAX_LIST; cntl=0; cntd=0;
  while(ob && (max > 0)) {
    if (ob != myself) {
      if (living(ob)) {
        live_list[cntl]=ob;
        cntl++;
      }
      else {
        dead_list[cntd]=ob;
        cntd++;
      }
    }
    ob = next_inventory(ob); max = max - 1;
  }

  /* If there are more objects than the max limit 
  */
  if (!max) write("Wow! What a lot of things, among them I see:\n");

  /* First write description of 'dead' objects
  */
 rep("deadlist arr : " + pointerp(dead_list) + "\n");
  if (cntd) {
        rep("Cntd..\n");
     item = describe(dead_list, 0);
    if (item) {
      t1 = "There are "; t2 = " here.";
      if (extract(item,0,0) < "a") { 
        t1 = ""; 
        t2 = " is here.";
      }
      if (sscanf(item,"the%s",stmp)==1) {
        t1 = ""; item=capitalize(item);
        t2 = " is here.";
      }
      if (sscanf(item,"a%s",stmp)==1) t1 = "There is ";
      if (sscanf(item,"%shere.",stmp) == 1) t2 = "";
      else if (sscanf(item,"%shere",stmp) == 1) t2 = ".";
      write(break_string(t1+item+t2, 76)+"\n");
    }
    dead_list=allocate(MAX_LIST); /* Clear the array */
  }
  
  /* Then write description of living objects
  */
  if (cntl) {
    item=describe(live_list,1);
    if (item) {
      if (cntl<2)
        write(break_string(capitalize(item) + " is here.",76)+"\n");
      else write(break_string(capitalize(item) + " are here.",76)+"\n");
    }
    live_list=allocate(MAX_LIST); /* Clear the array */
  }
  return 1;
}
static break_string(str,size)
{
  int arr,c,sz,ts;

  arr = explode(str+" "," ");
  if (!pointerp(arr)) return str;

  for (c=0,sz=0;c<sizeof(arr);c++) {
    if (sz+(ts=strlen(arr[c])) > size) {
      arr[c] = "\n" + arr[c]; sz = ts + 1;
    }
    else sz += ts + 1;
  }
  return implode(arr," ");
}

/* This is called directly from the room when we want the long description
*/
rdesc_long(long_desc,long_func,affect_objects,dest_dirs,skip_exits)
{
  int i;
  
  /* Long_desc of the room itself
  */
  if (long_func) call_other(previous_object(),long_func);
  if (long_desc) write(long_desc);
  
  /* Objects in the room affecting the long description
  */
  if (pointerp(affect_objects)) {
    i=1; /* if (affect_objects[0]>MAX_AFFECT) affect_objects[0]=MAX_AFFECT; */
    while (i<=affect_objects[0]) {
      if ((affect_objects[i]) &&
          (present(affect_objects[i],previous_object())))
        affect_objects[i]->affect_environment();
      else affect_objects[i]=0;
      i++;
    }
  }

  /* Do not print info on obvious exits if this is not wanted
  */
  if (skip_exits) return;

  /* Describe the obvious exits
  */
  if (!dest_dirs)
    write("    No obvious exits.\n");
  else {
    i = 2;
    if (sizeof(dest_dirs) == 3) write("    There is one obvious exit:");
    else write("    There are " + word_number(sizeof(dest_dirs)/3) +
               " obvious exits:");
    while(i < sizeof(dest_dirs)) {
      write(" " + dest_dirs[i-1]); i += 3;
      if (i == sizeof(dest_dirs) - 1) write(" and");
      else if (i < sizeof(dest_dirs)) write(",");
    }
    write("\n");
  }
}

/* Registration of objects that should be able to affect the
   long description of the room.
*/
rdesc_affect_long(ob,affect_objects)
{
  int cnt,a;
  if (!affect_objects) {
    a=allocate(1);
    a[0]=0;
  }
  else a=affect_objects;
  cnt=1; while (cnt<=a[0]) {
    if ((a[cnt]==ob) || (!objectp(a[cnt]))) {
      a[cnt]=ob; return a;
    }
    cnt++;
  }
  a[0]++;
  a = a + ({ ob });
  return a;
}

/* Called from move when a destination room can not be loaded
   Logs the error in /log/room.wizname and /log/room.ERRORS
   If the sci is logged in then he gets the error too
*/
rdesc_log_loaderror(efile,pobj,erl)
{
  string wiz,player,emsg,gdriverror;
  object pl;

  /* Find the responsible scientist or an Arch if sci is not logged in
  */
  wiz=creator(previous_object()); 
  if (!wiz) {
    wiz="backbone";
    pl=find_player(GAMEADMIN_WIZ); /* Tell Gameadmin when error in /room */
  }
  else pl=find_player(wiz);
  if ((!pl) && (this_player()) && (this_player()->query_level()>19))
    pl=this_player();

  if (!pl) pl=find_arches(); /* Tell an arch if sci not logged in */

  /* Find the name of the player or object that tried to move
  */
  if (!this_player()) player="(NULL,Prev: "+file_name(pobj)+")";
  else
    player=capitalize(this_player()->query_real_name())+" (Level: "+
      this_player()->query_level()+")";

  /* Construct error message and log it
  */
  emsg=" Player: "+player+", from:\n ("+file_name(previous_object())+
           ") "+query_verb()+" to ("+efile+")";
  gdriverror=catch(call_other(efile,"id",0));
  if (!gdriverror) {
    gdriverror=" In reset(): "+erl;
  }
  else gdriverror="Can't load object: " + erl;
  if (pl) player="[Told: "+capitalize(pl->query_real_name())+"]";
  else player="[LOGONLY]";
  log_file(wiz+".room",player+ctime(time())+" "+emsg+"\nErr: "+gdriverror+"\n");
  log_file(ROOM+".ERRORS",player+" "+ctime(time())+" "+emsg+"\nErr: "+gdriverror+"\n");

  /* Tell the player that he encountered an error
  */
  if ((this_player()) && (pl!=this_player())) {
    write("** Error **\n");
    write("Due to a slight mistake in this Creation you can't move there.\n");
    write("The creator responsible has been notified of this and will fix it.\n");
  }
  
  /* Tell the scientist he has a bug in his code, or an arch if sci not logged in
  */
  if (pl) {
    if (wiz==pl->query_real_name()) wiz="your";
    else if (pl==this_player()) wiz=capitalize(wiz+"'s");
    else {
      wiz=capitalize(wiz+"'s");
      tell_object(pl,"The below scientist is not logged in, you get this message because you're an Arch.\n");
    }
    tell_object(pl,"\nError in "+wiz+" room files, the move was:\n");
    tell_object(pl,emsg+"\n");
    tell_object(pl,"The error given by the Game Driver was:\n"+gdriverror+"\n");
  }
}

q_arch(ob)
{
  return (ob->query_level() >= 24);
}

find_arches()
{
  object apa;
  apa=filter_objects(users(),"q_arch",this_object());
  if (apa) return apa[random(sizeof(apa)-1)]; 
  return 0;
}

/* This routine fixes backwards compatibility with old room/room so that
   dest_dir can take both two and three arguments per exit. 
*/
rdesc_fix_dest(dest_dir)
{
  int c,i,fl;
  int dest_dir2;

/*
  log_file(ROOM+".USAGE",ctime(time())+": "+file_name(previous_object())+"\n");
*/
  if (!pointerp(dest_dir)) {
    dest_dir2=dest_dir; return;
  }
  if (sizeof(dest_dir)<3) fl=0;
  else {
    if ((!stringp(dest_dir[2])) || (dest_dir[2][0]=='#')) fl=1;
    else fl=0;
  }
  c=sizeof(dest_dir); 
  if (!fl) dest_dir2=allocate(3*c/2);
  else dest_dir2=allocate(c);
  i=0; c=0;
  while (i<sizeof(dest_dir)) {
    dest_dir2[c]=dest_dir[i]; c+=1; i+=1;
    dest_dir2[c]=dest_dir[i]; c+=1; i+=1;
    if (!fl) {
      dest_dir2[c]=0; c+=1;
    }
    else {
      if (stringp(dest_dir[i])) dest_dir2[c]=extract(dest_dir[i],1);
      else dest_dir2[c]=0;
      c+=1; i+=1;
    }
  }
  return dest_dir2;
}

/* To get a dump of variables, call the debug() function in the room
*/
rdesc_debug(short_desc,long_desc,long_func,dest_dir,dest_dir2,affect_objects,items,property,use_composite)
{
  write("\nshort_desc: ");  dump_array(short_desc,""); 
  if (long_desc) {
    write("\nlong_desc: ");  dump_array(long_desc,""); 
  }
  else {
    write("\nlong_func: ");  dump_array(long_func,""); 
  }
  write("\ndest_dir2: ");  dump_array(dest_dir2,""); 
  write("\ndest_dir: ");  dump_array(dest_dir,""); 
  if (affect_objects) {
    write("\naffect_objects: "); dump_array(affect_objects,""); 
  }
  if (items) {
    write("\nitems: "); dump_array(items,""); 
  }
  if (property) {
    write("\nproperty: "); dump_array(property,""); 
  }
  write("\nuse_composite: "); write(use_composite); write("\n");
}

dump_array(a,tab)
{
  int n,m;

  if (!pointerp(a)) {
    write(a); return;
  }
  else write("\n");
  m=sizeof(a);
  n=0;
  while (n<m) {
    write(tab+"["+n+"] = "); dump_elem(a[n],tab); n+=1;
  }
}

dump_elem(sak,tab)
{
  if (pointerp(sak)) {
    write("Array: \n"); dump_array(sak,tab+"   ");
  }
  else write(sak);
  write("\n");
}



/* This routine returns a number in text form
*/
word_number(num)
{
  string nums;
  string numt; 
  string ns,n2;
  int ilop,nm;

  nums = ({"one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"});
  numt = ({"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"});

  if (num<1) return "no";
  if (num<20) return nums[num-1];
  if (num>99) {
    if (num>999) {
      if (num>999999) return "many";
      return word_number(num/1000)+"thousand"+word_number(num%1000);
    }
    return word_number(num/100)+"hundred"+word_number(num%100);
  }
  if ((num%10)==0) return numt[num/10-2];
  else return numt[num/10-2]+nums[num%10-1];
}


/* Functions below this help describing multiple things
*/

#define FILTER(fa,fb,fc) fc=filter_objects(fa,fb,this_object())
#define DESCRIBE(a,l,s) parse_command("@describe",a,"short",l,s)
#define UNIQUE(a,s,r) parse_command("@unique",a,"short",s,r)

string gSame_uf;
int gTot_uf;

true_uf(ob) { return objectp(ob); }
same_uf(ob)
{
  if ((ob) && (gSame_uf==ob->short())) {
    gTot_uf++; return 0;
  }
  return 1;
}
  
money_add_uf(ob) 
{
  int cnt;
  string str;
  if (sscanf(ob->short(),"%d %s",cnt,str)==2) {
    if (gSame_uf!=str) return 0;
    gTot_uf+=cnt;
    return 1;
  }
  return 0;
}
not_money_uf(ob) { if (money_add_uf(ob)) return 0; else return 1; }
  

describe(arr,live)
{
  int a,b,c,cnt;
  string str;
  object tmp;
  
  if (objectp(arr)) arr=({arr});
  if (!pointerp(arr)) return 0;
  if (sizeof(arr)<1) return 0;

 rep("1..\n");
  /* Have we got this compiled yet?
  */
 rep("Before unique call arr was array : " + pointerp(arr) + "\n");
  UNIQUE(arr,tmp,a);

  /* If so just describe it and we are ready
  */
  rep("2.." + a + "  tmp : ");
  if (objectp(tmp)) rep(file_name(tmp) + "\n");
  else rep(tmp + "\n");
  if (a) {
    if (a[0]<1) return 0; /* There were only invis objects */
    DESCRIBE(a,live,str);
    return str;
  }

 rep("2.5..\n");
  /* Otherwise we must filter out unique objects here in LPC
  */
  rep("pointerp(arr) : " + pointerp(arr) + "\n");
  if (!pointerp(arr)) return 0;
  if (sizeof(arr)<1) return 0;
  rep("3..\n");
  FILTER(arr,"true_uf",c);        /* Copy array */
  a=allocate(sizeof(c)+1); a[0]=0;
  while(c) {
    gSame_uf=c[0]->short(); 
    if ((gSame_uf) && (sscanf(gSame_uf,"%d %s",cnt,str)==2) &&
        (c[0]->id("money"))) {
      gSame_uf=str; gTot_uf=0; tmp=clone_object("obj/money");
      FILTER(c,"money_add_uf",b); tmp->set_money(gTot_uf);
      FILTER(c,"not_money_uf",c);
      a[0]+=1; a[a[0]]=({1,tmp});
    }
    else {
      gTot_uf=0; tmp=c[0];
      FILTER(c,"same_uf",c); /* Counts same in gTot, filters out nonsame */
      if (gSame_uf) { /* Do not describe if invisible ( short()==0 ) */
        a[0]+=1; a[a[0]]=({gTot_uf,tmp});
      }
    }
  }
  if (a[0]<1) return 0; /* There were only invis objects */
  DESCRIBE(a,live,str); 
  return str;
}

rep(x) {
        object ob;
        if (ob = find_living("groo"))
                tell_object(ob, x);
}

shorts(arr) {
        int index;
        while (index < sizeof(arr)) {
                if (objectp(arr[index]))
                        arr[index] = arr[index]->short();
                index++;
        }
}
filter_objects(arr, fun, ob) {
        int index, count;
        string tmp_arr, ret_arr;
        tmp_arr = allocate(sizeof(arr));
        while (index < sizeof(arr)) {
                if (call_other(ob, fun, arr[index])) {
                        tmp_arr[count] = arr[index];
                        count++;
                }
                index++;
        }
        ret_arr = allocate(count);
        while (count) {
                count--;
                ret_arr[count] = tmp_arr[count];
        }
        return ret_arr;
}
