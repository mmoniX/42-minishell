/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:37:37 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/14 11:57:27 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*concat;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	concat = (char *)malloc(len * sizeof(char));
	if (concat == (void *)0)
		return (0);
	while (s1[i] != '\0')
	{
		concat[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		concat[i + j] = s2[j];
		j++;
	}
	concat[i + j] = '\0';
	return (concat);
}

// #include <stdio.h>
// int main(void)
// {
// 	char const *s1 = "hi!";
// 	char const *s2 = "Monika";
// 	char *val = ft_strjoin(s1, s2);
// 	printf("%s\n", val);	
// }