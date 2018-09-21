/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:02:43 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/20 17:02:46 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_mode(mode_t mode)
{
	const char	chars[] = "rwxrwxrwx";
	char		buf[10];
	size_t		i;

	i = 0;
	while (i < 9)
	{
		buf[i] = (mode & (1 << (8 - i))) ? chars[i] : '-';
		i++;
	}
	buf[9] = '\0';
	printf("%s ", buf);
}
//
// void			select_type(mode_t mode, char *c)
// {
// 	if ((mode & S_IFREG) == S_IFREG)
// 		*c = '-';
// 	if ((mode & S_IFDIR) == S_IFDIR)
// 		*c = 'd';
// 	if ((mode & S_IFCHR) == S_IFCHR)
// 		*c = 'c';
// 	if ((mode & S_IFBLK) == S_IFBLK)
// 		*c = 'b';
// 	if ((mode & S_IFLNK) == S_IFLNK)
// 		*c = 'l';
// 	if ((mode & S_IFSOCK) == S_IFSOCK)
// 		*c = 's';
// 	if ((mode & S_IFIFO) == S_IFIFO)
// 		*c = 'p';
// }

node    *createEmptyList(node *info)
{
    info = (node *)malloc(sizeof(node));

    info->d_name = NULL;
    info->perm = 0;
    info->mode = NULL;
    info->size = 0;
    info->blocks = 0;
    info->mtime = NULL;
    info->uid = NULL;
    info->gid = NULL;
    info->links = 0;
    info->next = NULL;

    return (info);
}

void appendToList(node *info, struct dirent sd, struct stat buf)
{
    node *temp = NULL;

    while(info->next != NULL)
        info = info->next;
    temp = (node *)malloc(sizeof(node));
    temp->buf = buf;
    temp->sd = sd;
    temp->d_name = strdup(sd.d_name);
    temp->perm = buf.st_mode;
    temp->mode = (char *)malloc(sizeof(char) * 12);
    strmode(temp->perm, temp->mode);
    temp->size = buf.st_size;
    temp->mtime = strdup(ctime(&buf.st_mtime) + 4);
    temp->uid = getpwuid(buf.st_uid)->pw_name;
    temp->gid = getgrgid(buf.st_gid)->gr_name;
    temp->blocks = buf.st_blocks;
    temp->links = buf.st_nlink;
    temp->next = NULL;
    info->next = temp;

    // sd->d_name, buf.st_mode, ctime(&buf.st_mtime),
    //  getpwuid(buf.st_uid)->pw_name, getgrgid(buf.st_gid)->gr_name,
    //   buf.st_nlink, buf.st_size, buf.st_blocks
}


void listDir(node *info, int flags[4])
{
    long long blocks;
    node    *temp;

    temp = info;
    info = info->next;
    info = name_sort(info, 1);
    if (flags[l] < 1 && flags[a] < 1 && flags[t] < 1 && flags[r] < 1)
    {
        while (info != NULL)
        {
            if (info->d_name[0] != '.')
                printf("%s\n", info->d_name);
            info = info->next;
        }
    }
    if (flags[l] == 1 && flags[a] == 1 && flags[t] == 0 && flags[r] == 0)
    {
        info = temp;
        blocks = 0;
        while (info != NULL)
        {
            blocks += info->blocks;
            info = info->next;
        }
        printf("total %lld\n", blocks);
        info = temp;
        info = info->next;
        info = name_sort(info, 1);
        while (info != NULL)
        {
            // printf("%4s", info->mode);
            print_mode(info->perm);
            printf("%3u ", info->links);
            printf("%s  ", info->uid);
            printf("%s ", info->gid);
            printf("%6lld ", info->size);
            printf("%.12s ", info->mtime);
            printf("%s\n", info->d_name);
            info = info->next;
        }
    }
    if (flags[l] == 1 && flags[a] == 1 && flags[t] == 1 && flags[r] == 0)
    {
        info = temp;
        blocks = 0;
        while (info != NULL)
        {
            blocks += info->blocks;
            info = info->next;
        }
        printf("total %lld\n", blocks);
        info = temp;
        info = info->next;
        info = name_sort(info, 1);
        info = time_sort(info, 1);
        while (info != NULL)
        {
            printf("%4s", info->mode);
            printf("%3u ", info->links);
            printf("%s  ", info->uid);
            printf("%s ", info->gid);
            printf("%6lld ", info->size);
            printf("%.12s ", info->mtime);
            printf("%s\n", info->d_name);
            info = info->next;
        }
    }
}
