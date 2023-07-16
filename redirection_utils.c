/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:52:33 by mpatrao           #+#    #+#             */
/*   Updated: 2023/07/15 17:01:01 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d_error(char *limiter)
{
	char		*tmp;
	int			fd;
	static int	n;
	int			test;

	test = 0;
	fd = open(".here_doc", O_RDONLY);
	tmp = get_next_line(fd);
	if (n)
		n++;
	while (tmp && int_free(tmp, 1))
	{
		if (!ft_strcmp(tmp, limiter))
			test = 1;
		tmp = get_next_line(fd);
		if (tmp && ++n)
			test = 0;
	}
	if (test && int_free(tmp, 1))
		return ;
	free(tmp);
	close(fd);
	print_error2(limiter, &n);
}

int	count_args(t_data *data, int j)
{
	int	c;

	c = j + 1;
	while (data->tokens[c]
		&& !(data->tokens[c][0] == '|' && !data->tokens[c][1]))
		c++;
	return (c);
}

pid_t	here_doc(char *limiter)
{
	int		doc;
	char	*buf;
	pid_t	p;

	signal(SIGINT, SIG_IGN);
	p = fork();
	if (p == 0)
	{
		signal(SIGINT, SIG_DFL);
		doc = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
		while (1)
		{
			write(1, "here_doc> ", 10);
			buf = get_next_line(STDIN_FILENO);
			if (!buf || (!ft_strncmp(buf, limiter, ft_strlen(limiter))
					&& buf[ft_strlen(limiter)] == '\n'))
				break ;
			write(doc, buf, ft_strlen(buf));
			free(buf);
		}
		close (doc);
		free(buf);
		exit(0);
	}
	return (p);
}

int	open_fds(char *redir, char *file)
{
	int		i;
	int		status;
	pid_t	p;

	i = -1;
	if (!ft_strcmp(redir, "<<"))
	{
		p = here_doc(file);
		waitpid(p, &status, 0);
		ctrl_d_error(file);
		signal_global();
		if (WIFSIGNALED(status) && WTERMSIG(status) == 2 && printf("\n"))
			return (-2);
		i = open(".here_doc", O_RDONLY);
	}
	else if (!ft_strcmp(redir, ">"))
		i = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(redir, ">>"))
		i = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp(redir, "<"))
		if (!access(file, R_OK))
			i = open(file, O_RDONLY);
	return (i);
}

int	get_fds(char **tokens, int *fdin, int *fdout, int c)
{
	while (tokens[c] && ft_strcmp(tokens[c], "|"))
	{
		if (!ft_strcmp(tokens[c], ">") || !ft_strcmp(tokens[c], ">>"))
			*fdout = open_fds(tokens[c], tokens[c + 1]);
		else if (!ft_strcmp(tokens[c], "<") || !ft_strcmp(tokens[c], "<<"))
			*fdin = open_fds(tokens[c], tokens[c + 1]);
		if (*fdin == -1 || *fdout == -1)
			break ;
		c++;
	}
	if (*fdout == -1 || *fdin == -1)
		print_error(tokens[c + 1], 0, "No such file or directory", 0);
	if (*fdin == -2)
	{
		set_exit_code(CTRL_C);
		return (1);
	}
	return (0);
}
