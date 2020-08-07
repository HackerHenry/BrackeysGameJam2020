#define NOISE_CUTOFF 2500
#define SPACE 0
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>
#include <iostream>
using namespace sf;
class CustomRecorder : public sf::SoundRecorder
{
public:
    bool isRunning=true;
private:
    RectangleShape obsticle1;
    RectangleShape obsticle2;
    RenderWindow win;
    Sprite sprite;
    Texture texture;
    Event event;
    unsigned long long points=0;
private:
    virtual bool onStart(){
        win.create(VideoMode(1024*2,600*2),"FlippyBird");
        win.setFramerateLimit(10);
        texture.loadFromFile("penguin.png");
        sprite.setTexture(texture);
        sprite.setPosition(10,300);
        obsticle1.setSize(Vector2f(50,1200));
        obsticle2.setSize(Vector2f(50,1200));
        obsticle1.setFillColor(Color::Black);
        obsticle2.setFillColor(Color::Black);
        obsticle1.setPosition(1024*2,500);
        obsticle2.setPosition(1024*2,-1200+100);
        return true;
    }
    virtual bool onProcessSamples(const Int16* samples, std::size_t sampleCount){
        while(win.pollEvent(event)){
            if(event.type == Event::Closed){
                std::cout << "Congratulation! Your points: " << points;
                isRunning = false;
                win.close();
            }
        }
        for(int i=0;i<sampleCount;i++){
            if(samples[i]>NOISE_CUTOFF){ // noise cancellation
               sprite.move(0,-40); 
            }
        }
        if(obsticle1.getPosition().x<0){
            int rand_int=rand()%300;
            obsticle1.setPosition(1024*2,-1200+100+rand_int+SPACE);
            obsticle2.setPosition(1024*2,500+rand_int);
            points+=10;
        }
        if(collision(obsticle1.getPosition().x ,obsticle1.getPosition().y,sprite.getPosition().x,sprite.getPosition().y)){isRunning=false;win.close();}
        if(collision(obsticle2.getPosition().x ,obsticle2.getPosition().y,sprite.getPosition().x,sprite.getPosition().y)){isRunning=false;win.close();}
        if(sprite.getPosition().y >= 600*2 || sprite.getPosition().y<=0){
            isRunning=false;
            win.close();
        }
        sprite.move(0,15);
        win.clear(Color::White);
        obsticle1.move(-20,0);
        obsticle2.move(-20,0);
        win.draw(sprite);
        win.draw(obsticle2);
        win.draw(obsticle1);
        win.display();
        return true;
    }
    bool collision(int cx,int cy,int bx,int by){
        if(cx<=bx && cx+50>=bx){
            if(cy<=by && cy+1200>=by){
                return true;
            }
        }
        return false;
    }
};
int main(){
    CustomRecorder rec;
    Clock clk;
    rec.start(60);
    while(rec.isRunning){}
    rec.stop();
}
