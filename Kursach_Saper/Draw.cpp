#include "Kursach_Saper.h"
//Рисует солнце/луну (темы)
void SelectedTheme(SDL_Renderer* &renderer,int theme)
{
    SDL_Surface *moonImage = IMG_Load("moon.bmp");
    SDL_SetColorKey(moonImage, SDL_TRUE,
     SDL_MapRGB(moonImage->format, 255, 255, 255));
    SDL_Texture *moonTexture = SDL_CreateTextureFromSurface(renderer, moonImage);
    SDL_FreeSurface(moonImage);
    
    SDL_Surface *sunImage = IMG_Load("sun.bmp");
    SDL_SetColorKey(sunImage, SDL_TRUE,
     SDL_MapRGB(sunImage->format, 255, 255, 255));
    SDL_Texture *sunTexture = SDL_CreateTextureFromSurface(renderer, sunImage);
    SDL_FreeSurface(sunImage);
    SDL_Rect dstrect;
    dstrect.x = 820; dstrect.y = 700;
    dstrect.h = 100; dstrect.w = 100;
    if (theme==0){SDL_RenderCopy(renderer, sunTexture, NULL, &dstrect);}
    else{SDL_RenderCopy(renderer, moonTexture, NULL, &dstrect);}
    
}
// Отрисовка режимов звука в меню
void DrawMusInMenu(SDL_Renderer* &renderer)
{
    SDL_Surface *sunImage = IMG_Load("musis_1.bmp");
    SDL_SetColorKey(sunImage, SDL_TRUE,
     SDL_MapRGB(sunImage->format, 255, 255, 255));
    SDL_Texture *sunTexture = SDL_CreateTextureFromSurface(renderer, sunImage);
    SDL_FreeSurface(sunImage);
    SDL_Rect dstrect={100,600,100,100};
   SDL_RenderCopy(renderer, sunTexture, NULL, &dstrect);
    
    SDL_Surface *suImage = IMG_Load("musisnot_1.bmp");
    SDL_SetColorKey(suImage, SDL_TRUE,
     SDL_MapRGB(suImage->format, 255, 255, 255));
    SDL_Texture *suTexture = SDL_CreateTextureFromSurface(renderer, suImage);
    SDL_FreeSurface(suImage);
    SDL_Rect dstrect1={250,600,100,100};
    SDL_RenderCopy(renderer, suTexture, NULL, &dstrect1);
}

// Текст меню
void drawText(SDL_Renderer *&renderer, SDL_Texture *texture, int num)
{
    SDL_Rect rect;
    switch (num)
    {
    case 1: rect = {250, 20, 400,  100};break;
    case 2: rect = {350, 310, 200,  100};break;
    case 3: rect =  {55, 170, 230,  80};break;
    case 4: rect =  {335, 170, 230,  80};break;
    case 5: rect ={615, 170, 230,  80};break;
    case 6: rect = {300, 450, 100,  80};break;
    case 7: rect = {500, 450, 100,  80};break;
    case 8: rect = {700, 700, 200,  100};break;
    case 9: rect = {100,600,100,100};break;
    case 10: rect = {250,600,100,100};break;
    case 11:rect={800,0,150,80};break;
    case 12:rect={800,100,150,100};break;
    case 13:rect={800,220,150,80};break;
    case 14:rect={800,320,150,80};break;
    case 15:rect={800,420,150,80};break;
    case 16:rect={800,520,150,100};break;
    case 17:rect={600, 700, 300,  100};break;
    case 18:rect={200,320,550,150};break;
    }
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    
}
//Отрисовка меню
void DrawMenu(SDL_Renderer* &renderer, TTF_Font *my_font,SDL_Rect rectlevel,SDL_Rect recttheme,SDL_Rect rectmus)
{
    SDL_Texture *textTexture;
    char text1[]="Режим игры";
    textTexture = getTextTexture1(renderer, text1, my_font);
    drawText(renderer, textTexture,1);
    char text2[]="Тема";
    textTexture = getTextTexture1(renderer, text2, my_font);
    drawText(renderer, textTexture,2);
    char text3[]="Легкий";
    textTexture = getTextTexture1(renderer, text3, my_font);
    drawText(renderer, textTexture,3);
    char text4[]="Средний";
    textTexture = getTextTexture1(renderer, text4, my_font);
    drawText(renderer, textTexture,4);
    char text5[]="Сложный";
    textTexture = getTextTexture1(renderer, text5, my_font);
    drawText(renderer, textTexture,5);
    char text6[]="День";
    textTexture = getTextTexture1(renderer, text6, my_font);
    drawText(renderer, textTexture,6);
    char text7[]="Ночь";
    textTexture = getTextTexture1(renderer, text7, my_font);
    drawText(renderer, textTexture,7);
    char text8[]="Начать";
    textTexture = getTextTexture1(renderer, text8, my_font);
    drawText(renderer, textTexture,8);
    char text9[]=" ";
    textTexture = getTextTexture1(renderer, text9, my_font);
    drawText(renderer, textTexture,9);
    char text10[]=" ";
    textTexture = getTextTexture1(renderer, text10, my_font);
    drawText(renderer, textTexture,10);
    SDL_RenderDrawRect(renderer, &rectlevel);
    SDL_RenderDrawRect(renderer, &recttheme);
    SDL_RenderDrawRect(renderer, &rectmus);
    DrawMusInMenu(renderer);
}