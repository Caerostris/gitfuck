#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "bf.h"
#include "gf2asm.h"

int8_t is_parent_folder(char *d_name);
int gf_line_compare(const void *line1, const void *line2);

int main(int argc, char *argv[])
{
	DIR *dir;
	FILE *out;
	struct dirent *entry;
	struct bf_state bf_state;
	struct array gf_program = array_create(sizeof(struct gf_line));

	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s <root folder>\n", argv[0]);
		return 1;
	}
	else if(argc == 2)
	{
		out = stdout;
	}
	else
	{
		out = fopen(argv[2], "w+");
		if(out == NULL)
		{
			perror(argv[2]);
			return 1;
		}
	}

	dir = opendir(argv[1]);
	while((entry = readdir(dir)) != NULL)
	{
		DIR *dir_line;
		struct dirent *lineentry;
		short is_comment = 0;
		struct gf_line line;
		struct stat line_stat;

		// skip files, . and ..
		if(entry->d_type != DT_DIR ||
			is_parent_folder(entry->d_name))
		{
			continue;
		}

		// check if this line is a comment
		chdir(argv[1]);
		dir_line = opendir(entry->d_name);
		while((lineentry = readdir(dir_line)) != NULL)
		{
			if(!is_parent_folder(lineentry->d_name))
			{
				is_comment = 1;
				break;
			}

		}
		stat(entry->d_name, &line_stat);
		chdir("..");

		// skip comments
		if(is_comment)
		{
			continue;
		}

		// interpret brainfuck line
		strncpy(line.text, entry->d_name, GF_LINE_MAX);
		line.timespec = line_stat.st_mtimespec;
		array_push(&gf_program, &line);
	}

	qsort(gf_program.values, array_size(&gf_program), sizeof(struct gf_line), gf_line_compare);

	bf_state = bf_start(out);
	for(unsigned int i = 0; i < array_size(&gf_program); i++)
	{
		struct gf_line line;
		array_get(&gf_program, i, &line);
		bf_interpret(&bf_state, line.text);
	}
	bf_end(bf_state);
	fclose(out);
}

int8_t is_parent_folder(char *d_name)
{
	return strcmp(d_name, "..") == 0 || strcmp(d_name, ".") == 0;
}

int gf_line_compare(const void *line1, const void *line2)
{
	const struct gf_line *l1 = line1, *l2 = line2;
	return l1->timespec.tv_sec - l2->timespec.tv_sec;
}
