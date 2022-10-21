/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:55:30 by parkharo          #+#    #+#             */
/*   Updated: 2022/09/29 18:16:10 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"		

static t_bool	init_players(void)
{
	char		*line;
	t_filler	*filler;

	filler = get_filler();
	if (get_next_line(STDIN_FILENO, &line) <= 0)
		return (false);
	if (ft_strstr(line, "p1"))
	{
		filler->cpu = 'X';
		filler->player = 'O';
	}
	else if (ft_strstr(line, "p2"))
	{
		filler->cpu = 'O';
		filler->player = 'X';
	}
	else
		return (false);
	ft_strdel(&line);
	return (true);
}

static t_bool	init_board(void)
{
	int			index;
	t_filler	*filler;

	filler = get_filler();
	filler->board = (char **)ft_memalloc(sizeof(char *) * (filler->dim.y + 1));
	if (!filler->board)
		return (false);
	index = 0;
	while (index <= filler->dim.y)
	{
		filler->board[index] = ft_strnew(filler->dim.x);
		if (!filler->board[index])
			return (false);
		index++;
	}
	filler->first = true;
	return (true);
}

static	t_bool	init_dim(void)
{
	char		*line;
	char		*tmp;
	t_vector	*dim;

	dim = get_dim();
	if (get_next_line(0, &line) <= 0)
		return (false);
	if (!line)
		return (false);
	tmp = line;
	while (*line && !ft_isdigit(*line))
		line++;
	dim->y = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line)
		dim->x = ft_atoi(++line);
	else
		dim->x = 0;
	if (!dim->x || !dim->y)
		return (false);
	ft_strdel(&tmp);
	return (true);
}

t_bool	init(void)
{
	return (init_players() && init_dim() && init_board());
}
