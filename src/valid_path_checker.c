/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_path_checker.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: svrielin <svrielin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 19:02:05 by svrielin      #+#    #+#                 */
/*   Updated: 2022/11/02 15:21:22 by svrielin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	locate_start_finish(t_map *map)
{
	int		row;
	int		column;

	row = 0;
	column = 0;
	while (row < map->rowlen)
	{
		while (column < map->columnlen)
		{
			if (map->grid[row][column] == 'P')
			{
				map->startrow = row;
				map->startcolumn = column;
			}
			if (map->grid[row][column] == 'E')
			{
				map->exitrow = row;
				map->exitcolumn = column;
			}
			column++;
		}
		column = 0;
		row++;
	}
}

bool	if_valid_cell(int row, int col, t_map *map, char **gridcopy)
{
	if (gridcopy[row][col] != 'V' && map->grid[row][col] != '1')
		return (true);
	else
		return (false);
}

void	count_entity(t_entity *entity, int row, int col, char **grid)
{
	if (grid[row][col] == 'E')
		entity->exit++;
	if (grid[row][col] == 'C')
		entity->collectible++;
}

void	flood_fill(int row, int col, t_map *map, char **gridcopy)
{
	const int	delta_row[] = {1, 0, -1, 0};
	const int	delta_col[] = {0, 1, 0, -1};
	int			next_row;
	int			next_col;
	int			i;

	i = 0;
	gridcopy[row][col] = 'V';
	while (i < 4)
	{
		next_row = row + delta_row[i];
		next_col = col + delta_col[i];
		if (if_valid_cell(next_row, next_col, map, gridcopy))
		{
			count_entity(&map->reached, next_row, next_col, map->grid);
			flood_fill(next_row, next_col, map, gridcopy);
		}
		i++;
	}
}

void	check_valid_path(t_map *map)
{
	char	**gridcopy;
	int		row;

	map->reached.exit = 0;
	map->reached.collectible = 0;
	gridcopy = copy_grid(map->grid, map->rowlen);
	locate_start_finish(map);
	flood_fill(map->startrow, map->startcolumn, map, gridcopy);
	row = 0;
	while (row < map->rowlen)
	{
		free(gridcopy[row]);
		row++;
	}
	free (gridcopy);
	if (map->reached.collectible != map->total_collectibles)
		so_long_error(MAP_PATH_COLL, map);
	if (map->reached.exit != 1)
		so_long_error(MAP_PATH, map);
}
