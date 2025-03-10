/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:27:36 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/09 20:54:42 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (n < 1)
		return (len);
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

// int main() 
// {
//     char src[] = "This is";
//     char dest[20];
//     size_t n = 5;
//     int func = ft_strlcpy(dest, src, n);
//     int lib = strlcpy(dest, src, n);
// 	printf("function: %i\nlibrary: %i\n", func, lib);
// 	return(0);
// }