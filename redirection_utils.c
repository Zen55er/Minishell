/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:52:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/06/16 14:45:50 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_pipes(t_data *data)
{
	int	i;

	i = 0;
	data->cmd_st->num_pipes = 0;
	while (data->tokens[i])
	{
		if (data->tokens[i] == "|")
			data->cmd_st->num_pipes++;
		i++;
	}
}

int	count_args(t_data *data, int j)
{
	int	c;

	c = j + 1;
	while (data->tokens[c] && data->tokens[c] != "|")
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
		if (!buf || (!ft_strncmp(buf, limiter, ft_strlen(limiter))
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

	if (!ft_strncmp(redir, ">", 2))
		i = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strncmp(redir, ">>", 2))
		i = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (!ft_strncmp(redir, "<", 2))
	{
		if (!access(file, F_OK & R_OK))
			i = open(file, O_RDONLY);
		else
			i = -1;
	}
	else if (!ft_strncmp(redir, "<<", 2))
		i = here_doc(file);
	return (i);
}

void	get_fds(char **tokens, int *fdin, int *fdout, int c)
{
	while (tokens[c] && !ft_strncmp(tokens[c], "|", 2))
	{
		if (!ft_strncmp(tokens[c], ">", 2)
			|| !ft_strncmp(tokens[c], ">>", 2))
		{
			if (*fdout)
				close(fdout);
			*fdout = open_fd(tokens[c], tokens[c + 1]);
		}
		else if (!ft_strncmp(tokens[c], "<", 2)
			|| !ft_strncmp(tokens[c], "<<", 2))
		{
			if (*fdin)
				close(fdin);
			*fdin = open_fd(tokens[c], tokens[c + 1]);
		}
		c++;
	}
}