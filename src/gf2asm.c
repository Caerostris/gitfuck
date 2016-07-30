#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "bf.h"

int8_t is_parent_folder(char *d_name);

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *entry;
	struct bf_state bf_state;

	if(argc < 2) {
		fprintf(stderr, "Usage: %s <root folder>\n", argv[0]);
		return 1;
	}

	bf_state = bf_start(stdout);

	dir = opendir(argv[1]);
	while((entry = readdir(dir)) != NULL)
	{
		DIR *line;
		struct dirent *lineentry;
		short is_comment = 0;
		char *linetext;

		// skip files, short directory names, . and ..
		if(entry->d_namlen < 3 ||
			entry->d_type != DT_DIR ||
			is_parent_folder(entry->d_name))
		{
			continue;
		}

		// check if this line is a comment
		chdir(argv[1]);
		line = opendir(entry->d_name);
		while((lineentry = readdir(line)) != NULL)
		{
			if(!is_parent_folder(lineentry->d_name))
			{
				is_comment = 1;
				break;
			}

		}
		chdir("..");

		// skip comments
		if(is_comment)
		{
			continue;
		}

		// skip leading alphanums
		linetext = entry->d_name;
		while(isalnum(*linetext))
		{
			linetext++;
		}

		// interpret brainfuck line
		bf_interpret(&bf_state, linetext);
	}
	bf_end(bf_state);
}

int8_t is_parent_folder(char *d_name)
{
	return strcmp(d_name, "..") == 0 || strcmp(d_name, ".") == 0;
}
