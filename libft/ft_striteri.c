/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:05:05 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/12 20:22:29 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// void f(unsigned int i, char *c)
// {
// 	*c = *c + i;
// }
// int main()
// {
// 	char s[] = "abcde";
// 	ft_striteri(s, f);
// 	printf("%s\n", s);
// 	return(0);
// }