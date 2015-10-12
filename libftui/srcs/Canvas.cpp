// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Canvas.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:22 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/12 16:13:15 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/Canvas.hpp"
#include "ft/utils.hpp"

extern "C"
{

#include <ft2build.h>
#include FT_FREETYPE_H

}

#include <cstring>
#include <vector>
#include <unordered_map>

#include <iostream> // TODO remove

namespace ftui
{

/*
** Globals used to manage fonts
*/
static FT_Library			g_freetype;
static bool					g_freetype_init = false;
static std::unordered_map<std::string, Canvas::font_t> g_faces_cache;
static std::vector<FT_Face>	g_faces;

Canvas::Canvas(ft::Color::t *bitmap, int width, int height) :
	_bitmap(bitmap),
	_width(width),
	_height(height),
	_clip(0, 0, width, height),
	_alpha(1.f)
{
}

Canvas::Canvas(Canvas const &src) :
	_bitmap(src._bitmap),
	_width(src._width),
	_height(src._height),
	_alpha(src._alpha)
{
}

Canvas::~Canvas(void)
{
}

Canvas			&Canvas::operator=(Canvas const &rhs)
{
	_bitmap = rhs._bitmap;
	_width = rhs._width;
	_height = rhs._height;
	_alpha = rhs._alpha;
	return (*this);
}

/*
** Bitmap
*/
ft::Color::t const	*Canvas::getBitmap(void) const
{
	return (_bitmap);
}

int				Canvas::getBitmapWidth(void) const
{
	return (_width);
}

int				Canvas::getBitmapHeight(void) const
{
	return (_height);
}

void			Canvas::clear(void)
{
	memset(_bitmap, 0, _width * _height * sizeof(ft::Color::t));
}

void			Canvas::clear(ft::Rect<int> const &rect)
{
	int const	width = rect.getWidth() * sizeof(ft::Color::t);
	int			end;
	int			offset;

	offset = rect.top * _width + rect.left;
	end = rect.getHeight() * _width + offset;
	while (offset < end)
	{
		memset(_bitmap + offset, 0, width);
		offset += _width;
	}
}

/*
** Clip
*/
ft::Rect<int> const	&Canvas::getClip(void) const
{
	return (_clip);
}

int				Canvas::getWidth(void) const
{
	return (_clip.getWidth());
}

int				Canvas::getHeight(void) const
{
	return (_clip.getHeight());
}

void			Canvas::applyClip(ft::Rect<int> const &rect)
{
	_clip.top += rect.top;
	_clip.left += rect.left;
	_clip.setSize(ft::make_vec(rect.getWidth(), rect.getHeight()));
}

void			Canvas::setClip(ft::Rect<int> const &rect)
{
	_clip = rect;
}

/*
** Alpha
*/
float			Canvas::getAlpha(void) const
{
	return (_alpha);
}

void			Canvas::applyAlpha(float alpha)
{
	_alpha *= alpha;
}

void			Canvas::setAlpha(float alpha)
{
	_alpha = alpha;
}

/*
** Render rect
*/
void			Canvas::drawRect(ft::Rect<int> const &rect, Params const &opt)
{
	if (ft::Color::a(opt.fillColor) != 0)
		_fillRect(rect, ft::Color::alpha(opt.fillColor, _alpha));
	if (ft::Color::a(opt.strokeColor) != 0)
		_strokeRect(rect, ft::Color::alpha(opt.strokeColor, _alpha),
			opt.lineWidth);
}

void			Canvas::_strokeRect(ft::Rect<int> const &rect,
					ft::Color::t color, int lineWidth)
{
	int const		left = rect.left + _clip.left;
	int const		right = rect.right + _clip.left;
	int				top;
	int				y;

	if (rect.getWidth() == 0 || rect.getHeight() == 0)
		return ;
	y = rect.bottom + _clip.top - 1;
	top = std::max(rect.bottom - lineWidth, rect.top) + _clip.top;
	while (y >= top)
		putPixel(left, y--, color, rect.getWidth());
	top = rect.top + _clip.top + lineWidth;
	while (y >= top)
	{
		putPixel(left, y, color, lineWidth);
		putPixel(right - lineWidth, y, color, lineWidth);
		y--;
	}
	top -= lineWidth;
	while (y >= top)
		putPixel(left, y--, color, rect.getWidth());
}

void			Canvas::_fillRect(ft::Rect<int> const &rect, ft::Color::t color)
{
	int const	left = rect.left + _clip.left;
	int const	top = rect.top + _clip.top;
	int const	width = rect.getWidth();
	int			y;

	y = rect.bottom + _clip.top;
	while (--y >= top)
		putPixel(left, y, color, width);
}

/*
** Render text
*/
void			Canvas::drawText(ft::Vec2<int> pos, std::string const &text,
					Params const &opt)
{
	FT_Face			face;
	FT_UInt			glyph_index;

	if (ft::Color::a(opt.fillColor) == 0 || opt.lineWidth <= 0
		|| opt.font >= g_faces.size())
		return ;
	pos += ft::make_vec(_clip.left, _clip.top);
	face = g_faces[opt.font];
	if (FT_Set_Pixel_Sizes(face, 0, opt.lineWidth))
		throw std::runtime_error("Cannot resize font (drawText)");
	for (uint32_t i = 0; i < text.size(); i++)
	{
		glyph_index = FT_Get_Char_Index(face, text[i]);
		if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
			continue ;
		if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
			continue ;
		{
			/*
			** TODO: move (putGreyBitmap)
			*/
			uint8_t const	*greyMap = face->glyph->bitmap.buffer;

			if (face->glyph->bitmap.pixel_mode != FT_PIXEL_MODE_GRAY)
				throw std::runtime_error("Unsupported font (drawText)");
			uint32_t	x = 0;
			uint32_t	y = face->glyph->bitmap.rows;
			uint32_t	dst_y = pos.y + (face->descender >> 6);
			uint32_t	height = (face->height + face->ascender + face->descender) >> 6;
			uint32_t	dst_x = pos.x + face->glyph->bitmap_left;
			while (y-- > 0)
			{
				x = 0;
				while (x < face->glyph->bitmap.width)
				{
					putPixel(x + dst_x, height - y + dst_y,
						ft::Color::alpha(opt.fillColor, greyMap[x]));
					x++;
				}
				greyMap += face->glyph->bitmap.pitch;
			}
		}
		pos.x += face->glyph->advance.x >> 6;
	}
}

ft::Vec2<int>	Canvas::measureText(std::string const &text, Params const &opt)
{
	ft::Vec2<int>	size(0, 0);
	FT_Face			face;
	FT_UInt			glyph_index;

	if (opt.lineWidth <= 0 || opt.font >= g_faces.size())
		return (size);
	face = g_faces[opt.font];
	if (FT_Set_Pixel_Sizes(face, 0, opt.lineWidth))
		throw std::runtime_error("Cannot resize font (measureText)");
	for (uint32_t i = 0; i < text.size(); i++)
	{
		glyph_index = FT_Get_Char_Index(face, text[i]);
		if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
			continue ;
		size.x += face->glyph->advance.x >> 6;
	}
	size.y = (face->height + face->ascender + face->descender) >> 6;
	std::cout << "text size: " << size << std::endl;
	return (size);
}

/*
** Font management
*/
Canvas::font_t	Canvas::getFont(std::string const &file)
{
	auto const			&it = g_faces_cache.find(file);

	if (!g_freetype_init)
	{
		if (FT_Init_FreeType(&g_freetype))
			throw std::runtime_error("Cannot load FreeType library");
		g_freetype_init = true;
	}
	if (it != g_faces_cache.end())
		return (it->second);
	return (loadFont(file));
}

Canvas::font_t	Canvas::loadFont(std::string const &file)
{
	FT_Face				face;

	if (FT_New_Face(g_freetype, file.c_str(), 0, &face))
		throw std::runtime_error(ft::f("Cannot load %", file));
	g_faces.push_back(face);
	return (g_faces.size() - 1);
}

};
