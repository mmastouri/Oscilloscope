/**************************************************************************************************
* FILE NAME:  TemplateView.cpp                                                                    *
* PURPOSE:    Setup the osciliscope screen, setup other widgets/ objects attached to the screen   *                                                                                    *
*                                                                                                 *
* FILE REFERENCES:                                                                                *
*                                                                                                 *
* Name I/O Description                                                                            *
* ---- --- -----------                                                                            *
*                                                                                                 *
* EXTERNAL VARIABLES:                                                                             *
* Source: < >                                                                                     *
*                                                                                                 *
* Name Type I/O Description                                                                       *
* ---- ---- --- -----------                                                                       *
*                                                                                                 *
* EXTERNAL REFERENCES:                                                                            *
*                                                                                                 *
* Name Description                                                                                *
* ---- -----------                                                                                *
*                                                                                                 *
* ABNORMAL TERMINATION CONDITIONS, ERROR AND WARNING MESSAGES:                                    *
*                                                                                                 *
* ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS:                                                         *
*                                                                                                 *
* NOTES:                                                                                          *
*                                                                                                 *
* REQUIREMENTS/FUNCTIONAL SPECIFICATIONS REFERENCES:                                              *
*                                                                                                 *
* DEVELOPMENT HISTORY:                                                                            *
*                                                                                                 *
* Date        Author      Change Id  Release   Description Of Change                              *
* ----        ------      ---------  -------   ---------------------                              *
* 28.06.2016  Hai Nguyen         01      1.0   Original Files, add comments and prolog            *
* 29.06.2016  Hai Nguyen         02      2.0   Porting to touchgfx 4.6.0                          *
*                                              Use SetUpButtonImage() from ChannelControlPannel   *
*                                                  class                                          *
* 30.06.2016  Hai Nguyen         03      2.0   Add CallBack and Callback function to deal with    *
*                                                  button insed the control panel                 *
* 01.07.2016  Hai Nguyen         04      2.0  Re-design interface                                 *
*                                                                                                 *
***************************************************************************************************/

#include <gui/main_screen/MainView.hpp>
#include <touchgfx\Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <gui\model\Model.hpp>
#include <gui\common\main_header.h>



