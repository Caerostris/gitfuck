#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>

void gf_write_line(char *basedir, unsigned int line, char *text);
int isbf(int c);

int main(int argc, char *argv[])
{
	FILE *fp;
	int c;
	unsigned int line = 0, buflen = 5, ctr = 0;
	char text[buflen];

	if(argc < 3)
	{
		printf("Usage: %s <infile> <outfolder>\n", argv[0]);
	}

	fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		perror(argv[1]);
		fclose(fp);
		return 1;
	}

	if(mkdir(argv[2], 600) != 0)
	{
		perror(argv[2]);
		fclose(fp);
		return 1;
	}

	text[ctr++] = '0';
	while((c = fgetc(fp)) != EOF)
	{
		if(!isalnum(c) && !isbf(c))
		{
			continue;
		}

		if(ctr >= sizeof(text) - 1)
		{
			text[sizeof(text) - 1] = '\0';
			gf_write_line(argv[2], line++, text);
			ctr = snprintf(text, buflen, "%u", line);
			continue;
		}

		text[ctr++] = c;
	}

	if(ctr > 0) {
		text[ctr] = '\0';
		gf_write_line(argv[2], line++, text);
	}

	fclose(fp);
}

void gf_write_line(char *basedir, unsigned int line, char *text)
{
	int len = strlen(basedir) + strlen(text) + 2;
	char buf[len];
	struct timeval times[2];
	snprintf(buf, len, "%s/%s", basedir, text);

	if(mkdir(buf, atoi("0700")) != 0)
	{
		perror(buf);
	}

	times[0].tv_sec = time(NULL);
	times[0].tv_usec = 0;
	times[1].tv_sec = line;
	times[1].tv_usec = 0;
	utimes(buf, times);
}

int isbf(int c)
{
	char ch = c;
	return ch == '.' || ch == ',' || ch == '[' || ch == ']' || ch == '+' || ch == '-' || ch == '>' || ch == '<';
}
