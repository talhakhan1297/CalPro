#include<vector>
#include<ctime>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include "date_time.h"
#include "days.h"
#include "months.h"
#include "year.h"

using namespace std;
using namespace sf;


class calander
{

public:
    calander* instance;
    vector<days*>month;
    vector<months*>monthwindow;
    vector<year*>yearwindow;
    days* target;
    time_t currentTime;
	struct tm* currentDate;
	int activemonth;
	int activeyear;
	Text yearlabel;
	Text monthlabel;
	Text daylabel;
	RenderWindow window;
	Font font;
	Texture downarrowImage;
	Texture uparrowImage;
	Sprite downarrow;
	Sprite uparrow;
	Event event;
	int goingyear;
    int monthScreenFlag = 0;



//------------------------------------------------------------------------//


string convertintostring(int n)
{
    stringstream ss;
    ss<<n;
    string returnString =  ss.str();
    return returnString;
}

//------------------------------------------------------------------------//

bool spriteincludepoint(Sprite* sprite,int x,int y)
{
    if(x >= sprite->getPosition().x && x < sprite->getPosition().x + sprite->getGlobalBounds().width
    && y >= sprite->getPosition().y && y < sprite->getPosition().y + sprite->getGlobalBounds().height)

        { return true; }

	return false;
}

//------------------------------------------------------------------------//

string GetMonthString(int monthNum)
{
	string returnString = "";

	switch(monthNum)
	{
		case 0: returnString = "January"; break;
		case 1: returnString = "February"; break;
		case 2: returnString = "March"; break;
		case 3: returnString = "April"; break;
		case 4: returnString = "May"; break;
		case 5: returnString = "June"; break;
		case 6: returnString = "July"; break;
		case 7: returnString = "August"; break;
		case 8: returnString = "September"; break;
		case 9: returnString = "October"; break;
		case 10: returnString = "November"; break;
		case 11: returnString = "December"; break;
	}

	return returnString;
}

//------------------------------------------------------------------------//

int GetDaysInMonth(int month, int year)
{
	int result = 0;

	switch(month)
	{
		case 0: result = 31; break;
		case 1: if(year % 4 == false && year % 100 != false || year % 400 == false)
                    {result = 29;}
                else
                    {result = 28;}
		break;
		case 2: result = 31; break;
		case 3: result = 30; break;
		case 4: result = 31; break;
		case 5: result = 30; break;
		case 6: result = 31; break;
		case 7: result = 31; break;
		case 8: result = 30; break;
		case 9: result = 31; break;
		case 10: result = 30; break;
		case 11: result = 31; break;
	}

	return result;
}

//------------------------------------------------------------------------//

void monthname()
{
    int index;
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
            { monthwindow.push_back(new months(20+77*j,190+73*i)); }
    }

    for(index = 0; index <= 15; index++)
    {
        monthwindow[index]->SetMons(index);
        if(index == currentDate->tm_mon)
        {   monthwindow[index]->SetType("active");}

        if(index > 11)
        {
            monthwindow[index]->SetMons(index);
            monthwindow[index]->SetType("inactive");
        }
    }
}

//------------------------------------------------------------------------//

void selectedmonthname()
{
    int index;
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
            { monthwindow.push_back(new months(20+77*j,190+73*i)); }
    }

    for(index = 0; index <= 15; index++)
    {
        monthwindow[index]->SetMons(index);
        if(index > 11)
        {
            monthwindow[index]->SetMons(index);
            monthwindow[index]->SetType("inactive");
        }
        else
        {   monthwindow[index]->SetType("default");}
    }
}

//------------------------------------------------------------------------//

void yearname()
{
    int index;
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
            { yearwindow.push_back(new year(20+77*j,190+73*i)); }
    }

    for(index = 0; index <= 15; index++)
    {
        yearwindow[index]->SetYears(index);

        if(index + 110 == currentDate->tm_year )
            { yearwindow[index]->SetType("active");}
        else
            { yearwindow[index]->SetType("default");}

    }
}


//------------------------------------------------------------------------//


