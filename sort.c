temp/* ************************************************************************** */
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
    temp->d_name = src->d_name;
    temp->perm = src->perm;
    temp->mode = src->mode;
    temp->size = src->size;
    temp->blocks = src->blocks;
    temp->mtime = src->mtime;
    temp->uid = src->uid;
    temp->gid = src->gid;
    temp->links = src->links;
    temp->next = src->next;
}

static void nodeSwap(node *one, node *two)
{
    node temp;

    temp = one;
    nodeDataCopy(one, two);
    nodeDataCopy(two, temp);
}

node *time_sort(node *info)
{
    node    *b;
    node    *s;

    b = info;
    while (b != NULL)
    {
        s = info;
        while (s->next != NULL)
        {
            if (s->)
        }
    }
}
