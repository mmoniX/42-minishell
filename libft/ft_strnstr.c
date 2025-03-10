/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:59:40 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/10 13:58:02 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *point, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (point[i] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < n)
	{
		j = 0;
		while ((str[i + j] == point[j]) && (i + j) < n)
		{
			if (point[j + 1] == '\0')
				return ((char *)(str + i));
			j++;
		}
		i++;
	}
	return (0);
}

// int main(void)
// {
//     char haystack[] = "Find me if you can";
//     char needle[12];
//     char *func = ft_strnstr(haystack, needle, 15);
//     char *lib = strnstr(haystack, needle, 15);
// 	printf("function: %s\nlibrary: %s\n", func, lib);
//     return 0;
// }
