#include <string.h>
#include <ctype.h>

#include "functions.h"

//I can't take credit for the implementation of this,
//credit to caf on StackOverflow for this elagant solution
int to_num(char c) {
	int n = -1;

	static const char *const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *p = strchr(alphabet, toupper((unsigned char) c));

	if (p != NULL) {
		n = p - alphabet;
	}

	return n;
}
