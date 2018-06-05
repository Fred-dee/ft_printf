/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdilapi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:41:01 by mdilapi           #+#    #+#             */
/*   Updated: 2018/06/05 11:41:02 by mdilapi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"
#include <stdio.h>

static char g_conversions[] = "sSpdDioOuUxXcC";
static char g_sflags[] = "#0-+ ";

int isIn(char c,const char *s)
{
	while (*s != '\0')
	{
		if(*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	argc(const char *s)
{
	const char *tmp;
	int count;

	tmp = s;
	count = 0;
	while (*tmp != '\0')
	{
		if (*tmp == '%' && *(tmp + 1) != '%') //This would just be escaped
		{
			tmp++;
			while(isIn(*tmp, g_sflags) == 1)
				tmp++;
			if(isIn(*tmp, g_conversions) == 1)
				count++;
		}
		tmp++;
	}
	return (count);
}

int	ft_printf(const char *s, ...)
{
	const char	*tmp;
	va_list		arg;
	int			ac;
	
	va_start(arg, s);
	tmp = s;
	ac = argc(s);
	while (*tmp != '\0')
	{
		if (*tmp == '%' && *(tmp + 1) != '%')
		{
			while(isIn(*tmp, g_sflags) == 1)
				tmp++;
			if(isIn(*tmp, g_conversions) == 1)
				tmp++;
		}
		else write(1, tmp, 1);
		tmp++;
	}
	//printf("Num argument: %d\n",argc(s));
	return (0);
}

/**
* Notes:
* if NULL is passed as the first and only parameter the function seg faults : printf(NULL);
* if an empty string is passed as the first and only parameter it returns 0 and prints nothing: printf("");
* NB!! The return value if printf is the number of characters printed
* with each successful call to va_arg it moves on to the next argument.
* va_arg does not know which is the last argument
* even with whitespaces inbetween the escape character and the identifier, printf works
* This behaviour is warned as undefined though : printf("Hello %     s", "world");
* %% will escape the escape character and allow you to print the character '%'
* Looking for the following conversions: sSpdDioOuUxXcC
* Manage the flags #0-+ and space
* must handle minimum field-width
* must manage precision
* must manage the flags hh, h, l, ll, j, et z
*/
