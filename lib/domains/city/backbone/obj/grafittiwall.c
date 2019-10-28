static string grafitti;
string readwrite;
string short;

short ()
{
   return short;
}
long()
{
   display_grafitti();
   write ("Do: 'scribble <text>'\n");
}
id (str)
{
   return str =="wall" || str=="grafitti";
}
init ()
{
   add_action ("scribble","scribble");
add_action("read", "read");
}
read(arg){
if( id(arg) ) return display_grafitti();
return 0;
}

reset (arg)
{
    
   short = "A grafitti wall";
   if (restore_me())
      grafitti=explode(readwrite,"%");
   else grafitti = ({"Killroy wasn't here! (yet)"});
}
scribble (str)
{
   int i;
   if (!str) { write ("Scribble what?\n"); return 1; }
   if (strlen (str) >60) { write ("Too large! Won't fit on the wall!\n"); return 1; }
   if (sizeof (grafitti)>=20) {
      i=0;
      while (i<sizeof(grafitti)-1) {
         grafitti[i]=grafitti[i+1];
         i++;
       }
      grafitti[i]=str;
   }
   else
      {
      grafitti=grafitti+({str});
   }
   write ("Ok.\n");
   say (this_player()->query_name()+" scribbles something on the wall.\n");
   log_file("grafstuff", this_player()->query_name()+" of "+query_ip_name()+" scribbled '"+str+"'\n");
   readwrite=implode(grafitti,"%");
   save_me();
   return 1;
}

display_grafitti()
{
   int i;
   write ("----------------------------------------------------------------\n");
   while (i<sizeof(grafitti)) {
      write (extract ("l "+grafitti[i]+"                                                              ",0,62));
      write ("l\n");
      i++;
   }
   write ("----------------------------------------------------------------\n");
   return 1;
}

restore_me() {  return restore_object ("obj/o/grafitti"); }
save_me() { return save_object ("obj/o/grafitti"); }




