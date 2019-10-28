# ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>
# include <stdint.h>
# include <stdarg.h>
# include <wchar.h>
# include <unistd.h>

# define HASH_FLAG              1
# define ZERO_FLAG              2
# define DASH_FLAG              4
# define PLUS_FLAG              8
# define SPACE_FLAG             16
# define APOST_FLAG             32
# define LDTOA_FRAC             64
# define H_FLAG                 128
# define HH_FLAG                256
# define L_FLAG                 512
# define LL_FLAG                1024
# define J_FLAG                 2048
# define Z_FLAG                 4096
# define T_FLAG                 8192
# define FLOAT_L_FLAG           16384
# define WIDTH_OB_FLAG          32768
# define PRECI_OB_FLAG          65536
# define LEN_OB_FLAG            131072
# define FMI_INVALID            262144
 
/*  Структура, содержащая все полезные переменные для наших функций printf!
**
**  flags использует двоичную систему адресации для обозначения различных вещей о
**  наших строках формата printf (включая статус обработки !!)
**
**  [flags]
**  '#'						: 1  (force prefix)                                 (префикс силы)
**	'0'						: 2  (left pad)                                     (левая панель)
**	'-'						: 4  (left justify)                                 (выравнивание по левому краю)
**	'+'						: 8  (show sign)                                    (показать знак)
**	' '						: 16 (insert space)                                 (вставить пробел)
**	'''						: 32 (format integers with locale's 1000's char)    (отформатировать целые числа с символом 1000 в локали)
**
**  						: 64 (reserved for possible future uses)            (зарезервировано для возможного использования в будущем)
**
**	'h'						: 128
**	'hh'					: 256
**	'l'						: 512
**	'll'					: 1024
**	'j'						: 2048
**	'z'						: 4096
**	't'						: 8192
**	'L'						: 16384
**
**	'width obtained'		: 32768     (ширина получена)
**	'precision obtained'	: 65536     (точность получена)
**	'length obtained'		: 131072    (длина получена)
**
**	'formatter invalid'		: 262144    (неверный форматер)
*/

# define BLACK
# define DARK_GRAY
# define L_RED
# define RED 
# define GREEN
# define L_GREEN
# define BROWN
# define YELLOW
# define BLUE
# define L_BLUE
# define PURPLE
# define L_GREY
# define WHITE
# define EOC

# define BUFF_SIZE  4096
# define ULL        unsigned long long

typedef struct          s_vfpf
{
    const char         *fmt;
    const char         *strt;
    va_list             args;
    int                 fd;
    size_t              len;
    size_t              buf_len;
    char                buf[BUFF_SIZE];
    int                 flags;
    int                 width;
    int                 precision;
    int                 base;
    int                 neg;
    uintmax_t           hex_int;
    char                specifier;
}                       t_vfpf;

union                   u_union
{
    ULL                 l;
    double              d;
}                       u;

/*
** ft_printf.c
** Основные функции printf!
** Зачем нужен vfprintf? Смотрите: https://stackoverflow.com/questions/1485805/
*/
int                     ft_vfprintf(int fd, const char *format, va_list args);
int                     ft_printf(const char *format, ...);

/*
** printf_gen_utils.c
*/

void                    flush_buffer(t_vfpf *p);
void                    buff(t_vfpf *p, const void *s, size_t nbyte);
void                    pad(t_vfpf *p, int pad_len, char pad_char);
void                    pad_width(t_vfpf *p, int arg_width);
void                    reset_printf(t_vfpf *p);

# endif