short() {
    return "The local prison";
}

long() {
    write("You are in the local prison.\n");
    write("There are no exits.\n");
}

void setup(void) {
    if (arg)
	return;
    set_light(1);
}

init() {
    add_action("quit"); add_verb("quit");
}

quit() { return 1; }

query_escape_proof() { return 1; }

query_light(){ return 1; }

