#include <stdlib.h>
#include <string.h>

#include "data.h"

typedef struct table_s *table;

typedef struct cell_s *cell;

typedef union  data_s *data;

table init_table() {
	table tab = calloc(256 * 64, sizeof(data));
	return(tab);
}
