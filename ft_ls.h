/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:01:06 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/20 17:01:12 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h> // for printf()
# include <stdlib.h> // for exit()
# include <sys/stat.h> // for mtime and permissions
# include <sys/types.h> // for DIR
# include <time.h> // for ctime
# include <pwd.h> // for getpwuid()
# include <grp.h> // for getgrgid()
# include <dirent.h> // for opendir()
# include <string.h> // for strmode()

typedef struct      s_file
{
    struct stat     buf;
    int             perm;
    char            *mode;
    unsigned int    links;
    long long       size;
    long long       blocks;
    char            *uid;
    char            *gid;
    char            *mtime;
    char            *d_name;
    struct  s_file  *next;
}                   node;

enum flags
{
    l,
    a,
    t,
    r
};

void findFlags(int flags[4], char *str);
node *getDir(char *path, node *info);
node *createEmptyList(node *info);
void appendToList(node *info, char *data, int perm, char *mtime, char *uid, char *gid, unsigned int links, long long size, long long blocks);
void listDir(node *info, int flags[4]);

#endif
