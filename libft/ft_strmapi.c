/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:23:29 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/12 20:25:06 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*str;

	i = 0;
	len = ft_strlen(s);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == (void *)0)
		return (0);
	while (i < len)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// char f(unsigned int i, char c)
// {
// 	return (c + i);
// }
// int main()
// {
// 	char *s = "abcd";
// 	char *res = ft_strmapi(s, *f);
// 	printf("%s\n", res);
// 	return(0);
// }