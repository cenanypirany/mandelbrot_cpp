#include <iostream>
#include <SFML/Graphics.hpp>
#include <complex>

using namespace std;

int mandelbrot(double realVal, double imagVal, int maxIter)
{
    complex<double> initC(realVal, imagVal);
    complex<double> c(realVal, imagVal);
    
    for (int n = 1; n < maxIter; n++)
    {
        c = c * c + initC;
        if (isinf(c.imag()))
        {
            return n * 10;
        }
    }

    return 0;
}

sf::VertexArray getPoints(int side, double unit, double xCenter, double yCenter, int maxIter)
{
    double xNeg = xCenter - ((side * unit) / 2);
    double xPos = ((side * unit) / 2) + xCenter;
    double yNeg = yCenter - ((side * unit) / 2);
    double yPos = ((side * unit) / 2) + yCenter;

    sf::VertexArray sfPoints(sf::Points, side * side);

    double xCounter = xNeg;
    double yCounter = yNeg;
    int pointCount = 0;

    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            int mbVal = mandelbrot(xCounter, yCounter, maxIter);
            if (mbVal != 0)
            {
                sfPoints[pointCount].position = sf::Vector2f(i, j);
                int opacity = (mbVal * 255) / maxIter;
                sfPoints[pointCount].color = sf::Color(0, 0, 255, opacity);
                pointCount += 1;
            }

            yCounter += unit;
        }

        yCounter = yNeg;
        xCounter += unit;
    }

    return sfPoints;
}

void consoleOut(double xCenter, double yCenter, int maxIter, double unit)
{
    string details = "Center X: " + to_string(xCenter) + " | Center Y: " + to_string(yCenter) + 
        " | Max Iterations: " + to_string(maxIter) + " | Unit: " + to_string(unit);
    system("cls");
    cout << details << endl;
}

int main()
{
    int side = 600;
    double unit = 0.01;
    double xCenter = 0.0;
    double yCenter = 0.0;

    int maxIter = 200;

    cout.precision(20);

    consoleOut(xCenter, yCenter, maxIter, unit);

    string title;
    title = "Mandelbrot " + to_string(side) + "x" + to_string(side);
    sf::RenderWindow window(sf::VideoMode(side, side), title);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed) {
                
                switch (event.key.code)
                {
                    case sf::Keyboard::Left:
                        xCenter -= unit * 10;
                        break;
                    case sf::Keyboard::Right:
                        xCenter += unit * 10;
                        break;
                    case sf::Keyboard::Up:
                        yCenter -= unit * 10;
                        break;
                    case sf::Keyboard::Down:
                        yCenter += unit * 10;
                        break;
                    case sf::Keyboard::Z:
                        unit = unit + unit / 10;
                        break;
                    case sf::Keyboard::X:
                        unit = unit - unit / 10;
                        break;
                    case sf::Keyboard::A:
                        maxIter -= 50;
                        break;
                    case sf::Keyboard::S:
                        maxIter += 50;
                        break;
                }

                sf::VertexArray sfPoints = getPoints(side, unit, xCenter, yCenter, maxIter);
                
                window.clear();
                window.draw(sfPoints);
                window.display();
                consoleOut(xCenter, yCenter, maxIter, unit);
            }

            if (event.type == sf::Event::Closed) window.close();
        }
    }

    return 0;
}