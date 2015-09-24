/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VerticalLayout.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:43 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/24 11:42:28 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTICALLAYOUT_HPP
# define VERTICALLAYOUT_HPP

# include <vector>

# include "ALayout.hpp"
# include "IViewHolder.hpp"

namespace ftui
{

class	VerticalLayout : public ALayout
{
public:
	virtual ~VerticalLayout(void);

	AView					*createChild(std::string const &type, ...);

	static AView			*createView(XmlParser &xml);

protected:

	VerticalLayout(XmlParser &xml);

private:
	VerticalLayout(void) = delete;
	VerticalLayout(VerticalLayout const &src) = delete;
	VerticalLayout			&operator=(VerticalLayout const &rhs) = delete;

public:
	class	ViewHolder : public IViewHolder
	{
	public:
		virtual ~ViewHolder(void);

		virtual ALayout			*getParent(void);
		virtual ALayout const	*getParent(void) const;

		virtual AView			*getView(void);
		virtual AView const		*getView(void) const;

		virtual Vec2<int>		getPos(void) const;
		virtual Vec2<int>		getSize(void) const;

	protected:

		ViewHolder(XmlParser &xml);

		AView				*_view;

	private:
		ViewHolder(void) = delete;
		ViewHolder(ViewHolder const &src) = delete;
		ViewHolder			&operator=(ViewHolder const &rhs) = delete;
	};
};

};

#endif
