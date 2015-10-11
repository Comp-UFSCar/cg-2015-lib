/** @file base_functions.h
 *  @brief Header file for Base Functions for the library.
 *
 *  This contains all the basic functions that will provide assistance to other functions
 *  and to work with all the available structures.
 *
 *  @author Thales Menato (thamenato)
 *  @author Daniel Nobusada (nobusada)
 *
 */

#ifndef FUNCTIONS_LIB_H
#define FUNCTIONS_LIB_H

#include <X11/Xlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

/** @brief Creates a virtual device and displays the BufferDevice content on it.
 *
 *  This function uses the X11 to create a "simulated" display to our device, it is
 *  way that we can see if the lib functions are working properly / see their results.
 *  Usually this is called inside the main function.
 *
 *  @param device BufferDevice that you want to display.
 *  @param palette Palette that shall be used to define colors.
 *  @return True if X11 starts properly, otherwise False.
 */
int XDump(struct BufferDevice * device, struct Palette * palette);

/** @brief Set the World values.
 *  @param xmin Minimum value for X.
 *  @param xmax Maximum value for X.
 *  @param ymin Minimum value for Y.
 *  @param ymax Maximum value for Y.
 */
void setWorld(float xmin, float xmax, float ymin, float ymax);

/** @brief Allocates the memory for BufferDevice based on parameters.
 *  @param xmax Maximum value for X, width of BufferDevice matrix.
 *  @param ymax Maximum value for Y, height of BufferDevice matrix.
 *  @return Memory address with BufferDevice using parameters values.
 */
struct BufferDevice * createBuffer(int xmax, int ymax);

/** @brief Allocates the memory for Window and set parameters.
 *  @param xmin Minimum value for X, start point.
 *  @param xmax Maximum value for X, end point.
 *  @param ymin Minimum value for X, start point.
 *  @param ymax Maximum value for Y, end point.
 *  @return Memory address with Window using parameters values.
 */
struct Window * createWindow(float xmin, float xmax, float ymin, float ymax);

/** @brief Normalizes Point2D from Universe to Window.
 *  @param p Point2D to be normalized.
 *  @param win Window to be used as normalization parameter.
 *  @return Normalized Point2D.
 */
struct Point2D * sru2srn(struct Point2D * p, struct Window * win);

/** @brief Normalized Point2D to BufferDevice position.
 *  @param normP The normalized Point2D to be used.
 *  @param device BufferDevice where the point will be set.
 *  @return Point2D position at the BufferDevice.
 */
struct Point2D * srn2srd(struct Point2D * normP, struct BufferDevice * device);

/** @brief Allocates memory and set values for Point2D members.
 *  @param x value of x.
 *  @param y value of y.
 *  @param the color number that will be used as reference on Palette.
 *  @return Memory address with Point2D using parameters values.
 */
struct Point2D * setPoint(double x, double y, int color);

/** @brief Creates an Object2D allocating it's memory based on number of points.
 *  @param max_points Maximum of points that this object will have.
 *  @return Memory address with Object2D struct.
 */
struct Object2D * createObject(int max_points);

//TODO Documentacao do setObject
int setObject(struct Point2D * p, struct Object2D * obj);

//TODO Documentacao do drawObject
int drawObject(struct Object2D *object, struct Window *window, struct BufferDevice * device);

//TODO Documentacao do changeColor
struct Object2D *changeColor(struct Object2D *object, int color);

/** @brief Create a Palette with parameter number of colors.
 *  @param numberOfColors The number of colors that this Palette will have.
 *  @return Memory address with allocated Palette.
 */
struct Palette * createPalette(int numberOfColors);

/** @brief Set a new color to a Palette.
 *
 *  Using float values in range [0,1] for each color (RGB), it tries to add a new
 *  color to the palette.
 *
 *  @param red float value in range [0,1] for Red color.
 *  @param green float value in range [0,1] for Green color.
 *  @param blue float value in range [0,1] for Blue color.
 *  @return True if added to palette, False if palette was already full.
 */
int setColor(float red, float green, float blue, struct Palette *palette);

/** @brief Get a Color from Palette.
 *  @param colorNumber Index of color wanted.
 *  @param palette Palette that will be used.
 *  @return Color defined on palette.
 */
struct Color *getColor(int colorNumber, struct Palette *palette);

#endif