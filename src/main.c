/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:23:24 by parkharo          #+#    #+#             */
/*   Updated: 2022/10/21 18:29:30 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	play_p1(t_vector pos, t_piece piece)
{
	unsigned char	index;
	t_vector		curr;	
	char			**board;

	board = *get_board();
	pos.y = -1;
	while (++pos.y < get_dim()->y)
	{
		pos.x = -1;
		while (++pos.x < get_dim()->x)
		{
			if (is_ours(board[pos.y][pos.x]))
			{
				index = -1;
				while (++index < piece.count)
				{
					curr.x = pos.x - piece.snippet[index].x;
					curr.y = pos.y - piece.snippet[index].y;
					update_result(piece, curr);
				}
			}
		}
	}
}

static void	play_p2(t_vector pos, t_piece piece)
{
	unsigned char	index;
	t_vector		curr;
	char			**board;

	board = *get_board();
	pos.y = get_dim()->y;
	while (--pos.y)
	{
		pos.x = get_dim()->x;
		while (--pos.x)
		{
			if (is_ours(board[pos.y][pos.x]))
			{
				index = -1;
				while (++index < piece.count)
				{
					curr.x = pos.x - piece.snippet[index].x;
					curr.y = pos.y - piece.snippet[index].y;
					update_result(piece, curr);
				}
			}
		}
	}
}

static void	play_move(t_piece piece)
{
	t_vector		pos;

	pos.x = 0;
	pos.y = 0;
	if (get_filler()->cpu == 'X')
		play_p1(pos, piece);
	else
		play_p2(pos, piece);
}

int	main(void)
{
	t_piece		piece;
	t_result	*move;

	if (!init())
		return (1);
	while (1)
	{
		if (!update_board(get_dim()->x, get_dim()->y))
			return (1);
		if (!update_piece(&piece))
			return (1);
		move = get_result();
		move->position.x = 0;
		move->position.y = 0;
		move->block = 0;
		move->distance = 255;
		play_move(piece);
		ft_printf("%d %d\n", move->position.y, move->position.x);
	}
	return (0);
}
