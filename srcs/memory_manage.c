/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekang <gekang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 13:45:16 by donghwki          #+#    #+#             */
/*   Updated: 2020/07/19 17:59:32 by gekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_02.h"
#include <stdlib.h>

void	free_key(t_dict *dict)
{
	int i;

	i = 0 - 1;
	while (++i < dict->size)
		free(dict->key[i]);
	free(dict->key);
}

void	free_value(t_dict *dict)
{
	int i;

	i = 0 - 1;
	while (++i < dict->size)
		free(dict->value[i]);
	free(dict->value);
}

void	free_dict(t_dict *dict)
{
	if (g_flag & 0x10)
		return ;
	if (!(g_flag & 0x20))
		free_key(dict);
	if (!(g_flag & 0x40))
		free_value(dict);
	free(dict);
}

void	free_dict_split(char **split, int size)
{
	int i;

	i = 0 - 1;
	while (++i < size)
	{
		free(split[i]);
	}
	free(split);
}
