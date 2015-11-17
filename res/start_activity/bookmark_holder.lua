-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   bookmark_holder.lua                                :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2015/11/16 15:14:38 by ngoguey           #+#    #+#             --
--   Updated: 2015/11/17 18:43:27 by ngoguey          ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

local frame = _G['bookmark-holder']
assert(frame ~= nil)

function frame:at(i)
  local sz = frame:size();
  local v;

  if i < sz then
	return self:rawat(i);
  end
  while (sz < i + 1) do
	v = createView('Bookmark', 'Bookmark' .. tostring(i));
	self:addView(v);
	v:setVisibility(0);
	sz = sz + 1;
  end
  return v;
end

frame.rawat = getmetatable(frame).at;
