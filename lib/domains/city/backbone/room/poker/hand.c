/*  Cards support for casino games *//*  Author: Shalafi */inherit "/std/object";

#include <ansi.h>
create() {
   set_name("hand");
}

show_hand(string hand, object him, int bar) {
   string *cards, *suit, retstr;
   int *rank; 
   int i, j, ansi;
 
   if (!hand || !him) return 1;
   if(him->query_ansi()) ansi = 1;
   else ansi=0;
   cards=explode(hand, ",");
   i=sizeof(cards);
   rank=allocate(i);
   suit=allocate(i);
   if (!i) return 1; 
   if (i>5) i=5;
   for (j=0;j<i;j++) {
      if (sscanf(cards[j], "%d %s", rank[j], suit[j])!=2) {
         rank[j]=1;
         suit[j]="s";
      }               
      if (suit[j]!="h" && suit[j]!="s" && suit[j]!="c" && suit[j]!="d") 
         suit[j]="s";
      if (rank[j]<1 || rank[j]>13)
         rank[j]=1;
   }                        
   retstr="";
   if (ansi) retstr+=BOLD+WHITE;
   for (j=0;j<i;j++)
      retstr+="  ---------";
   retstr+="\n";       
  /*  line 2 */   for (j=0;j<i;j++) { 
      retstr+="  |";  
      if (bar==2 && j==0) retstr+=" X X X |";
      else {
      if (ansi && (suit[j]=="h" || suit[j]=="d"))
         retstr+=RED;
      if (ansi && (suit[j]=="c" || suit[j]=="s"))   
         retstr+=BLUE;
      if (rank[j]==1) retstr+="A ";
      else if (rank[j]<10) retstr+=rank[j]+" ";
      if (rank[j]==10) retstr+=rank[j];
      if (rank[j]==11) retstr+="J ";
      if (rank[j]==12) retstr+="Q ";
      if (rank[j]==13) retstr+="K ";
      if (ansi) retstr+=WHITE;
      if (suit[j]=="c")
         if (ansi) retstr+=BLUE+" _   "+WHITE+"|";
         else retstr+=" _   |";            
      else   
         retstr+="     |";
   }
   } 
   retstr+="\n";      
  /*  line 3 */   for (j=0;j<i;j++) {
   if (bar==2 && j==0) retstr+="  |  X X  |";
   else {
      if (suit[j]=="c")
         if (ansi) retstr+="  |  "+BLUE+"( )  "+WHITE+"|";
         else retstr+="  |  ( )  |";     
      if (suit[j]=="s")
         if (ansi) retstr+="  |  "+BLUE+"/^\\  "+WHITE+"|";
         else retstr+="  |  /^\\  |";   
       if (suit[j]=="h")
          if (ansi) retstr+="  | "+RED+"/\\ /\\ "+WHITE+"|";
          else retstr+="  | /\\ /\\ |";
       if (suit[j]=="d")
          if (ansi) retstr+="  |  "+RED+"/ \\  "+WHITE+"|";
          else retstr+="  |  / \\  |";  
   }
   }           
   retstr+="\n";
  /*  line 4 */   for (j=0;j<i;j++) {
   if (bar==2 && j==0) retstr+="  | X X X |";
   else {
      if (suit[j]=="c")
         if (ansi) retstr+="  | "+BLUE+"(_ _) "+WHITE+"|";
         else retstr+="  | (_ _) |";   
      if (suit[j]=="s")
         if (ansi) retstr+="  | "+BLUE+"(_ _) "+WHITE+"|";
         else retstr+="  | (_ _) |";    
       if (suit[j]=="h")
          if (ansi) retstr+="  | "+RED+"\\   / "+WHITE+"|";
          else retstr+="  | \\   / |"; 
      if (suit[j]=="d")
         if (ansi) retstr+="  | "+RED+"<   > "+WHITE+"|";
         else retstr+="  | <   > |";      
   }
   }
   retstr+="\n";
  /*  line 5 */   for (j=0;j<i;j++) {
   if (bar==2 && j==0) retstr+="  |  X X  |";
   else {
      if (suit[j]=="c")
         if (ansi) retstr+="  |   "+BLUE+"I   "+WHITE+"|";
         else retstr+="  |   I   |";
      if (suit[j]=="s") 
         if (ansi) retstr+="  |   "+BLUE+"I   "+WHITE+"|";  
         else retstr+="  |   I   |";     
      if (suit[j]=="h")
         if (ansi) retstr+="  |  "+RED+"\\ /  "+WHITE+"|";
         else retstr+="  |  \\ /  |";          
      if (suit[j]=="d") 
         if (ansi) retstr+="  |  "+RED+"\\ /  "+WHITE+"|";
         else retstr+="  |  \\ /  |";        
   }
   }
   retstr+="\n";
  /*  line 6 */   for (j=0;j<i;j++) {
   if (bar==2 && j==0) retstr+="  | X X X |";
   else {
      retstr+="  |     ";
      if (ansi && (suit[j]=="h" || suit[j]=="d"))
         retstr+=RED;
      if (ansi && (suit[j]=="c" || suit[j]=="s"))   
         retstr+=BLUE;             
      if (rank[j]==1) retstr+=" A";
      else if (rank[j]<10) retstr+=" "+rank[j];
      if (rank[j]==10) retstr+="10";
      if (rank[j]==11) retstr+=" J";
      if (rank[j]==12) retstr+=" Q";
      if (rank[j]==13) retstr+=" K";
      if (ansi) retstr+=WHITE;
      retstr+="|";
   }
   }
   retstr+="\n";       
   for (j=0;j<i;j++)
      retstr+="  ---------";
   if (ansi) retstr+=NORMAL;
   retstr+="\n";       
   if (bar==1) retstr+=
"      1          2          3          4          5\n";
 
   tell_object(him, retstr);
   return 1;
}                          

rank_card(int hmm) {
   switch (hmm) {
      case 2: return "Two"; break;
      case 3: return "Three"; break;
      case 4: return "Four"; break;
      case 5: return "Five"; break;
      case 6: return "Six"; break;
      case 7: return "Seven"; break;
      case 8: return "Eight"; break;
      case 9: return "Nine"; break;
      case 10: return "Ten"; break;
      case 11: return "Jack"; break;
      case 12: return "Queen"; break;
      case 13: return "King"; break;
      default: return "Ace"; break;
   }
}

string id_card(string card) {
   int rank;
   string suit, retstr;
   if (!card) return "";
   if (sscanf(card, "%d %s", rank, suit)!=2) return "";
   switch(rank) {
      case 2: retstr="Two"; break;
      case 3: retstr="Three"; break;
      case 4: retstr="Four"; break;
      case 5: retstr="Five"; break;
      case 6: retstr="Six"; break;
      case 7: retstr="Seven"; break;
      case 8: retstr="Eight"; break;
      case 9: retstr="Nine"; break;
      case 10: retstr="Ten"; break;
      case 11: retstr="Jack"; break;
      case 12: retstr="Queen"; break;
      case 13: retstr="King"; break;
      default: retstr="Ace"; break;
   }
   retstr+=" of ";
   switch(suit) {
      case "c": retstr+="Clubs"; break;
      case "d": retstr+="Diamonds"; break;
      case "h": retstr+="Hearts"; break;
      default: retstr+="Spades"; break;
   }
   return retstr;
}
