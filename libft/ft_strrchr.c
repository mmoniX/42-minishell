/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:02:33 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/10 14:29:32 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	i = len;
	while (i > 0)
	{
		if (str[i - 1] == (char)c)
			return ((char *)(str + i - 1));
		i--;
	}
	if ((char)c == '\0')
		return ((char *)(str + len));
	return (0);
}

// int main(void)
// {
//     char str[] = "monika";
//     int ch = 'e';
//     char *res = ft_strrchr(str, ch);
//     printf("%s\n", res);
//     return (0);
// }