/***************************************************************************************************
*                                                                                                  *
* FUNCTION NAME:  setupScreen                                                                      *
*                                                                                                  *
* ARGUMENTS:                                                                                       *
*                                                                                                  *
* ARGUMENT TYPE I/O DESCRIPTION                                                                    *
* -------- ---- --- -----------                                                                    *
*                                                                                                  *
* RETURNS:   void                                                                                  *
*                                                                                                  *
***************************************************************************************************/
void MainView::setupScreen()
{
	tickCounter = 0;
	panelChn[CHANNEL_1].associatedChannel = 0;
	panelChn[CHANNEL_2].associatedChannel = 1;
	MeasureButtonClicked = FALSE;

	// overide default model settings from savedones
	appContext.Restore();

	presenter->p_SetYOffset(CHANNEL_1, 115 - 38);
	presenter->p_SetYOffset(CHANNEL_2, 230 - 38);
	presenter->p_SetTrigger(CHANNEL_1, true);
	presenter->p_SetTrigger(CHANNEL_2, true);
	presenter->p_SetTriggerType(CHANNEL_1, FALLING);
	presenter->p_SetTriggerType(CHANNEL_2, FALLING);

	presenter->p_SetTriggerValue(CHANNEL_1, 20);
	presenter->p_SetTriggerValue(CHANNEL_2, 20);
	presenter->p_SetTimeScale(CHANNEL_1, DIV_100uS);
	presenter->p_SetTimeScale(CHANNEL_2, DIV_100uS);
	presenter->p_SetVoltageScale(CHANNEL_1, DIV_2V);
	presenter->p_SetVoltageScale(CHANNEL_2, DIV_2V);
	/*
	* Background configuration: add application,
	*   grid, control panel and channel background
	*/
	presenter->activate();
	appBackground.setBitmap(Bitmap(BITMAP_APPBACKGROUND_ID));
	appBackground.setXY(0, 0);
	add(appBackground);

	oziBackground.setBitmap(Bitmap(BITMAP_OZIBACKGROUND_ID));
	oziBackground.setXY(3, 3);
	add(oziBackground);

	controlPanelBackground.setBitmap(Bitmap(BITMAP_CONTROLPANEL_ID));
	controlPanelBackground.setXY(314, 3);
	add(controlPanelBackground);

	channelBackground.setBitmap(Bitmap(BITMAP_CHANNELINFO_CH1_ID));
	channelBackground.setXY(349, 240);
	add(channelBackground);

	/*
	* Button section:  Configure buttons for changing between two channels
	*/

	rightButton.setBitmaps(Bitmap(BITMAP_RIGHTBUTTONUNPRESS_ID), Bitmap(BITMAP_RIGHTBUTTONPRESS_ID));
	rightButton.setXY(450, 240);
	rightButton.setAction(buttonClickedCallback);
	add(rightButton);

	leftButton.setBitmaps(Bitmap(BITMAP_LEFTBUTTONUNPRESS_ID), Bitmap(BITMAP_LEFTBUTTONPRESS_ID));
	leftButton.setXY(315, 240);
	leftButton.setAction(buttonClickedCallback);
	add(leftButton);

	/*
	* Text section:  Configure Text label "Channel 1, channel 2"
	*/
	channelTxT[CHANNEL_1].setTypedText(TypedText(T_CHN1));
	channelTxT[CHANNEL_2].setTypedText(TypedText(T_CHN2));


	chnTextViewPort.setPosition( channelBackground.getX(),
								 channelBackground.getY(),
								 channelBackground.getWidth(),
								 channelBackground.getHeight());

	chnControlPanelViewPort.setPosition( controlPanelBackground.getX(),
		                                 controlPanelBackground.getY() + 5,
		                                 controlPanelBackground.getWidth(),
		                                 controlPanelBackground.getHeight());

	add(chnControlPanelViewPort);

	for (int i = 0; i < NUMBER_OF_CHANNEL; i++)
	{
		channelTxT[i].setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
		channelTxT[i].setWidth(channelBackground.getWidth());
		channelTxT[i].setHeight(channelBackground.getHeight());

		/*
		* Control pannel section: setup control pannel for 2 channels, setup viewport for slide transition
		*                         between two channels
		*/
		panelChn[i].SetUpButtonImage(BITMAP_BUTTONUPON_ID,
			BITMAP_BUTTONUPOFF_ID,
			BITMAP_BUTTONDOWNON_ID,
			BITMAP_BUTTONDOWNOFF_ID,
			BITMAP_LEFTBUTTONPRESS_ID,
			BITMAP_LEFTBUTTONUNPRESS_ID,
			BITMAP_RIGHTBUTTONPRESS_ID,
			BITMAP_RIGHTBUTTONUNPRESS_ID);

		panelChn[i].setup(presenter->p_GetYOffset(i),

			controlPanelBackground.getWidth(),
			controlPanelBackground.getHeight(),
			BITMAP_CHNCONTROLBUTTONON_ID,
			BITMAP_CHNCONTROLBUTTONOFF_ID,
			BITMAP_BUTTONUPOFF_ID,
			BITMAP_BUTTONUPON_ID,
			BITMAP_BUTTONDOWNOFF_ID,
			BITMAP_BUTTONDOWNON_ID, presenter->p_GetXOffset(i), presenter->p_GetYOffset(i));

		panelChn[i].SetChannelPanelCallback(CtrlPanelBtnPressCallback);

		/*
		* Add control pannels and channel text lable into the viewport for sliding animation
		*/

		chnTextViewPort.add(channelTxT[i]);
		chnControlPanelViewPort.add(panelChn[i]);

		channelTxT[i].setXY( -channelTxT[selectedChnIndex].getWidth(),
			                 (chnTextViewPort.getHeight() - channelTxT[i].getHeight()) / 2 + 4);

		panelChn[i].setPosition( -panelChn[selectedChnIndex].getWidth(),
			                     0,
			                     controlPanelBackground.getWidth(),
			                     controlPanelBackground.getHeight());
	}

	add(chnTextViewPort);
	selectedChnIndex = CHANNEL_2;
	slideTexts(LEFT);

	/*
	* Graph section: setup the graph
	*/

	graph[CHANNEL_1].setPosition(3, 0,
		                     presenter->p_GetYOffset(CHANNEL_1),
							 oziBackground.getWidth(), 
							 oziBackground.getHeight());

	graph[CHANNEL_1].SetGraphColor(Color::getColorFrom24BitRGB(102, 178, 255));
	graph[CHANNEL_1].SetGraphData(presenter->p_GetTriggerData(CHANNEL_1));

	graph[CHANNEL_2].setPosition(3, 0,
		                     presenter->p_GetYOffset(CHANNEL_2),
							 oziBackground.getWidth(), 
							 oziBackground.getHeight());

	graph[CHANNEL_2].SetGraphColor(Color::getColorFrom24BitRGB(255, 128, 0));
	graph[CHANNEL_2].SetGraphData(presenter->p_GetTriggerData(CHANNEL_2));

	graph_container.setPosition(oziBackground.getX(),
								oziBackground.getY(),
								oziBackground.getWidth(),
								oziBackground.getHeight());
	
	add(graph_container);

	Application::getInstance()->registerTimerWidget(&graph[CHANNEL_1]);
	Application::getInstance()->registerTimerWidget(&graph[CHANNEL_2]);


	/*
	* Marker section: Setup the Marker
	*/

	marker1.setPosition(oziBackground.getX(), oziBackground.getY(), oziBackground.getWidth(), oziBackground.getHeight());
	marker1.setup(marker1.getX(), marker1.getHeight(), marker1.getWidth(), Color::getColorFrom24BitRGB(99, 215, 121));

	add(marker1);

	marker2.setPosition(oziBackground.getX(), oziBackground.getY(), oziBackground.getWidth(), oziBackground.getHeight());
	marker2.setup( oziBackground.getWidth() - 50, marker2.getHeight(), marker2.getWidth(), Color::getColorFrom24BitRGB(99, 215, 121));

	add(marker2);

	/*
	* Trigger Line: Setup the Trigger Line
	*/
	triggLine[CHANNEL_2].setPosition(0,
		                   0,
		                   graph[CHANNEL_2].getWidth(),
		                   graph[CHANNEL_2].getHeight() + 10);

	triggLine[CHANNEL_2].setup(   BITMAP_CHANNEL2_ID,
		                 graph[CHANNEL_2].getY(),
		                 presenter->p_GetTriggerValue(CHANNEL_2),
		                 Color::getColorFrom24BitRGB(255, 128, 0));

	add(triggLine[CHANNEL_2]);

	presenter->p_SetTriggerValue(CHANNEL_2, presenter->p_GetVoltScale2Pixel(CHANNEL_2) - triggLine[CHANNEL_2].TriggerPosition());

	triggLine[CHANNEL_1].setPosition (0,
		                    0,
		                    graph[CHANNEL_1].getWidth(),
		                    graph[CHANNEL_1].getHeight() + 10);
		                    
	triggLine[CHANNEL_1].setup(BITMAP_CHANNEL1_ID,
		                 graph[CHANNEL_1].getY(),
		                 presenter->p_GetTriggerValue(CHANNEL_1),
		                 Color::getColorFrom24BitRGB(102, 178, 255));

	


	presenter->p_SetTriggerValue(CHANNEL_1, presenter->p_GetVoltScale2Pixel(CHANNEL_2) - triggLine[CHANNEL_1].TriggerPosition());

	add(triggLine[CHANNEL_1]);

	/*
	 *  Display Value section
	 */
	cursor_text.setTypedText(TypedText(T_CURSOR_US));
	cursor_text.setColor(Color::getColorFrom24BitRGB(246, 241, 237));
	cursor_text.setXY(25, 245);
	add(cursor_text);

	/*cursor_txt_background.setXY(70, 243);
	cursor_txt_background.setBitmap(Bitmap(BITMAP_TEXT_BACKGROUND_ID));
	add(cursor_txt_background);*/

	trigger_lvl[CHANNEL_1].setTypedText(TypedText(T_TRIG1_LEVEL));
	trigger_lvl[CHANNEL_1].setColor(Color::getColorFrom24BitRGB(246, 241, 237));
	trigger_lvl[CHANNEL_1].setXY(125, 245);
	add(trigger_lvl[CHANNEL_1]);

	//trig_txt_background[CHANNEL_1].setXY(165, 243);
	//trig_txt_background[CHANNEL_1].setBitmap(Bitmap(BITMAP_TEXT_BACKGROUND_ID));
	//add(trig_txt_background[CHANNEL_1]);

	trigger_lvl[CHANNEL_2].setTypedText(TypedText(T_TRIG2_LEVEL));
	trigger_lvl[CHANNEL_2].setColor(Color::getColorFrom24BitRGB(246, 241, 237));
	trigger_lvl[CHANNEL_2].setXY(220, 245);
	add(trigger_lvl[CHANNEL_2]);

	//trig_txt_background[CHANNEL_2].setXY(260, 243);
	//trig_txt_background[CHANNEL_2].setBitmap(Bitmap(BITMAP_TEXT_BACKGROUND_ID));
	//add(trig_txt_background[CHANNEL_2]);

	Unicode::snprintf(cursor_buff, 10, "%d", 0);
	cursor_value_wildcard.setTypedText(TypedText(T_CURSOR_VALUE));
	cursor_value_wildcard.setWildcard(cursor_buff);
	cursor_value_wildcard.setPosition(57, 245,50,20);
	cursor_value_wildcard.setColor(Color::getColorFrom24BitRGB(255, 255, 255));
	add(cursor_value_wildcard);


	Unicode::snprintf(trig_buff[CHANNEL_1], 5, "%d", 0);
	trig_value_wildcard[CHANNEL_1].setTypedText(TypedText(T_TRIGG1_VALUE));
	trig_value_wildcard[CHANNEL_1].setWildcard(trig_buff[CHANNEL_1]);
	trig_value_wildcard[CHANNEL_1].setPosition(160, 244, 50, 20);
	trig_value_wildcard[CHANNEL_1].setColor(Color::getColorFrom24BitRGB(255, 255, 255));
	add(trig_value_wildcard[CHANNEL_1]);
	trig_value_wildcard[CHANNEL_1].invalidate();

	Unicode::snprintf(trig_buff[CHANNEL_2], 5, "%d", 0);
	trig_value_wildcard[CHANNEL_2].setTypedText(TypedText(T_TRIGG2_VALUE));
	trig_value_wildcard[CHANNEL_2].setWildcard(trig_buff[CHANNEL_2]);
	trig_value_wildcard[CHANNEL_2].setPosition(255, 244, 50, 20);
	trig_value_wildcard[CHANNEL_2].setColor(Color::getColorFrom24BitRGB(255, 255, 255));
	add(trig_value_wildcard[CHANNEL_2]);
	trig_value_wildcard[CHANNEL_2].invalidate();

	/*
     * Control Menu section	
   	 */
	control_menu.setup(SlideMenu::EAST, Bitmap(BITMAP_SLIDEMENU_ID), Bitmap(BITMAP_SIDESLIDEBUTTON_ID), Bitmap(BITMAP_SIDESLIDEBUTTON_PRESS_ID), 0, 0, 291, 0);
	control_menu.setXY(3, 235);
	control_menu.setVisiblePixelsWhenCollapsed(15);
	control_menu.setExpandedStateTimeout(500);
	add(control_menu);

	txt_ctrl_menu[CHANNEL_1].setTypedText(TypedText(T_CHN1_CTRL_MENU));
	txt_ctrl_menu[CHANNEL_1].setColor(Color::getColorFrom24BitRGB(246, 241, 237));
	txt_ctrl_menu[CHANNEL_1].setXY(5,8);
	control_menu.add(txt_ctrl_menu[CHANNEL_1]);

	chn_enable[CHANNEL_1].setBitmaps(Bitmap(BITMAP_CHNCONTROLBUTTONOFF_ID), Bitmap(BITMAP_CHNCONTROLBUTTONON_ID));
	chn_enable[CHANNEL_1].setXY(40, 7);
	chn_enable[CHANNEL_1].setAction(buttonClickedCallback);
	
	
	chn_enable[CHANNEL_1].forceState(true);

	txt_ctrl_menu[CHANNEL_2].setTypedText(TypedText(T_CHN2_CTRL_MENU));
	txt_ctrl_menu[CHANNEL_2].setColor(Color::getColorFrom24BitRGB(246, 241, 237));
	txt_ctrl_menu[CHANNEL_2].setXY(85, 8);
	control_menu.add(txt_ctrl_menu[CHANNEL_2]);

	chn_enable[CHANNEL_2].setBitmaps(Bitmap(BITMAP_CHNCONTROLBUTTONOFF_ID), Bitmap(BITMAP_CHNCONTROLBUTTONON_ID));
	chn_enable[CHANNEL_2].setXY(120, 7);
	chn_enable[CHANNEL_2].setAction(buttonClickedCallback);

	chn_enable[CHANNEL_2].forceState(true);
	

	meas_enable.setBitmaps(Bitmap(BITMAP_CHNCONTROLBUTTONOFF_ID), Bitmap(BITMAP_CHNCONTROLBUTTONON_ID));
	meas_enable.setXY(225, 7);
	meas_enable.setAction(buttonClickedCallback);
	meas_enable.forceState(false);

	meas_ctrl_menu.setTypedText(TypedText(T_MEAS_CTRL_MENU));
	meas_ctrl_menu.setColor(Color::getColorFrom24BitRGB(246, 241, 237));
	meas_ctrl_menu.setXY(165, 8);
	control_menu.add(meas_ctrl_menu);


	graph_container.add(graph[CHANNEL_1]);
	graph_container.add(graph[CHANNEL_2]);
	control_menu.add(chn_enable[CHANNEL_1]);
	control_menu.add(chn_enable[CHANNEL_2]);
	control_menu.add(meas_enable);
	


	// Init Panel from default / saved settings 
	for (int i = 0; i < NUMBER_OF_CHANNEL; i++)
	{
		panelChn[i].SetTriggerButton(presenter->p_GetTrigger(i));
		panelChn[i].SetFallingButton(presenter->p_GetTriggerType(i));
		panelChn[i].SetMarkerButton(presenter->p_GetTrigger(i));
		panelChn[i].setScaleSettings(presenter->p_GetTimeScale(i), presenter->p_GetVoltageScale(i));
	}
	Intro();
}

