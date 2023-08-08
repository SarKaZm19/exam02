#include <stdarg.h>
#include <unistd.h>

void	print_int_base(int nb, int base, int *count)
{
	char	*hex_base = "0123456789abcdef";

	if (nb == -2147483648)
	{
		*count += write(1, "-2", 2);
		nb = 147483648;
	}
	if (nb < 0)
	{
		nb *= -1;
		*count += write(1, "-", 1);
	}
	if (nb >= base)
		print_int_base((nb / base), base, count);
	*count += write(1, &hex_base[nb % base], 1);
}

void	print_str(char *str, int *count)
{
	int i = -1;
	if (!str)
	{
		*count += write (1, "(null)", 6);
		return ;
	}
	while (str[++i])
		*count += write(1, &str[i], 1);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	int	count;

	count = 0;
	va_start (ap, format);
	while (*format)
	{
		if (*format == '%' && (*(format + 1) == 's' || *(format + 1) == 'd' || *(format + 1) == 'x'))
		{
			format++;
			if (*format == 's')
				print_str(va_arg(ap, char *), &count);
			if (*format == 'd')
				print_int_base(va_arg(ap, long long int), 10, &count);
			if (*format == 'x')
				print_int_base(va_arg(ap, long long int), 16, &count);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}
#include "stdio.h"

int main()
{
	char 	*str = "Hello";
	char 	*str2 = "world";
	char 	*str3 = "Hello world";
	char	*str4 = NULL;
	int		count_str = 0;
	int		count_fstr = 0;
	int		count_int = 0;
	int		count_fint = 0;
	printf("comparing... first is printf, second is ft_printf\n");
	count_fstr = printf(".%s. .%s. .%s. .%s.\n", str, str2, str3, str4);
	count_str = ft_printf(".%s. .%s. .%s. .%s.\n", str, str2, str3, str4);
	int	i = 0;
	int j = 42;
	int k = 2147483647;
	int l = -42;
	int m = -2147483648;
	count_fint = printf(".%d. .%d. .%d. .%d. .%d.\n", i, j, k, l, m);
	count_int = ft_printf(".%d. .%d. .%d. .%d. .%d.\n", i, j, k, l, m);
	ft_printf("count_fstr = %d count_fint = %d\n", count_fstr, count_fint);
	ft_printf("count_str = %d count_int = %d\n", count_str, count_int);

	
}