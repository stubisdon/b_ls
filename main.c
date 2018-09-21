/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 16:01:29 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/18 15:42:40 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void findFlags(int flags[4], char *str)
{
    int i;

    i = -1;
    while (++i < 4)
        flags[i] = 0;
    i = -1;
    while (++i < 4)
    {
        if (str[i] == 'l')
            flags[l] = 1;
        else if (str[i] == 'a')
            flags[a] = 1;
        else if (str[i] == 't')
            flags[t] = 1;
        else if (str[i] == 'r')
            flags[r] = 1;
    }
}

node *getDir(char *path, node *info)
{
    DIR             *dir;
    struct dirent   *sd;
    struct stat     buf;
    long long       count;

    count = 0;
    dir = opendir(path);
    if (dir == NULL)
    {
        printf("ls: %s: No such file or directory.\n", path);
        return NULL;
    }
    info = createEmptyList(info);
    while ((sd=readdir(dir)) != NULL)
    {
        stat(sd->d_name, &buf);
        appendToList(info, *sd, buf);
    }
    closedir(dir);
    return (info);
}

int main (int argc, char **argv)
{
    int             i;
    int             flags[4];
    node            *info;

    info = NULL;
    i = 1;
    if (argc == 1)
    {
        if ((info = getDir(".", info)) != NULL)
            listDir(info, flags);
    }
    else
    {
        if (argv[1][0] == '-')
        {
            findFlags(flags, &argv[1][1]);
            i++;
        }
        if (argc == 2)
        {
            if ((info = getDir(".", info)) != NULL)
                listDir(info, flags);
        }
        while (i < argc)
        {
            if ((info = getDir(argv[i], info)) != NULL)
            {
                printf("%s:\n", argv[i]);
                listDir(info, flags);
                printf("\n");
            }
            i++;
        }
    }
    return (0);
}
