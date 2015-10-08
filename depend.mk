O_FILES :=	o/srcs/GlCanvasHolder.o o/srcs/SolidView.o o/srcs/main.o

LIBS_DEPEND := libftui/libftui.a

libs:
	make -C libftui
.PHONY: libs



MAX_SOURCE_LEN := 23
o/srcs/GlCanvasHolder.o: srcs/GlCanvasHolder.cpp include/GlCanvasHolder.hpp \
	libftui/include/ft/Rect.hpp libftui/include/ft/Vec.hpp \
	libftui/include/ft/assert.hpp libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ftui/Canvas.hpp \
	libftui/include/ftui/libftui.hpp include/gl.hpp \
	libftui/include/ft/utils.hpp | o/srcs/
o/srcs/SolidView.o: srcs/SolidView.cpp include/SolidView.hpp \
	libftui/include/ft/Rect.hpp libftui/include/ft/Vec.hpp \
	libftui/include/ft/assert.hpp libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ftui/AView.hpp \
	libftui/include/ftui/Canvas.hpp libftui/include/ftui/libftui.hpp \
	libftui/include/ftui/lua.hpp | o/srcs/
o/srcs/main.o: srcs/main.cpp libftui/include/ft/utils.hpp \
	libftui/include/ft/Vec.hpp libftui/include/ft/assert.hpp \
	libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ftui/Activity.hpp \
	libftui/include/ftui/DefaultEventBox.hpp libftui/include/ftui/EventBox.hpp \
	libftui/include/ftui/EventParams.hpp libftui/include/ftui/IEventBox.hpp \
	libftui/include/ftui/IEventParams.hpp libftui/include/ftui/IViewHolder.hpp \
	libftui/include/ftui/libftui.hpp libftui/include/ftui/lua.hpp \
	libftui/include/ftui/templates/Activity.tpp \
	libftui/include/ftui/luaCFunctions_helpers.hpp include/GlCanvasHolder.hpp \
	libftui/include/ft/Rect.hpp libftui/include/ftui/Canvas.hpp \
	include/SolidView.hpp libftui/include/ftui/AView.hpp include/gl.hpp \
	| o/srcs/
