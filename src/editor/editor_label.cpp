// Pingus - A free Lemmings clone
// Copyright (C) 2007 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "editor/editor_label.hpp"

#include "engine/display/drawing_context.hpp"
#include "pingus/fonts.hpp"

namespace Editor {

EditorLabel::EditorLabel(const Rect& rect_, const std::string& text_) :
  RectComponent(rect_),
  text(text_)
{
}

EditorLabel::EditorLabel(const std::string& text_) :
  text(text_)
{
}

void
EditorLabel::draw (DrawingContext& gc)
{
  gc.print_left(Fonts::verdana11,
                Vector2i(rect.left, rect.top + rect.get_height()/2 - Fonts::verdana11.get_height()/2),
                text);
}

void
EditorLabel::update (float delta)
{
}

} // namespace Editor

/* EOF */