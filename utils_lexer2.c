/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:31:01 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/13 15:33:37 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bad_substitution(char *str, int end)
{
	char	*temp;

	temp = ft_substr(str, 0, end);
	printf("minishell: %s: bad substitution\n", temp);
	free(temp);
	return (-1);
}
