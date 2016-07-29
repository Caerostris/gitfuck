#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#include "bf.h"

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *entry;
	struct bf_state bf_state;

	if(argc < 2) {
		printf("Usage: %s <root folder>\n", argv[0]);
	}

	bf_state = bf_start(stdout);

	dir = opendir(argv[1]);
	while((entry = readdir(dir)) != NULL)
	{
		DIR *line;
		struct dirent *lineentry;
		short is_comment = 0;
		char *linetext;

		if(entry->d_namlen < 3 || entry->d_type != DT_DIR || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
		{
			continue;
		}

		chdir(argv[1]);
		line = opendir(entry->d_name);
		while((lineentry = readdir(line)) != NULL)
		{
			if(strcmp(lineentry->d_name, "..") == 0 || strcmp(lineentry->d_name, ".") == 0)
			{
				continue;
			}

			is_comment = 1;
			break;
		}
		chdir("..");

		if(is_comment)
		{
			continue;
		}

		linetext = entry->d_name;
		while(isalpha(*linetext))
		{
			linetext++;
		}
		bf_interpret(&bf_state, linetext);
	}
	bf_end(bf_state);
}
