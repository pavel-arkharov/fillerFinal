/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:12:07 by parkharo          #+#    #+#             */
/*   Updated: 2022/09/27 20:43:59 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

unsigned long	ft_distance(t_vector pos1, t_vector pos2)
{
	return (ft_sqrt(ft_pow(pos1.x - pos2.x, 2) + ft_pow(pos1.y - pos2.y, 2)));
}

t_bool	update_board(int width, int height)
{
	t_vector				index;
	char					***board;
	char					*line;

	index.y = -1;
	board = get_board();
	if (get_next_line(STDIN_FILENO, &line) <= 0)
		return (false);
	ft_strdel(&line);
	if (!get_filler()->first)
		if (get_next_line(STDIN_FILENO, &line) <= 0)
			return (false);
	if (!get_filler()->first)
		ft_strdel(&line);
	while (++index.y < height)
	{
		index.x = -1;
		if (get_next_line(STDIN_FILENO, &line) <= 0)
			return (false);
		while (++index.x < width)
			(*board)[index.y][index.x] = line[4 + index.x];
		ft_strdel(&line);
	}
	get_filler()->first = false;
	return (true);
}

static t_vector	execute_p1(void)
{
	t_vector	pos;
	t_vector	*limit;
	t_filler	*filler;

	filler = get_filler();
	limit = get_dim();
	pos.y = -1;
	while (++pos.y < limit->y)
	{
		pos.x = -1;
		while (++pos.x < limit->x)
		{
			if (filler->board[pos.y][pos.x] == 'O'
			|| filler->board[pos.y][pos.x] == 'o')
				return (pos);
		}
	}
	return (pos);
}

static t_vector	execute_p2(void)
{
	t_vector	pos;
	t_filler	*filler;

	filler = get_filler();
	pos.y = get_dim()->y;
	while (--pos.y)
	{
		pos.x = get_dim()->x;
		while (--pos.x)
		{
			if (filler->board[pos.y][pos.x] == 'X'
			|| (filler->board[pos.y][pos.x]) == 'x')
				return (pos);
		}
	}
	return (pos);
}

t_vector	nearest_opponent(void)
{
	t_filler	*filler;

	filler = get_filler();
	if (filler->cpu == 'O')
		return (execute_p1());
	else
		return (execute_p2());
}
