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
	//printf("ft_strchr called\n");
	while (str && *str)
	{
		if (*str == (char)c)
		{
			//printf("ft_strchr exit: 1\n");
			return ((char *)str);
		}
		str++;
	}
	if ((char)c == '\0')
	{
		//printf("ft_strchr exit: 2\n");
		return ((char *)str);
	}
	//printf("ft_strchr exit: 3\n");
	return (NULL);
}

char	*ft_free(char **data, char *new)
{
	//printf("ft_free called: 1\n");
	free(*data);
	*data = NULL;
	//printf("ft_free exit\n");
	return (new);
}

char	*read_file(int fd, char *buffer, char **nbuff)
{
	int		next;

	next = 1;
	//printf("read_file called: 1\n");
	while (next != 0)
	{
		next = read(fd, buffer, BUFFER_SIZE);
		if (next <= -1 || (next == 0 && *nbuff[0] == '\0'))
		{
			//printf("read_file exit: 1\n");
			return (ft_free(nbuff, NULL));
		}
		else if (next == 0)
			break ;
		buffer[next] = '\0';
		*nbuff = ft_free(nbuff, ft_strjoin(*nbuff, buffer));
		if (ft_strchr(*nbuff, '\n'))
			break ;
	}
	//printf("read_file exit 2\n");
	return (*nbuff);
}

char	*get_currline(int fd, char *buffer, char **nbuff, char *rval)
{
	int		character;
	//printf("get_currline called\n");
	character = 1;
	read_file(fd, buffer, nbuff);
	if (ft_strchr(*nbuff, '\0'))
	{
		rval = ft_strdup(*nbuff);
		character = 0;
	}
	else if (ft_strchr(*nbuff, '\n'))
		rval = ft_substr(*nbuff, 0, ft_strchr(*nbuff, '\n') - *nbuff + 1);
	else
	{
		//printf("get_currline exit 1\n");
		return (NULL);
	}
	if (character)
		*nbuff = ft_free(nbuff, ft_strdup(ft_strchr(*nbuff, '\n') + 1));
	else
		*nbuff = ft_free(nbuff, ft_strdup(ft_strchr(*nbuff, '\0')));
	//printf("get_currline exit 2\n");
	return (rval);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*rval;
	static char	*nbuff;
	size_t		j;

	//printf("get_next_line called\n");
	j = 0;
	rval = NULL;
	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		//printf("get_next_line exit 1\n");
		return (ft_free(&nbuff, NULL));
	}
	buffer = (char *)malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	while (j < BUFFER_SIZE + 1)
		buffer[j++] = 0;
	if (nbuff == NULL)
	{
		//printf("\033[0;31m\nHERE\n\033[0m");
		nbuff = ft_strdup("");
	}
	rval = get_currline(fd, buffer, &nbuff, rval);
	free(buffer);
	buffer = NULL;
	if (!rval)
	{
		ft_free(&nbuff, NULL);
		ft_free(&rval, NULL);
		//printf("get_next_line exit 2\n");
		return (NULL);
	}
	//printf("get_next_line exit 3\n");
	return (rval);
}
#ifdef _MAIN_
int main()
{
	int fd;
	int	i;
	char *result;
	i = 1;
	fd = open("/Users/lnambaji/Documents/Cursus/get_next_line/get_next_line1/1char.txt", O_RDWR);
	if (fd == -1) {
		perror("Couldn't open the file. Try again.");
		return (0);
	}
	result = get_next_line(fd);
	printf("%d: %s\n", i, result);
	while (result)
	{
		printf("%d: %s\n", i, result);
		result = get_next_line(fd);
		if (i == 1)
			free (result);
		i++;
	}
	close(fd);
	return (0);
}
#endif