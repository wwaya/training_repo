/**************************************************************************
 *  Copyright 2012 KISS Institute for Practical Robotics                  *
 *                                                                        *
 *  This file is part of libkovan.                                        *
 *                                                                        *
 *  libkovan is free software: you can redistribute it and/or modify      *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation, either version 2 of the License, or     *
 *  (at your option) any later version.                                   *
 *                                                                        *
 *  libkovan is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with libkovan. Check the LICENSE file in the project root.      *
 *  If not, see <http://www.gnu.org/licenses/>.                           *
 **************************************************************************/

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "geom.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pixel
{
	int r;
	int g;
	int b;
} pixel;

/**
 * Opens the default system camera for use.
 * \return 1 on success, 0 on failure
 * \see camera_open_device
 * \see camera_close
 */
int camera_open();

/**
 * Opens a camera for use.
 * \param number The camera's id. 0 is the first camera, 1 is the second camera, etc.
 * \return 1 on success, 0 on failure
 * \see camera_open
 * \see camera_close
 */
int camera_open_device(int number);

/**
 * Loads the config file specified by name.
 * \param name The configuration to load. Configuration file names are case sensitive.
 * \note You must include the config file extension ".conf" in the name parameter.
 * \return 1 on success, 0 on failure.
 */
int camera_load_config(const char *name);

/**
 * Sets the camera's x resolution.
 * \param width The width in pixels
 */
void set_camera_width(int width);

/**
 * Sets the camera's y resolution.
 * \param width The height in pixels
 */
void set_camera_height(int height);

/**
 * Pulls a new image from the camera for processing.
 * \return 1 on success, 0 on failure.
 */
int camera_update();

/**
 * \param p The point at which the pixel lies.
 * \return The rgb value of the pixel located at point p.
 * \note A (r, g, b) value of (-1, -1, -1) will be returned for points that are out of range.
 */
pixel get_camera_pixel(point2 p);

/**
 * \return Number of channels in the current configuration.
 * \see get_object_count
 */
int get_channel_count();

/**
 * \param channel The channel to scan for objects.
 * \note Objects are sorted by area, largest first.
 * \return Number of objects in the given channel, -1 if channel doesn't exist.
 * \see get_channel_count
 */
int get_object_count(int channel);

/**
 * \return The string data associated with a given object on a given channel.
 * If there is no data associated, 0 is returned.
 * \note This data is not guaranteed to be null terminated.
 * \note This string pointer will be invalid after a call to camera_update()
 * \see get_object_data_length
 */
const char *get_object_data(int channel, int object);

/**
 * \return The length of the string data associated with a given object on a given channel.
 * If there is no data associated, 0 is returned. If the channel or object is invalid, 0 is returned.
 * \see get_object_data
 */
int get_object_data_length(int channel, int object);

/**
 * \return The confidence, between 0.0 and 1.0, that given object on the given channel is significant.
 * If the channel or object doesn't exist, 0.0 is returned.
 */
double get_object_confidence(int channel, int object);

/**
 * \return The object's bounding box area. -1 is returned if the channel or object doesn't exist.
 */
int get_object_area(int channel, int object);

/**
 * \return The bounding box of the given object on the given channel.
 */
rectangle get_object_bbox(int channel, int object);

/**
 * \return The (x, y) center of the given object on the given channel.
 */
point2 get_object_centroid(int channel, int object);

/**
 * Cleanup the current camera instance.
 * \see camera_open
 * \see camera_open_device
 */
void camera_close();

#ifdef __cplusplus
}
#endif


#endif
