#ifndef COMMANDS
#define COMMANDS

struct trie_node_s {
	///list of all the children (note: most won't exist)
	struct trie_node_s *children[27];

	///function pointer for function to call or null if DNE
	///I'm using a char for the parameter because I don't
	///feel like writing 100 commands right now. Maybe later 
	void (*command)(char final);
}

typedef struct trie_node_s *trie_node;

#endif
