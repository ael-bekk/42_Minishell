/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:15:08 by ael-bekk          #+#    #+#             */
/*   Updated: 2021/11/10 11:19:30 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# define TRUE 1
# define BUFFER_SIZE 1024

typedef struct s_list
{
	void			*key;
	void			*value;
	struct s_list	*next;
}	t_list;

// part 1
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

// part 2
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// part ~
int     ft_double_strlen(char **s);
char	*ft_strjoin_freed(char *s1, char *s2, int type);
char	*ft_strchr_line(const char *s, int c);
char	*ft_strjoin_freed2(char *s1, char *s2, int type);
char    **ft_str_double_join(char ***s1, char **s2, int l1, int l2);
void    ft_free(char **s);
int		ft_strcmp(char*s1, char*s2);

// part 3 *linked_list*
t_list	*ft_lstnew(void *key, void *value);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));

// part 4 *get_next_line*
void	*ft_free11(char **s);
char	*read_buff11(int fd, char **buff);
char	*read_line11(int fd, char **buff);
char	*get_next_line11(int fd);

int		find_new_line11(char *s);
char	*ft_strjoin11(char *s1, char *s2);
char	*ft_substr11(char *s, int end);
void	ft_new_buff11(char **buff, int start);

#endif
