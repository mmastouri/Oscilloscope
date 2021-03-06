/**************************************************************************************************
* FILE NAME: Model.cpp                                                                            *
*                                                                                                 *
* PURPOSE:   Provide functions to read and write to the data                                      *
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
* Date         Author     Change Id Release  Description Of Change                                *
* ----         ------     --------- -------  ---------------------                                *
* 30.06.2016   Hai Nguyen        01     2.0  Original Files                                       *
*                                                                                                 *
***************************************************************************************************/
#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/***************************************************************************************************
*                                                                                                  *
* FUNCTION NAME: Model                                                                             *
*                                                                                                  *
* ARGUMENTS:                                                                                       *
*                                                                                                  *
* ARGUMENT TYPE I/O DESCRIPTION                                                                    *
* -------- ---- --- -----------                                                                    *
*                                                                                                  *
* RETURNS:                                                                                         *
*                                                                                                  *
***************************************************************************************************/
Model::Model() : modelListener(0)
{
	
	chan1.trigger_level = 20;
	chan2.trigger_level = 20;

	chan1.y_offset = 0;
	chan2.y_offset = 0;

	chan1.x_offset = 0;
	chan2.x_offset = 0;
	
	chan1.voltage_scale = DIV_2V;
	chan2.voltage_scale = DIV_2V;

	chan1.time_scale = DIV_100uS;
	chan2.time_scale = DIV_100uS;

	chan1.trigger_found = false;
	chan2.trigger_found = false;

	chan1.is_triggered = false;
	chan2.is_triggered = false;

	chan1.triger_type = RISING;
	chan2.triger_type = RISING;

	prevch[1] = prevch[2] = 1;
  counter = 0;

}

/***************************************************************************************************
*                                                                                                  *
* FUNCTION NAME: tick                                                                              *
*                                                                                                  *
* ARGUMENTS:                                                                                       *
*                                                                                                  *
* ARGUMENT TYPE I/O DESCRIPTION                                                                    *
* -------- ---- --- -----------                                                                    *
*                                                                                                  *
* RETURNS:                                                                                         *
*                                                                                                  *
***************************************************************************************************/
void Model::tick()
{
}

void Model::SetRawData(int channel, uint16_t *data)
{
	
	int i;
	switch (channel)
	{
		case CHANNEL_1:
			for( i = 0; i < 1000; i++)
			{
				chan1.raw_data[i] = ((*(data + i)) * GetVoltageScale2Pixel(CHANNEL_1)) / 4096;
			}
			break;
		case CHANNEL_2:
			for( i = 0; i < 1000; i++)
			{
				chan2.raw_data[i] = ((*(data + i)) * GetVoltageScale2Pixel(CHANNEL_2))/ 4096;
			}
			break;
	}
}

int Model::getSignalPeak(int channel)
{
	int max = 0, min = 0;

	switch (channel)
	{
	case CHANNEL_1:
		max = chan1.raw_data[0];
		min = chan1.raw_data[0];

		for (int i = 0; i < NUMBER_OF_POINT; i++)
		{
			if (chan1.raw_data[i] > max)
			{
				max = chan1.raw_data[i];
			}

			if (chan1.raw_data[i] < min)
			{
				min = chan1.raw_data[i];
			}

		}
		break;

	case CHANNEL_2:
		max = chan2.raw_data[0];
		min = chan2.raw_data[0];
		
		for (int i = 0; i < NUMBER_OF_POINT; i++)
		{
			if (chan2.raw_data[i] > max)
			{
				max = chan2.raw_data[i];
			}

			if (chan2.raw_data[i] < min)
			{
				min = chan1.raw_data[i];
			}
		}
		break;
	}
	return max - min ;
}

