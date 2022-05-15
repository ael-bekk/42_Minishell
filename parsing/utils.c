#include "../inc/minishell.h"

char	*ft_strchr_line(const char *s, int c)
{
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	if (c == 0)
		return ((char *)(s + ft_strlen(s)));
	while (s[i])
		if (s[i++] == (char)c)
			return ((char *)(s + i - 1));
	return (0);
}

char	*ft_strjoin_freed(char *s1, char *s2, int type)
{
	size_t		i;
	size_t		j;
	char		*str;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	if (type == 0 && s1[0] != '\0')
		str[i++] = '\n';
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_strjoin_freed2(char *s1, char *s2, int type)
{
	size_t		i;
	size_t		j;
	char		*str;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	if (type == 0 && s1[0] != '\0')
		str[i++] = '\n';
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}