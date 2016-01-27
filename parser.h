/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 16:59:42 by nbouteme          #+#    #+#             */
/*   Updated: 2016/01/27 16:59:59 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <libft/math.h>
# include <libft/mlx.h>

t_sparse_model	*parse_file(char **file);
t_model			*flatten_model(t_sparse_model *sm);

#endif
