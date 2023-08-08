#include "get_next_line.h"

char	*ft_free_return(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (NULL);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

int		get_index(char *line, char c)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && line[i] != c)
		i++;
	if (line[i] != c)
		return (-1);
	return (i);
}

char	*add_save_to_line(char *save)
{
	int	len_s;
	char	*line;
	int		i;

	len_s = ft_strlen(s);
	if (!len_s)
		return (NULL);
	line = malloc(sizeof(char) * (len_s + 1));
	i = -1;
	while (save[++i])
		line[i] = save[i];
	line[i] = '\0';
	return (line);
}

char	*add_buf_to_line(char *line, char *buf, int len_buf)
{
	char	*new_line;
	int		len_line;
	int		i;

	len_line = ft_strlen(line);
	if (!len_line && !len_buf)
		return (ft_free_return(line));
	new_line = malloc(sizeof(char *) * (len_line + len_buf + 1));
	if (!new_line)
		return (ft_free_return(line));
	i = -1;
	while (++i < len_line)
		new_line[i] = line[i];
	while (i < len_buf + len_line)
	{
		new_line[i] = *buf;
		i++;
		buf++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

char	*read_loop(int fd, char *line)
{
	int		ret;
	char	buf[BUFFER_SIZE + 1];
	
	ret = 1;
	while (get_index(line, '\n') == -1 && ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return(ft_free_return(line));
		buf[ret] = '\0';
		line = add_buf_to_line(line, buf, ret);
		if (!line)
			return (NULL);
	}
	return (line);
}

void	get_new_save(char *save, char *line, int start)
{
	int	i;
	int	j;

	i = 0;
	while (line[start])
	{
		save[i] = line[start]; 
		i++;
		start++;
	}
	save[i] = '\0';
}

char	*get_ret_line(line, save, nl_index)
{
	char	*ret_line;
	int		i;

	if (line[nl_index] && line[nl_index] == '\n')
			nl_index++;
	ret_line = malloc(sizeof(char *) * (nl_index + 1));
	if (!ret_line)
		return (ft_free_return(line));
	i = 0;
	while (i < nl_index)
	{
		ret_line[i] = line[i];
		i++;
 	}
	if (line[i] == '\n') // a verif mais on rentre jamais dedans
		new_line[i] = '\n';
	ret_line[i] = '\0';
	return (ret_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	save[BUFFER_SIZE + 1];
	int			nl_index;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	line = add_save_to_line(save);
	save[0] = '\0';
	nl_index = get_index(line, '\n');
	if (nl_index == -1)
	{
		line = read_loop(fd, line);
		if (!line)
			return (NULL);
		nl_index = get_index(line, '\n');
	}
	if (nl_index != -1)
	{
		get_new_save(save, line, nl_index + 1);
		line = get_ret_line(line, nl_index);
	}
	return (line);
}