int Model::getSignalFreq(int channel)
{
	int zeroindex[3];
	int zerocount = 0, freq, diff;
	int cursig0, cursig1, cursig2, cursig3;
	int offset = getSignalPeak(channel) / 2;

	switch (channel)
	{
	case CHANNEL_1:

		for (int i = 0; i < 2 * NUMBER_OF_POINT - 4; i++)
		{
			cursig0 = ((chan1.raw_data[i] - offset) > 0);
			cursig1 = ((chan1.raw_data[i+1] - offset) > 0);
			cursig2 = ((chan1.raw_data[i+2] - offset) > 0);
			cursig3 = ((chan1.raw_data[i+3] - offset) > 0);


			if ((cursig0 == cursig1) &&(cursig2 == cursig3) && (cursig0 != cursig2))
			{
				zeroindex[zerocount++] = i;
				if (zerocount > 2)
					break;
			}

		}
		break;

	case CHANNEL_2:
		for (int i = 0; i < 2 * NUMBER_OF_POINT - 1; i++)
		{
			cursig0 = ((chan2.raw_data[i] - offset) > 0);
			cursig1 = ((chan2.raw_data[i + 1] - offset) > 0);
			cursig2 = ((chan2.raw_data[i + 2] - offset) > 0);
			cursig3 = ((chan2.raw_data[i + 3] - offset) > 0);


			if ((cursig0 == cursig1) && (cursig2 == cursig3) && (cursig0 != cursig2))
			{
				zeroindex[zerocount++] = i;
				if (zerocount > 2)
					break;
			}

		}
		break;
	}

	if (zerocount > 2)
	{
		diff = (9 * (zeroindex[2] - zeroindex[0]) +  prevch[channel])/10;
		prevch[channel] = diff;
		counter = 2;
    freq = 1000000000 / (diff * (1000 * GetTimeScale2Pixel(channel)));   
	}

	else
	{
		if(counter -- < 0)
		{
			counter = 0;
			freq = 0; 
		}
		else
		{
		 diff = prevch[channel];
		 freq = 1000000000 / (diff * (1000 * GetTimeScale2Pixel(channel)));
		}
	}

	

	return freq;
}


void Model::ConvertToTriggerData(int channel)
{
	int trigg_position;
	                                                                       
	int i;
	int j;

	switch (channel)
	{
		case CHANNEL_1:
			trigg_position = 0;
			chan1.trigger_found = false;
			if (chan1.is_triggered == true)
			{
				if (chan1.triger_type == RISING)
				{
					for (i = 99 ; i < 1000 - 305; i++)
					{
						if ((chan1.raw_data[i]  <= chan1.trigger_level) &&
							(chan1.raw_data[i + 1] <= chan1.trigger_level) &&
							(chan1.raw_data[i + 2] > chan1.trigger_level) &&
							(chan1.raw_data[i + 3] > chan1.trigger_level))
						{
							trigg_position = i + 2 + chan1.x_offset;
							chan1.trigger_found = true;
							for (j = 0; j < NUMBER_OF_POINT; j++)
							{
								chan1.trigger_data[j] = (chan1.raw_data[trigg_position]);
								trigg_position++;
							}
							break;
						}
					}
					if (chan1.trigger_found == false)
					{
						for (i = 0 + chan1.x_offset; i < NUMBER_OF_POINT; i++)
						{
							chan1.trigger_data[i] = (chan1.raw_data[99 + i]);
						}
					}
				}
				else
				{
					for (i = 99 ; i < 1000 - 305 ; i++)
					{
						if ((chan1.raw_data[i]  >= chan1.trigger_level) &&
							(chan1.raw_data[i + 1] >= chan1.trigger_level) &&
							(chan1.raw_data[i + 2] < chan1.trigger_level) &&
							(chan1.raw_data[i + 3] < chan1.trigger_level))
						{
							trigg_position = i + 2 + chan1.x_offset ;
							chan1.trigger_found = true;
							for (j = 0; j < NUMBER_OF_POINT; j++)
							{
								chan1.trigger_data[j] = (chan1.raw_data[trigg_position]);
								trigg_position++;
							}
							break;
						}
					}
					if (chan1.trigger_found == false)
					{
						for (i = 0 + chan1.x_offset; i < NUMBER_OF_POINT; i++)
						{
							chan1.trigger_data[i] = (chan1.raw_data[99 + i]);
						}
					}
				}
				
			}
			else
			{
				for (i = 0 + chan1.x_offset; i < NUMBER_OF_POINT; i++)
				{
					chan1.trigger_data[i] = (chan1.raw_data[99 + i]);
				}
			}
			
		break;

		case CHANNEL_2:
			trigg_position = 0;
			chan2.trigger_found = false;
			if (chan2.is_triggered == true)
			{
				if (chan2.triger_type == RISING)
				{
					for (i = 99; i < 1000 - 305; i++)
					{
						if ((chan2.raw_data[i] <= chan2.trigger_level) &&
							(chan2.raw_data[i + 1] <= chan2.trigger_level) &&
							(chan2.raw_data[i + 2]  > chan2.trigger_level) &&
							(chan2.raw_data[i + 3]  > chan2.trigger_level))
						{
							chan2.trigger_found = true;
							trigg_position = i + 2 + chan2.x_offset;
							for (j = 0; j < NUMBER_OF_POINT; j++)
							{
								chan2.trigger_data[j] =  (chan2.raw_data[trigg_position]);
								trigg_position++;
							}
							break;
						}
					}
					if (chan2.trigger_found == false)
					{
						for (i = 0 + chan2.x_offset; i < NUMBER_OF_POINT; i++)
						{
							chan2.trigger_data[i] =  (chan2.raw_data[99 + i]);
						}
					}
				}
				else
				{
					for (i = 99 ; i < 1000 - 305; i++)
					{
						if ((chan2.raw_data[i] >= chan2.trigger_level) &&
							(chan2.raw_data[i + 1] >= chan2.trigger_level) &&
							(chan2.raw_data[i + 2]  < chan2.trigger_level) &&
							(chan2.raw_data[i + 3]  < chan2.trigger_level))
						{
							chan2.trigger_found = true;
							trigg_position = i + 2 + chan2.x_offset;
							for (j = 0; j < NUMBER_OF_POINT; j++)
							{
								chan2.trigger_data[j] =  (chan2.raw_data[trigg_position]);
								trigg_position++;
							}
							break;
						}
					}
					if (chan2.trigger_found == false)
					{
						for (i = 0 + chan2.x_offset; i < NUMBER_OF_POINT; i++)
						{
							chan2.trigger_data[i] =  (chan2.raw_data[99 + i]);
						}
					}
				}
			}
			else
			{
				for (i = 0 + chan2.x_offset; i < NUMBER_OF_POINT; i++)
				{
					chan2.trigger_data[i] =  (chan2.raw_data[99 + i]);
				}
			}
			
		break;
	}
}

