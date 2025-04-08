#ifndef CGUI_SDL_HPP
#define CGUI_SDL_HPP
#include<vector>
#include <iostream>
#include "include/SDL.h"
//#include "SDL_ttf.h"
#include <string>
#include <unordered_map>
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
double avg(GV a);
double min(GV a);

double max(GV a);

bool ValInRange(double val, GV range);
bool VecInArea(GV vec, area a);
class Component {
    public:
    GV pos;
    GV size;
    SDL_Color bgcolor;
    SDL_Color rdcolor;
    Component(GV Pos, GV Size, SDL_Color Bgcolor): size(Size), pos(Pos), bgcolor(Bgcolor) ,rdcolor(Bgcolor){}; 
    Component(GV Pos, GV Size): size(Size), pos(Pos) {}; 
    virtual void RenderSelf(SDL_Renderer *r);
    virtual void HEvent(Screen*s);
};
class Label : public Component {
    public:
        std::string val; 
        void RenderSelf(SDL_Renderer *r);
};
class Screen {
    private:
    SDL_Event e;
    std::vector<Component> components;
    //std::unordered_map<std::string,std::vector<int>> idmap;
    int width, height;
    SDL_Window *w;
    SDL_Renderer *r;
    GV mousepos = GV(0,0);
    public:
    Screen(SDL_Window *wind, SDL_Renderer *rend): w(wind), r(rend){};
    Screen() : w(nullptr), r(nullptr) {};
    void DrawPixel(int x, int y);
    void AddComponent(Component c);
    /*void DrawRect(int x, int y, int w, int h) {
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
    }*/
    void HandleEvents(SDL_Event e);
    void RenderComponents(); /*{
        for(int i = 0; i < components.size();i++) {
            if(&components[i] != nullptr) {
            components[i].RenderSelf(r);
            }
        }
    }*/
    void UpdateScreen();
};
};
#endif