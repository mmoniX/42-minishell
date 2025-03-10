/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:54:47 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/10 18:28:18 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(str + i));
	return (0);
}

// int main(void)
// {
//     char str[] = "hi there!";
//     int ch = 'i';
//     char *res = ft_strchr(str, ch);
//     printf("%s\n", res);
//     return (0);
// }