/***************************************************************************************************
*                                                                                                  *
* FUNCTION NAME:  tearDownScreen                                                                   *
*                                                                                                  *
* ARGUMENTS:                                                                                       *
*                                                                                                  *
* ARGUMENT TYPE I/O DESCRIPTION                                                                    *
* -------- ---- --- -----------                                                                    *
*                                                                                                  *
* RETURNS:   void                                                                                  *
*                                                                                                  *
***************************************************************************************************/
void MainView::tearDownScreen()
{
}

void MainView::SetMeasureButton(bool state)
{
	MeasureButtonClicked = state;
	meas_enable.forceState(state);
}


bool MainView::isMeasButtonClicked(void)
{
	return MeasureButtonClicked;
}

/***************************************************************************************************
*                                                                                                  *
* FUNCTION NAME:  buttonClicked                                                                    *
*                                                                                                  *
* ARGUMENTS:                                                                                       *
*                                                                                                  *
* ARGUMENT TYPE             I/O    DESCRIPTION                                                     *
* -------- ----             ---    -----------                                                     *
* source   AbstractButton     I    The source of the clicked button                                *
*                                                                                                  *
* RETURNS:   void                                                                                  *
*                                                                                                  *
***************************************************************************************************/
void MainView::buttonClicked(const AbstractButton& source)
{
	/*Chenking which button is pressed then call the approriate event handler function*/

	if (&source == &leftButton)
	{
		slideTexts(LEFT);
	}

	else if (&source == &rightButton)
	{

		slideTexts(RIGHT);
	}
	else if (&source == &chn_enable[CHANNEL_1])
	{
		control_menu.resetExpandedStateTimer();
		if (chn_enable[CHANNEL_1].getState() == true)
		{
			remove(triggLine[CHANNEL_1]);
			add(triggLine[CHANNEL_1]);
			graph_container.add(graph[CHANNEL_1]);
		}
		else
		{
			remove(triggLine[CHANNEL_1]);
			graph_container.remove(graph[CHANNEL_1]);

		}
	}
	else if (&source == &chn_enable[CHANNEL_2])
	{
		control_menu.resetExpandedStateTimer();
		if (chn_enable[CHANNEL_2].getState() == true)
		{
			remove(triggLine[CHANNEL_2]);
			add(triggLine[CHANNEL_2]);
			graph_container.add(graph[CHANNEL_2]);
		}
		else
		{
			remove(triggLine[CHANNEL_2]);
			graph_container.remove(graph[CHANNEL_2]);
		}
	}

	else if (&source == &meas_enable)
	{
		control_menu.resetExpandedStateTimer();
		if (MeasureButtonClicked == FALSE)
		{
			MeasureButtonClicked = TRUE;
		}
		else
		{
			MeasureButtonClicked = FALSE;
		}
	}
}

