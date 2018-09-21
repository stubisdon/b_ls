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

// void			print_mode(mode_t mode)
// {
// 	const char	chars[] = "rwxrwxrwx";
// 	char		buf[10];
// 	size_t		i;
//
// 	i = 0;
// 	while (i < 9)
// 	{
// 		buf[i] = (mode & (1 << (8 - i))) ? chars[i] : '-';
// 		i++;
// 	}
// 	buf[9] = '\0';
// 	ft_printf("%s ", buf);
// }
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

void appendToList(node *info, char *data, int perm, char *mtime, char *uid, char *gid, unsigned int links, long long size, long long blocks)
{
    node *temp = NULL;

    while(info->next != NULL)
        info = info->next;
    temp = (node *)malloc(sizeof(node));
    temp->d_name = strdup(data);
    temp->perm = perm;
    temp->mode = (char *)malloc(sizeof(char) * 12);
    strmode(temp->perm, temp->mode);
    temp->size = size;
    temp->mtime = strdup(mtime + 4);
    temp->uid = uid;
    temp->gid = gid;
    temp->blocks = blocks;
    temp->links = links;
    temp->next = NULL;
    info->next = temp;
}


void listDir(node *info, int flags[4])
{
    long long blocks;
    node    *temp;

    temp = info;
    info = info->next;
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
