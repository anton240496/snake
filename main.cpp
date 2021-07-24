#include <iostream>
#include <conio.h>
#include <QTimer>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x,y;
int fruitx, fruity, score;
int telx[100], tely[100];
int ntail;
enum eDirection {stop = 0, lefts, rights, up, down};
eDirection dir;

void Setup(){
    gameOver = false;
   // startover = true;
    dir = stop;
    x=width/2 -1;
   y =height/2 -1;
   srand(time(NULL));
    fruitx=rand()%width-1;
    fruity=rand()% height-1;
    score = 0;

}

void Draw(){
    Sleep(70);
  system("cls");
  //Sleep(33);

   for(int i=0;i<width+1; i++)
       cout<<"#";
   cout<< endl;

   for(int i=0; i<height; i++){
     for(int j =0; j<width; j++){
         if(j==0 || j==width-1)
             cout<< "#";
         if (i== y && j==x)
             cout<<"0";
         else if (i==fruity && j== fruitx)
             cout << "F";
         else{
             bool print = false;
             for(int k=0 ; k<ntail; k++ ){
                 if (telx[k]==j && tely[k] ==i){
                    print = true;
                     cout<<'o';
                 }

             }
             if (!print){
         cout<<" ";
             }
         }
     }
     cout <<endl;
   }

   for(int i=0;i<width+1; i++)
       cout<<"#";
   cout<< endl;
   cout << "Score: " << score << endl;
}

void Input(){
  if(_kbhit()){
      switch (_getch()) {
      case 'a':
          dir = lefts;
          break;
      case 'd':
          dir= rights;
          break;
      case 'w':
          dir= up;
          break;
      case 's':
          dir= down;
          break;
      case 'x':
          gameOver= true;
          break;

      case 'q':
                  Setup();
                  break;


      }
  }
}

void logic(){
    int prevx = telx[0];
    int prevy=tely[0];
    int prev2x, prev2y;
    telx[0]=x;
    tely[0]=y;

    for (int i=1; i<ntail; i++){
        prev2x = telx[i];
        prev2y= tely[i];
        telx[i] = prevx;
        tely[i]=prevy;
        prevx=prev2x;
        prevy= prev2y;
    }
    switch (dir) {
    case lefts:
        x--;
        break;
    case rights:
        x++;
        break;
    case up:
        y--;
        break;
    case down:
        y++;
        break;
    }

//    if (x==width || x<0 || y==height || y<0){
//        gameOver=true;

//    }
    if(x>=width-1){
        x=0;
    }else if(x<0){
        x=width-2;
    }

    if(y>=height){
        y=0;
    }else if(y<0){
        y=height-1;
    }

    for(int i=0; i<ntail; i++){
        if (telx[i]==x && tely[i]==y)
            gameOver=true;
    }

    if(x== fruitx && y==fruity){
        score +=10;
        fruitx=rand()%width;
        fruity=rand()% height;
        ntail++;
    }
}

int main()
{
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        logic();

    }
    return  0;
}
