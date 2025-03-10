/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:57:22 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/14 11:58:36 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	size_t	final_len;
	char	*final;

	i = 0;
	len = ft_strlen(s1);
	if (s1 == (void *)0 || set == (void *)0)
		return (0);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	while (len > i && ft_strchr(set, s1[len - 1]))
		len--;
	final_len = len - i + 1;
	final = (char *)malloc(final_len * sizeof(char));
	if (final == (void *)0)
		return (0);
	ft_strlcpy(final, s1 + i, final_len);
	return (final);
}

// int main()
// {
//     char const *s1 = "ababaaaMy name is Simonbbaaabba";
//     char const *set = "";
//     char *trimmed;
//     trimmed = ft_strtrim(s1, set);
//     if (trimmed)
//     {
//         printf("%s\n", trimmed);
//         free(trimmed);
//     }
//     return (0);
// }