void MainView::Intro(void)
{
	back_ground.setPosition(0,0,480,272);
	back_ground.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
	add(back_ground);

	arrow.setBitmap(Bitmap(BITMAP_ARROW_ID));
	arrow.setXY(0, 0);
	arrow.setAlpha(0);
	add(arrow);
}

/***************************************************************************************************
*                                                                                                  *
* FUNCTION NAME:  slideTexts                                                                       *
*                                                                                                  *
* ARGUMENTS:                                                                                       *
*                                                                                                  *
* ARGUMENT   TYPE       I/O   DESCRIPTION                                                          *
* --------   ----       ---   -----------                                                          *
* direction  Direction    I   direction of the slide animation                                     *
*                                                                                                  *
* RETURNS:   void                                                                                  *
*                                                                                                  *
***************************************************************************************************/
void MainView::slideTexts(SlideDirection direction)
{
	/*
	* Slide animation for control pannel and text labels
	* Calculate the position needed for the slide animation, procced the animation
	* Prepare for the next slide animation
	* Enable, disable graph according to the channel
	*/

	for (int i = 0; i < NUMBER_OF_CHANNEL; i++)
	{
		/* Checking if is there any slide animation or not*/
		if (channelTxT[i].isRunning())
			return;
	}

	int animationDuration = 14;
	int animationDirection = (direction == LEFT) ? -1 : 1;
	int animationDistance = animationDirection * chnTextViewPort.getWidth();
	int animationDistance1 = animationDuration * chnControlPanelViewPort.getWidth();

	int nextSelectedText = (selectedChnIndex + NUMBER_OF_CHANNEL + animationDirection) % NUMBER_OF_CHANNEL;

	/*
	* Slide selected object
	*/
	channelTxT[selectedChnIndex].startMoveAnimation(channelTxT[selectedChnIndex].getX() + animationDistance,
	                                               	4,
		                                            animationDuration,
		                                            EasingEquations::quintEaseInOut);

	panelChn[selectedChnIndex].startMoveAnimation(panelChn[selectedChnIndex].getX() + animationDistance1,
		                                          panelChn[selectedChnIndex].getY(),
		                                          animationDuration,
		                                          EasingEquations::quintEaseInOut);

	int xOffsetForText = (chnTextViewPort.getWidth() - channelTxT[nextSelectedText].getWidth()) / 2;

	int xOffsetForContainer = (chnControlPanelViewPort.getWidth() - panelChn[nextSelectedText].getWidth()) / 2;

	/*Prepare for the next slide*/
	channelTxT[nextSelectedText].moveTo(xOffsetForText - animationDistance, 4);
	panelChn[nextSelectedText].moveTo(xOffsetForContainer - animationDistance1,
		                              panelChn[nextSelectedText].getY());

	channelTxT[nextSelectedText].startMoveAnimation( channelTxT[nextSelectedText].getX() + animationDistance,
		                                             4,
													 animationDuration,
													 EasingEquations::quintEaseInOut);

	panelChn[nextSelectedText].startMoveAnimation( panelChn[nextSelectedText].getX() + animationDistance1,
												   panelChn[nextSelectedText].getY(),
												   animationDuration,
												   EasingEquations::quintEaseInOut);

	selectedChnIndex = nextSelectedText;

	if(selectedChnIndex == CHANNEL_2)
	channelBackground.setBitmap(Bitmap(BITMAP_CHANNELINFO_CH2_ID));
	else
	channelBackground.setBitmap(Bitmap(BITMAP_CHANNELINFO_CH1_ID));
	
}

