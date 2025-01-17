
#include "Kursach_Saper.h"
SDL_Window *win = NULL;
SDL_Surface *scr = NULL;
SDL_Surface *flower = NULL;
int SCREEN_W= 950;
int SCREEN_H=800;
int MIN_COUNT ; //количество мин
int KLET_COUNT; //количество клеток
int KlET_STR ;  //количество клеток в строке
int A_KLET ;    //сторона клетки
int LIFE_COUNT; //количество жизней

//Инициализация клетки в структуре.
void initKlet(Klet* kletka, double x, double y, double w, double h,int sost,int tap) {
    kletka->x = x;
    kletka->y = y;
    kletka->w=w;
    kletka->h = h;
    kletka->sost=sost;
    kletka->tap=tap;
    kletka->min=false;
}
//Размещение мин на поле
void Min_Num(int *MinNum,int cur_num)
{
    srand(time(NULL));
    int j=0;
    int *M_N_K=new int [KLET_COUNT];
    for (int i = 0; i <KLET_COUNT;i++){M_N_K[i] = i;}
    std::random_shuffle(M_N_K, M_N_K+KLET_COUNT);
  
    while (j<MIN_COUNT)
    {
        if (M_N_K[j]!=cur_num )
        {
            MinNum[j]=M_N_K[j];
            j++;
        }
    } 
}
//Подсчет мин вокруг клетки
int Min_Vocrug(int TecNum,int *MinNum)
{
    int count=0;
    int lv,v,rv,r,rn,n,ln,l;
    lv=TecNum-KlET_STR-1;
    v=TecNum-KlET_STR;
    rv=TecNum-KlET_STR+1;
    r=TecNum+1;
    rn=TecNum+KlET_STR+1;
    n=TecNum+KlET_STR;
    ln=TecNum+KlET_STR-1;
    l=TecNum-1;
    for(int i=0;i<KlET_STR;i++)
    {
        if (TecNum==i*KlET_STR){lv=-1;l=-1;ln=-1;}
        if(TecNum==(i*KlET_STR)+4){rv=-1;r=-1;rn=-1;}
    }
    for (int i=0;i<MIN_COUNT;i++)
    {
        if (lv==MinNum[i]){count++;}
        if (v==MinNum[i]){count++;}
        if (rv==MinNum[i]){count++;}
        if (r==MinNum[i]){count++;}
        if (rn==MinNum[i]){count++;}
        if (n==MinNum[i]){count++;}
        if (ln==MinNum[i]){count++;}
        if (l==MinNum[i]){count++;}
    }
    return count;
}
//Вывод количества мин вокруг клетки
void text_on_klet(SDL_Renderer *& renderer,SDL_Rect rect_klet[],TTF_Font*my_font,int *MinNum,int i,int theme) {
    char text1[10];
    int k1;
        k1=Min_Vocrug(i,MinNum);
        _itoa_s(k1,text1,10);
        SDL_Rect rect={rect_klet[i].x,rect_klet[i].y,rect_klet[i].w,rect_klet[i].h};
        SDL_Texture * textTexture1= getTextTexture(renderer,text1,my_font,k1,theme);
        SDL_RenderCopy(renderer,textTexture1,NULL,&rect);
}
//Отрисовка поля
void risuem_kletochki(SDL_Renderer *& renderer,int theme)
{
    if (theme==0){SDL_SetRenderDrawColor(renderer, 209, 73, 91, 0);}
    else{SDL_SetRenderDrawColor(renderer,5, 4, 4,0);}
    SDL_Rect rect;
    int sdwig=0;
    for(int i=0;i<KlET_STR+1;i++)
    {
        rect={sdwig,0,3,SCREEN_H};SDL_RenderFillRect(renderer, &rect);
        if (i%2==0){sdwig+=A_KLET-1;}else{sdwig+=A_KLET;}
    }
    
    int sdwig1=0;
    for(int i=0;i<KlET_STR+2;i++)
    {
        rect={0,sdwig1,SCREEN_H,3};SDL_RenderFillRect(renderer, &rect);
        if (i%2==0){sdwig1+=A_KLET-1;}else{sdwig1+=A_KLET;}
    }
}
//Отрисовка открытых мин
void draw_mins(SDL_Renderer* &renderer, SDL_Rect rect_klet[],int count, SDL_Texture* texture,Klet *kletka,int *MinNum,int theme)
{
    SDL_Surface *minImage = IMG_Load("mina_2.bmp");
    SDL_SetColorKey(minImage, SDL_TRUE,
     SDL_MapRGB(minImage->format, 255, 255, 255));
    SDL_Texture *minTexture = SDL_CreateTextureFromSurface(renderer, minImage);
    SDL_FreeSurface(minImage);
    SDL_Surface *flagImage;
    if(theme==0){flagImage= IMG_Load("day.bmp");}else{flagImage= IMG_Load("night.bmp");}
    SDL_SetColorKey(flagImage, SDL_TRUE,
     SDL_MapRGB(flagImage->format, 255, 255, 255));
    SDL_Texture *flagTexture = SDL_CreateTextureFromSurface(renderer, flagImage);
    SDL_FreeSurface(flagImage);
    bool fl=false;
    for (int i = 0; i < count; i++)
    {
        for (int j=0; j<MIN_COUNT;j++)
        {
            if (i==MinNum[j]){
                if ( kletka[i].sost==1){SDL_RenderCopy(renderer, minTexture, NULL, &rect_klet[i]);}}
        }
        if(kletka[i].tap==0 &&  kletka[i].sost!=1){SDL_RenderCopy(renderer, flagTexture, NULL, &rect_klet[i]);}
    }
}
//Рисует флажочки
void draw_flags(SDL_Renderer* &renderer, SDL_Rect rect_klet[],int count, SDL_Texture* texture,Klet *kletka,int theme)
{
     SDL_Surface *flagImage;
    if(theme==0){flagImage= IMG_Load("day.bmp");}else{flagImage= IMG_Load("night.bmp");}
     SDL_SetColorKey(flagImage, SDL_TRUE,
      SDL_MapRGB(flagImage->format, 255, 255, 255));
     SDL_Texture *flagTexture = SDL_CreateTextureFromSurface(renderer, flagImage);
     SDL_FreeSurface(flagImage);
    for (int i = 0; i < count; i++)
    {
        if (kletka[i].tap==0 && kletka[i].sost!=1){SDL_RenderCopy(renderer, flagTexture, NULL, &rect_klet[i]);}
        if(kletka[i].tap!=0 &&  kletka[i].sost!=1){SDL_RenderCopy(renderer, texture, NULL, &rect_klet[i]);}
    }
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_Init(0);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
    win = SDL_CreateWindow(u8"САПЕР", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);
    bool mainexit=false;
    SDL_SetRenderDrawColor(renderer, 229, 195, 209, 0);
    SDL_RenderClear(renderer);
    TTF_Init();
    TTF_Font* my_font = TTF_OpenFont("3.ttf", 100);
    SDL_Rect rect1 = {250, 20, 400,  100};
    SDL_Rect rect2 = {350, 310, 200,  100};
    SDL_Rect rect3 = {55, 170, 230,  80};
    SDL_Rect rect4 = {335, 170, 230,  80};
    SDL_Rect rect5 = {615, 170, 230,  80};    
    SDL_Rect rect6 = {300, 450, 100,  80};
    SDL_Rect rect7 = {500, 450, 100,  80};
    SDL_Rect rect8 = {700, 700, 200,  100};
    SDL_Rect rect9 = {100,600,100,100};
    SDL_Rect rect10 = {250,600,100,100};
    SDL_Rect rect17 = {600, 700, 300,  100};
    SDL_Rect recttheme;
    SDL_Rect rectlevel;
    SDL_Rect rectmus;
    int vict=0;
    while(!mainexit)
    {
        bool start=false;
        bool exit=false;
        bool drex=false;
        bool choise=false;
    SDL_Event eventStart;
    int set[3][4];
    int selected=0;
    createSettings(set);
    int theme=set[0][0];//0-день, 1-ночь
    int level=0;
    for(int i=0;i<3;i++){if (set[i][3]==1){selected=i;}}
    switch (selected)
    {
    case 0:{
            rectlevel=rect3;
            if (set[0][0]==0){recttheme=rect6;}else{recttheme=rect7;}
            if (set[0][1]==0){rectmus=rect10;}else{rectmus=rect9;}
            break;}
    case 1:{
            rectlevel=rect4;
            if (set[1][0]==0){recttheme=rect6;}else{recttheme=rect7;}
            if (set[1][1]==0){rectmus=rect10;}else{rectmus=rect9;}
            break;}
    case 2:{
            rectlevel=rect5;
            if (set[2][0]==0){recttheme=rect6;}else{recttheme=rect7;}
            if (set[2][1]==0){rectmus=rect10;}else{rectmus=rect9;}
            break;}
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    while (!start)
    {
        while (SDL_PollEvent(&eventStart))
        {
            if ((eventStart.type == SDL_QUIT)||(eventStart.type== SDL_MOUSEBUTTONDOWN&& eventStart.button.button == SDL_BUTTON_LEFT && isBallHit(rect8,eventStart.button.x,eventStart.button.y))){if((eventStart.type == SDL_QUIT)){exit=true;mainexit=true;drex=true;choise=true;}start = true;}
            DrawMenu(renderer,my_font,rectlevel,recttheme,rectmus);
            if(eventStart.type== SDL_MOUSEBUTTONDOWN&& eventStart.button.button == SDL_BUTTON_LEFT)
            {
                if( isBallHit(rect3,eventStart.button.x,eventStart.button.y)){level=0;set[0][3]=1;set[1][3]=0;set[2][3]=0;rectlevel=rect3;}
                if( isBallHit(rect4,eventStart.button.x,eventStart.button.y)){level=1;set[1][3]=1;set[0][3]=0;set[2][3]=0;rectlevel=rect4;}
                if ( isBallHit(rect5,eventStart.button.x,eventStart.button.y)){level=2;set[2][3]=1;set[1][3]=0;set[0][3]=0;rectlevel=rect5;}
                if( isBallHit(rect6,eventStart.button.x,eventStart.button.y)){theme=0;set[level][0]=0;recttheme=rect6;}
                if( isBallHit(rect7,eventStart.button.x,eventStart.button.y)){theme=1;set[level][0]=1;recttheme=rect7;}
                if(isBallHit(rect9,eventStart.button.x,eventStart.button.y)){set[level][1]=1;rectmus=rect9;}
                if(isBallHit(rect10,eventStart.button.x,eventStart.button.y)){set[level][1]=0;rectmus=rect10;}
            }
        }
        exportToFile(set);
        SDL_RenderPresent(renderer);
    }
    SDL_RenderClear(renderer);
    if (theme==0)
    {
        SDL_SetRenderDrawColor(renderer, 229, 195, 209, 0);
    }else{ SDL_SetRenderDrawColor(renderer, 74, 25, 66,0);}
    SDL_RenderClear(renderer);
    createSettings(set);
    for(int i=0;i<3;i++){if (set[i][3]==1){selected=i;}}
    switch (selected)
    {
    case 0:{MIN_COUNT=5 ;
            KLET_COUNT=25;
            KlET_STR=5 ;
            A_KLET=160;
            break;}
    case 1:{MIN_COUNT=10 ;
            KLET_COUNT=100;
            KlET_STR=10 ;
            A_KLET=80;
            break;}
    case 2:{MIN_COUNT=16 ;
            KLET_COUNT=256;
            KlET_STR=16 ;
            A_KLET=50;
            break;}
    }
    switch (MIN_COUNT)
    {
    case 5:LIFE_COUNT=2;break;
    case 10:LIFE_COUNT=4;break;
    case 15:LIFE_COUNT=7;break;
    }
    int loc_life=0;
    int clear_klet=KLET_COUNT-MIN_COUNT;
    int open_klet=1;
    if(set[selected][1]==1){  loadmusic();}else{ Mix_PauseMusic();}
    int *MinNum=new int [MIN_COUNT];
    Klet* kletka=new Klet [KLET_COUNT];
    SDL_Rect *rect_klet=new SDL_Rect[KLET_COUNT];
    int kl=0;
    SDL_Surface *flagImage = IMG_Load("bab.bmp");
    SDL_SetColorKey(flagImage, SDL_TRUE,
    SDL_MapRGB(flagImage->format, 255, 255, 255));
    SDL_Texture *flagTexture = SDL_CreateTextureFromSurface(renderer, flagImage);
    SDL_FreeSurface(flagImage);

    //Получение координат всех клеток в структуре
    for (int i=0;i<KlET_STR;i++){for (int j=0;j<KlET_STR;j++){initKlet(&kletka[kl],A_KLET*j,A_KLET*i,A_KLET,A_KLET,0,0);kl+=1;}}

    //Передача координат всех клеток из структуры в рект
    for (int i=0;i<KLET_COUNT;i++){rect_klet[i].x=kletka[i].x;rect_klet[i].y=kletka[i].y;rect_klet[i].w=kletka[i].w;rect_klet[i].h=kletka[i].h;}
    SelectedTheme(renderer,theme);
    SDL_Event event;
    bool quit = false;
    TTF_Init();
    int first=0;
    int start_time = time(NULL);
        SDL_Texture *textTexture;
        char text18[]="ВЫ ВЫИГАЛИ!!!";
        char text19[]="ВЫ ПРОИГРАЛИ!!!";
        char text17[]="Сыграть снова";
        char text11[]="Время";
        textTexture = getTextTexture1(renderer, text11, my_font);
        drawText(renderer, textTexture,11);
        char text13[]="Рекорд";
        textTexture = getTextTexture1(renderer, text13, my_font);
        drawText(renderer, textTexture,13);
        char text14[1000];
        _itoa_s(set[selected][2],text14,10);
        textTexture = getTextTexture1(renderer, text14, my_font);
        drawText(renderer, textTexture,14);
        char text15[]="Жизни";
        textTexture = getTextTexture1(renderer, text15, my_font);
        drawText(renderer, textTexture,15);
        while (!quit && !exit)
        {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){quit = true;exit=true;mainexit=true;drex=true;choise=true;}
            char text12[1000];
            int tectime=time(NULL);
            int yourtime=tectime-start_time;
            _itoa_s(yourtime,text12,10);
            textTexture = getTextTexture1(renderer, text12, my_font);
            drawText(renderer, textTexture,12);
            char text16[10];
            int lives=LIFE_COUNT-loc_life;
            _itoa_s(lives,text16,10);
            textTexture = getTextTexture1(renderer, text16, my_font);
            drawText(renderer, textTexture,16);
            switch (event.type)
            
            {
            case SDL_MOUSEBUTTONDOWN:// Проверка, какая клеточка выделена
                if(event.button.button == SDL_BUTTON_LEFT)//Флажок
                    {
                    for (int i = 0; i < KLET_COUNT; i++)
                    {
                        if (isBallHit(rect_klet[i], event.button.x, event.button.y))
                        {
                            if(kletka[i].tap==0 && kletka[i].sost!=1)
                            {
                                //СОЗДАНИЕ КАРТИНКИ ФЛАЖКА
                                kletka[i].tap=1;
                                draw_flags(renderer,rect_klet,KLET_COUNT,flagTexture,kletka,theme);
                                 if(set[selected][1]==1)sound_flag();
                            }
                            else
                            {
                                if(kletka[i].tap==1 && kletka[i].sost!=1)
                                {
                                    //УДАЛЕНИЕ КАРТИНКИ ФЛАЖКA
                                    kletka[i].tap=0;
                                    draw_flags(renderer,rect_klet,KLET_COUNT,flagTexture,kletka,theme);
                                     if(set[selected][1]==1)sound_flag();
                                }
                            }
                        }
                    }
                    }   
                if(event.button.button == SDL_BUTTON_RIGHT)//Лопата
                    {
                    for (int i = 0; i < KLET_COUNT; i++)
                    {
                        if (isBallHit(rect_klet[i], event.button.x, event.button.y))
                        {
                            if (first==0)// Открытие первой клетки. Создание списка мин
                            {
                                Min_Num(MinNum,i);
                                // Для тестирования следует открыть. Выводит в консоль номера клеток с минами.
                                // for(int k=0;k<MIN_COUNT;k++)
                                // {
                                // cout << MinNum[k]<< "   ";
                                // }
                                // cout<<"\n";
                                //ПОЛЕ 5x5 ВЫГЛЯДИТ ТАК
                                // 0  1  2  3  4
                                // 5  6  7  8  9
                                // 10 11 12 13 14
                                // 15 16 17 18 19
                                // 20 21 22 23 24
                                if(set[selected][1]==1)sound_open_klet();
                                first=1;
                            }
                            bool fl=true;
                            for (int l=0;l<MIN_COUNT;l++)
                            {
                                if (i==MinNum[l])//Здесь мина!!!
                                    {
                                     if(set[selected][1]==1)sound_min_open();
                                    loc_life+=1;
                                    kletka[i].min=true;
                                    }
                            }
                            if(loc_life==LIFE_COUNT ||clear_klet==open_klet )
                            {// вывод результатов и выход из игры
                                if(clear_klet==open_klet){text_on_klet(renderer,rect_klet,my_font,MinNum,i,theme); int rec=time(0)-start_time;
                                    if(set[0][2]>rec){set[0][2]=rec;}vict=1;}
                                if(loc_life==LIFE_COUNT){kletka[i].sost=1;draw_mins(renderer,rect_klet,KLET_COUNT,flagTexture,kletka,MinNum,theme);vict=0;}
                                fl=false;
                            }
                            if (fl)
                            {    if(set[selected][1]==1)sound_open_klet();
                                kletka[i].sost=1;
                                if(!kletka[i].min){text_on_klet(renderer,rect_klet,my_font,MinNum,i,theme);open_klet++;}
                                else{draw_mins(renderer,rect_klet,KLET_COUNT,flagTexture,kletka,MinNum,theme);}
                            }
                            else{Sleep(1000); quit=true;}
                        }
                    }
                    }
                exportToFile(set);
                break;
                 
            }
        }
        for (int i=0;i<KLET_COUNT;i++){rect_klet[i].x=kletka[i].x;rect_klet[i].y=kletka[i].y;rect_klet[i].w=kletka[i].w;rect_klet[i].h=kletka[i].h;}
        risuem_kletochki(renderer,theme);
        SDL_RenderPresent(renderer);
    }
        SDL_RenderClear(renderer);
        SDL_Event choiseevent;
        SDL_SetRenderDrawColor(renderer, 229, 195, 209, 0);
        SDL_RenderClear(renderer);
        while (!choise && !drex)
        { 
            while (SDL_PollEvent(&choiseevent))
            {
                if (choiseevent.type == SDL_QUIT){choise = true;mainexit=true;}
                textTexture = getTextTexture1(renderer, text17, my_font);
                drawText(renderer, textTexture,17);
                if (vict==0){textTexture = getTextTexture1(renderer, text19, my_font); if(set[selected][1]==1)sound_lose();}
                else{textTexture = getTextTexture1(renderer, text18, my_font); if(set[selected][1]==1)sound_win();}
                drawText(renderer, textTexture,18);
                if(choiseevent.type== SDL_MOUSEBUTTONDOWN && choiseevent.button.button == SDL_BUTTON_LEFT)
                {
                    if( isBallHit(rect17,choiseevent.button.x,choiseevent.button.y)){SDL_RenderClear(renderer);mainexit=false;choise=true;drex=true;}
                }
            }
            SDL_RenderPresent(renderer);
        }
    }

    TTF_CloseFont(my_font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    // SDL_DestroyTexture(textTexture);
    SDL_Quit();
    return 0;
    }
