-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   randomPuzzleButton.lua                             :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/09 15:58:50 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/09 19:00:03 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local frame = randomPuzzleButton
assert(frame ~= nil);

function frame:onClick(_, _)
   local grid = generate_grid(11, true);
   local puzzleFrame = puzzleFrame;

   puzzleFrame:showGrid(grid);
end

frame:setCallback('onClick', frame.onClick);