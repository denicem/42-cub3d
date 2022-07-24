/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 21:52:50 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/07/24 22:39:22 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	progress_bar(void)
{
	int			i;
	static char	bar[500];
	const char	*lable;
	char		*someonesmom;

	someonesmom = "███████████████████";
	i = 0;
	lable = "|/-\\";
	ft_memset(bar, 0, 102 * sizeof(char));
	printf("\e[0;35m \
                LOADING PLEASE WAIT ...\e[0m\n");
	while (i <= 100)
	{
		if (i % 3 == 0)
			ft_strlcpy(&bar[i], someonesmom, 500);
		printf("\r\e[4;35m\e[40m\e[1;98m%-2s\e[0m\e[36m [%d%%] [%c]", bar,
			i, lable[i % 4]);
		usleep(35000);
		fflush(stdout);
		i ++;
	}
	printf("\n");
}

void	jumpscare(void)
{
	int	random_num;

	random_num = random() % 1000;
	if (random_num == 15)
	{
		random_num *= (random() % 26);
		if (random_num % 2)
			system("afplay textures/jumpscare1.mp3 &");
		else
			system("afplay textures/jumpscare2.mp3 &");
	}
}
