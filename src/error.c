/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:18:03 by svrielin      #+#    #+#                 */
/*   Updated: 2022/10/30 15:13:32 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

char *error_messages(t_error errorcode)
{
	char	*message[] = {
		"Exit: congratulations you won the game!\n",
		"Error: map invalid, not surrounded by walls\n",
		"Error: map invalid, invalid char found\n",
		"Error: map invalid, map should contain 1 player\n",
		"Error: map invalid, map should contain 1 exit\n",
		"Error: map invalid, map should contain 1 or more collectibles\n",
		"Error: map has no valid path to the exit\n",
		"Error: map has no valid path where everything can be collected\n",
		"Error: map invalid, too big for current screen size\n",
		"Error: map invalid, map is not rectangular\n",
	};
	return (message[errorcode]);
}

int		so_long_error_free(t_error code, t_game *game)
{
	delete_img(game->mlx, &game->sprite);
	mlx_terminate(game->mlx);
	return (so_long_error(code, &game->map));
}

int	so_long_error(t_error code, t_map *map)
{
	int row = 0;
	while (row < map->rowlen)
	{
		free(map->grid[row]);
		row++;
	}
	ft_putstr_fd(error_messages(code), STDERR_FILENO);
	if (code == SUCCES)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}