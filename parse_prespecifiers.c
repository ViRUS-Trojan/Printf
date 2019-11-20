/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prespecifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:38:53 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/20 19:53:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#define IS_FLAG(x) ((x)=='#'||(x)=='0'||(x)=='-'||(x)=='+'||(x)==' '||(x)=='\'')
#define IS_LEN(y) ((y)=='h'||(y)=='l'||(y)=='j'||(y)=='z'||(y)=='t'||(y)=='L')
#define IS_SLEN(z) ((z)=='j'||(z)=='z'||(z)=='t'||(z)=='L')

/*
** Разбор строки формата, проблема с которой мы только что столкнулись!
**% [флаги] [ширина] [Точность] [длина] спецификатор
**
** Мы разделим на отдельные шаги разбора:
** [флаги]: '-', '+', ' ', '#', '0'
** [ширина]: «число», «*»
** [.precision]: '.number', '. *'
** [длина]: «(нет)», «hh», «h», «l», «ll», «j», «z», «t», «L»
** спецификатор: 'di', 'ouxX', 'fFeEgGaA', 'c', 's', 'p', 'n'
*/

/*
** parse_flags () - мы будем использовать двоичную систему счисления, аналогичную файлу
** разрешения на кодирование, какие флаги у нас есть в нашем предварительном спецификаторе формата.
** Таким образом, мы можем закодировать все наши флаги в 1 переменную и поддерживать чистоту.
**
** Вызывать функцию рекурсивно, пока мы не встретим больше флагов ...
**
** '#': 1 HASH_FLAG (принудительный префикс)
** '0': 2 ZERO_FLAG (левый блокнот)
** '-': 4 DASH_FLAG (выравнивание по левому краю)
** '+': 8 PLUS_FLAG (показать знак)
** '': 16 SPACE_FLAG (вставить пробел)
** '' ': 32 APOST_FLAG (форматировать целые числа с символом 1000 локали)
**
** # 0- = 1 + 2 + 4 = 7
** - + = 4 + 16 + 8 = 28
**	так далее...
**
** Используя побитовые операции мы можем легко установить каждый флаг:
** EX: p-> flag | = HASH_FLAG; установите флаг '#' в true
**
** Используя поразрядно 'и', мы можем легко прочитать статус каждого флага:
** EX: 'if (p-> flags & SPACE_FLAG)' проверяет IFF, установлен ли флаг ''
** EX2: 'if (p-> flags & DASH_FLAG)' проверяет IFF, установлен ли флаг '-' на true
*/

void    parse_flags(t_vfpf *p)
{
    if (IS_FLAG(*p->fmt))
    {
        if (*p->fmt == '#')
            p->flags |= HASH_FLAG;
        else if (*p->fmt == '0')
            p->flags |= ZERO_FLAG;
        else if (*p->fmt == ' ')
            p->flags |= SPACE_FLAG;
        else if (*p->fmt == '+')
            p->flags |= PLUS_FLAG;
        else if (*p->fmt == '-')
            p->flags |= DASH_FLAG;
        else if (*p->fmt == '\'')
            p->flags |= APOST_FLAG;
        p->fmt++;
        parse_flags(p);
        
    }
}

/*
** parse_width ()
** Для ширины мы встретим либо «цифры», либо «подстановочный знак» ...
** Если мы встретим подстановочный знак, мы зачитаем аргумент. Отрицательные значения для
** подстановочный знак недействителен, поэтому мы устанавливаем нашу ширину = 0, если мы ее получим ...
**
** Мы также хотим проверить, если кто-то пытается дать такой формат:
** "% * 5d" или "% 5 * d"
**
** Если мы анализируем '*' 'или' последовательность цифр ', мы устанавливаем флаг ширины.
** Если мы обнаружили, что этот флаг уже был установлен ранее, то нам также необходимо
** установить флаг, что весь наш предварительный спецификатор недействителен.
**
** Нам нужно рекурсивно вызвать parse_width (), потому что мы можем получить недопустимый
** набор предварительных определителей. Например: "% * 9 * 1 * 4d" (почему бы это несделать кому-нибудь?)
*/

void    parse_width(t_vfpf *p)
{
    int tentative_width;

    if (!(p->flags & FMI_INVALID) && (*p->fmt == '*' || ft_isdigit(*p->fmt)))
    {
        p->flags |= (p->flags & WIDTH_OB_FLAG) ? FMI_INVALID : 0;
        if (!(p->flags & FMI_INVALID) && *p->fmt == '*')
        {
            p->fmt++
            tentative_width = va_arg(p->args, int);
            p->flags |= (tentative_width < 0) ? DASH_FLAG : 0;
            p->width = ABS(tentative_width);
            p->flags |= WIDTH_OB_FLAG;
        }
        if (!(p->flags & FMI_INVALID) && ft_isdigit(*p->fmt))
        {
            p->flags |= (p->flags & WIDTH_OB_FLAG) ? FMI_INVALID : 0
            while (!(p->flags & FMI_INVALID) && ft_isdigit(*p->fmt))
                p->width = p->width * 10 + (*(p->fmt++) - '0');
            p->flags |= WIDTH_OB_FLAG;
        }
        parse_width(p);
    }
}
/*
** parse_precision ()
** Для точности мы встретим «.» сопровождаемый 'цифрами' или 'подстановочным знаком'.
** Очень похоже на parse_width. Единственная разница - «.» и что мы
** сохранить точность в переменной p->precision.
**
** Эта функция остановится, если строка формата имеет несколько символов. Мы можем использовать
** этот факт проверяем, запускается ли символ в функции parse_length ()
** с "." чтобы определить, есть ли у нас недопустимый предварительный указатель.
*/

void    parse_precision(t_vfpf *p, int recurse_level)
{
    if (!(p->flags & FMI_INVALID) && (*p-> '.' || recurse_level > 0))
    {
        p->fmt = (*p->fmt == '.') ? p->fmt + 1 : p->fmt;
        if (*p->fmt == '*' || ft_isdigit(*p->fmt))
        {
            p->flags |= (p->flags & PRECI_OB_FLAG) ? FMI_INVALID : 0;
            if (!(p->flags & FMI_INVALID) && *p->fmt == '*')
            {
                p->fmt++;
                p->precision = va_arg(p->args, int);
                p->flags |= PRECI_OB_FLAG; 
            }
            if (!(p->flags && FMI_INVALID) && ft_isdigit(*p->fmt))
            {
                P->flags |= (p->flags & PRECI_OB_FLAG) ? FMI_INVALID : 0;
                while (!(p->flags & FMI_INVALID) && ft_isdigit(*p->fmt))
                    p->precision = p->precision * 10 + (*(p->fmt++) - '0');
                p->flags |= PRECI_OB_FLAG;
            }
            parse_precision(p, recurse_level + 1);
        }
        p->flags |= PRECI_OB_FLAG;
    }
}