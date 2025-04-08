#include<vector>
#include "include/SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>
#pragma once
namespace CGUI {
    class Screen;
class GV {
    public:
    int x;
    int y;
    GV(int X, int Y) : x(X), y(Y) {};
};
class area {
    public:
        GV a,b;
    area(GV A, GV B) : a(A), b(B) {};
    area(): a(GV(0,0)), b(GV(0,0)) {};
};
double avg(GV a) {
    return (a.x + a.y) /2;
}
double min(GV a) {
    return (a.x > a.y) ? a.y : a.x;
}

double max(GV a) {
    return (a.x > a.y) ? a.x : a.y;
}

bool ValInRange(double val, GV range) {
    if(val > min(range) && val < max(range)) {
        return true;
    } 
    return false;
}
bool VecInArea(GV vec, area a) {
    return(ValInRange(vec.x,GV(a.a.x,a.b.x)) & ValInRange(vec.y,GV(a.a.y,a.b.y)));
}
class Component {
    public:
    GV pos;
    GV size;
    SDL_Color bgcolor;
    SDL_Color rdcolor;
    Component(GV Pos, GV Size, SDL_Color Bgcolor): size(Size), pos(Pos), bgcolor(Bgcolor) ,rdcolor(Bgcolor){}; 
    Component(GV Pos, GV Size): size(Size), pos(Pos) {}; 
    virtual void RenderSelf(SDL_Renderer *r) {};
    virtual void HEvent(Screen*s) {};
};
class Label : public Component {
    public:
        std::string val; 
        void RenderSelf(SDL_Renderer *r) {
            //sdl2 ttf stuff

        }   
};
class Screen {
    public:
    std::vector<Component> components;
    int width, height;
    SDL_Window *w;
    SDL_Renderer *r;
    GV mousepos = GV(0,0);
    Screen(SDL_Window *wind, SDL_Renderer *rend): w(wind), r(rend){};
    Screen() : w(nullptr), r(nullptr) {};
    void DrawPixel(int x, int y) {
        SDL_RenderDrawPoint(r,x,y);
    }
    void AddComponent(Component c) {
        components.push_back(c);
    }
    void DrawRect(int x, int y, int w, int h) {
        SDL_Rect *rc;
        rc->x = x;
        rc->y = y;
        rc->w = w;
        rc->h = h;
        SDL_RenderDrawRect(r,rc);
    }
    void DrawRect(GV pos, GV size) {
        SDL_Rect *rc;
        rc->x = pos.x;
        rc->y = pos.y;
        rc->w = size.x;
        rc->h = size.y;
        SDL_RenderDrawRect(r,rc);
    }
    void HandleEvents(SDL_Event e) {
        SDL_GetRelativeMouseState(&mousepos.x,&mousepos.y);
        for(int i = 0; i < components.size();i++) {
            components[i].HEvent(this);
        }
    }
    void RenderComponents() {
        for(int i = 0; i < components.size();i++) {
            components[i].RenderSelf(r);
        }
    }
    void UpdateScreen() {
      SDL_RenderPresent(r);
    }
};
};