void CurrentMonth()
{	//create day objects.
	for(int h = 0; h < 6; h++)
	{
		for(int w = 0; w < 7; w++)
		{ month.push_back(new days(20 + (w *44), 230 + (h * 38))); }
	}


	int dayOfTheWeek = currentDate->tm_wday;

	//find which day of the week the first of the month falls under.
	for(int d = currentDate->tm_mday; d > 0; d--)
	{
		if(dayOfTheWeek == 0)
		{ dayOfTheWeek = 6; }

		else
		{ dayOfTheWeek--; }
	}



	int daysInLastMonth = 0;

	if(currentDate->tm_mon != 0)
        { daysInLastMonth = GetDaysInMonth(currentDate->tm_mon - 1, currentDate->tm_year + 1900); }

    else
        { daysInLastMonth = GetDaysInMonth(11, (currentDate->tm_year - 1) + 1900); }



	int daysInThisMonth = GetDaysInMonth(currentDate->tm_mon, currentDate->tm_year + 1900);


	//even without this, the calendar is still accurate. It just looks nicer to have some days from the previous month displayed.
	if(dayOfTheWeek == 0)
        {dayOfTheWeek += 7;}

	int index = 0;


	//set last month's days.
	for(int n = daysInLastMonth - (dayOfTheWeek); n <= daysInLastMonth; n++)
        {
		month[index]->SetNumber(n);
		month[index]->SetType("inactive");
		index++;
        }


	//set this month's days.
	for(int i = 1; i <= daysInThisMonth; i++)
	{
		month[index]->SetNumber(i);

		if(i == currentDate->tm_mday)
		{ month[index]->SetType("current"); }

		else
		{ month[index]->SetType("default"); }

		index++;
	}


	//set next month's days.
	for(int r = 1; index < month.size(); r++)
	{
		month[index]->SetNumber(r);
		month[index]->SetType("inactive");
		index++;
	}
}

//------------------------------------------------------------------------//

void NextMonth()
{

	int dayOfTheWeek = 0;
	bool found = false;


	for(int d = 0; d < month.size(); d++)
	{
		if(month[d]->gettype() == "inactive" && month[d]->getnumber() == 1)
			{ found = true; }

		else if(found == false)
		{
			if(dayOfTheWeek == 6)
				{ dayOfTheWeek = 0; }
			else
				{ dayOfTheWeek++; }
		}
	}


	if(activemonth == 11)
		{
		activemonth = 0;
		activeyear++;
		}

	else
		{ activemonth++; }



	monthlabel.setString(GetMonthString(activemonth) + " " + convertintostring(activeyear));

	int daysInLastMonth = 0;

	if(activemonth!= 0)
		{ daysInLastMonth = GetDaysInMonth(activemonth - 1, activeyear); }

	else
		{ daysInLastMonth = GetDaysInMonth(11, activeyear - 1); }



	int daysInThisMonth = GetDaysInMonth(activemonth, activeyear);

	int index = 0;


	//even without this, the calendar is still accurate. It just looks nicer to have some days from the previous month displayed.
	if(dayOfTheWeek == 0){dayOfTheWeek += 7;}

	//set last month's days.
	for(int n = daysInLastMonth - (dayOfTheWeek - 1); n <= daysInLastMonth; n++)
	{
		month[index]->SetNumber(n);
		month[index]->SetType("inactive");
		index++;
	}


	//set this month's days.
	for(int i = 1; i <= daysInThisMonth; i++)
	{
		month[index]->SetNumber(i);

		if(i == currentDate->tm_mday && activemonth == currentDate->tm_mon && activeyear== currentDate->tm_year + 1900)
		{ month[index]->SetType("current"); }

		else
		{ month[index]->SetType("default"); }

		index++;
	}

	//set next month's days.
	for(int r = 1; index < month.size(); r++)
	{
		month[index]->SetNumber(r);
		month[index]->SetType("inactive");
		index++;
	}

}

//------------------------------------------------------------------------//

