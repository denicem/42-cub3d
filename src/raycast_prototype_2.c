/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_prototype_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:31:40 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/13 03:00:24 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define mapW  8      //map width
#define mapH  8      //map height
#define mapS 64      //map cube size

#include <math.h>

float dist(t_vect a, t_vect b, float ang)
{
	(void) ang;
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

void raycast_prototype_2()
{

	int map[]=           //the map array. Edit to change level but keep the outer walls
	{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,	
	};
	
	t_vect ray;
	int ray_angle = player_angle;
	t_vect offset;
	int dof;
	int i = 0;
	int mapX, mapY, mapP;
	while (i < 1)
	{
		//horizontal
		dof = 0;
		float dist_hor = 10000;
		t_vect ray_hor = player;
		float aTan = -1/tan(ray_angle);
		if (ray_angle > PI) // LOOK UP
		{
			ray.y = (((int) player.y >> 6) << 6) - 0.0001;
			ray.x = (player.y - ray.y) * aTan + player.x;
			offset.y = -64;
			offset.x = -offset.y * aTan;
		}
		if (ray_angle < PI) // LOOK_DOWN
		{
			ray.y = (((int) player.y >> 6) << 6) + 64;
			ray.x = (player.y - ray.y) * aTan + player.x;
			offset.y = 64;
			offset.x = -offset.y * aTan;
		}
		if (ray_angle == 0 || ray_angle == PI) // LOOK LEFT OR RIGHT
		{
			ray.x = player.x;
			ray.y = player.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mapX = (int) (ray.x) >> 6;
			mapY = (int) (ray.y) >> 6;
			mapP = mapY * mapW  + mapX;
			if (mapP > 0 && mapP < mapW * mapH && map[mapP] == 1) // HIT WALL
			{
				ray_hor = ray;
				dist_hor = dist(player, ray_hor, ray_angle);
				dof = 8;
			}
			else
			{
				ray.x += offset.x;
				ray.y += offset.y;
				dof++;
			}
		}

		// vertical
		dof = 0;
		float dist_ver = 10000;
		t_vect ray_ver = player;
		double nTan = -tan(ray_angle);
		if (ray_angle > PI2 && ray_angle < PI3) // LOOK LEFT
		{
			ray.x = (((int) player.x >> 6) << 6) - 0.0001;
			ray.y = (player.y - ray.x) * nTan + player.y;
			offset.x = -64;
			offset.y = -offset.x * nTan;
		}
		if (ray_angle < PI2 || ray_angle > PI3) // LOOK RIGHT
		{
			ray.x = (((int) player.x >> 6) << 6) + 64;
			ray.y = (player.x - ray.x) * nTan + player.y;
			offset.x = 64;
			offset.y = -offset.x * nTan;
		}
		if (ray_angle == 0 || ray_angle == PI)
		{
			ray.x = player.x;
			ray.y = player.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mapX = (int) (ray.x) >> 6;
			mapY = (int) (ray.y) >> 6;
			mapP = mapY * mapW  + mapX;
			if (mapP > 0 && mapP < mapW * mapH && map[mapP] == 1)
			{
				ray_ver = ray;
				dist_ver = dist(player, ray_ver, ray_angle);
				dof = 8;
			}
			else
			{
				ray.x += offset.x;
				ray.y += offset.y;
				dof++;
			}
		}
		
		printf("RAY_HOR: %f %f\n", ray_hor.x, ray_hor.y);
		printf("DIST_HOR: %f \n", dist_hor);
		printf("RAY_VER: %f %f\n", ray_ver.x, ray_ver.y);
		printf("DIST_VER: %f \n", dist_ver);
		printf("RAY: %f %f\n", ray.x, ray.y);
		if (dist_ver < dist_hor)
			ray = ray_ver;
		if (dist_hor < dist_ver)
			ray = ray_hor;
		i++;
	}
}