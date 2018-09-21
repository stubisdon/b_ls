/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:08:17 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/20 17:08:18 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void nodeDataCopy(node *dest, node *src)
{
    node *temp;

    temp = dest;
    temp->buf = src->buf;
    temp->sd = src->sd;
    temp->d_name = src->d_name;
    temp->perm = src->perm;
    temp->mode = src->mode;
    temp->size = src->size;
    temp->blocks = src->blocks;
    temp->mtime = src->mtime;
    temp->uid = src->uid;
    temp->gid = src->gid;
    temp->links = src->links;
    // temp->next = src->next;
}

static void nodeSwap(node *one, node *two)
{
    node *temp;

    temp = (node *)malloc(sizeof(node));
    nodeDataCopy(temp, one);
    nodeDataCopy(one, two);
    nodeDataCopy(two, temp);
}

node *time_sort(node *info, int is_asc)
{
    node    *b;
    node    *s;

    b = info;
    while (b != NULL)
    {
        s = info;
        while (s->next != NULL)
        {
            if (is_asc ? s->buf.st_mtime < s->next->buf.st_mtime : s->buf.st_mtime > s->next->buf.st_mtime)
                nodeSwap(s, s->next);
            if (s->buf.st_mtime == s->next->buf.st_mtime)
            {
                if (is_asc ? s->buf.st_mtimespec.tv_nsec < s->next->buf.st_mtimespec.tv_nsec : s->buf.st_mtimespec.tv_nsec < s->next->buf.st_mtimespec.tv_nsec)
                nodeSwap(s, s->next);
            }
            s = s->next;
        }
        b = b->next;
    }
    return (info);
}

node    *name_sort(node *info, int is_asc)
{
    node    *b;
    node    *s;
    b = info;
    while (b != NULL)
    {
        s = info;
        while (s->next != NULL)
        {
            if (is_asc ? strcmp(s->d_name, s->next->d_name) > 0 : strcmp(s->d_name, s->next->d_name) < 0)
                nodeSwap(s, s->next);
            s = s->next;
        }
        b = b->next;
    }
    return (info);
}
