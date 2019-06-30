/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashari <ashari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 19:13:27 by ashari            #+#    #+#             */
/*   Updated: 2019/06/30 19:13:28 by ashari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "material.h"
# include "intersection.h"

# define SHAPE_DATA_SIZE_RESERVE	128

# define SHAPE_ID_SPHERE			0
# define SHAPE_ID_PLANE				1
# define SHAPE_ID_CYLINDER			2
# define SHAPE_ID_CONE				3
# define SHAPE_ID_AABB				4

typedef	struct						s_shape
{
	int								id;
	unsigned char					data[SHAPE_DATA_SIZE_RESERVE];
	t_material						material;
	int								highlight;
}									t_shape;

#endif
