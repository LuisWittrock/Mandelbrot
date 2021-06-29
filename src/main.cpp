#include <SFML/Graphics.hpp>
#include <iostream>

//if number is stable color pixel black else color pixel white. Real color comes later

using namespace std;
using namespace sf;

class Frame
{
    public:
        RenderWindow window;
        Event event;
        int WINDOW_HEIGHT = 300;
        int WINDOW_WIDTH = 300;
};

class Mandelbrot : Frame
{
    public:
        VertexArray varray;
        int maxEscape = 1000;

        float graphXMax = 2; //2
        float graphXMin = -0.5; //-0.5

        float graphYMax = 1; //1
        float graphYMin = -1; //-1

        float pixelToGraph(int pixelCoord, float graphWidth, int imageWidth, float graphMin) //translates pixel to graph coordinate
        {
            return ((float)pixelCoord*(graphWidth/(float)imageWidth)) + graphMin;
        }

        int calcMandelbrotEscape(float real, float imaginary)
        {
            float zReal, zImag;
            float z0Real, z0Imag;
            int n, currEscape;
            zReal = zImag = 0;
            z0Real = z0Imag = 0;

            for(int n = 0; n<=maxEscape; n++)
            {
                z0Real = ((zReal * zReal) - (zImag * zImag) - real);
                z0Imag = (2 * (zReal * zImag)) + imaginary;

                if (((z0Real * z0Real) + (z0Imag * z0Imag)) >= 4) //if it gets bigger then the number that would head towards infinity we break out and return the amount of cycles needed
                {
                    currEscape = n;
                    return currEscape;
                }

                zReal = z0Real;
                zImag = z0Imag;
                currEscape = maxEscape;
            }
            return currEscape; //if we we dont head towards infinity we can say that for our cycle the number remains stable and color it black
        }

        void checkInputs() //zoom into the mandelbrot
        {
            while(1)
            {
                if(Keyboard::isKeyPressed(Keyboard::Space))
                {
                    graphXMax = 2;
                    graphXMin = -0.5;
                    graphYMax = 1;
                    graphYMin = -1;
                    break;
                }
                if(Keyboard::isKeyPressed(Keyboard::Down))
                {
                    cout << "up \n";
                    graphXMax += 0.1;
                    graphXMin -= 0.1*0.25;
                    graphYMax += 0.05;
                    graphYMin -= 0.05;
                    break;
                }
                if(Keyboard::isKeyPressed(Keyboard::Up))
                {
                    cout << "down \n";
                    graphXMax -= 0.1;
                    graphXMin += 0.1*0.25;
                    graphYMax -= 0.05;
                    graphYMin += 0.05;
                    break;
                }
                if(Keyboard::isKeyPressed(Keyboard::D))
                {
                    cout << "up \n";
                    graphXMax += 0.05;
                    graphXMin += 0.05;
                    break;
                }
                    
                if(Keyboard::isKeyPressed(Keyboard::A))
                {
                    cout << "down \n";
                    graphXMax -= 0.05;
                    graphXMin -= 0.05;
                    break;
                }
                if(Keyboard::isKeyPressed(Keyboard::S))
                {
                    cout << "Right \n";
                    graphYMax += 0.05;
                    graphYMin += 0.05;
                    break;
                }
                if(Keyboard::isKeyPressed(Keyboard::W))
                {
                    cout << "Left \n";
                    graphYMax -= 0.05;
                    graphYMin -= 0.05;
                    break;
                } 
            }
            
                
            
        }

        void calcMandelbrot(int horizontal, int vertical)
        {
            varray.clear();
            float graphX;
            float graphY;
            int escape;
            Vertex vertex;

            for(int y = 0; y<WINDOW_HEIGHT; y++)
            {
                graphY = pixelToGraph(y,graphYMax-graphYMin, WINDOW_HEIGHT, graphYMin);
                for(int x = 0; x<WINDOW_WIDTH; x++)
                {
                    vertex.position = Vector2f(x,y);
                    graphX = pixelToGraph(x, graphXMax-graphXMin, WINDOW_WIDTH, graphXMin);
                    escape = calcMandelbrotEscape(graphX, graphY);

                    if(escape == maxEscape)
                    {
                        vertex.color = Color::Black;
                    }
                    else vertex.color = Color(escape%255,escape%255,escape%255);

                    varray.append(vertex);
                }
            }
        }

        void drawMandelbrot()
        {
            window.create(VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Mandelbrot");
            
            while(window.isOpen())
            {
                calcMandelbrot(WINDOW_WIDTH, WINDOW_HEIGHT);
                while(window.pollEvent(event))
                {
                    if(event.type == sf::Event::Closed) window.close();
                }
                
                window.clear();
                window.draw(varray);
                window.display();
                checkInputs();
            }
        }

};

int main()
{
    Frame frame;
    Mandelbrot mandelbrot;
    mandelbrot.drawMandelbrot();
}