/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sounania <sounania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:35:10 by sounania          #+#    #+#             */
/*   Updated: 2026/02/06 09:29:00 by sounania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isalnum(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static int	count_digits(int n)
{
	int	len;
	int	temp;
	int	sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	temp = n * sign;
	len = 0;
	if (n <= 0)
		return (1);
	while (temp > 0)
	{
		len++;
		temp /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		temp;
	int		sign;
	int		offset;

	sign = 1;
	if (n < 0)
		sign = -1;
	len = count_digits(n);
	offset = (sign < 0);
	str = malloc(len + offset + 1);
	if (!str)
		return (NULL);
	str[len + offset] = '\0';
	if (sign < 0)
		str[0] = '-';
	temp = n * sign;
	while (len-- > 0)
	{
		str[len + offset] = (temp % 10) + '0';
		temp /= 10;
	}
	return (str);
}
