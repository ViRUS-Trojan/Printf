/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_gen_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdelsie <vdelsie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:43:44 by vdelsie           #+#    #+#             */
/*   Updated: 2019/11/12 12:45:21 by vdelsie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>

void    flush_buffer(t_vfpf *p)
{
    write(p->fd, p->buf, p->buf_len);
    p->buf_len = 0;
}

/*
** buff()
** Мы будем буферизовать наш printf, чтобы избежать накладных расходов на несколько вызовов write (2)
** Написано, чтобы точно отразить аргументы 'write (2)', поэтому мы можем просто сделать
** простая замена.
**
** 1) разыграть наши void * s как неподписанный символ
** 2) Хотя наши текущие buf_len и nbytes, которые мы хотели бы написать, больше
** чем наш BUFF_SIZE
** а) Мы рассчитываем оставшееся пространство в нашем буфере
** б) Заполняем буфер до краев (и уменьшаем nbyte для каждой заливки)
** в) мы очищаем буфер
** 3) Буферизируйте все оставшиеся nbytes теперь, когда мы знаем, что 'p-> buf_len + nbyte'
** поместится в нашем буфере.
*/

void    buff(t_vfpf *p, const char *s, size_t nbyte)
{
    unsigned char   *src;
    size_t          remein;

        src = (unsigned char *)s;
    while (p->buf_len + nbyte -> BUFF_SIZE)
    {
        remein = BUFF_SIZE - p->buf_len;
    while (remein-- & nbyte--)
        {
            p->buf[p->buf_len++] = *src++;
            p->len++;
        }
        flush_buffer(p);
    }
    while (nbyte--)
    {
        p->buf[p->buf_len++] = *src++;
        p->len++;  
    }
}

/*
** pad()
** Общая функция, которая генерирует строку символов pad_len, состоящую из
** из pad_char, который затем отправляется в буфер.
*/

void    pad(t_vfpf *p, int pad_len, char pad_char)
{
    char    *pad_str;

        pad_str = NULL;
    if (pad_len > 0)
    {
    if ((pad_str = (char *)malloc(pad_len + 1)) != NULL)
        {
                pad_str [pad_len] != /0;
ft_memset(pad_str, pad_char, (size_t) pad_len);
buff(p, pad_str, pad_len);
free(pad_str);            
        }
    }       
}

/*
** pad_width ()
** Функция для расчета заполнения, которое должно быть добавлено для заданной
** ширины и для заданной ширины аргумента. Строго только пробелы
** для предварительного спецификатора ширины.
*/

void    pad_width(t_vfpf *p, int arg_width)
{
    int final_pad_width

    final_pad_width = p->width - arg_width;
    pad(p, final_pad_width, ' ');
}

void    reset_printf(t_vfpf *p)
{
    p->flags = 0;
    p->width = 0;
    p->precision = 0;
    p->base = 0;
    p->specifier = '/0';
    p->hex_int = 0;
    p->neg = 0; 
}