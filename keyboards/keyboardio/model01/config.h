/*
Copyright 2018 James Laird-Wah

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* key matrix size; rows are doubled for split */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

/* Hardware brightness cap applied to every LED channel (0-255), whatever set
 * the colour. 160 matches Kaleidoscope's solid colours, which are calibrated
 * to draw 500mA or less. Set to 255 to disable the cap. */
#ifndef MODEL01_LED_MAX_VALUE
#    define MODEL01_LED_MAX_VALUE 160
#endif
