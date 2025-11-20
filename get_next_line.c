#include "get_next_line.h"
#include <stdlib.h>

static char	*read_and_join(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (stash);
}

static char	*extract_and_clean(char **stash)
{
	char	*line;

	line = ft_extract_line(*stash);
	*stash = ft_trim_stash(*stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s_stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s_stash = read_and_join(fd, s_stash);
	if (!s_stash)
		return (NULL);
	line = extract_and_clean(&s_stash);
	return (line);
}