void Model::SetXOffset(int channel, int value)
{
	switch (channel)
	{
	case CHANNEL_1:
		chan1.x_offset = value;
		break;
	case CHANNEL_2:
		chan2.x_offset = value;
		break;
	}
}

int Model::GetXOffset(int channel)
{
	int value;
	switch (channel)
	{
	case CHANNEL_1:
		value = chan1.x_offset;
		break;
	case CHANNEL_2:
		value = chan2.x_offset;
		break;
	}
	return value;
}

void Model::SetTriggerValue(int channel, int value)
{
	switch (channel)
	{
	case CHANNEL_1:
		chan1.trigger_level = value;
		break;
	case CHANNEL_2:
		chan2.trigger_level = value;
		break;
	}
}

int Model::GetTriggerValue(int channel)
{
	int value;
	switch (channel)
	{
	case CHANNEL_1:
		value = chan1.trigger_level;
		break;
	case CHANNEL_2:
		value = chan2.trigger_level;
		break;
	}
	return value;
}

void Model::SetTrigger(int channel, bool value)
{
	
	switch (channel)
	{
	case CHANNEL_1:
		chan1.is_triggered = value;
		break;
	case CHANNEL_2:
		chan2.is_triggered = value;
		break;
	}
}

bool Model::GetTrigger(int channel)
{
	bool value;
	switch (channel)
	{
	case CHANNEL_1:
		value = chan1.is_triggered;
		break;
	case CHANNEL_2:
		value = chan2.is_triggered;
		break;
	}
	return value;
}

void Model::SetTriggerType(int channel, bool value)
{
	switch (channel)
	{
	case CHANNEL_1:
		chan1.triger_type = value;
		break;
	case CHANNEL_2:
		chan2.triger_type = value;
		break;
	}
}

bool Model::GetTriggerType(int channel)
{
	bool value;
	switch (channel)
	{
	case CHANNEL_1:
		value = chan1.triger_type;
		break;
	case CHANNEL_2:
		value = chan2.triger_type;
		break;
	}
	return value;
}

void Model::SetTimeScale(int channel, int value)
{
	switch (channel)
	{
		case CHANNEL_1:
			chan1.time_scale = value;
			break;
		case CHANNEL_2:
			chan2.time_scale = value;
			break;
	}
}

int Model::GetTimeScale(int channel)
{
	int temp_value;
	switch (channel)
	{
		case CHANNEL_1:
			temp_value = chan1.time_scale;
			break;
		case CHANNEL_2:
			temp_value = chan2.time_scale;
			break;
	}
	return temp_value;
}

void Model::SetVoltageScale(int channel, int value)
{
	switch (channel)
	{
		case CHANNEL_1:
			chan1.voltage_scale = value;
			break;
		case CHANNEL_2:
			chan2.voltage_scale = value;
			break;
	}
}

int Model::GetVoltageScale(int channel)
{

	int temp_value;
	switch (channel)
	{
	case CHANNEL_1:
		temp_value = chan1.voltage_scale;
		break;
	case CHANNEL_2:
		temp_value = chan2.voltage_scale;
		break;
	}
	return temp_value;
}

