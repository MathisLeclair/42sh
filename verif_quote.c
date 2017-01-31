/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 14:20:36 by mleclair          #+#    #+#             */
/*   Updated: 2017/01/31 14:27:34 by mleclair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	verif_quote(char *input)
{
	int i;
	int quote;
	int dquote;

	quote = 0;
	dquote = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '"' && dquote == 0)
			dquote = 1;
		else if (input[i] == '\'' && quote == 0)
			quote = 1;
		else if (input[i] == '"' && dquote == 1)
			quote = 0;
		else if (input[i] == '\'' && quote == 1)
			quote = 0;
		else if ((input[i] == '"' && quote == 1) ||
			(input[i] == '\'' && dquote == 1))
			verif_quote(input + i);
	}
}
