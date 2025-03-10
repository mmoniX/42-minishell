/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:33:15 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/09 20:53:23 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = 0;
	src_len = ft_strlen(src);
	while (dest[dest_len] != '\0' && dest_len < n)
		dest_len++;
	if (dest_len == n)
		return (n + src_len);
	while (src[i] != '\0' && i < (n - dest_len - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if ((dest_len + i) < n)
		dest[dest_len + i] = '\0';
	else if (n > 0)
		dest[n - 1] = '\0';
	return (dest_len + src_len);
}

// int main() 
// {
//     char src[] = "This is";
//     char dest[20];
//     size_t n = 5;
//     int func = ft_strlcat(dest, src, n);
//     int lib = strlcat(dest, src, n);
// 	printf("function: %i\nlibrary: %i\n", func, lib);
// 	return(0);
// }