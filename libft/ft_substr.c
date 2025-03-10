/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:01:34 by mmonika           #+#    #+#             */
/*   Updated: 2024/11/16 15:53:18 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*copy;

	i = 0;
	if (s == (void *)0)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == (void *)0)
		return (0);
	while (i < len)
	{
		copy[i] = s[start + i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

// #include <stdio.h>
// int main(void)
// {
// 	char const *s = "hihow are you.";
// 	char *val = ft_substr(s, 0, 3);
// 	printf("%s\n", val);	
// }