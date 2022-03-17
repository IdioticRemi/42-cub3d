/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 09:15:04 by selee             #+#    #+#             */
/*   Updated: 2021/05/03 13:07:32 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *string, char sep)
{
	int		count;
	int		index;
	bool	in_a_word;
	char	c;

	if (string == 0)
		return (0);
	index = 0;
	count = 0;
	in_a_word = false;
	while (string[index] != '\0')
	{
		c = string[index++];
		if (in_a_word)
		{
			if (c == sep)
				in_a_word = false;
		}
		else if (c != sep)
		{
			in_a_word = true;
			count++;
		}
	}
	return (count);
}

static char	*ft_read_word(const char **string, char sep)
{
	char		*result;
	int			len;
	const char	*cursor;

	len = 0;
	cursor = *string;
	while (*cursor != '\0' && *cursor != sep)
	{
		cursor++;
		len += 1;
	}
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, *string, len);
	result[len] = '\0';
	*string = cursor;
	return (result);
}

static void	ft_skip_separators(const char **string, char sep)
{
	const char	*cursor;

	cursor = *string;
	while (*cursor == sep)
		cursor++;
	*string = cursor;
}

static void	ft_cleanup(char **words, int up_to)
{
	int		word_index;

	word_index = 0;
	while (word_index < up_to)
	{
		free(words[word_index]);
		word_index += 1;
	}
	free(words);
}

char	**ft_split(const char *string, char sep)
{
	char		**words;
	int			word_index;
	int			word_count;
	char		*new_word;
	const char	*cursor;

	word_count = ft_count_words(string, sep);
	words = malloc((word_count + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	word_index = 0;
	cursor = &string[0];
	while (word_index < word_count)
	{
		ft_skip_separators(&cursor, sep);
		new_word = ft_read_word(&cursor, sep);
		if (!new_word)
		{
			ft_cleanup(words, word_index);
			return (NULL);
		}
		words[word_index++] = new_word;
	}
	words[word_index] = NULL;
	return (words);
}
