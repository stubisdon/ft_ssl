/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 09:09:23 by dkotov            #+#    #+#             */
/*   Updated: 2018/09/07 11:11:34 by dkotov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>

# include "libft.h"

typedef struct	s_var
{
	char		*flags;
	int			width;
	int			precision;
	char		*type;
	char		converser;
}				t_var;

void			struct_init(t_var *var);
int				ft_printf(const char *format, ...);
int				dispatch(char **buff, t_var var, va_list ap);

/*
** Argument functions
*/

int				ft_check_type(const char *str, t_var *var);
int				ft_isflag(char c);
int				ft_istype(const char *str, char **type);
int				ft_isconverser(const char *str, char *converser);

/*
** Converser functions
*/

void			fct_void(char **buff, t_var var, va_list ap);
void			fct_void_edge(char **buff, char *str, t_var var);
char			*number_dispatch(t_var var, va_list ap);
void			number_new(char **buff, t_var var, va_list ap);

void			string_new(char **buff, t_var var, va_list ap);
void			wstring_new(char **buff, t_var var, va_list ap);
void			char_new(char **buff, t_var var, va_list ap);
void			wchar_new(char **buff, t_var var, va_list ap);
void			procent_new(char **buff, t_var var);

char			*ft_itoa_base_long(uint64_t value, int base);
void			number_long(char **buff, t_var var, va_list ap);
void			number_octal(char **buff, t_var var, va_list ap);
void			number_hexa(char **buff, t_var var, va_list ap);

char			*fct_precision(char *str, t_var var);
char			*fct_wprecision(wchar_t *wstr, t_var var);
char			*fct_width_new(char *str, t_var var, int len);
char			*fct_precision_int(char *str, t_var var, int len);
char			*number_flag(char *str, t_var var, int len);

/*
** Helper functions
*/

int				handle_null(char *str);
char			*free_str(char *str, char *newstr);
char			*free_join(char *s1, char *s);
char			*free_append(char *s1, char s);
char			*ft_appendwchar(char *buff, wchar_t c);

#endif
