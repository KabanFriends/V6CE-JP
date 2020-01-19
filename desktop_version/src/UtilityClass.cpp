#include "UtilityClass.h"

#include "SDL.h"

#include <sstream>

#include <algorithm>

/* Used by UtilityClass::GCString to generate a button list */
const char *GCChar(SDL_GameControllerButton button)
{
	if (button == SDL_CONTROLLER_BUTTON_A)
	{
		return "A";
	}
	else if (button == SDL_CONTROLLER_BUTTON_B)
	{
		return "B";
	}
	else if (button == SDL_CONTROLLER_BUTTON_X)
	{
		return "X";
	}
	else if (button == SDL_CONTROLLER_BUTTON_Y)
	{
		return "Y";
	}
	else if (button == SDL_CONTROLLER_BUTTON_BACK)
	{
		return "BACK";
	}
	else if (button == SDL_CONTROLLER_BUTTON_GUIDE)
	{
		return "GUIDE";
	}
	else if (button == SDL_CONTROLLER_BUTTON_START)
	{
		return "START";
	}
	else if (button == SDL_CONTROLLER_BUTTON_LEFTSTICK)
	{
		return "L3";
	}
	else if (button == SDL_CONTROLLER_BUTTON_RIGHTSTICK)
	{
		return "R3";
	}
	else if (button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
	{
		return "LB";
	}
	else if (button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
	{
		return "RB";
	}
	SDL_assert(0 && "Unhandled button!");
	return NULL;
}

bool is_number(const std::string& s)
{
    try {
        (void)std::stod(s);
        return true;
    } catch (std::invalid_argument &) {
        return false;
    }
}

int ss_toi( std::string _s )
{
	std::istringstream i(_s);
	int x;
	i >> x;
	return x;
}

growing_vector<std::string> split( const std::string &s, char delim, growing_vector<std::string> &elems )
{
	std::stringstream ss(s);
	std::string item;
	while(std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

growing_vector<std::string> split( const std::string &s, char delim )
{
	growing_vector<std::string> elems;
	return split(s, delim, elems);
}

UtilityClass::UtilityClass() :
glow(0),
	glowdir(0)
{
	for (int i = 0; i < 30; i++)
	{
		splitseconds.push_back(int((i * 100) / 30));
	}

	slowsine = 0;
	globaltemp = 0;
	temp = 0;
	temp2 = 0;
}

std::string UtilityClass::String( int _v )
{
	std::ostringstream os;
	os << _v;
	return(os.str());
}

std::string UtilityClass::GCString(growing_vector<SDL_GameControllerButton> buttons)
{
	std::string retval = "";
	for (size_t i = 0; i < buttons.size(); i += 1)
	{
		retval += GCChar(buttons[i]);
		if ((i + 1) < buttons.size())
		{
			retval += ",";
		}
	}
	return retval;
}

std::string UtilityClass::twodigits( int t )
{
	if (t < 10)
	{
		return "0" + String(t);
	}
	if (t >= 100)
	{
		return "??";
	}
	return String(t);
}

std::string UtilityClass::timestring( int t )
{
	//given a time t in frames, return a time in seconds
	tempstring = "";
	temp = (t - (t % 30)) / 30;
	if (temp < 60)   //less than one minute
	{
		t = t % 30;
		tempstring = String(temp) + ":" + twodigits(splitseconds[t]);
	}
	else
	{
		temp2 = (temp - (temp % 60)) / 60;
		temp = temp % 60;
		t = t % 30;
		tempstring = String(temp2) + ":" + twodigits(temp) + ":" + twodigits(splitseconds[t]);
	}
	return tempstring;
}

std::string UtilityClass::number( int _t )
{
	const int BIGGEST_SMALL_NUMBER = 50;
	const char* smallnumbers[] = {"0", "1", "2", "3", 
		"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50"};

	if(_t <= BIGGEST_SMALL_NUMBER) {
		return smallnumbers[_t];
	}

	return "Lots";
}

bool UtilityClass::intersects( SDL_Rect A, SDL_Rect B )
{
	return (SDL_HasIntersection(&A, &B) == SDL_TRUE);
}

void UtilityClass::updateglow()
{
	slowsine++;
	if (slowsine >= 64) slowsine = 0;

	if (glowdir == 0) {
		glow+=2;
		if (glow >= 62) glowdir = 1;
	}else {
		glow-=2;
		if (glow < 2) glowdir = 0;
	}
}