void PreviousMonth()
{
	int numToFind = 0;

	if(activemonth != 0)
	{ numToFind = GetDaysInMonth(activemonth - 1, activeyear); }

	else
	{ numToFind = GetDaysInMonth(11, activeyear - 1); }


	int dayOfTheWeek = 0;
	bool found = false;


	//find reference point (the final day) from the current month.
	for(int d = 0; d < month.size(); d++)
	{
		if(month[d]->gettype() == "inactive" && month[d]->getnumber() == numToFind)
			{ found = true; }

		else if(found == false)
		{
			if(dayOfTheWeek == 6)
			{ dayOfTheWeek = 0; }

			else
			{ dayOfTheWeek++; }
		}
	}


	//find the day of the week that the first of last month falls under.
	for(int a = numToFind - 1; a >= 1; a--)
	{
		if(dayOfTheWeek == 0)
			{ dayOfTheWeek = 6; }

		else
			{  dayOfTheWeek--; }
	}


	//change current month.
	if(activemonth == 0)
		{
		activemonth = 11;
		activeyear--;
		}

	else
		{ activemonth--; }


	monthlabel.setString(GetMonthString(activemonth) + " " + convertintostring(activeyear));

	int daysInLastMonth = 0;

	if(activemonth != 0)
		{ daysInLastMonth = GetDaysInMonth(activemonth- 1, activeyear); }

	else
		{ daysInLastMonth = GetDaysInMonth(11, activeyear - 1); }


	int daysInThisMonth = GetDaysInMonth(activemonth, activeyear);

	int index = 0;

	//even without this, the calendar is still accurate. It just looks nicer to have some days from the previous month displayed.
	if(dayOfTheWeek == 0)
		{dayOfTheWeek += 7;}


	//set last month's days.
	for(int n = daysInLastMonth - (dayOfTheWeek - 1); n <= daysInLastMonth; n++)
	{
		month[index]->SetNumber(n);
		month[index]->SetType("inactive");
		index++;
	}

	//set this month's days.
	for(int i = 1; i <= daysInThisMonth; i++)
	{
		month[index]->SetNumber(i);

		if(i == currentDate->tm_mday && activemonth == currentDate->tm_mon && activeyear == currentDate->tm_year + 1900)
		{ month[index]->SetType("current"); }

		else
		{ month[index]->SetType("default"); }

		index++;
	}

	//set next month's days.
	for(int r = 1; index < month.size(); r++)
	{
		month[index]->SetNumber(r);
		month[index]->SetType("inactive");
		index++;
	}
}

//------------------------------------------------------------------------//





