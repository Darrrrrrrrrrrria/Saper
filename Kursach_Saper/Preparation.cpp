#include "Kursach_Saper.h"
Mix_Music *fon = NULL;
Mix_Chunk* Sound = NULL;
//Музыка на фон
void loadmusic()
{
    fon = Mix_LoadMUS("2.wav");
    Mix_PlayMusic(fon, -1);
}
//Звук на открытие мины
void sound_min_open()
{
    Sound = Mix_LoadWAV("boom.wav");
    Mix_PlayChannel(-1, Sound, 0);
}
//Звук на флаг
void sound_flag()
{
    Sound = Mix_LoadWAV("flag.wav");
    Mix_PlayChannel(-1, Sound, 0);
}
//Звук на победу
void sound_win()
{
    Sound = Mix_LoadWAV("win.wav");
    Mix_PlayChannel(-1, Sound, 0);
}
//Звук на поражение
void sound_lose()
{
    Sound = Mix_LoadWAV("lose.wav");
    Mix_PlayChannel(-1, Sound, 0);
}
//Звук на открытие чистой кленки
void sound_open_klet()
{
    Sound = Mix_LoadWAV("lopata.wav");
    Mix_PlayChannel(-1, Sound, 0);
}

//Текст для поля
SDL_Texture* getTextTexture(SDL_Renderer* &renderer, char*text, TTF_Font *font,int k1,int theme)
{
    SDL_Surface* textSurface = NULL;
    SDL_Color fore_color = { 56,22,103 };
    SDL_Color back_color = { 230, 187, 190};
    if (theme==0)
    {
        switch (k1)
        {
        case 0:{fore_color = { 255, 89, 94 };break;}
        case 1:{fore_color = { 128, 15, 47 };break;}
        case 2:{fore_color = { 201, 24, 74 };break;}
        case 3:{fore_color = { 231, 29, 54 };break;}
        case 4:{fore_color = { 106, 4, 15 };break;}
        case 5:{fore_color = { 217, 4, 41 };break;}
        case 6:{fore_color = { 3, 7, 30};break;}
        }
        back_color = {  229, 195, 209};
    }
    else{
        switch (k1)
        {
        case 0:{fore_color = { 255, 89, 94 };break;}
        case 1:{fore_color = { 231, 198, 255 };break;}
        case 2:{fore_color = { 200, 182, 255 };break;}
        case 3:{fore_color = { 184, 192, 255 };break;}
        case 4:{fore_color = { 187, 208, 255 };break;}
        case 5:{fore_color = { 200, 182, 255 };break;}
        case 6:{fore_color = { 190, 149, 196 };break;}
        }
        back_color = {   74, 25, 66};
    }
    textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return texture;
}
//Парсит строку по |
string* parseLine(string& line)
{
    string* ptrToArray = new string[9];
    string arrayElem = "";
    
    for (int i = 0, j = 0; i < line.size(); i++)
    {
        if (line[i] == '|' && ++i < line.size())
        {
            while (line[i] != '|')
                arrayElem += line[i++];

            ptrToArray[j++] = arrayElem;
            arrayElem = "";
            i--;
        }
    }
    
    return ptrToArray;
}
//Забирает настройки из файла в set, где set[0]-легкий уровень,set[1]-средний,set[2]-сложный.
//set[0][0]-тема(0-день,1-ночь),set[0][1]-музыка(0-нет, 1-есть), set[0][2]-рекорд по времени,set[0][3]-выбрана тема или нет
void createSettings(int set[3][4])
{
  
    string line;
    ifstream QFile("record.txt");
    if (QFile.is_open())
    {
        int j=0;
        while (getline(QFile, line))
        {
            string* parsedLine;
            parsedLine = parseLine(line);

            for (int i = 0; i < 4; i++)
            {
                set[j][i]=stoi(parsedLine[i]);
            }
            j++;
        }
        QFile.close();
    }

    else
    {
        cout
            << "|--------------------------------------------------|" << endl
            << "|                 !!! Ошибка !!!                   |" << endl
            << "|--------------------------------------------------|" << endl
            << "|           Файл не был открыт для записи          |" << endl
            << "|   Проверьте правильность указанного пути файла   |" << endl
            << "|--------------------------------------------------|" << endl; 

        exit(0);
    }
}
//Кладет настройки, полученные в процессе игры в файл
void exportToFile(int set[3][4])
{
    ofstream file("record.txt");
    if (!file.is_open())
    {
        std::cerr
            << "|--------------------------------------------------|\n"
            << "|        >>> Ошибка при открытии файла <<<         |\n"
            << "|--------------------------------------------------|\n";
        return;
    }
    for (int i=0;i<3;i++)
    {
        file << "|" <<set[i][0]
       << "|" << set[i][1]
       << "|" << set[i][2]
        << "|" << set[i][3]
       << "|\n";
    }
    file.close();
}
// Текстура для меню
SDL_Texture* getTextTexture1(SDL_Renderer* &renderer, char*text, TTF_Font *font)
{
    SDL_Surface* textSurface = NULL;
    SDL_Color fore_color = { 71,42,62  };
    SDL_Color back_color = { 230,168,215 };
    textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return texture;
}
//Проверка на выделение клеточки
bool isBallHit(SDL_Rect rect_klet, int x, int y)
{
    if (rect_klet.w == 0) return false;
    int centerX = rect_klet.x + rect_klet.w / 2;
    int centerY = rect_klet.y + rect_klet.h / 2;
    int radius = rect_klet.w / 2;
    return sqrt((centerX - x)*(centerX - x) + (centerY - y)*(centerY - y)) < radius;
}