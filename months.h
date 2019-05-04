#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>


using namespace std;
using namespace sf;

string month()
    {
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
        return months[ (now->tm_mon) ];
    }

class months
{
	public:
        Font font;
        Text mname;
        Text monthlabel2;
        RectangleShape  box;
        RectangleShape  line;
        int xpos;
        int ypos;

    months(int x,int y)
    {
        font.loadFromFile("Roboto-Regular.ttf");
        xpos=x;
        ypos=y;

        line.setSize(sf::Vector2f(360, 1));
        line.setFillColor(sf::Color(100, 100, 100));
        line.setPosition(0,140);

		box.setFillColor(Color::Transparent);
		box.setSize(Vector2f(76.25f,71.56f));
		box.setOutlineColor(sf::Color(19, 100, 206));
		box.setOutlineThickness(1);
		box.setPosition(xpos,ypos);

		mname.setColor(Color::White);
		mname.setCharacterSize(16);
		mname.Bold;
		mname.setPosition(25+x , y+25);
		mname.setFont(font);
		mname.setString("");
	}

//--------------------------------------------------------------------------------------------//


int obtainx()
	{return xpos;}
int obtainy()
    {return ypos;}

//--------------------------------------------------------------------------------------------//

string ConvertIntoString(int n)
{
    stringstream ss;
    ss<<n;
    string returnString =  ss.str();
    return returnString;
}

//--------------------------------------------------------//

void SetType(string type )
{
    if(type=="active")
    {
        box.setFillColor(Color(19,100,206));
        mname.setColor(Color(255,255,255));
    }
    else if(type=="default")
    {
        box.setFillColor(Color::Transparent);
        mname.setColor(Color(255,255,255));
    }
    else if(type=="inactive")
        { mname.setColor(Color(100,100,100)); }
}

//--------------------------------------------------------------------------------------------//

void SetMons(int mnum)
{
    if(mnum == 0)
        {mname.setString("Jan");}
    else if(mnum == 1)
        {mname.setString("Feb");}
    else if(mnum == 2)
        {mname.setString("Mar");}
    else if(mnum == 3)
        {mname.setString("Apr");}
    else if(mnum == 4)
        {mname.setString("May");}
    else if(mnum == 5)
        {mname.setString("Jun");}
    else if(mnum == 6)
        {mname.setString("Jul");}
    else if(mnum == 7)
        {mname.setString("Aug");}
    else if(mnum == 8)
        {mname.setString("Sep");}
    else if(mnum == 9)
        {mname.setString("Oct");}
    else if(mnum == 10)
        {mname.setString("Nov");}
    else if(mnum == 11)
        {mname.setString("Dec");}
    else if(mnum == 12)
        {mname.setString("Jan");}
    else if(mnum == 13)
        {mname.setString("Feb");}
    else if(mnum == 14)
        {mname.setString("Mar");}
    else if(mnum == 15)
        {mname.setString("Apr");}
    }

//--------------------------------------------------------------------------------------------//

void drawm(RenderWindow* window)
{
    window->draw(box);
    window->draw(monthlabel2);
    window->draw(mname);
    window->draw(line);
}
};
