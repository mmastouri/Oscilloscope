/******************************************************************************
*
* @brief     This file is part of the TouchGFX 4.6.0 evaluation distribution.
*
* @author    Draupner Graphics A/S <http://www.touchgfx.com>
*
******************************************************************************
*
* @section Copyright
*
* This file is free software and is provided for example purposes. You may
* use, copy, and modify within the terms and conditions of the license
* agreement.
*
* This is licensed software for evaluation use, any use must strictly comply
* with the evaluation license agreement provided with delivery of the
* TouchGFX software.
*
* The evaluation license agreement can be seen on www.touchgfx.com
*
* @section Disclaimer
*
* DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
* no obligation to support this software. Draupner Graphics A/S is providing
* the software "AS IS", with no express or implied warranties of any kind,
* including, but not limited to, any implied warranties of merchantability
* or fitness for any particular purpose or warranties against infringement
* of any proprietary rights of a third party.
*
* Draupner Graphics A/S can not be held liable for any consequential,
* incidental, or special damages, or any other relief, or for any claim by
* any third party, arising from your use of this software.
*
*****************************************************************************/
#include <gui/common/Graph.hpp>
#include <math.h>
#include <stdio.h>


Graph::Graph()
{
	graphColor = Color::getColorFrom24BitRGB(0x07, 0x89, 0xBA);
	graphBlendColor = Color::getColorFrom24BitRGB(71, 71, 71);
	
	counter = 0;
	
	setWidth(graphWidth);
	setHeight(graphHeight);

	for (int i = 0; i < graphWidth; ++i)
	{
		curveSegments[i].y = 0;
		curveSegments[i].alphas[0] = 0;
	}
}


void Graph::calculateSegments()
{
	for (int i = 0; i < graphWidth; i++)
	{
		counter++;

		//inject new values in already processed indexes
		values[GetCurrentIndex(0)] = (int)*(p_gragh_data + i);

		calculateOneSegment();
	}
}

void Graph::calculateOneSegment()
{
	uint16_t nbralpha = 0;
	uint16_t distance;
	uint16_t direction, maxdistance;

	CurveSegment& curveSegment = curveSegments[GetCurrentIndex(0)];

	uint16_t valueCur  = values[GetCurrentIndex(1)];
	uint16_t valueNext = values[GetCurrentIndex(2)];

	distance  = abs(valueNext - valueCur);
	direction = (valueNext - valueCur) > 0 ? 1 : 0;


	curveSegment.y = 0;
	memset(curveSegment.alphas, 0, graphAlphasPerColumn);

	curveSegment.y = valueCur;
	maxdistance = distance = MIN(distance, graphAlphasPerColumn);

	if (distance < graphLineWidth)
	{
		curveSegment.alphas[nbralpha++] = 255;

	}
	else
	{
		if (!direction)
		{
			curveSegment.y = valueNext;
		}


		while (distance--)
		{
			uint8_t alpha;
#if 0
			if(distance > (maxdistance/2))
				alpha = (uint8_t)(255 - 0.5f * (255 * distance) / maxdistance);
			else
				alpha = (uint8_t)(255 - 0.5f * (255 * (maxdistance- distance)) / maxdistance);
#else
			alpha = 255;
#endif

			curveSegment.alphas[nbralpha++] = alpha;
		}

	}
}


void Graph::drawCurve(uint16_t* frameBuffer, const Rect& invalidatedArea) const
{
	// invalidatedArea is relative to enclosing container
	Rect absoluteRect = getRect();

	uint16_t index = 0;
	int y ;
	uint8_t* alphas;

	for (int x = invalidatedArea.x + 1; x < invalidatedArea.right() - 1 ; x++)
	{
		CurveSegment curveSegment = curveSegments[GetCurrentIndex(index++)];

		y = absoluteRect.height/2  + absoluteRect.y - curveSegment.y;

		alphas = &curveSegment.alphas[0];

		// Graph is drawn with absolute coordinates
		uint32_t offset = (absoluteRect.x + x) + HAL::DISPLAY_WIDTH *  y;

		while (*alphas)
		{
			if ( y > 0)
			{
				if (*alphas == 255)
				{
					frameBuffer[offset] = graphColor;
				}
				else
				{
					frameBuffer[offset] = blend(graphColor, graphBlendColor, *alphas);
				}
			}
			alphas++;
			y--;
			offset -= HAL::DISPLAY_WIDTH;
		}
	}
}


void Graph::SetGraphColor(colortype color)
{
	graphColor = color;
	
}

void Graph::SetGraphData(int *data)
{
	p_gragh_data = data;
}

Rect Graph::getSolidRect() const
{
	return Rect(0, 0, 0, 0);
}

uint16_t Graph::GetCurrentIndex(int16_t offset) const
{
	return (offset + counter) % graphWidth;
}


void Graph::setY(int16_t y)
{

	Widget::setY(y + y_offset);
}

void Graph::setPosition(int16_t x, int16_t y, int16_t width, int16_t height)
{
	y_offset = y;
	Widget::setPosition(x, y, width, height);
	for (int i = 0; i < graphPointsInGraph; i++)
	{
		values[i] = 0;
	}
}

void Graph::draw(const Rect& invalidatedArea) const
{
	uint16_t* frameBuffer = (uint16_t*)HAL::getInstance()->lockFrameBuffer();

	drawCurve(frameBuffer, invalidatedArea);

	HAL::getInstance()->unlockFrameBuffer();
}

void Graph::handleTickEvent()
{

	calculateSegments();
	invalidate();
}