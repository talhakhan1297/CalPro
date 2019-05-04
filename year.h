#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

using namespace std;
using namespace sf;

class year
{
	public:
        Font font;
        Text yname;
        Text yearlabel;
        RectangleShape  box;
        RectangleShape  line;
        int xpos;
        int ypos;

    year(int x,int y)
    {
        font.loadFromFile("Roboto-Regular.ttf");
        xpos=x;
        ypos=y;

        line.setSize(sf::Vector2f(360, 1));
        line.setFillColor(sf::Color(100, 100, 100));
        line.setPosition(0,140);

        yearlabel.setColor(Color::White);
        yearlabel.setCharacterSize(20);
        yearlabel.setPosition(20,155);
        yearlabel.setFont(font);
        yearlabel.setString("2010-2025");

		box.setFillColor(Color::Transparent);
		box.setSize(Vector2f(76.25f,71.56f));
		box.setOutlineColor(sf::Color(19, 100, 206));
		box.setOutlineThickness(1);
		box.setPosition(xpos,ypos);

		yname.setColor(Color::White);
		yname.setCharacterSize(16);
		yname.Bold;
		yname.setPosition(20+x , y+25);
		yname.setFont(font);
		yname.setString("");
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
        yname.setColor(Color(255,255,255));
    }
    else if(type=="default")
    {
        box.setFillColor(Color::Transparent);
        yname.setColor(Color(255,255,255));
    }
}

//--------------------------------------------------------------------------------------------//

void SetYears(int mnum)
{
    if(mnum == 0)
        {yname.setString("2010");}
    else if(mnum == 1)
        {yname.setString("2011");}
    else if(mnum == 2)
        {yname.setString("2012");}
    else if(mnum == 3)
        {yname.setString("2013");}
    else if(mnum == 4)
        {yname.setString("2014");}
    else if(mnum == 5)
        {yname.setString("2015");}
    else if(mnum == 6)
        {yname.setString("2016");}
    else if(mnum == 7)
        {yname.setString("2017");}
    else if(mnum == 8)
        {yname.setString("2018");}
    else if(mnum == 9)
        {yname.setString("2019");}
    else if(mnum == 10)
        {yname.setString("2020");}
    else if(mnum == 11)
        {yname.setString("2021");}
    else if(mnum == 12)
        {yname.setString("2022");}
    else if(mnum == 13)
        {yname.setString("2023");}
    else if(mnum == 14)
        {yname.setString("2024");}
    else if(mnum == 15)
        {yname.setString("2025");}
    }

//--------------------------------------------------------------------------------------------//

void drawm(RenderWindow* window)
{
    window->draw(box);
    window->draw(yearlabel);
    window->draw(yname);
    window->draw(line);
}
};

