/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:39:36 by parkharo          #+#    #+#             */
/*   Updated: 2022/10/21 18:25:33 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static t_bool	set_piece_len(t_piece *piece)
{
	char	*tmp;
	char	*line;

	if (get_next_line(STDIN_FILENO, &line) <= 0)
		return (false);
	if (!line)
		return (false);
	tmp = line;
	while (*line && !ft_isdigit(*line))
		line++;
	piece->len.y = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line)
		piece->len.x = ft_atoi(++line);
	else
		piece->len.x = 0;
	if (!piece->len.x || !piece->len.y)
		return (false);
	ft_strdel(&tmp);
	return (true);
}

static t_bool	set_piece_shape(t_piece *piece)
{
	char		*line;
	int			index;
	t_vector	pos;

	pos.y = -1;
	piece->shape = (char **)ft_memalloc(sizeof(char *) * (piece->len.y + 1));
	index = 0;
	piece->count = 0;
	while (index < piece->len.y)
	{
		if (get_next_line(STDIN_FILENO, &line) <= 0)
			return (false);
		piece->shape[index++] = ft_strdup(line);
		ft_strdel(&line);
	}
	while (++pos.y < piece->len.y)
	{
		pos.x = -1;
		while (++pos.x < piece->len.x)
		{
			if (piece->shape[pos.y][pos.x] == '*')
				piece->count++;
		}
	}
	return (true);
}

static t_vector	new_bound(void)
{
	t_vector	new;

	new.x = 0;
	new.y = 0;
	return (new);
}

static t_bool	set_piece_origin(t_piece *piece)
{
	t_vector		pos;
	t_vector		bound;
	unsigned char	index;

	bound = new_bound();
	pos.y = -1;
	index = 0;
	piece->snippet = (t_vector *)ft_memalloc(sizeof(t_vector) * piece->count);
	while (++pos.y < piece->len.y)
	{
		pos.x = -1;
		while (++pos.x < piece->len.x)
		{
			if (piece->shape[pos.y][pos.x] == '*')
			{
				piece->snippet[index++] = pos;
				if (pos.y < bound.y || bound.y == -1)
					bound.y = pos.y;
				if (pos.x < bound.x || bound.x == -1)
					bound.x = pos.x;
			}
		}
	}
	piece->origin = bound;
	return (true);
}

t_bool	update_piece(t_piece *piece)
{
	static int	first = 1;

	if (!set_piece_len(piece))
		return (false);
	if (!first && piece->shape)
		ft_tabdel(&(piece->shape));
	if (!first && piece->snippet)
		ft_memdel((void **)&(piece->snippet));
	if (!set_piece_shape(piece))
		return (false);
	if (!set_piece_origin(piece))
		return (false);
	first = 0;
	return (true);
}
