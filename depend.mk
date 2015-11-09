O_FILES :=	o/srcs/GlCanvasHolder.o o/srcs/Grid.o o/srcs/IState.o o/srcs/Main.o \
			o/srcs/OCamlBinding.o o/srcs/OCamlBinding_lua.o \
			o/srcs/StartState.o o/srcs/Tiles.o

LIBS_DEPEND := libftui/libftui.a

libs:
	make -C libftui
.PHONY: libs



MAX_SOURCE_LEN := 25
o/srcs/GlCanvasHolder.o: srcs/GlCanvasHolder.cpp include/GlCanvasHolder.hpp \
	libftui/include/ft/Color.hpp libftui/include/ft/Rect.hpp \
	libftui/include/ft/Vec.hpp libftui/include/ft/assert.hpp \
	libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ftui/Canvas.hpp \
	libftui/include/ftui/libftui.hpp include/gl.hpp \
	libftui/include/ft/utils.hpp | o/srcs/
o/srcs/Grid.o: srcs/Grid.cpp include/Grid.hpp libftui/include/ft/utils.hpp \
	| o/srcs/
o/srcs/IState.o: srcs/IState.cpp include/Grid.hpp include/ISolverListener.hpp \
	include/IState.hpp include/OCamlBinding.hpp libftui/include/ft/Color.hpp \
	libftui/include/ft/Rect.hpp libftui/include/ft/Vec.hpp \
	libftui/include/ft/assert.hpp libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ft/utils.hpp \
	libftui/include/ftui/Canvas.hpp libftui/include/ftui/libftui.hpp \
	include/StartState.hpp include/tiles/Tiles.hpp \
	libftui/include/ftui/Activity.hpp libftui/include/ftui/DefaultEventBox.hpp \
	libftui/include/ftui/EventBox.hpp libftui/include/ftui/EventParams.hpp \
	libftui/include/ftui/IEventBox.hpp libftui/include/ftui/IEventParams.hpp \
	libftui/include/ftui/IViewHolder.hpp \
	libftui/include/ftui/templates/Activity.tpp \
	libftui/include/ftui/templates/EventBox.tpp | o/srcs/
o/srcs/Main.o: srcs/Main.cpp libftui/include/ft/utils.hpp \
	include/config_window.hpp include/ftce/math.hpp libftui/include/ft/Vec.hpp \
	libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp include/GlCanvasHolder.hpp \
	libftui/include/ft/Color.hpp libftui/include/ft/Rect.hpp \
	libftui/include/ft/assert.hpp libftui/include/ftui/Canvas.hpp \
	libftui/include/ftui/libftui.hpp include/gl.hpp include/Grid.hpp \
	include/ISolverListener.hpp include/OCamlBinding.hpp include/IState.hpp \
	include/StartState.hpp include/tiles/Tiles.hpp \
	libftui/include/ftui/Activity.hpp libftui/include/ftui/DefaultEventBox.hpp \
	libftui/include/ftui/EventBox.hpp libftui/include/ftui/EventParams.hpp \
	libftui/include/ftui/IEventBox.hpp libftui/include/ftui/IEventParams.hpp \
	libftui/include/ftui/IViewHolder.hpp \
	libftui/include/ftui/templates/Activity.tpp \
	libftui/include/ftui/templates/EventBox.tpp include/Main.hpp | o/srcs/
o/srcs/OCamlBinding.o: srcs/OCamlBinding.cpp include/Grid.hpp \
	include/ISolverListener.hpp include/OCamlBinding.hpp \
	libftui/include/ft/Vec.hpp libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ft/utils.hpp | o/srcs/
o/srcs/OCamlBinding_lua.o: srcs/OCamlBinding_lua.cpp include/Grid.hpp \
	include/ISolverListener.hpp include/OCamlBinding.hpp \
	libftui/include/ft/Vec.hpp libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ft/utils.hpp | o/srcs/
o/srcs/StartState.o: srcs/StartState.cpp include/Grid.hpp \
	include/ISolverListener.hpp include/IState.hpp include/OCamlBinding.hpp \
	include/StartState.hpp include/tiles/Tiles.hpp \
	libftui/include/ft/Color.hpp libftui/include/ft/Rect.hpp \
	libftui/include/ft/Vec.hpp libftui/include/ft/assert.hpp \
	libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ft/utils.hpp \
	libftui/include/ftui/Activity.hpp libftui/include/ftui/Canvas.hpp \
	libftui/include/ftui/DefaultEventBox.hpp libftui/include/ftui/EventBox.hpp \
	libftui/include/ftui/EventParams.hpp libftui/include/ftui/IEventBox.hpp \
	libftui/include/ftui/IEventParams.hpp libftui/include/ftui/IViewHolder.hpp \
	libftui/include/ftui/libftui.hpp \
	libftui/include/ftui/templates/Activity.tpp \
	libftui/include/ftui/templates/EventBox.tpp include/config_window.hpp \
	include/ftce/math.hpp | o/srcs/
o/srcs/Tiles.o: srcs/Tiles.cpp include/tiles/Tiles.hpp \
	libftui/include/ft/Vec.hpp libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp include/gl.hpp | o/srcs/
