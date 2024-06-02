#include <stdio.h>
#include <stdlib.h>
#include <locale>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <ctime>
#include <math.h>
#include <SDL_mixer.h>
#include <algorithm>
#include <complex.h>
#include <fstream>
#include <iostream>
#include<string>
#include<windows.h>
#include <locale>
using namespace std;
struct Klet{double x, y,w,h;int sost,tap;bool min;};
void initKlet(Klet* kletka, double x, double y, double w, double h,int sost,int tap);//Инициализация клетки в структуре.
void loadmusic();//Музыка на фон
void sound_min_open();//Звук на открытие мины
void sound_flag();//Звук на флаг
void sound_win();//Звук на победу
void sound_lose();//Звук на поражение
void sound_open_klet();//Звук на открытие чистой клетки
bool isBallHit(SDL_Rect rect_klet, int x, int y);//Проверка на выделение клеточки
void Min_Num(int *MinNum,int cur_num);//Размещение мин на поле
int Min_Vocrug(int TecNum,int *MinNum);//Подсчет мин вокруг клетки
SDL_Texture* getTextTexture(SDL_Renderer* &renderer, char*text, TTF_Font *font,int k1,int theme);//Текст для поля
void text_on_klet(SDL_Renderer *& renderer,SDL_Rect rect_klet[],TTF_Font*my_font,int *MinNum,int i,int theme);//Вывод количества мин вокруг клетки
void risuem_kletochki(SDL_Renderer *& renderer,int theme);//Отрисовка поля
void draw_mins(SDL_Renderer* &renderer, SDL_Rect rect_klet[],int count, SDL_Texture* texture,Klet *kletka,int *MinNum,int theme);//Отрисовка открытых мин
void draw_flags(SDL_Renderer* &renderer, SDL_Rect rect_klet[],int count, SDL_Texture* texture,Klet *kletka,int theme);//Рисует флажочки
string* parseLine(string& line);//Парсит строку по |
void createSettings(int set[3][4]);//Забирает настройки из файла в set, где set[0]-легкий уровень,set[1]-средний,set[2]-сложный. set[0][0]-тема(0-день,1-ночь),set[0][1]-музыка(0-нет, 1-есть), set[0][2]-рекорд по времени
void exportToFile(int set[3][4]);//Кладет настройки, полученные в процессе игры в файл
void SelectedTheme(SDL_Renderer* &renderer,int theme);//Рисует солнце/луну (темы)
void DrawMusInMenu(SDL_Renderer* &renderer);// Отрисовка режимов звука в меню
SDL_Texture* getTextTexture1(SDL_Renderer* &renderer, char*text, TTF_Font *font);// Текстура для меню
void drawText(SDL_Renderer *&renderer, SDL_Texture *texture, int num);// Текст меню
void DrawMenu(SDL_Renderer* &renderer, TTF_Font *my_font,SDL_Rect rectlevel,SDL_Rect recttheme,SDL_Rect rectmus);//Отрисовка меню



