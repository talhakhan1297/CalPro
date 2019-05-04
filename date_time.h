#include<sstream>
#include<string>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include "console_formatting.h"


class Date_Time
{
public:
    sf::Font font;
    sf::Font font2;
    sf::Text time;
    sf::Text date;

//---------------------------------------------------------------//

Date_Time()
{
    font.loadFromFile("Roboto-Regular.ttf");
    font2.loadFromFile("Roboto-Thin.ttf");

    time.setFont(font2);
    time.setCharacterSize(55);
    time.setColor(sf::Color::White);
    time.setPosition(sf::Vector2f(20.0f,20.0f));

    date.setFont(font);
    date.setCharacterSize(15);
    date.setColor(sf::Color::White);
    date.setPosition(sf::Vector2f(20.0f,105.0f));
}

//---------------------------------------------------------//

string ConvertIntoString(int n)
{
    stringstream ss;
    ss<<n;
    string returnString =  ss.str();
    return returnString;
}
//--------------------------------------------------------//

void display_date_time()
{
    dateAndTime now;
    time.setString(now.time12());
    date.setString(now.weekDay()+ ", " + now.month() + " " + this->ConvertIntoString(now.day()) +", "+ this->ConvertIntoString(now.year()));
}

//--------------------------------------------------------//

void draw_dt(sf::RenderWindow* window)
{
    window->draw(time);
    window->draw(date);
}

};
