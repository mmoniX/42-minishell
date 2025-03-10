/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:15:00 by mmonika           #+#    #+#             */
/*   Updated: 2025/03/10 14:49:41 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// int main (void)
// {
//     char s1[] = "Gdi";
//     char s2[] = "gdhes";
//     int func = ft_strncmp(s1, s2, 2);
//     int lib = strncmp(s1, s2, 2);
// 	printf("function: %i\nlibrary: %i\n", func, lib);
// 	return(0);
// }