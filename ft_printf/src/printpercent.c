/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printpercent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:06:22 by parkharo          #+#    #+#             */
/*   Updated: 2022/02/12 20:13:40 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	printpercent(t_parse *parser)
{
	int		ret;
	char	c;

	c = ' ';
	ret = 0;
	if (!parser->negative_width)
	{
		if (parser->zero_padding)
			c = '0';
		while (--parser->width > 0)
			ret += write(1, &c, 1);
		return (ret += write(1, "%", 1));
	}
	else
	{
		ret += write(1, "%", 1);
		while (--parser->width > 0)
			ret += write(1, &c, 1);
	}
	return (ret);
}
