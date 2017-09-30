#include "raster_image.hpp"

raster_image::raster_image(unsigned int width, unsigned int height)
{
	image_red_array = new color_component[width*height];
	image_green_array = new color_component[width*height];
	image_blue_array = new color_component[width*height];
	
	image_width = width;
	image_height = height;
	
	for (unsigned int y = 0; y < height; y++) //Set all pixels to white.
	{
		for (unsigned int x = 0; x < width; x++)
		{
			image_red_array[y*width+x] = 255;
			image_green_array[y*width+x] = 255;
			image_blue_array[y*width+x] = 255;
		}
	}
}

raster_image::~raster_image()
{
	delete[] image_red_array;
	delete[] image_green_array;
	delete[] image_blue_array;
}

color_component* raster_image::get_image_red_array()
{
	return image_red_array;
}

color_component* raster_image::get_image_green_array()
{
	return image_green_array;	
}

color_component* raster_image::get_image_blue_array()
{
	return image_blue_array;
}

void raster_image::set_pixel(unsigned int x, unsigned int y, color c)
{
	image_red_array[y*image_width+x] = (color_component)((c >> 16) & 255);
	image_green_array[y*image_width+x] = (color_component)((c >> 8) & 255);
	image_blue_array[y*image_width+x] = (color_component)(c & 255);
}
