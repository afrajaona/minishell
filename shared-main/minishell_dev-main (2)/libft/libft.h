/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrazafia <hrazafia@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:40:53 by hrazafia          #+#    #+#             */
/*   Updated: 2024/10/06 11:44:06 by hrazafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include <stdarg.h>

# define ADDR_PRE "0x"
# define NULL_STR "(null)"
# define NULL_PTR "(nil)"

# define N 1

typedef int	(*t_func)(va_list *);

typedef struct s_content
{
	char				*value;
	size_t				len;
	struct s_content	*next;
}	t_content;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_atoi(const char *nptr);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isempty(char *s);
int			ft_isprint(int c);
int			ft_isspace(char c);
char		*ft_itoa(int nbr);
void		ft_lstadd_back(t_list **lst_ptr, t_list *node);
void		ft_lstadd_front(t_list **lst_ptr, t_list *node);
void		ft_lstclear(t_list **lst_ptr, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*get_next_line(int fd);
t_content	*ft_new_content(char *s, size_t len);
void		ft_clear_content(t_content **content);
size_t		ft_len_content(t_content *content);
void		ft_clean_buffer(t_content **content);
int			ft_printf(const char *format, ...);
int			ft_call_func(t_func func, char conv, va_list *ap);
int			ft_print_arg(const char *format, va_list *ap);
int			ft_print_char(va_list *ap);
int			ft_print_int(va_list *ap);
int			ft_print_lhex(va_list *ap);
int			ft_print_percent(va_list *ap);
int			ft_print_ptr(va_list *ap);
int			ft_print_str(va_list *ap);
int			ft_print_uhex(va_list *ap);
int			ft_print_uint(va_list *ap);
int			ft_putchar(char c);
int			ft_putstr(char *str);
int			ft_putnbr(int nbr, int n);
int			ft_puthex(uintptr_t nbr, int n);
t_func		ft_select_func(char conv);

#endif
