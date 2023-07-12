/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:52:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/07/11 14:06:37 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_data *data, int j)
{
	int	c;

	c = j + 1;
	while (data->tokens[c]
		&& !(data->tokens[c][0] == '|' && !data->tokens[c][1]))
		c++;
	return (c);
}

int	here_doc(char *limiter)
{
	int		doc;
	char	*buf;

	doc = open(".here_doc", O_RDWR, O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(1, "here_doc>", 9);
		buf = get_next_line(STDIN_FILENO);
		if (!buf || (!ft_strcmp(buf, limiter)
				&& buf[ft_strlen(limiter)] == '\n'))
			break ;
		write(doc, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close (doc);
	return (doc);
}

int	open_fds(char *redir, char *file)
{
	int	i;

	i = -1;
	if (!ft_strcmp(redir, ">"))
		i = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(redir, ">>"))
		i = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp(redir, "<"))
	{
		if (!access(file, R_OK))
			i = open(file, O_RDONLY);
		else
			i = -1;
	}
	else if (!ft_strcmp(redir, "<<"))
		i = here_doc(file);
	if (i == -1)
		return (-1);
	return (i);
}

void	get_fds(char **tokens, int *fdin, int *fdout, int c)
{
	while (tokens[c] && ft_strcmp(tokens[c], "|"))
	{
		if (!ft_strcmp(tokens[c], ">")
			|| !ft_strcmp(tokens[c], ">>"))
		{
			*fdout = open_fds(tokens[c], tokens[c + 1]);
			if (*fdout == -1)
				break ;
		}
		else if (!ft_strcmp(tokens[c], "<")
			|| !ft_strcmp(tokens[c], "<<"))
		{
			*fdin = open_fds(tokens[c], tokens[c + 1]);
			if (*fdin == -1)
				break ;
		}
		c++;
	}
	if (*fdout == -1 || *fdin == -1)
		print_error(tokens[c + 1], 0, "No such file or directory", 0);
}
