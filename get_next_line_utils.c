#include "get_next_line.h"
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;
	size_t	i;

	if (!s1)
		len1 = 0;
	else
		len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		result[i + len1] = s2[i];
		i++;
	}
	result[len1 + len2] = '\0';
	free(s1);
	return (result);
}

char	*ft_extract_line(char *stash)
{
	char	*newline;
	size_t	len;
	char	*line;
	size_t	i;

	newline = ft_strchr(stash, '\n');
	if (newline)
		len = newline - stash + 1;
	else
		len = ft_strlen(stash);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

char	*ft_trim_stash(char *stash)
{
	char	*newline;
	size_t	len;
	char	*new_stash;
	size_t	i;

	newline = ft_strchr(stash, '\n');
	if (!newline)
	{
		free(stash);
		return (NULL);
	}
	len = ft_strlen(newline + 1);
	new_stash = malloc(len + 1);
	if (!new_stash)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_stash[i] = newline[1 + i];
		i++;
	}
	new_stash[len] = '\0';
	free(stash);
	return (new_stash);
}