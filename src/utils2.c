/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:10:58 by parkharo          #+#    #+#             */
/*   Updated: 2022/09/29 08:26:52 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	valid_pos(t_piece piece, t_vector pos)
{
	char			**board;
	unsigned char	index;
	t_vector		curr;
	int				used;

	board = *get_board();
	index = -1;
	used = 0;
	while (++index < piece.count)
	{
		curr.x = pos.x + piece.snippet[index].x;
		curr.y = pos.y + piece.snippet[index].y;
		if (curr.x < 0 || curr.y < 0
			|| curr.x >= get_dim()->x
			|| curr.y >= get_dim()->y)
			return (0);
		if (board[curr.y][curr.x] != '.')
			used++;
		if (used > 1)
			return (0);
	}
	return (1);
}

static void	update_count(unsigned char *count, char c, char c2, t_vector curr)
{	
	char	**b;

	b = *get_board();
	*count += (b[curr.y][curr.x + 1] == c || b[curr.y][curr.x + 1] == c2)
		+ (b[curr.y][curr.x - 1] == c || b[curr.y][curr.x - 1] == c2)
		+ (b[curr.y + 1][curr.x] == c || b[curr.y + 1][curr.x] == c2)
		+ (b[curr.y - 1][curr.x] == c || b[curr.y - 1][curr.x] == c2);
}

static unsigned char	count_block(t_piece piece,
	t_vector pos, char c, char c2)
{
	unsigned char	count;
	unsigned char	index;
	t_vector		curr;

	index = -1;
	count = 0;
	while (++index < piece.count)
	{
		curr.x = pos.x + piece.snippet[index].x;
		curr.y = pos.y + piece.snippet[index].y;
		if (curr.x + 1 >= get_dim()->x || curr.y + 1 >= get_dim()->y
			|| curr.x - 1 < 0 || curr.y - 1 < 0)
			return (0);
		update_count(&count, c, c2, curr);
	}
	return (count);
}

void	update_result(t_piece piece, t_vector curr)
{
	t_result		*res;
	unsigned char	block;
	unsigned char	dis;
	t_filler		*filler;

	res = get_result();
	filler = get_filler();
	if (valid_pos(piece, curr))
	{
		block = count_block(piece, curr, filler->cpu, ft_tolower(filler->cpu));
		dis = ft_distance(curr, nearest_opponent());
		if (block > res->block)
		{
			res->block = block;
			res->position = curr;
		}
		else if (block == res->block && dis < res->distance)
		{
			res->distance = dis;
			res->position = curr;
		}
	}
}

t_bool	is_ours(char c)
{
	char	ours;

	ours = get_filler()->player;
	return (c == ours || c == ft_tolower(ours));
}