void HandleInput(Event* event)
{
    if(event->type == Event::MouseButtonPressed)
    {
		if(event->mouseButton.button == Mouse::Left)
		{
			//Handle directional arrows.
			if(monthScreenFlag==0)
            {
                if(spriteincludepoint(&downarrow, event->mouseButton.x, event->mouseButton.y) == true)
                    {NextMonth(); }

                else if(spriteincludepoint(&uparrow, event->mouseButton.x, event->mouseButton.y) == true)
                    { PreviousMonth(); }
            }


            if(monthScreenFlag==0)
            {
                if(event->mouseButton.x >= monthlabel.getPosition().x &&
                    event->mouseButton.x <= monthlabel.getPosition().x + monthlabel.getGlobalBounds().width &&
                    event->mouseButton.y >= monthlabel.getPosition().y &&
                    event->mouseButton.y <= monthlabel.getPosition().y + monthlabel.getGlobalBounds().height)
                {
                    monthname();
                    monthScreenFlag = 1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }
                    else
                    { selectedmonthname(); }
                }
            }


            else if(monthScreenFlag==1)
            {
                if(event->mouseButton.x >= 20 && event->mouseButton.x < 80 && event->mouseButton.y >= monthlabel.getPosition().y &&
                   event->mouseButton.y <= monthlabel.getPosition().y + monthlabel.getGlobalBounds().height)
                {
                    yearname();
                    monthScreenFlag = 2;
                }
            }

            if(event->mouseButton.x >= 20 && event->mouseButton.x < 150 && event->mouseButton.y >= 105 && event->mouseButton.y <= 115)
                { monthScreenFlag = 0; }

//----------------------------------------------------------------------------------//


            //Controls Zoom in
        if(monthScreenFlag==1)
        {
            if(event->mouseButton.x>=20&&event->mouseButton.x<20+77*1&&event->mouseButton.y>=195&&event->mouseButton.y<260)
            {
               if(0<=activemonth)
                {
                    for(int i=activemonth;i>0;i--)
                        { PreviousMonth(); }

                    monthScreenFlag=0;
                }

                if(activemonth<=0)
                {
                    for(int i=activemonth;i<0;i++)
                        { NextMonth(); }

                    monthScreenFlag=0;
                }
            }



            if(event->mouseButton.x>=20+77*1&&event->mouseButton.x<20+2*77&&event->mouseButton.y>=195&&event->mouseButton.y<260)
            {

                if(1<=activemonth)
                {
                    for(int i=activemonth;i>1;i--)
                        { PreviousMonth(); }

                    monthScreenFlag=0;
                }

                if(activemonth<=1)
                {
                    for(int i=activemonth;i<1;i++)
                        { NextMonth();}

                    monthScreenFlag=0;
                }
            }

            if(event->mouseButton.x>=20+2*77&&event->mouseButton.x<20+3*77&&event->mouseButton.y>=195&&event->mouseButton.y<260)
            {

                if(2<=activemonth)
                {
                    for(int i=activemonth;i>2;i--)
                        { PreviousMonth(); }

                    monthScreenFlag=0;
                }

                if(activemonth<=2)
                {
                    for(int i=activemonth;i<2;i++)
                        { NextMonth(); }

                    monthScreenFlag=0;
                }
            }

            if(event->mouseButton.x>=20+3*77&&event->mouseButton.x<20+4*77&&event->mouseButton.y>=195&&event->mouseButton.y<260)
            {

                if(3<=activemonth)
                {
                    for(int i=activemonth;i>3;i--)
                        { PreviousMonth(); }

                    monthScreenFlag=0;
                }

                if(activemonth<=3)
                {
                    for(int i=activemonth;i<3;i++)
                        { NextMonth(); }

                    monthScreenFlag=0;
                }
            }

            if(event->mouseButton.x>=20&&event->mouseButton.x<97&&event->mouseButton.y>=261&&event->mouseButton.y<324)
            {

                if(4<=activemonth)
                {
                    for(int i=activemonth;i>4;i--)
                    { PreviousMonth(); }

                    monthScreenFlag=0;
                }

                if(activemonth<=4)
                {
                    for(int i=activemonth;i<4;i++)
                        { NextMonth(); }

                    monthScreenFlag=0;
                }
            }

            if(event->mouseButton.x>=20+77*1&&event->mouseButton.x<20+2*77&&event->mouseButton.y>=261&&event->mouseButton.y<324)
            {

                if(5<=activemonth)
                {
                    for(int i=activemonth;i>5;i--)
                        { PreviousMonth(); }

                    monthScreenFlag=0;
                }

                if(activemonth<=5)
                {
                    for(int i=activemonth;i<5;i++)
                        { NextMonth(); }

                    monthScreenFlag=0;
                }
            }

            if(event->mouseButton.x>=20+77*2&&event->mouseButton.x<20+3*77&&event->mouseButton.y>=261&&event->mouseButton.y<324)
            {

                if(6<=activemonth)
                {
                    for(int i=activemonth;i>6;i--)
                        { PreviousMonth(); }

                    monthScreenFlag=0;
                }

                if(activemonth<=6)
                {
                    for(int i=activemonth;i<6;i++)
                        { NextMonth(); }

                    monthScreenFlag=0;
                }
            }

            if(event->mouseButton.x>=20+77*3&&event->mouseButton.x<20+4*77&&event->mouseButton.y>=261&&event->mouseButton.y<324)
            {
                if(7<=activemonth)
                {
                    for(int i=activemonth;i>7;i--)
                        { PreviousMonth(); }

                    monthScreenFlag=0;
                }

                if(activemonth<=7)
                {
                    for(int i=activemonth;i<7;i++)
                        { NextMonth(); }

                    monthScreenFlag=0;
                }
            }



            if(event->mouseButton.x>=20&&event->mouseButton.x<97&&event->mouseButton.y>=325&&event->mouseButton.y<390)
            {
                if(8<=activemonth)
                {
                    for(int i=activemonth;i>8;i--)
                        { PreviousMonth(); }

                    monthScreenFlag=0;
                }

                if(activemonth<=8)
                {
                    for(int i=activemonth;i<8;i++)
                        { NextMonth(); }

                    monthScreenFlag=0;
                }
            }

            if(event->mouseButton.x>=20+77*1&&event->mouseButton.x<20+2*77&&event->mouseButton.y>=325&&event->mouseButton.y<390)
            {
                if(9<=activemonth)
                {
                    for(int i=activemonth;i>9;i--)
                        { PreviousMonth(); }

                    monthScreenFlag=0;
                }

                if(activemonth<=9)
                {
                    for(int i=activemonth;i<9;i++)
                        { NextMonth(); }

                    monthScreenFlag=0;
                }
            }
             if(event->mouseButton.x>=20+77*2&&event->mouseButton.x<20+3*77&&event->mouseButton.y>=325&&event->mouseButton.y<390)
            {
                if(10<=activemonth)
                {
                    for(int i=activemonth;i>10;i--)
                        { PreviousMonth(); }

                    monthScreenFlag=0;

                }

            if(activemonth<=10)
                {
                    for(int i=activemonth;i<10;i++)
                        { NextMonth(); }

                    monthScreenFlag=0;
                }
            }

            if(event->mouseButton.x>=20+77*3&&event->mouseButton.x<20+4*77&&event->mouseButton.y>=325&&event->mouseButton.y<390)
            {
                if(11<=activemonth)
                {
                    for(int i=activemonth;i>11;i--)
                        { PreviousMonth(); }

                    monthScreenFlag=0;
                }

                if(activemonth<=11)
                {
                    for(int i=activemonth;i<11;i++)
                        { NextMonth(); }

                    monthScreenFlag=0;
                }
            }



        }


        if(monthScreenFlag==2)
        {
           if(event->mouseButton.x>=20&&event->mouseButton.x<20+77*1&&event->mouseButton.y>=195&&event->mouseButton.y<260)
            {
                if(2010<=activeyear)
                {
                    while(2010<activeyear)
                        { PreviousMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                        { monthname(); }

                    else
                    { selectedmonthname(); }
                }

                if(activeyear<=2010)
                {
                    while(activeyear<2010)
                        { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                        { monthname(); }

                    else
                        { selectedmonthname(); }
                }
            }



            if(event->mouseButton.x>=20+77*1&&event->mouseButton.x<20+2*77&&event->mouseButton.y>=195&&event->mouseButton.y<260)
            {
                if(2011<=activeyear)
                {
                    while(2011<activeyear)
                        { PreviousMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                        { monthname(); }
                    else
                        { selectedmonthname(); }

                }

                if(activeyear<=2011)
                {
                    while(activeyear<2011)
                        { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                        { monthname(); }
                    else
                        { selectedmonthname(); }

                }
            }

            if(event->mouseButton.x>=20+2*77&&event->mouseButton.x<20+3*77&&event->mouseButton.y>=195&&event->mouseButton.y<260)
            {
                if(2012<=activeyear)
                {
                    while(2012<activeyear)
                        { PreviousMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }

                    else
                    { selectedmonthname(); }

                }

                if(activemonth<=2)
                {
                    while(activeyear<2012)
                        { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                        { monthname(); }

                    else
                        { selectedmonthname(); }

                }
            }

            if(event->mouseButton.x>=20+3*77&&event->mouseButton.x<20+4*77&&event->mouseButton.y>=195&&event->mouseButton.y<260)
            {
               if(2013<=activeyear)
                {
                    while(2013<activeyear)
                        { PreviousMonth(); }

                    monthScreenFlag=1;

                if(activeyear==currentDate->tm_year+1900)
                { monthname(); }

                else
                { selectedmonthname(); }

                }

                if(activeyear<=2013)
                {
                    while(activeyear<2013)
                        { NextMonth(); }

                    monthScreenFlag = 1;

                    if(activeyear==currentDate->tm_year+1900)
                        { monthname(); }
                    else
                        { selectedmonthname(); }

                }
            }
             if(event->mouseButton.x>=20&&event->mouseButton.x<97&&event->mouseButton.y>=261&&event->mouseButton.y<324)
            {
                if(2014<=activeyear)
                {
                    while(2014<activeyear)
                        { PreviousMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }

                    else
                    { selectedmonthname(); }

                }

                if(activeyear<=2014)
                {
                    while(activeyear<2014)
                        { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                        { monthname(); }
                    else
                    { selectedmonthname(); }

                }
            }

            if(event->mouseButton.x>=20+77*1&&event->mouseButton.x<20+2*77&&event->mouseButton.y>=261&&event->mouseButton.y<324)
            {
                if(2015<=activeyear)
                {
                    while(2015<activeyear)
                        { PreviousMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }

                    else
                    { selectedmonthname(); }

                }

                if(activeyear<=2015)
                {
                    while(activeyear<2015)
                        { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }

                    else
                    { selectedmonthname(); }

                }
            }
             if(event->mouseButton.x>=20+77*2&&event->mouseButton.x<20+3*77&&event->mouseButton.y>=261&&event->mouseButton.y<324)
            {
               if(2016<=activeyear)
                {
                    while(2016<activeyear)
                        { PreviousMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                        { monthname(); }
                    else
                    { selectedmonthname(); }

                }

                if(activeyear<=2016)
                {
                    while(activeyear<2016)
                        { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }
                    else
                    { selectedmonthname(); }

                }
            }
             if(event->mouseButton.x>=20+77*3&&event->mouseButton.x<20+4*77&&event->mouseButton.y>=261&&event->mouseButton.y<324)
            {
               if(2017<=activeyear)
                {
                    while(2017<activeyear)
                        { PreviousMonth(); }

                    monthScreenFlag=0;

                }

                if(activeyear<=2017)
                {
                    while(activeyear<2017)
                        { NextMonth(); }
                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }
                    else
                    { selectedmonthname(); }

                }
            }



            if(event->mouseButton.x>=20&&event->mouseButton.x<97&&event->mouseButton.y>=325&&event->mouseButton.y<390)
            {
                if(2018<=activeyear)
                {
                    while(2018<activeyear)
                        { PreviousMonth(); }

                    monthScreenFlag=1;
                }

                if(activemonth<=8)
                {
                    while(activeyear<2018)
                        { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }

                    else
                    { selectedmonthname(); }
                }
            }


            if(event->mouseButton.x>=20+77*1&&event->mouseButton.x<20+2*77&&event->mouseButton.y>=325&&event->mouseButton.y<390)
            {
                if(2019<=activeyear)
                {
                    while(2019<activeyear)
                    { PreviousMonth(); }

                    monthScreenFlag=1;
                }

                if(activemonth<=2019)
                {
                    while(activeyear<2019)
                    { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                        { monthname(); }

                    else
                        { selectedmonthname(); }

                }
            }

            if(event->mouseButton.x>=20+77*2&&event->mouseButton.x<20+3*77&&event->mouseButton.y>=325&&event->mouseButton.y<390)
            {
                if(2020<=activeyear)
                {
                    while(2020<activeyear)
                    { PreviousMonth(); }

                    monthScreenFlag=1;
                }

                if(activeyear<=2020)
                {
                    while(activeyear<2020)
                    { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }
                    else
                    { selectedmonthname(); }

                }
            }

            if(event->mouseButton.x>=20+77*3&&event->mouseButton.x<20+4*77&&event->mouseButton.y>=325&&event->mouseButton.y<390)
            {
                if(2021<=activeyear)
                {
                    while(2021<activeyear)
                        { PreviousMonth(); }

                    monthScreenFlag=1;
                }

                if(activeyear<2021)
                {
                    while(activeyear<2021)
                    { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }
                    else
                    { selectedmonthname(); }

                }
            }

            if(event->mouseButton.x>=20&&event->mouseButton.x<97&&event->mouseButton.y>=392&&event->mouseButton.y<467)
            {
                if(2022<=activeyear)
                {
                    while(2022<activeyear)
                    { PreviousMonth(); }

                    monthScreenFlag=1;
                }

                if(activeyear<=2022)
                {
                    while(activeyear<2022)
                    { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                        { monthname(); }

                    else
                        { selectedmonthname(); }
                }
            }

            if(event->mouseButton.x>=20+77*1&&event->mouseButton.x<20+2*77&&event->mouseButton.y>=392&&event->mouseButton.y<467)
            {
                if(2023<=activeyear)
                {
                    while(2023<activeyear)
                    { PreviousMonth(); }

                    monthScreenFlag=1;
                }

                if(activeyear<=2023)
                {
                    while(activeyear<2023)
                    { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }

                    else
                    { selectedmonthname(); }

                }
            }

            if(event->mouseButton.x>=20+77*2&&event->mouseButton.x<20+3*77&&event->mouseButton.y>=392&&event->mouseButton.y<467)
            {
                if(2024<=activeyear)
                {
                    while(2024<activeyear)
                    { PreviousMonth(); }

                    monthScreenFlag=1;
                }

                if(activeyear<=2024)
                {
                    while(activeyear<2024)
                    { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }
                    else
                    { selectedmonthname(); }

                }
            }

            if(event->mouseButton.x>=20+77*3&&event->mouseButton.x<20+4*77&&event->mouseButton.y>=392&&event->mouseButton.y<467)
            {
                if(2025<=activeyear)
                {
                    while(2025<activeyear)
                    { PreviousMonth(); }

                    monthScreenFlag=1;
                }

                if(activeyear<2025)
                {
                    while(activeyear<2025)
                    { NextMonth(); }

                    monthScreenFlag=1;

                    if(activeyear==currentDate->tm_year+1900)
                    { monthname(); }

                    else
                    { selectedmonthname(); }

                }
            }



            }
		}
    }
}


//------------------------------------------------------------------------//

Text ongoingyear()
{
    yearlabel.setString(convertintostring(activeyear));
    yearlabel.setFont(font);
	yearlabel.setCharacterSize(20);
	yearlabel.setPosition(20,155);
	return yearlabel;

}

//------------------------------------------------------------------------//
calander()
{
	window.create(sf::VideoMode(360, 500), "CalPro", Style::Close);


	font.loadFromFile("Roboto-Regular.ttf");

	currentTime = time(0);
	currentDate = localtime(&currentTime);


	activemonth = currentDate->tm_mon;
	activeyear = currentDate->tm_year + 1900;

	monthlabel.setString(GetMonthString(currentDate->tm_mon) + " " + convertintostring(currentDate->tm_year + 1900));
	monthlabel.setFont(font);
	monthlabel.setCharacterSize(20);
	monthlabel.setPosition(20,155);

	daylabel.setString(" Sun     Mon    Tue    Wed    Thu     Fri      Sat  ");
	daylabel.setPosition(20, 200);
	daylabel.setFont(font);
	daylabel.setCharacterSize(15);


	downarrowImage.loadFromFile("downarrow.png");
	uparrowImage.loadFromFile("uparrow.png");
	downarrow.setTexture(downarrowImage);
	downarrow.setScale(0.15,0.15);
	downarrow.setPosition(300, 157);
	uparrow.setTexture(uparrowImage);
	uparrow.setPosition(250, 157);
	uparrow.setScale(0.15,0.15);
	downarrowImage.setSmooth(true);
	uparrowImage.setSmooth(true);


	CurrentMonth();
	yearname();
}

//------------------------------------------------------------------------//

calander* GetInstance()
{
    instance = new calander();
	return instance;
}

//------------------------------------------------------------------------//

void Run()
{
    Date_Time now;
	while(window.isOpen())
    {
        now.display_date_time();
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
			{ window.close(); }

            HandleInput(&event);
        }

            window.clear(sf::Color(30,30,30));
            now.draw_dt(&window);


            if(monthScreenFlag==0)
            {
                window.draw(downarrow);
                window.draw(monthlabel);
                window.draw(uparrow);
                window.draw(daylabel);
                for(int d = 0; d < month.size(); d++)
                { month[d]->Draw(&window); }
            }
            else if(monthScreenFlag==1)
            {
                for(int j = 0; j < monthwindow.size(); j++)
                { monthwindow[j] -> drawm(&window); }
                  window.draw(ongoingyear());
            }

            else
            {
                for(int j = 0; j < yearwindow.size(); j++)
                    { yearwindow[j] -> drawm(&window); }
            }
            window.display();

    }
}
//------------------------------------------------------------------------//
};//end of class calendar



