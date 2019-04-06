#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

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

char *to_char(int i) {
	char *out = calloc(3, sizeof(char));
	static const char *const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (i < 26) {
		strncpy(out, alphabet + i, 1);
		out[1] = '\0';
	} else {
		int tens = (i / 26) - 1;
		strncpy(out, alphabet + tens, 1);
		int ones = i % 26;
		strncat(out, alphabet + ones, 1);
	}
	out[2] = '\0';
	return out;
}
