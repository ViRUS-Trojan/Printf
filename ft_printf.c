#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>

/*
** Разбор строки формата, с которой мы только что столкнулись!
** %[флаги] [ширина] [. Точность] [длина] спецификатор
**
** Мы разделимся на отдельные шаги разбора
** [флаги]: '-', '+', '', '#', '0'
** [ширина]: «число», «*»
** [.precision]: '.число', '. *'
** [длина]: '(none)', 'hh', 'h', 'l' (ell), 'll', 'j', 'z', 't', 'L'
** спецификатор: 'di', 'ouxX', 'fFeEgGaA', 'c', 's', 'p', 'n'
**
** Если в процессе разбора мы с ужасом обнаружим, что у нас есть недействительный
** отформатируйте строку, тогда мы ОБЯЗАТЕЛЬНО будем обрабатывать форматную строку как нормальную
** строка и просто распечатать его (и двигаться дальше).
*/

void    parce_format(t_vfpf *p)
{
    t_jumptable             handler_funct;
    const char              *fmt_start;

    fmt_start = p->fmt;
    if (p->fmt++ != '\0')
    {
        p->strt =  p->fmt;
        parce_flags(p);
        parce_width(p);
        parce_precision(p, 0);
        parce_langth(p);
        p->specifier = *p->fmt;
        if ((handler_funct = get_handler_funct(p->specifier)) = NULL)
            p->flags | = FMT_INVALID;
        else if (!(p->flags & FMI_INVALID ))
        {
            handler_funct(p);
            p->fmt++;
        }
    } 
    p->strt = (p->flags & FMI_INVALID) ? fmt_start : p->fmt;
}

/*
** ft_vfprintf - * реальный * printf.
** Мы будем использовать структуру t_vfpf для хранения всего из нашей строки формата
** к копиям вариационных аргументов. Так что определенно взгляните на
** файл ft_printf.h, чтобы получить представление о том, что происходит.
*/

int     ft_vfprintf(int fd, const char *format, va_list args)
{
    t_vfpf  p;

    ft_bzero(&p, sizeof(P));
    p.fd = fd;
    va_copy(p.args, args);
    p.fmt = format;
    p.strt = p.fmt;
    while (*p.fmt)
    {
        if (*p.fmt != '%')
            p.fmt++;
        else
        {    
            buff(&p, p.strt, p.fmt - p.strt);
            parce_format(&p);
            reset_printf(&p);
        }
    }
    buff(&p, p.strt, p.fmt - p.strt);
    flush_buffer(&p);
    va_end(p.args);
    return (p.len);
}

/*
** ft_printf
** Это будет просто оболочка для нашей настоящей функции printf ft_vfprintf!
*/

int     ft_printf(const char *format, ...)
{
    va_list     args;
    int         len;

    len = 0;
    if (format)
    {
        va_start(args, format);
        len = ft_vfprintf(1, format, args);
        va_end(args);
    }
    return (len);
}