/* ************************************************************************** */
/*																		      */
/*														:::	  ::::::::        */
/*   get_next_line.c									:+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: lnambaji <lnambaji@student.42.fr>		  +#+  +:+	   +#+		      */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2023/04/13 15:49:10 by lnambaji		  #+#	#+#			      */
/*   Updated: 2023/04/27 14:27:50 by lnambaji		 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*str;

	str = s;
	while (*str && str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*unique(char **data, char	*new)
{
	free(*data);
	*data = NULL;
	return (new);
}

char	*read_file(int fd, char *buffer, char **nbuff)
{
	int		next;

	next = 69;
	while (next != 0)
	{
		next = read(fd, buffer, BUFFER_SIZE);
		if (next <= -1 || (next == 0 && *nbuff[0] == '\0'))
			return (unique(nbuff, NULL));
		else if (next == 0)
			break ;
		buffer[next] = '\0';
		*nbuff = unique(nbuff, ft_strjoin(*nbuff, buffer));
		if (ft_strchr(*nbuff, '\n'))
			break ;
	}
	return (*nbuff);
}

char	*get_currline(int fd, char *buffer, char **nbuff, char *rval)
{
	int		character;

	read_file(fd, buffer, nbuff);
	if (ft_strchr(*nbuff, '\n'))
		rval = ft_substr(*nbuff, 0, ft_strchr(*nbuff, '\n') - *nbuff + 1);
	else if (ft_strchr(*nbuff, '\0'))
	{
		rval = ft_strdup(*nbuff);
		character = 0;
	}
	else
		return (NULL);
	if (character)
		*nbuff = unique(nbuff, ft_strdup(ft_strchr(*nbuff, '\n') + 1));
	else
		*nbuff = unique(nbuff, ft_strdup(ft_strchr(*nbuff, '\0')));
	return (rval);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*rval;
	static char	*nbuff;
	size_t		j;

	j = 0;
	rval = NULL;
	if (fd < 0 || read(fd, 0, 0) < 0)
		return (unique(&nbuff, NULL));
	buffer = (char *)malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	while (j < BUFFER_SIZE + 1)
		buffer[j++] = 0;
	if (nbuff == NULL)
		nbuff = ft_strdup("");
	rval = get_currline(fd, buffer, &nbuff, rval);
	free(buffer);
	buffer = NULL;
	if (!rval)
	{
		unique(&nbuff, NULL);
		unique(&rval, NULL);
		return (NULL);
	}
	return (rval);
}
int main()
{
	int fd;
	int	i;
	char *result;
	i = 0;
	fd = open("/Users/lnambaji/Documents/Cursus/get_next_line/1char.txt", O_RDWR);
	if (fd == -1) {
		perror("Couldn't open the file. Try again.");
		return (0);
	}
	result = get_next_line(fd);
	printf("%d: %s", i, result);
    while (result)
    {
		printf("%d: %s", i, result);
	    result = get_next_line(fd);
		if (i == 1)
		free (result);
	    i++;
    } 
	return (0);
}
