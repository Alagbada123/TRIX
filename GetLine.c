#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t len_a = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		x = getline(buf, &len_p, stdin);
		x = _getline(info, buf, &len_p);
		if (x > 0)
		{
			if ((*buf)[x - 1] == '\n')
			{
				(*buf)[x - 1] = '\0';
				x--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			{
				*len = x;
				info->cmd_buf = buf;
			}
		}
	}
	return (x);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t k, l, len;
	ssize_t x = 0;
	char **buf_a = &(info->arg), *a;

	_putchar(BUF_FLUSH);
	x = input_buf(info, &buf, &len);
	if (x == -1)
		return (-1);
	if (len)
	{
		l = k;
		p = buf + k;

		check_chain(info, buf, &l, k, len);
		while (l < len)
		{
			if (is_chain(info, buf, &l))
				break;
			l++;
		}

		k = l + 1;
		if (k >= len)
		{
			k = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_a = a;
		return (_strlen(a));
	}

	*buf_a = buf;
	return (x);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t x = 0;

	if (*i)
		return (0);
	x = read(info->readfd, buf, READ_BUF_SIZE);
	if (x >= 0)
		*i = x;
	return (x);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: c
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t k, len;
	size_t p;
	ssize_t x = 0, c = 0;
	char *a = NULL, *new_a = NULL, *b;

	a = *ptr;
	if (a && length)
		c = *length;
	if (k == len)
		k = len = 0;

	x = read_buf(info, buf, &len);
	if (x == -1 || (x == 0 && len == 0))
		return (-1);

	b = _strchr(buf + k, '\n');
	p = b ? 1 + (unsigned int)(b - buf) : len;
	new_a = _realloc(a, c, c ? c + p : p + 1);
	if (!new_a)
		return (a ? free(a), -1 : -1);

	if (c)
		_strncat(new_a, buf + k, p - k);
	else
		_strncpy(new_a, buf + k, p - k + 1);

	c += p - k;
	k = p;
	a = new_a;

	if (length)
		*length = c;
	*ptr = a;
	return (c);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
