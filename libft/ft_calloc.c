/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:46:00 by mmonika           #+#    #+#             */
/*   Updated: 2024/10/14 11:54:46 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t n)
{
	size_t	i;
	char	*temp_var;
	size_t	total_size;

	i = 0;
	total_size = (count * n);
	temp_var = (char *)malloc(total_size * sizeof(char));
	if (temp_var == (void *)0)
		return (0);
	while (i < total_size)
	{
		temp_var[i] = 0;
		i++;
	}
	return (temp_var);
}

// int main() 
// {
//    int n = 5;
//    int *func;
//    int *lib;
//    func = (int*)ft_calloc(n, sizeof(int));
//    lib = (int*)calloc(n, sizeof(int));
//    if (func == NULL || lib == NULL)
//    {
//       fprintf(stderr, "Memory allocation failed!\n");
//       return 1;
//    }
//    printf("Function elements: ");
//    for (int i = 0; i < n; i++) 
//    {
//       printf("%d ", func[i]);
//    }
//    printf("\n");
//    printf("Library elements: ");
//    for (int i = 0; i < n; i++) 
//    {
//       printf("%d ", lib[i]);
//    }
//    printf("\n");
//    free(func);
//    free(lib);
//    return 0;
// }