float Model::GetTimeScale2Pixel(int channel)
{
	float temp_value;
	if (channel == CHANNEL_1)
	{
		switch (chan1.time_scale)
		{
			//div 25us
		case 13:
			temp_value = 0.653f;
			break;
			//div 50us
		case 0:
			temp_value = 1.307f;
			break;
			//div 100us 
		case 1:
			temp_value = 2.614f;
			break;
			//div 200us 
		case 2:
			temp_value = 5.228f;
			break;
			//div 500us 
		case 3:
			temp_value = 13.071f;
			break;
			//div 1ms
		case 4:
			temp_value = 26.143f;
			break;
			//div 2ms
		case 5:
			temp_value = 52.287f;
			break;
			//div 5ms
		case 6:
			temp_value = 130.718f;
			break;
			//div 10ms
		case 7:
			temp_value = 261.437f;
			break;
			//div 20ms
		case 8:
			temp_value = 522.875f;
			break;
			//div 50ms
		case 9:
			temp_value = 1307.189f;
			break;
			//div 100ms
		case 10:
			temp_value = 2614.379f;
			break;
			//div 200ms
		case 11:
			temp_value = 5228.758f;
			break;
			//div 500ms
		case 12:
			temp_value = 13071.895f;
			break;
		}
	}
	else
	{
		switch (chan2.time_scale)
		{
			//div 25us
		case 13:
			temp_value = 0.653f;
			break;
			//div 50us
		case 0:
			temp_value = 1.307f;
			break;
			//div 100us 
		case 1:
			temp_value = 2.614f;
			break;
			//div 200us 
		case 2:
			temp_value = 5.228f;
			break;
			//div 500us 
		case 3:
			temp_value = 13.071f;
			break;
			//div 1ms
		case 4:
			temp_value = 26.143f;
			break;
			//div 2ms
		case 5:
			temp_value = 52.287f;
			break;
			//div 5ms
		case 6:
			temp_value = 130.718f;
			break;
			//div 10ms
		case 7:
			temp_value = 261.437f;
			break;
			//div 20ms
		case 8:
			temp_value = 522.875f;
			break;
			//div 50ms
		case 9:
			temp_value = 1307.189f;
			break;
			//div 100ms
		case 10:
			temp_value = 2614.379f;
			break;
			//div 200ms
		case 11:
			temp_value = 5228.758f;
			break;
			//div 500ms
		case 12:
			temp_value = 13071.895f;
			break;
		}
	}
	return temp_value;
}




int Model::GetVoltageScale2Pixel(int channel)
{
	int temp_value = 0;

	if (channel == CHANNEL_1)
	{
		switch (chan1.voltage_scale)
		{
			//div 2V
			case 7:
				temp_value = 63;
				break;

			//div 1V
			case 6:
				temp_value = 125;
				break;
			//div 500mV
			case 5:
				temp_value = 251;
				break;
			//div 200mV
			case 4:
				temp_value = 627;
				break;
			// div 100mV
			case 3:
				temp_value = 1254;
			//div 50 mV
			case 2:
				temp_value = 2508;
				break;
			//div 20mv
			case 1:
				temp_value = 6270;
				break;
			//div 10 mV
			case 0:
				temp_value = 12540;
				break;
		}
	}
	else
	{
		switch (chan2.voltage_scale)
		{
			//div 2V
			case 7:
				temp_value = 63;
				break;

				//div 1V
			case 6:
				temp_value = 125;
				break;
				//div 500mV
			case 5:
				temp_value = 251;
				break;
				//div 200mV
			case 4:
				temp_value = 627;
				break;
				// div 100mV
			case 3:
				temp_value = 1254;
				//div 50 mV
			case 2:
				temp_value = 2508;
				break;
				//div 20mv
			case 1:
				temp_value = 6270;
				break;
				//div 10 mV
			case 0:
				temp_value = 12540;
				break;
		}
	}

	return temp_value;
}

int * Model::GetTriggerData(int channel)
{
	int * p_temp;
	switch (channel)
	{
		case CHANNEL_1:
			p_temp = chan1.trigger_data;
			break;
		case CHANNEL_2:
			p_temp = chan2.trigger_data;
			break;
	}
	return p_temp;
}

void Model::SetYOffset(int channel, int value)
{
	switch (channel)
	{
	case CHANNEL_1:
		chan1.y_offset = value;
		break;
	case CHANNEL_2:
		chan2.y_offset = value;
		break;
	}
}

int Model::GetYOffset(int channel)
{
	int temp;
	switch (channel)
	{
	case CHANNEL_1:
		temp = chan1.y_offset;
		break;
	case CHANNEL_2:
		temp = chan2.y_offset;
		break;
	}
	return temp;
}