/***************************************************************************************************
*                                                                                                  *
* FUNCTION NAME:  handleTickEvent                                                                  *
*                                                                                                  *
* ARGUMENTS:                                                                                       *
*                                                                                                  *
* ARGUMENT   TYPE       I/O   DESCRIPTION                                                          *
* --------   ----       ---   -----------                                                          *
*                                                                                                  *
* RETURNS:   void                                                                                  *
*                                                                                                  *
***************************************************************************************************/
void MainView::handleTickEvent()
{	
	float temp_value;


	/* Update model according to HMI update */ 
	for (int i = 0; i < NUMBER_OF_CHANNEL; i++)
	{
		presenter->p_SetTimeScale(i, panelChn[i].GetTimeBaseIndex());
		presenter->p_SetVoltageScale(i, panelChn[i].GetVoltBaseIndex());
		presenter->p_SetRawData(i);
		presenter->p_SetYOffset(i, panelChn[i].GetYOffset());
		presenter->p_SetXOffset(i, panelChn[i].GetXOffset());
		presenter->p_SetTrigger(i, panelChn[i].isTriggerButtonClicked());
		presenter->p_SetTriggerType(i, panelChn[i].isFallingButtonClicked());


		presenter->p_SetTriggerValue(i, triggLine[i].TriggerPosition());

		/* Update GUI according to HMI update */
		graph[i].setY(presenter->p_GetYOffset(i));
		graph[i].invalidate();

		triggLine[i].EnableLine(panelChn[i].isMarkerButtonClicked());
	}

	marker1.EnableLine(isMeasButtonClicked());
	marker2.EnableLine(isMeasButtonClicked());
	cursor_value = abs(marker1.MarkerPosition() - marker2.MarkerPosition());

	temp_value = cursor_value * presenter->p_GetTimeScale2Pixel(CHANNEL_2);
	if (presenter->p_GetTimeScale(CHANNEL_2) > 3)
		temp_value = (temp_value / 1000);

	Unicode::snprintfFloat(cursor_buff, 10, "%.2f", temp_value);
	cursor_value_wildcard.invalidate();

	for (int i = 0; i < NUMBER_OF_CHANNEL; i++)
	{
		temp_value = presenter->p_GetTriggerValue(i) * presenter->p_VoltagePerPixel(i);
		if (presenter->p_GetVoltageScale(i) > 5)
			temp_value = temp_value / 1000;

		Unicode::snprintfFloat(trig_buff[i], 5, "%.2f", temp_value);
		trig_value_wildcard[i].invalidate();


		triggLine[i].setYoffset(presenter->p_GetYOffset(i));
		triggLine[i].invalidate();
	}
	tickCounter++;
	if (tickCounter % 1 == 0)
	{
		alpha++;
		arrow.setAlpha(alpha);
		arrow.invalidate();
	}
	if (alpha == 255)
	{
		tickCounter = 0;
		remove(arrow);
		remove(back_ground);
	}

}
/***************************************************************************************************
*                                                                                                  *
* FUNCTION NAME:  CtrlPanelBtnPressed                                                              *
*                                                                                                  *
* ARGUMENTS:                                                                                       *
*                                                                                                  *
* ARGUMENT   TYPE       I/O   DESCRIPTION                                                          *
* --------   ----       ---   -----------                                                          *
* button_ID  uint8_t      I   The ID of the pressed button inside control panel                    *
*                                                                                                  *
* RETURNS:   void                                                                                  *
*                                                                                                  *
***************************************************************************************************/
void MainView::CtrlPanelBtnPressed(const uint8_t button_ID)
{
	uint8_t temp = 0;
}