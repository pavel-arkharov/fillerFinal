/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:04:20 by parkharo          #+#    #+#             */
/*   Updated: 2022/09/29 08:26:57 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "ft_printf.h"

typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct s_piece
{
	char			**shape;
	unsigned char	count;
	t_vector		*snippet;
	t_vector		origin;
	t_vector		len;
}				t_piece;

typedef struct s_result
{
	t_vector		position;
	unsigned char	block;
	unsigned char	distance;
}				t_result;

typedef struct s_filler
{
	char		cpu;
	char		player;
	char		**board;
	t_vector	dim;
	t_result	result;
	t_bool		first;
}				t_filler;

/* Singleton class 'object' accessor */
t_filler		*get_filler(void);

/* Object's members accessors */
char			***get_board(void);
t_vector		*get_dim(void);
t_result		*get_result(void);

/* Game steps functions */
t_bool			init(void);
t_bool			update_board(int width, int height);
t_bool			update_piece(t_piece *piece);
t_vector		nearest_opponent(void);
t_bool			is_ours(char c);
void			update_result(t_piece piece, t_vector curr);

/* Math function that could be migrated to libft */
unsigned long	ft_distance(t_vector pos1, t_vector pos2);

#endif