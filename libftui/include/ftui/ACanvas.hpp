/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACanvas.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:16:40 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/02 10:25:20 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACANVAS_HPP
# define ACANVAS_HPP

# include "ftui/libftui.hpp"

namespace ftui
{

/*
** ACanvas
** -
** Base class for a drawing canvas
** -
** TODO: Think about ACanvas and implement one
*/
class	ACanvas
{
public:
	ACanvas(void);
	virtual ~ACanvas(void);

protected:

private:
	ACanvas(ACanvas const &src);
	ACanvas			&operator=(ACanvas const &rhs);
};

};

#endif
