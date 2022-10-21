/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:30:30 by parkharo          #+#    #+#             */
/*   Updated: 2022/03/15 16:46:14 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static	void	negativecase(t_parse *parser, size_t len, int *ret)
{
	while (parser->width > (int)len || (parser->width > parser->precision
			&& parser->precision != -1))
	{
		*ret += write (1, " ", 1);
		--parser->width;
	}
}

int	printstring(t_parse *parser)
{
	char	*str;
	int		ret;
	size_t	len;

	ret = 0;
	str = va_arg(parser->args, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (!parser->negative_width)
	{
		while (parser->width > (int)len || (parser->width > parser->precision
				&& parser->precision != -1))
		{
			ret += write (1, " ", 1);
			--parser->width;
		}
	}
	if (parser->precision == -1 || parser->precision >= (int)len)
		ret += write(1, str, len);
	else
		ret += write(1, str, parser->precision);
	if (parser->negative_width)
		negativecase(parser, len, &ret);
	return (ret);
}
