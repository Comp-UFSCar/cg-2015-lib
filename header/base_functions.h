/** @file base_functions.h
 *  @brief Header file for Base Functions for the library.
 *
 *  This contains all the basic functions that will provide assistance to other functions
 *  and to work with all the available structures.
 *
 *  @author Thales Menato (thamenato)
 *  @author Daniel Nobusada (nobusada)
 *  @author Marcelo Lopes Lotufo (0tho)
 *
 */

#ifndef FUNCTIONS_LIB_H
#define FUNCTIONS_LIB_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "../header/structs.h"
#include "../header/object2d_functions.h"


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
int XDump(struct BufferDevice *device, struct Palette *palette);

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
struct BufferDevice *createBuffer(int xmax, int ymax);

/** @brief Allocates the memory for Window and set parameters.
 *  @param xmin Minimum value for X, start point.
 *  @param xmax Maximum value for X, end point.
 *  @param ymin Minimum value for X, start point.
 *  @param ymax Maximum value for Y, end point.
 *  @return Memory address with Window using parameters values.
 */
struct Window *createWindow(float xmin, float xmax, float ymin, float ymax);

/** @brief Normalizes Point2D from Universe to Window.
 *  @param p Point2D to be normalized.
 *  @param win Window to be used as normalization parameter.
 *  @return Normalized Point2D.
 */
struct Point2D *sru2srn(struct Point2D *p, struct Window *win);

/** @brief Normalized Point2D to BufferDevice position.
 *  @param normP The normalized Point2D to be used.
 *  @param device BufferDevice where the point will be set.
 *  @return Point2D position at the BufferDevice.
 */
struct Point2D *srn2srd(struct Point2D *normP, struct BufferDevice *device);

/** @brief Allocates memory and set values for Point2D members.
 *  @param x value of x.
 *  @param y value of y.
 *  @param the color number that will be used as reference on Palette.
 *  @return Memory address with Point2D using parameters values.
 */
struct Point2D *createPoint2D(double x, double y);

/** @brief Creates an Object2D allocating it's memory based on number of points.
 *  @param max_points Maximum of points that this object will have.
 *  @return Memory address with Object2D struct.
 */
struct Object2D *createObject2D(int max_points, int borderColor, int fillColor);

/** @brief Add a Point2D to an Object2D.
 *  @param p Point2D that will be added to the object.
 *  @param obj Object2D that will receive the point.
 *  @return True if point was added, False otherwise.
 */
int addPoint2DToObject2D(struct Point2D *p, struct Object2D *obj);


/** @brief Create an equivalent Object2D and return it.
 *  @param object The Object2D that will be cloned.
 */
struct Object2D *getObject2DClone(struct Object2D *object);

/** @brief Create a Palette with parameter number of colors.
 *  @param numberOfColors The number of colors that this Palette will have.
 *  @return Memory address with allocated Palette.
 */
struct Palette *createPalette(int numberOfColors);

/** @brief Create an RGBColor.
 *
 *  Using float values in range [0,255] for each color (RGB),
 *  it defines a new struct RGBColor and returns it.
 *
 *  @param red float value in range [0,255] for Red color.
 *  @param green float value in range [0,255] for Green color.
 *  @param blue float value in range [0,255] for Blue color.
 *  @return RGBColor containing all information passed.
 */
struct RGBColor newRGBColor(float red, float green, float blue);

/** @brief Create an HSVColor.
 *
 *  Using float values in range [0,255] for each information (HSV),
 *  it defines a new struct HSVColor and returns it.
 *
 *  @param hue float value in range [0,360] for hue.
 *  @param saturation float value in range [0,255] for saturation.
 *  @param value float value in range [0,255] for value.
 *  @return HSVColor containing all information passed.
 */
struct HSVColor newHSVColor(float hue, float saturation, float value);

/** @brief Add a HSVColor to the palette.
 *
 *  Converts the HSVColor received to RGBColor and add it to the palette.
 *
 *  @param hsvColor The HSVColor that will be added.
 *  @param palette Palette where color will be added.
 *  @return True if color was added, False otherwise.
 */
int addHSVColorToPalette(struct HSVColor hsvColor, struct Palette *palette);

/** @brief Add a RGBColor to a Palette.
 *
 *  Tried to add a new RGBColor to the palette, if already full it will
 *  return false.
 *
 *  @param rgbColor The RGBColor to be added.
 *  @param palette Palette where color will be added.
 *  @return True if added to palette, False if palette was already full.
 */
int addRGBColorToPalette(struct RGBColor rgbColor, struct Palette *palette);

/** @brief Get a RGBColor from Palette.
 *
 *  Get the RGBColor representation of the color inside the palette
 *  using colorNumber as index.
 *
 *  @param colorNumber Index of color wanted.
 *  @param palette Palette that will be used.
 *  @return RGBColor defined on that palette index.
 */
struct RGBColor *getRGBColorFromPalette(int colorNumber, struct Palette *palette);

/** @brief Get a HSVColor from Palette.
 *
 *  Get the HSVColor representation of the color inside the palette
 *  using colorNumber as index.
 *
 *  @param colorNumber Index of color wanted.
 *  @param palette Palette that will be used.
 *  @return HSVColor defined on that palette index.
 */struct HSVColor *getHSVColorFromPalette(int colorNumber, struct Palette *palette);

/** @brief Convert the color from RGB to HSV.
 *  @param rgbColor the RGB color to be converted.
 *  @return HSVColor equivalent to the RGB.
 */
struct HSVColor *rgb2hsv(struct RGBColor rgbColor);

/** @brief Convert the color from HSV to RGB.
 *  @param hsvColor the HSV color to be converted.
 *  @return RGBColor equivalent to the HSV.
 */
struct RGBColor *hsv2rgb(struct HSVColor hsvColor);

/** @brief Set the Object2D border and fill colors.
 *  @param obj Object2D to receive color parameters.
 *  @param borderColor int value of palette's color index for border.
 *  @param fillColor int value of palette's color index for filling.
 */
void setObject2DColor(struct Object2D *obj, int borderColor, int fillColor);

#endif