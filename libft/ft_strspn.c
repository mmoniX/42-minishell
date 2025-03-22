/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:11:43 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/22 16:12:15 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				break ;
			j++;
		}
		if (accept[j] == '\0')
			break ;
		i++;
	}
	return (i);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char *s = "zabcdef";
// 	char *accept = "abc";
// 	printf("custom: %lu\nmain: %lu\n", ft_strspn(s, accept), strspn(s, accept));
// 	return (0);
// }