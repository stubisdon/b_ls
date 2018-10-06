/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_ls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 13:01:23 by exam              #+#    #+#             */
/*   Updated: 2018/10/03 13:01:33 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>

// declare a struct with 3 items:

typedef struct 		s_list
{
	struct stat		buf; // (1) buf with "man 2 stat" data
	char 			*name; // (2) the name of the file (sd->d_name)
	struct s_list	*next; // (3) a pointer to the next item.
}					node;

// enums for something like flags[l] == 1

enum flags
{
	l,
	a,
	t,
	r
};

// I create the HEAD of the linked list as an empty "node"

node *createEmpty(node *info)
{
	info = (node *)malloc(sizeof(node));
	info->name = NULL; // set a pointer to NULL to prevent SEGFAULT
	info->next = NULL; // set a pointer to NULL to prevent SEGFAULT

	return (info);
}

void appendToList(node *info, char *name, struct stat buf)
{
	node *temp;
	temp = (node *)malloc(sizeof(node));
	temp->name = name;
	temp->buf = buf;
	temp->next = NULL;
	while (info->next != NULL) // this loop puts us to the end of linked list
		info = info->next;
	info->next = temp; // this line appends the temp node to the end of a list
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void copyData(node *src, node *dst)
{
	node *temp;
	temp = dst;
	temp->name = src->name;
	temp->buf = src->buf;
}

void nodeSwap(node *one, node *two)
{
	node *temp;
	temp = (node *)malloc(sizeof(node));
	copyData(one, temp);
	copyData(two, one);
	copyData(temp, two);
}

node *sortName(node *info, int is_asc)
{
	node *b;
	node *s;

	b = info;
	while (b != NULL)
	{
		s = info;
		while (s->next != NULL)
		{
			if (is_asc ? ft_strcmp(s->name, s->next->name) < 0 :
					ft_strcmp(s->name, s->next->name) > 0)
				nodeSwap(s, s->next);
			s = s->next;
		}
		b = b->next;
	}
	return (info);
}

node *sortTime(node *info, int is_asc)
{
	node *b;
	node *s;

	b = info;
	while (b != NULL)
	{
		s = info;
		while (s->next != NULL)
		{
			if (is_asc ? s->buf.st_mtime > s->next->buf.st_mtime : s->buf.st_mtime < s->next->buf.st_mtime)
				nodeSwap(s, s->next);
			if (s->buf.st_mtime == s->next->buf.st_mtime)
				if (is_asc ? s->buf.st_mtimespec.tv_nsec > s->next->buf.st_mtimespec.tv_nsec  : s->buf.st_mtimespec.tv_nsec < s->next->buf.st_mtimespec.tv_nsec)
					nodeSwap(s, s->next);
			s = s->next;
		}
		b = b->next;
	}
	return (info);
}

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char *ft_strjoin(char *str1, char *str2)
{
	char *temp;
	int i = 0;
	int j = 0;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 2));
	while (str1[i] != '\0')
	{
		temp[i] = str1[i];
		i++;
	}
	temp[i] = '/';
	i++;
	while (str2[j] != '\0')
	{
		temp[i] = str2[j];
		i++;
		j++;
	}
	temp[i] = '\0';
	return (temp);
}

// openFile function would read from a folder or a file

node *openFile(node *info, char *path)
{
	DIR				*dir;
	struct dirent 	*sd;
	struct stat		buf;

	info = createEmpty(info);
	dir = opendir(path);
	if (dir == NULL)
	{
		lstat(path, &buf);
		if ((buf.st_mode & S_IFREG) == S_IFREG) // checking if it's a file
			appendToList(info, path, buf);
		else
			printf("ls: %s: No such file or directory\n", path);
	}
	else
	{
		while ((sd = readdir(dir)) != NULL)
		{
			lstat(ft_strjoin(path, sd->d_name), &buf); // ft_strjoin to read from any other folder
			appendToList(info, sd->d_name, buf);
		}
	}
	return (info);

}

void print_mode(mode_t mode)
{
	static char buf[] = "rwxrwxrwx";
	static char temp[10]; // create a temp string of 9 chars + '\0'
	size_t i = 0; // i for a loop

	while (i < 9)
	{
		temp[i] = (mode & (1 << (8 - i))) ? buf[i] : '-'; // magic bitcycle
		i++;
	}
	temp[9] = '\0';
	printf("%s ", temp);
}

void select_mode(mode_t mode, char *c)
{
	if ((mode & S_IFDIR) == S_IFDIR)
		*c = 'd';
	if ((mode & S_IFCHR) == S_IFCHR)
		*c = 'c';
	if ((mode & S_IFIFO) == S_IFIFO)
		*c = 'p';
	if ((mode & S_IFBLK) == S_IFBLK)
		*c = 'b';
	if ((mode & S_IFREG) == S_IFREG)
		*c = '-';
	if ((mode & S_IFLNK) == S_IFLNK)
		*c = 'l';
	if ((mode & S_IFSOCK) == S_IFSOCK)
		*c = 's';
}

void printList(node *info, int flags[4])
{
	node *temp;
	int rev = 0;
	temp = info;
	char c;
	long long blocks = 0;

	info = info->next;
	while (info != NULL)
	{
		blocks += info->buf.st_blocks;
		info = info->next;
	}
	info = temp;
	info = info->next;
	if (flags[r] == 1)
		rev = 1;
	info = sortName(info, rev);
	if (flags[t] == 1)
		info = sortTime(info, rev);
	if (flags[a] == 1 && flags[l] == 1)
	{
		if ((info->buf.st_mode & S_IFDIR) == S_IFDIR)
		{
			printf("%s:\n", info->name);
			printf("total %lld\n", blocks);
		}
		while (info != NULL)
		{
			select_mode(info->buf.st_mode, &c); // selects 1 char for a file type
			printf("%c", c);
			print_mode(info->buf.st_mode); // prints 'rwxrwxrwx' == permissions
			printf("%4i ", info->buf.st_nlink); // get st_nlink and print it
			printf("%-6s ", getpwuid(info->buf.st_uid)->pw_name); // print user
			printf("%-12s ", getgrgid(info->buf.st_gid)->gr_name); //print group
			printf("%6lld ", info->buf.st_size); // print size as long long
			printf("%.12s ", ctime(&info->buf.st_mtime) + 4);
			printf("%s\n", info->name);
			info = info->next;
		}
	}
	if (flags[a] != 1 && flags[l] == 1)
	{
		blocks = 0;
		while (info != NULL)
		{
			if (info->name[0] != '.')
				blocks += info->buf.st_blocks;
			info = info->next;
		}
		info = temp;
		info = info->next;
		if ((info->buf.st_mode & S_IFDIR) == S_IFDIR)
		{
			printf("%s:\n", info->name);
			printf("total %lld\n", blocks);
		}
		while (info != NULL)
		{
			if (info->name[0] != '.')
			{
				select_mode(info->buf.st_mode, &c);
				printf("%c", c);
				print_mode(info->buf.st_mode);
				printf("%4i ", info->buf.st_nlink);
				printf("%-6s ", getpwuid(info->buf.st_uid)->pw_name);
				printf("%-12s ", getgrgid(info->buf.st_gid)->gr_name);
				printf("%6lld ", info->buf.st_size);
				printf("%.12s ", ctime(&info->buf.st_mtime) + 4);
				printf("%s\n", info->name);
			}
			info = info->next;
		}
	}
	if (flags[a] == 1 && flags[l] != 1)
	{
		while (info != NULL)
		{
			printf("%s\n", info->name);
			info = info->next;
		}
	}
	if (flags[a] != 1 && flags[l] != 1)
	{
		while (info != NULL)
		{
			if (info->name[0] != '.')
			{
				printf("%s\n", info->name);
			}
			info = info->next;
		}
	}
}

void initFlags(int flags[4])
{
	int i = 0;
	while (i < 4)
	{
		flags[i] = -1;
		i++;
	}
}

void getFlags(char *str, int flags[4])
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == 'l')
			flags[l] = 1;
		if (str[i] == 'a')
			flags[a] = 1;
		if (str[i] == 't')
			flags[t] = 1;
		if (str[i] == 'r')
			flags[r] = 1;
		i++;
	}
}

int main (int argc, char **argv)
{
	node *info;
	char *path;
	int	flags[4];
	int read = 0;
	int i = 1;

	info = NULL;
	initFlags(flags);
	if (argc == 1)
	{
		path = ".";
		info = openFile(info, path);
		printList(info, flags);
	}
	if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			path = ".";
			getFlags(&argv[1][1], flags);
			info = openFile(info, path);
			printList(info, flags);
		}
		else
		{
			info = openFile(info, argv[1]);
			printList(info, flags);
		}
	}
	else
	{
		while (i < argc)
		{
			if (argv[i][0] == '-' && read == 0)
			{
				getFlags(&argv[i][1], flags);
				i++;
			}
//			if (argv[i][0] == '-' && read == 1)
//			{
//				printf("ls: %s: No such file or directory\n", argv[i]);
//			}
			if (argv[i][1] != '-')
			{
				path = argv[i];
				info = openFile(info, path);
				printList(info, flags);
				read = 1;
			}
			i++;
			printf("\n");
		}
	}
//	printf("flags: l = %d, a = %d, t = %d, r = %d\n", flags[l], flags[a], flags[t], flags[r]);
	return (0);
}

