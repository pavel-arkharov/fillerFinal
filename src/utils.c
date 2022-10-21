/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:10:30 by parkharo          #+#    #+#             */
/*   Updated: 2022/10/03 12:30:17 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_filler	*get_filler(void)
{
	static t_filler	filler;

	return (&filler);
}

char	***get_board(void)
{
	t_filler	*filler;

	filler = get_filler();
	return (&filler->board);
}

t_vector	*get_dim(void)
{
	t_filler	*filler;

	filler = get_filler();
	return (&filler->dim);
}

t_result	*get_result(void)
{
	t_filler	*filler;

	filler = get_filler();
	return (&filler->result);
}
