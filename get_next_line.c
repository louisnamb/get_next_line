/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:49:10 by lnambaji          #+#    #+#             */
/*   Updated: 2023/04/14 15:23:20 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int get_next_line(int fd)
{
    char	buffer[1024];
    ssize_t	bytes_read;
	int		i;
	char	*new_buff;

    if (fd == -1) {
		perror("Couldn't open the file. Try again.");
		return (1);
    }
	i = 0;
    bytes_read = read(fd, buffer, sizeof(buffer));
	new_buff = malloc(sizeof(char *) * sizeof(buffer) + 1);
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		new_buff[i] = buffer[i];
		i++;
	}
	printf("bytes allocated: %zu str:\n %s\n", sizeof(buffer), new_buff);
	printf("\n\n");
	close(fd); // close file when done
    return 0;
}


int main(int argc, char **argv)
{
	int fd;
	fd = open("/Users/lnambaji/Documents/Cursus/get_next_line/example.txt", O_RDONLY);
	get_next_line(fd);
	return (0);
}

/*
Get_next_line notes:
- use open and closefp function
- define BUFFER_SIZE in your header file
- copies buffer sized bytes but prints until the newline character and stops
- next time you run get_next_line, its going to start after the newline character
	hence the static variable
- for it to print the rest (until the newline character)

Research areas:
- research fgets() function

Steps:
- Open the file and create a pointer to the first character of the file
- store buffer sized characters in the buffer variable, including the 
  newline character. 
- print up to newline characters. free whats left of the newline character
  and keep whats right of it
*/