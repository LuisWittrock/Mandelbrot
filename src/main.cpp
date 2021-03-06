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
        int WINDOW_HEIGHT = 500;
        int WINDOW_WIDTH = 500;
};

class Mandelbrot : Frame
{
    public:
        VertexArray varray;
        int maxEscape = 500;

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
                if(Keyboard::isKeyPressed(Keyboard::Up))
                {

                    graphXMax -= 0.1*(graphXMax-graphXMin);
                    graphXMin += 0.1*0.25*(graphXMax-graphXMin);
                    graphYMax -= 0.05*(graphYMax-graphYMin);
                    graphYMin += 0.05*(graphYMax-graphYMin);
                    break;
                }
                if(Keyboard::isKeyPressed(Keyboard::D))
                {

                    graphXMax += 0.05;
                    graphXMin += 0.05;
                    break;
                }
                    
                if(Keyboard::isKeyPressed(Keyboard::A))
                {

                    graphXMax -= 0.05;
                    graphXMin -= 0.05;
                    break;
                }
                if(Keyboard::isKeyPressed(Keyboard::S))
                {

                    graphYMax += 0.05;
                    graphYMin += 0.05;
                    break;
                }
                if(Keyboard::isKeyPressed(Keyboard::W))
                {

                    graphYMax -= 0.05;
                    graphYMin -= 0.05;
                    break;
                } 
            }
            
                
            
        }

        void calcMandelbrot(int horizontal, int vertical)
        {
            int colors[16][3] = {{66,30,15},{25,7,26},{9,1,47},{4,4,73},{0,7,100},{57,125,209},{134,181,229},{211,236,248},{248,201,95},{255,170,0},{204,128,0},{153,87,0},{106,52,4}};
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
                    else
                    {
                        vertex.color = Color(colors[escape%13][0],colors[escape%16][1],colors[escape%16][2]);
                    }
                    
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