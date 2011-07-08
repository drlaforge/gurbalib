void usage() {
  write("Usage: store [-h] OBJECT\n");
  write("If you are in a storage area, you can store your items with this " +
     "comand.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: sell, buy, retrieve\n");
}

void main( string str ) {
  object ob;

  if ( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  ob = this_player()->present( str );

  if( !ob ) {
    write( "You can't seem to find the " + lowercase( str ) + "." );
    return;
  }

  if( !this_environment()->is_storage() ) {
    this_player()->write( "Perhaps you should try storing your item in a " +
      "storage location?" );
    return;
  }

  this_environment()->store_object( ob );
}
