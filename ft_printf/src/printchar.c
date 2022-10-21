/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:36:23 by parkharo          #+#    #+#             */
/*   Updated: 2022/02/12 18:00:44 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	printchar(t_parse *parser)
{
	int		ret;
	char	charac;

	ret = 0;
	charac = va_arg(parser->args, int);
	if (!parser->negative_width)
	{
		while (--parser->width > 0)
			ret += write(1, " ", 1);
		return (ret += write(1, &charac, 1));
	}
	else
	{
		ret += write(1, &charac, 1);
		while (--parser->width > 0)
			ret += write(1, " ", 1);
	}
	return (ret);
}
