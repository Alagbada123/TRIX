#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int k, l, p, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (k = 0; str[k] != '\0'; k++)
		if (!is_delim(str[k], d) && (is_delim(str[k + 1], d) || !str[k + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, l = 0; l < numwords; l++)
	{
		while (is_delim(str[k], d))
			k++;
		p = 0;
		while (!is_delim(str[k + p], d) && str[k + p])
			p++;
		s[l] = malloc((p + 1) * sizeof(char));
		if (!s[l])
		{
			for (p = 0; p < l; p++)
				free(s[p]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < p; n++)
			s[l][n] = str[k++];
		s[l][n] = 0;
	}
	s[l] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int k, l, p, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (k = 0; str[k] != '\0'; k++)
		if ((str[k] != d && str[k + 1] == d) ||
		    (str[k] != d && !str[k + 1]) || str[k + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, l = 0; l < numwords; l++)
	{
		while (str[k] == d && str[k] != d)
			k++;
		p = 0;
		while (str[k + p] != d && str[k + p] && str[k + p] != d)
			p++;
		s[l] = malloc((p + 1) * sizeof(char));
		if (!s[l])
		{
			for (p = 0; p < l; p++)
				free(s[p]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < p; n++)
			s[l][n] = str[k++];
		s[l][n] = 0;
	}
	s[l] = NULL;
	return (s);
}
