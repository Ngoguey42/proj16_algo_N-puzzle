-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   start_activity.lua                                 :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/07 13:47:07 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/10 14:33:25 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local puzzleFrame = puzzleFrame;
assert(puzzleFrame ~= nil)

PUZZLEFRAME_TEXT_SIZE = 16;

function drawTextCenter(canvas, text, x, y)
	text_w, text_h = canvas:measureText(text, PUZZLEFRAME_TEXT_SIZE);
	canvas:drawText(text, x - (text_w / 2), y - (text_h / 2), 0xFF555555, PUZZLEFRAME_TEXT_SIZE);
end

function puzzleFrame:showGrid(grid)
   puzzleFrame.curPuzzle = grid;
   puzzleFrame.w = getPuzzleW(grid);
   puzzleFrame:queryRedraw();
   return ;
end

function puzzleFrame:onDraw(canvas)
   canvas:setFont("/Library/Fonts/Arial Black.ttf");
   if self.curPuzzle ~= nil then

	  assert(self.w ~= nil and self.w > 0);
	  assert(self.wpx ~= nil and self.wpx > 0);

	  local insets = 5.; -- INSET BORDER OF THE VIEW
	  local spacing = 1.; -- SPACING BETWEEN TILES

	  local last = self.w - 1;
	  local tile_w = (self.wpx - insets * 2 - spacing * last) / self.w;

	  local dt = tile_w + spacing;
	  local ypx = insets;
	  local xpx = 0.;
	  local i = 0;

	  for y = 0, last do
		 xpx = insets;
		 for x = 0, last do
			i = y * self.w + x;
			if self.curPuzzle[i] ~= 0 then
			   canvas:drawRect(xpx, ypx, xpx + tile_w, ypx + tile_w
							   , 0xB0FF0000, 0xA5FF0000, 8);
			   drawTextCenter(canvas, tostring(self.curPuzzle[i])
			   				  , xpx + (tile_w / 2), ypx + (tile_w / 2));
			end
			xpx = xpx + dt;
		 end
		 ypx = ypx + dt;
	  end

   end
end

function puzzleFrame:onSizeChange(x, _)
   print("puzzleFrame:onSizeChange: ", x, y, a);
   self.wpx, _ = x;
   puzzleFrame:queryRedraw();
end

puzzleFrame:setCallback('onDraw', puzzleFrame.onDraw);
puzzleFrame:setCallback('onSizeChange', puzzleFrame.onSizeChange);
puzzleFrame:setCallback('onMouseMove', function(self, x, y)
						   -- print("lua:onMouseMove", x, y);
									 end
);
puzzleFrame:setCallback('onMouseDown', function(self, x, y, b, m)
						   print("lua:onMouseDOWN", x, y, b, m);
									 end
);
puzzleFrame:setCallback('onMouseUp', function(self, x, y, b, m)
						   print("lua:onMouseUP", x, y, b, m);
									 end
);
puzzleFrame:setCallback('onKeyDown', function(self, b, m)
						   print("lua:onKeyDOWN", b, m);
						   if b == 32 then
							  self:hookMouseMove(0);
						   end
									 end
);
puzzleFrame:setCallback('onKeyUp', function(self, b, m)
						   print("lua:onKeyUP", b, m);
						   if b == 32 then
							  self:hookMouseMove(1);
						   end
									 end
);
puzzleFrame:hookMouseMove(1);
puzzleFrame:hookMouseClick(1);
puzzleFrame:hookKeyboard(1);

puzzleFrame.curPuzzle = {};
puzzleFrame.w = 3;

-- ft.ptab(puzzleFrame);
-- ft.ptab(AView);
-- ft.ptab(Canvas);

local caca = 42;
pipi = 42;
ft.ptab(_G);
