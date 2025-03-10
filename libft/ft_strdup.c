/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:35:38 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/14 11:54:13 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dup_s1;

	i = 0;
	dup_s1 = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (dup_s1 == (void *)0)
		return (0);
	while (s1[i] != '\0')
	{
		dup_s1[i] = s1[i];
		i++;
	}
	dup_s1[i] = '\0';
	return (dup_s1);
}

// int main()
// {
//     char src[] = "GeeksForGeeks";
//     char *func = ft_strdup(src);
//     char *lib = strdup(src);
//     printf("lib: %s\n", lib);
//     printf("func: %s\n", func);
//     return 0;
// }