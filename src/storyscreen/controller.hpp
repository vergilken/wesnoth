/* $Id$ */
/*
   Copyright (C) 2009 by Ignacio R. Morelle <shadowm2006@gmail.com>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2
   or at your option any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

/**
 * @file storyscreen/controller.hpp
 * Storyscreen controller (interface).
 */

#ifndef STORYSCREEN_CONTROLLER_HPP_INCLUDED
#define STORYSCREEN_CONTROLLER_HPP_INCLUDED

#include "events.hpp"
#include "variable.hpp"
#include "video.hpp"

class display;
class game_state;
// class vconfig;

namespace storyscreen {

class part;
class floating_image;

class controller
{
public:
	controller(display& disp, const vconfig& data, const std::string& scenario_name);
	~controller();

	/**
	 * Display all story screen parts in a first..last sequence.
	 */
	void show_all_parts();
	/**
	 * Display a single story screen part.
	 * @return Next part requested by the user interface.
	 */
	size_t show_part(size_t part_num);

private:
	// Executes WML flow instructions and inserts parts.
	void resolve_wml(const vconfig& cfg);
	// Used by ctor.
	void build_parts() {
		resolve_wml(data_);
	}
	// Used by dtor.
	void clear_parts();

	display& disp_;
	const resize_lock disp_resize_lock_;
	const events::event_context evt_context_;

	vconfig data_;
	std::string scenario_name_;

	// The part cache.
	std::vector<part*> parts_;

	// The state of the world.
	game_state* gamestate_;

public:
	struct no_parts {};
	struct quit {};

};

} // end namespace storyscreen

#endif /* ! STORYSCREEN_CONTROLLER_HPP_INCLUDED */
