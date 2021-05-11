/*******************************************************************************************
* FILE NAME: TriggerLine.cpp                                                               *
* PURPOSE:   Create Trigger Line Widget to indicate the level of the trigger               *
*            This widget is touchable                                                      *
*                                                                                          *
* FILE REFERENCES:                                                                         *
*                                                                                          *
* Name I/O Description                                                                     *
* ---- --- -----------                                                                     *
*                                                                                          *
* EXTERNAL VARIABLES:                                                                      *
* Source: < >                                                                              *
*                                                                                          *
* Name Type I/O Description                                                                *
* ---- ---- --- -----------                                                                *
*                                                                                          *
* EXTERNAL REFERENCES:                                                                     *
*                                                                                          *
* Name Description                                                                         *
* ---- -----------                                                                         *
*                                                                                          *
* ABNORMAL TERMINATION CONDITIONS, ERROR AND WARNING MESSAGES:                             *
*                                                                                          *
* ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS:                                                  *
*                                                                                          *
* NOTES:                                                                                   *
*                                                                                          *
* REQUIREMENTS/FUNCTIONAL SPECIFICATIONS REFERENCES:                                       *
*                                                                                          *
* DEVELOPMENT HISTORY:                                                                     *
*                                                                                          *
* Date        Author      Change Id  Release  Description Of Change                        *
* ----        ------      ---------  -------  ---------------------                        *
* 28.06.2016  Hai Nguyen         01     1.0   Original File, adding File Prolog and comment*
* 29.06.2016  Hai Nguyen         02     2.0   Porting to touchgfx 4.6.0                    *
*                                                                                          *
*******************************************************************************************/

#include <gui/common/TriggerLine.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>

/*****************************************************************************************
*                                                                                        *
* FUNCTION NAME: TriggerLine - constructor                                               *
*                                                                                        *
* ARGUMENTS:                                                                             *
*                                                                                        *
* ARGUMENT TYPE I/O DESCRIPTION                                                          *
* -------- ---- --- -----------                                                          *
*                                                                                        *  
* RETURNS:                                                                               *
*                                                                                        *
*****************************************************************************************/

TriggerLine::TriggerLine():markerDraggedCallback(this, &TriggerLine::handleMarkerDragEvent),
                          markerSnappedCallback(this, &TriggerLine::handleMarkerSnappedEvent)
{
}


/*****************************************************************************************
*                                                                                        *
* FUNCTION NAME: setup                                                                   *
*                                                                                        *
* ARGUMENTS:                                                                             *
*                                                                                        *
* ARGUMENT       TYPE     I/O   DESCRIPTION                                              *
* --------       ----     ---   -----------                                              *
* offset      int       I   Position of the marker on x Coordinate                   *
* marker_length   int       I   The length of the marker                                 *
* graph_height    int       I   The limit of the y Coordinate, to keep the graph in the  *
*                                  screen                                                *
* marker_color    uint16_t  I   Define the color of the line                             *
*                                                                                        *
* RETURNS:  void                                                                         *
*                                                                                        *
*****************************************************************************************/


#define X_OFFSET 306

void TriggerLine::setup(int channel, int offset, int marker_length, int graph_height, uint16_t marker_color)
{
	/* LOCAL VARIABLES:
	*
	* Variable      Type      Description
	* ------------- -------   -------------------------------------
	* height_limit  int       Copy the value of graph_height
	* y_marker      int       Copy the value of y_position
	*/
	height_limit = graph_height;
	y_marker = offset;
	length = marker_length;
	trigger_position = y_marker;
	associated_channel = channel;
	/*
	* Configure the width, height, color and position of the trigger line
	* Enable touchable
	* Add to the screen
	*/
	line_painter.setColor(marker_color);
	line.setLineWidth(2);
	line.setPosition(-X_OFFSET, y_marker, marker_length +  2 * X_OFFSET, 50 );
	line.setStart(0, 5);
	line.setEnd(marker_length + 2 * X_OFFSET, 5);
	line.setPainter(line_painter);
	line.setDragAction(markerDraggedCallback);
	line.setSnappedAction(markerSnappedCallback);
	line.setTouchable(true);
	add(line);

	channel_idx.setBitmap(Bitmap(BITMAP_CHANNEL1_ID));

	channel_idx.setXY(286, y_marker);
	add(channel_idx);
}

/*****************************************************************************************
*                                                                                        *
* FUNCTION NAME: ~TriggerLine - deconstructor                                            *
*                                                                                        *
* ARGUMENTS:                                                                             *
*                                                                                        *
* ARGUMENT TYPE I/O DESCRIPTION                                                          *
* -------- ---- --- -----------                                                          *
*                                                                                        *
* RETURNS:                                                                               *
*                                                                                        *
*****************************************************************************************/
TriggerLine::~TriggerLine()
{
}

/*****************************************************************************************
*                                                                                        *
* FUNCTION NAME: handleMarkerDragEvent                                                   *
*                                                                                        *
* ARGUMENTS:                                                                             *
*                                                                                        *
* ARGUMENT TYPE       I/O DESCRIPTION                                                    *
* -------- ----       --- -----------                                                    *
* evt      DragEvent    I Pointer to the DragEvent class                                 *
*                                                                                        *
* RETURNS:  void                                                                         *
*                                                                                        *
*****************************************************************************************/
void TriggerLine::handleMarkerSnappedEvent(void)
{
	channel_idx.setXY(286, y_marker);
	channel_idx.invalidate();
}
/*****************************************************************************************
*                                                                                        *
* FUNCTION NAME: handleMarkerDragEvent                                                   *
*                                                                                        *
* ARGUMENTS:                                                                             *
*                                                                                        *
* ARGUMENT TYPE       I/O DESCRIPTION                                                    *
* -------- ----       --- -----------                                                    *
* evt      DragEvent    I Pointer to the DragEvent class                                 *
*                                                                                        *
* RETURNS:  void                                                                         *
*                                                                                        *
*****************************************************************************************/
void TriggerLine::handleMarkerDragEvent(const DragEvent& evt)
{
	/*
	 *  Check if the Displacement of DragEvent is exceed the boundary or not
	 *  If yes, keep it at the boundary
	 *  If no, move to the new position
	 */

	channel_idx.setY(line.getY() + evt.getDeltaY());

	if (evt.getDeltaY() > (height_limit - 10))
		y_marker = height_limit - 10;
	else if (y_marker + evt.getDeltaY() < 0)
		y_marker = 0;
	else if (y_marker + evt.getDeltaY() > (volt_offset ))
		y_marker = (volt_offset);
	else
	{
		y_marker = y_marker + evt.getDeltaY();

	}
	trigger_position = y_marker;
	
	line.setSnapPosition(-X_OFFSET, y_marker);

	invalidate();
}

/*****************************************************************************************
*                                                                                        *
* FUNCTION NAME: EnableLine                                                              *
*                                                                                        *
* ARGUMENTS:                                                                             *
*                                                                                        *
* ARGUMENT TYPE       I/O DESCRIPTION                                                    *
* -------- ----       --- -----------                                                    *
* enable   bool         I Flag to check if we want to enable the trigger line or not     *
*                                                                                        *
* RETURNS:  void                                                                         *
*                                                                                        *
*****************************************************************************************/
void TriggerLine::EnableLine(bool enable)
{
	line.setVisible(enable);
	channel_idx.setVisible(enable);
	invalidate();
}	


int TriggerLine::TriggerPosition(void)
{
	return trigger_position;
}

void TriggerLine::SetYOffset(int y)
{
}

void TriggerLine::SetVoltOffset(int value)
{
	volt_offset = value;
}
