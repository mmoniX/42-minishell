/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:03:53 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/13 12:40:42 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	if (n == 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*mem_al(int len)
{
	char	*tmp;

	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (tmp == (void *)0)
		return (0);
	tmp[0] = '0';
	return (tmp);
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*str;

	len = int_len(n);
	i = len - 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = mem_al(len);
	if (str == (void *)0)
		return (0);
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	while (n != 0)
	{
		str[i] = ((n % 10) + '0');
		n = n / 10;
		i--;
	}
	str[len] = '\0';
	return (str);
}

// int main()
// {
// 	int n = 0;
// 	char *val = ft_itoa(n);
// 	printf("%s\n", val);
// 	return (0);
// }