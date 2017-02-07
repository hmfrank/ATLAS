#include <string.h>

static size_t max_n_days = 42;
static int show_table_header = 1;
static int show_days = 1;
static int show_total_count = 1;
static int show_date = 1;
static int show_requests = 1;
static int show_users = 1;
static int show_in_bytes = 1;
static int show_out_bytes = 1;

size_t const * const MAX_N_DAYS = &max_n_days;
int const * const SHOW_TABLE_HEADER = &show_table_header;
int const * const SHOW_DAYS = &show_days;
int const * const SHOW_TOTAL_COUNT = &show_total_count;
int const * const SHOW_DATE = &show_date;
int const * const SHOW_REQUESTS = &show_requests;
int const * const SHOW_USERS = &show_users;
int const * const SHOW_IN_BYTES = &show_in_bytes;
int const * const SHOW_OUT_BYTES = &show_out_bytes;

void parseCommandLineArguments(int argc, char **argv)
{
	if (argv == NULL)
		return;

	char *arg;

	for (int i = 1; i < argc; i++)
	{
		if ((arg = argv[i]) == NULL)
			continue;

		if (strncasecmp(arg, "-r=", 3) == 0)
		{
			show_table_header = strchr(arg + 3, 'h') != NULL;
			show_days = strchr(arg + 3, 'd') != NULL;
			show_total_count = strchr(arg + 3, 't') != NULL;
		}
		else if (strncasecmp(arg, "-c=", 3) == 0)
		{
			show_date = strchr(arg + 3, 'd') != NULL;
			show_requests = strchr(arg + 3, 'r') != NULL;
			show_users = strchr(arg + 3, 'u') != NULL;
			show_in_bytes = strchr(arg + 3, 'i') != NULL;
			show_out_bytes = strchr(arg + 3, 'o') != NULL;
		}
		else if (strncasecmp(arg, "-m=", 3) == 0)
		{
			// TODO: let user choose with method is used for counting (avl-tree or hyperloglog)
		}

		// TODO: let user choose max_n_days
	}
}
