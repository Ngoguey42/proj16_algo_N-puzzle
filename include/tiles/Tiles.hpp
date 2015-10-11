// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tiles.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/11 11:52:03 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/11 13:34:33 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TILES_HPP
# define TILES_HPP

//# include <string>
//# include <iostream>
//# include <stdexcept>
# include <array>
# include <vector>

# include "ft/Vec.hpp"

class Tiles
{
public:
	Tiles(ft::Vec2<int> const rectSize
		  , ft::Vec2<int> const triangleSize = ft::Vec2<int>(100, 100)
		  , int const pointRandomRadius = 30);
	virtual ~Tiles();

	void			render(void);

	
protected:
private:
	typedef ft::Vec2<float>						pos_t;
	typedef ft::Vec3<float>						col_t;
	typedef std::pair<pos_t, col_t>				point_t;
	typedef std::array<point_t, 3>				triangle_t;
	typedef std::vector<triangle_t>				mesh_t;

	typedef std::vector<point_t>				tmp_line_t;
	typedef std::vector<tmp_line_t>				tmp_grid_t;

	class Tmp
	{
	public:
		
		ft::Vec2<int> const		rectSize;
		ft::Vec2<int> const		triangleSize;
		int const				pointRandomRadius;

		ft::Vec2<int>			gridDim;
		tmp_grid_t				grid;

		Tmp(ft::Vec2<int> const rectSize
			, ft::Vec2<int> const triangleSize
			, int const pointRandomRadius);
		~Tmp();
		
	private:
		void					_buildGridDim(void);
		void					_buildGrid(void);

		ft::Vec2<float>			_pointDeltaPos(void);

		Tmp() = delete;
		Tmp(Tmp const &src) = delete;
		Tmp						&operator=(Tmp const &rhs) = delete;
	};
	
	unsigned int								_p;
	unsigned int								_me;
	mesh_t										_mesh;

	
	Tiles() = delete;
	Tiles(Tiles const &src) = delete;
	Tiles						&operator=(Tiles const &rhs) = delete;
};
//std::ostream					&operator<<(std::ostream &o, Tiles const &rhs);

#endif // ********************************************************* TILES_HPP //