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

void TriggerLine::setup(int bmchannel, int offset,  int trigger_level, uint16_t marker_color)
{
	trigger_position = trigger_level;
	marker = offset + 115; //getHeight() - trigger_position;
	
	y_offset = offset;
	line_painter.setColor(marker_color);
	line.setLineWidth(1);
	line.setPosition(-X_OFFSET, marker - 1, getWidth() +  2 * X_OFFSET, 50 );
	line.setStart(0, 0);
	line.setEnd(getWidth() + 2 * X_OFFSET, 0);
	line.setPainter(line_painter);
	line.setDragAction(markerDraggedCallback);
	line.setSnappedAction(markerSnappedCallback);
	line.setTouchable(true);
	line.setAlpha(128);

	add(line);

    channel_idx.setBitmap(Bitmap(bmchannel));
	channel_idx.setXY(286, marker - 5);
	channel_idx.setAlpha(250);
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
	//channel_idx.setY(y_marker - 5);
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
	channel_idx.setY(marker + evt.getDeltaY() - 5);

    if (marker  + getY() + evt.getDeltaY()  < 10) // OK
		   marker =  - getY() + 10;
	else if (marker + evt.getDeltaY() > 115 + y_offset) //fail
		   marker = 115 + y_offset;
	else
	{
		   marker = marker + evt.getDeltaY();
	}
	trigger_position = 230 - marker;

	line.setSnapPosition(-X_OFFSET, marker);

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

void TriggerLine::setYoffset(int offset)
{
	y_offset = offset;

	marker = offset + 115; //getHeight() - trigger_position;
	line.setY(marker);
	channel_idx.setY(marker - 5);
}