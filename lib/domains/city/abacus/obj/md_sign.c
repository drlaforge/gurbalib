inherit "/std/sign";

private string get_sign_text(void) {
   return
      " %^RED%^      _______________________\n" +
      "     =(_______________________)=\n" +
      "       |                     |\n" +
      "       |      Welcome to     |\n" +
      "       |             	     |\n" +
      "       |      MacDonalds     |\n" +
      "       |                     |\n" +
      "       |   Come again soon.  |\n" +
      "       |                     |\n" +
      "       |_____________________|\n" +
      "     =(______________________()=%^RESET%^";
}

void setup(void) {
   set_short("--sign--");
   set_message(get_sign_text());
   set_long("It's a business sign. Perhaps you should read it.");

}
