/***************************************************************************
* NAME:     TriggerLine.hpp                                                *
*                                                                          *
* PURPOSE:  Header of TriggerLine.cpp                                      *
*                                                                          *
* PULIC VARIABLES:                                                         *
*                                                                          *
* Variable        Type            Description                              *
* --------        ----            -----------                              *
*                                                                          *
* PULIC FUNCTIONS:                                                         *
*                                                                          *
* Name                  Return      Description                            *
* ----                  ------      -----------                            *
* TriggerLine           N/A         Constructor for TriggerLine object     *
* ~TriggerLine          virtual     Deconstructor of TriggerLine object    *
* setup                 void        Setup the properties of TriggerLine    *
*                                     object                               *
* handleMarkerDragEvent void        Event Handle for Drag event of the     *
*                                     object                               *
* EnableLine            void        Enable the object on the screen        *
*                                                                          *
* PRIVATE VARIABLES:                                                       *
*                                                                          *
* Variable        Type            Description                              *
* --------        ----            -----------                              *
* marker          Snapper<Line>   Instance of a Lne object                 *
*                                  with snapper properties                 *
* marker_painter  PainterRGB565   Instance of Painter object with          *
*                                  color format RGB565                     *
* y_marker        int             Y position of the trigger line           *
* height_limit    int             Maximum height that the trigger line     *
*                                   can be moved                           *
*                                                                          *
* PRIVATE FUNCTIONS:                                                       *
*                                                                          *
* Name                    Return               Description                 *
* ----                    ------               -----------                 *
* markerDraggedCallback   Callback function    Callback of Drag event      * 
*                                                                          *
* DEVELOPMENT HISTORY:                                                     *
*                                                                          *
* Date        Author     Change Id Release  Description Of Change          *
* ----        ------     --------- -------  ---------------------          *
* 28.06.2016  Hai Nguyen        01     1.0  Original File, Adding prolog   *
* 28.06.2016  Hai Nguyen		02     2.0  Porting to touchgfx 4.6.0      * 
*                                                                          *
***************************************************************************/

#ifndef TRIGGERLINE_HPP
#define TRIGGERLINE_HPP

#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/mixins/Snapper.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <gui\common\main_header.h>

using namespace touchgfx;

class  TriggerLine : public Container
{
public:
	TriggerLine();

	virtual ~TriggerLine();


	void TriggerLine::setup(int channel, int offset, int marker_length, int graph_height, uint16_t marker_color);
	void handleMarkerDragEvent(const DragEvent&);
	void handleMarkerSnappedEvent(void);
	void EnableLine(bool enable);
	int TriggerPosition(void);
	void SetYOffset(int y);

private:

	int trigger_position; 
	int y_marker;
	int y_offset;
	int height_limit;
	int length;
	int volt_offset;
	int associated_channel;


	Image channel_idx;
	Snapper<Line> line;
	PainterRGB565 line_painter;
	Callback< TriggerLine, const DragEvent& > markerDraggedCallback;
	Callback< TriggerLine > markerSnappedCallback;
	
	
};
#endif