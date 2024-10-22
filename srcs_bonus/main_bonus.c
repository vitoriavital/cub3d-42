/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:07:27 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/22 17:22:00 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static int	validate_input(int argc, char **argv, t_game *game)
{
	if (argc < 2)
	{
		printf("Error: Not enough params!\n");
		free(game);
		return (EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		printf("Error: Too many params!\n");
		free(game);
		return (EXIT_FAILURE);
	}
	if (read_map(argv[1], game) == -1)
	{
		free_game(game);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	init_canvas(t_game *game)
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", true);
	if (!mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	image = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!image)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	game->image = image;
	game->mlx = mlx;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (validate_input(argc, argv, game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_canvas(game) == EXIT_FAILURE)
	{
		free_game(game);
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(game->mlx, ft_game, game);
	mlx_loop_hook(game->mlx, ft_mini_map, game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	return (EXIT_SUCCESS);
}
