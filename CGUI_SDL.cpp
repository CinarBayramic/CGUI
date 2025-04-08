#define DEBUG 0
#include<vector>
#include "include/SDL.h"
//#include "SDL_ttf.h"
#include <iostream>
#include <string>
#include "CGUI_SDL.hpp"
#pragma once
namespace CGUI {

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

    void Component::RenderSelf(SDL_Renderer *r){
    //std::cout << "Rendering Self!\n";
    SDL_Color start;
    SDL_GetRenderDrawColor(r,&start.r,&start.g,&start.b,&start.a);
    SDL_SetRenderDrawColor(r,rdcolor.r,rdcolor.g,rdcolor.b,rdcolor.a);
    //SDL_SetRenderDrawColor(r,rdcolor.r,rdcolor.g,rdcolor.b,rdcolor.a);
    SDL_Rect rc; // dikdörtgenler pointer olamaz
    rc.x = pos.x;
    rc.y = pos.y;
    rc.w = size.x;
    rc.h = size.y;
    SDL_RenderFillRect(r, &rc); // dikdörgenlerin adresini alıp fonksiyona veriyoruz.
    SDL_SetRenderDrawColor(r,start.r,start.g,start.b,start.a);
    }
    void Component::HEvent(Screen*s) {
        
        rdcolor = bgcolor;
        area a = area(pos,GV(pos.x+size.x,pos.y+size.y));
        if(VecInArea(s->mousepos,a)) {
            /*std::cout << "you are wrong!!!";
            std::cout << s->mousepos.x << "M_X        " ;
            std::cout << s->mousepos.y << "M_Y\n";
            std::cout << a.a.x << "X "<< a.a.y << "Y\n";
            std::cout << a.b.x << "X "<< a.b.y << "Y\n";
            SDL_Delay(10000);*/
            rdcolor.a = 0;
            rdcolor.r = 0;
            rdcolor.g = 0;
            rdcolor.b = 0;
        } else {
            rdcolor.r = bgcolor.r;
            rdcolor.g = bgcolor.g;
            rdcolor.b = bgcolor.b;  
        }
    }



    void Screen::DrawPixel(int x, int y) {
        SDL_RenderDrawPoint(r,x,y);
    }
    void Screen::AddComponent(Component c) {
        components.push_back(c);
    }
    /*void Screen::DrawRect(int x, int y, int w, int h) {
        SDL_Rect *rc;
        rc->x = x;
        rc->y = y;
        rc->w = w;
        rc->h = h;
        SDL_RenderDrawRect(r,rc);
    }
    void Screen::DrawRect(GV pos, GV size) {
        SDL_Rect *rc;
        rc->x = pos.x;
        rc->y = pos.y;
        rc->w = size.x;
        rc->h = size.y;
        SDL_RenderDrawRect(r,rc);
    }*/
    void Screen::HandleEvents(SDL_Event e) {
        for(int i = 0; i < components.size();i++) {
            components[i].HEvent(this);
        }
    }
    void Screen::RenderComponents() {
        for(int i = 0; i < components.size();i++) {
            components[i].RenderSelf(r);
        }
    }
    void Screen::UpdateScreen() {
      SDL_RenderPresent(r);
      int x,y;
      SDL_GetMouseState(&x,&y);
      mousepos = GV(x,y);
      #if DEBUG > 0
      std::cout << mousepos.x << "M_X        " ;   
      std::cout << mousepos.y << "M_Y\n";
        #endif
    }
};