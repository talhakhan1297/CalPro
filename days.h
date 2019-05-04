#include<iostream>
#include<sstream>
#include<string>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

using namespace std;
using namespace sf;

class days //days class
{
public:
    RectangleShape rectday;
    RectangleShape line;
    int xpos,ypos;
    int number;
    Text numdate;
    string type0;
    Font font;
    bool selected0;

//------------------------------------------------------------------------//

days(int x,int y)
{
    font.loadFromFile("Roboto-Regular.ttf");
    xpos=x;
    ypos=y;
    rectday.setPosition(x,y);
    rectday.setOrigin(0,0);
    rectday.setOutlineThickness(1);
    rectday.setFillColor(Color::Transparent);
    rectday.setOutlineColor(sf::Color(19, 100, 206));
    rectday.setSize(sf::Vector2f(43.0f,37.0f));

    line.setSize(sf::Vector2f(360, 1));
    line.setFillColor(sf::Color(100, 100, 100));
    line.setPosition(0,140);


    numdate.setString("");
    numdate.setFont(font);
    numdate.setCharacterSize(12);
    numdate.setPosition(xpos+15,ypos+10);
    type0="default";

}

//------------------------------------------------------------------------//


int getx()
    {return xpos;}

int gety()
    {return ypos;}

string gettype()
    { return type0; }

int getnumber()
	{ return number;}

//------------------------------------------------------------------------//

void SetNumber(int x)
{
    number = x;
    string numstring;
    stringstream ss;
    ss << number;
    numstring = ss.str();
    numdate.setString(numstring);
}

//------------------------------------------------------------------------//

void SetType(string type)
{
    type0 = type;

    if(type0 == "default")
        {
        rectday.setFillColor(Color::Transparent);
        numdate.setColor(Color(255,255,255));
        }

    else if(type0 == "current")
        { rectday.setFillColor(sf::Color(19, 100, 206)); }

    else if(type0 == "inactive")
        { numdate.setColor(Color(100,100,100)); }
}

//------------------------------------------------------------------------//

void SetSelected(bool selected)
{
    selected0 == selected;

    if(selected0 == true)
        { rectday.setOutlineColor(Color::Magenta); }

    else
        { rectday.setOutlineColor(Color::Blue); }
}

//------------------------------------------------------------------------//

void Draw(RenderWindow* window)
{
    window->draw(rectday);
    window->draw(numdate);
    window->draw(line);
}

//------------------------------------------------------------------------//

};//end days class
