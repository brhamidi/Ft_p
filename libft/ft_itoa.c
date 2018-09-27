/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:48:20 by bhamidi           #+#    #+#             */
/*   Updated: 2017/03/19 14:11:25 by bhamidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_get_nb_octet(int *nb_bytes, int *is_neg, long int n)
{
	if (n < 0)
	{
		*is_neg = 1;
		n = n * -1;
	}
	while (n != 0)
	{
		if (n < 10)
		{
			*nb_bytes = *nb_bytes + 1;
			return ;
		}
		else
		{
			*nb_bytes = *nb_bytes + 1;
			n = n / 10;
		}
	}
}

static void		ft_fill_str(char *str, long int n, int *index)
{
	if (n < 0)
		n = n * -1;
	if (n >= 10)
	{
		ft_fill_str(str, n % 10, index);
		ft_fill_str(str, n / 10, index);
	}
	else
	{
		str[*index] = n + 48;
		*index = *index + 1;
	}
}

char			*ft_itoa(int n)
{
	int		nb_bytes;
	int		is_neg;
	char	*result;
	int		i;

	i = 0;
	is_neg = 0;
	nb_bytes = 0;
	ft_get_nb_octet(&nb_bytes, &is_neg, (long int)n);
	if (nb_bytes == 0)
	{
		result = ft_strdup("0");
		return (result);
	}
	if (is_neg == 1)
		nb_bytes++;
	if (!(result = ft_strnew(sizeof(char) * (nb_bytes + 1))))
		return (NULL);
	ft_fill_str(result, (long int)n, &i);
	if (is_neg == 1)
		result[nb_bytes - 1] = '-';
	result[nb_bytes] = '\0';
	ft_strrev(result);
	return (result);
}
