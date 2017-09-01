//---------------------------------------------------------------------------

#include <vcl.h>
#include<stdio.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
Graphics::TBitmap*back;
bool LeftKeyDown,RightKeyDown;

int LevelData[2][400]=
{
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,
0,0,0,2,1,1,1,1,1,1,1,1,1,1,1,1,2,0,0,0,
0,0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,0,
0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,
3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,
0,3,1,1,1,1,1,2,2,2,2,2,2,1,1,1,1,1,3,0,
0,0,3,1,1,1,1,2,2,2,2,2,2,1,1,1,1,3,0,0,
0,0,0,3,1,1,1,1,1,1,1,1,1,1,1,1,3,0,0,0,
0,0,0,0,3,1,1,1,1,1,1,1,1,1,1,3,0,0,0,0,
0,0,0,0,0,3,1,1,1,1,1,1,1,1,3,0,0,0,0,0,
0,0,0,0,0,0,3,1,1,1,1,1,1,3,0,0,0,0,0,0,
0,0,0,0,0,0,0,3,1,1,1,1,3,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,3,1,1,3,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

};



//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

randomize();
for(int j=0;j<20;j++)
        for(int i=0;i<20;i++)
        {
        Level[i][j]=0;
        }

LeftKeyDown=false;
RightKeyDown=false;
PositionBall();
CurrentLevel=1;
}
//---------------------------------------------------------------------------
void TForm1::LoadBlockPicture()
{
Graphics::TBitmap*b=new Graphics::TBitmap();
Block[0]=NULL;
b->LoadFromFile("препятствия.bmp");
for(int i=1;i<5;i++)
        {
        Block[i]=new Graphics::TBitmap();
        Block[i]->Width=25;
        Block[i]->Height=15;
        Block[i]->Canvas->CopyRect(Rect(0,0,25,15),
                                   b->Canvas,
                                   Rect(0,(i-1)*15,25,(i-1)*15+15));
        }
b->Free();
}

void TForm1::CheckBorders()
{
if(BallX<0)
        {
        if(BallSpeedX<=0)BallSpeedX*=-1;
        }else
if(BallX>(dx-9))
        {
        if(BallSpeedX>0)BallSpeedX*=-1;
        }else
if(BallY<0)
        {
        if(BallSpeedY<=0)BallSpeedY*=-1;
        }
if(BallY>dy+20)
        {
         LifesCol--;
         if(LifesCol<0)
                {
                Timer1->Enabled=false;
                ShowMessage("Игра проиграна\nПроходите все сначала");
                PositionBall();
                CurrentLevel=1;
                LoadLevel(CurrentLevel);
                LifesCol=3;
                Timer1->Enabled=true;
                }else
                {
                Timer1->Enabled=false;
                ShowMessage("Проиграна жизнь.\nКоличество оставшихся = "+IntToStr(LifesCol));
                PositionBall();
                Timer1->Enabled=true;
                }
        }

}

void TForm1::Draw(int x,int y,int type)
        {
         if(type!=0)
         back->Canvas->Draw(x,y,Block[type]);
        }

void TForm1::LoadLevel(int LevelNumber)
{
for(int j=0;j<20;j++)
        for(int i=0;i<20;i++)
        {
        Level[i][j]=LevelData[LevelNumber-1][j*20+i];
        }


}


void TForm1::Cls(TColor color)
{
back->Canvas->Brush->Color=color;
back->Canvas->FillRect(Rect(0,0,dx,dy));
}

void TForm1::Flip()
{
Form1->Canvas->Draw(0,0,back);
}



void TForm1::DrawLevel()
{
int tx=0;int ty=0;
back->Canvas->Draw(BallX,BallY,Ball);
for(int j=0;j<20;j++)
        {
        for(int i=0;i<20;i++,tx+=25)
        {
         Draw(tx,ty,Level[i][j]);
        }
        tx=0;
        ty+=15;
        }
back->Canvas->Draw(BitaX,380,Bita);
for(int i=0;i<LifesCol;i++)
        {
        back->Canvas->Brush->Color=clBlue;
        back->Canvas->Ellipse(10+i*10,10,20+i*10,20);
        }
}

void TForm1::CheckBita()
{
RECT Rect1=Rect(BallX,BallY,BallX+9,BallY+9);
RECT Rect2=Rect(BitaX,380,BitaX+40,390);
RECT Rect3=Rect(0,0,0,0);
if(IntersectRect(&Rect3,&Rect1,&Rect2))
        {
        if(BallY<375)BallY=371;
        int BallCenter=BallX+4;
        int BitaCenter=BitaX+20;
        int LengthOtCentra=abs(BallCenter-BitaCenter);
        float TempSpeed=LengthOtCentra*0.15;
        if(BallSpeedX>0)BallSpeedX=TempSpeed;
                        else
                        BallSpeedX=-TempSpeed;
        BallSpeedY*=-1;
        }

}

void TForm1::MoveBall()
{
BallX+=BallSpeedX;
BallY+=BallSpeedY;
CheckBorders();
CheckBita();
}


void __fastcall TForm1::FormCreate(TObject *Sender)
{
back=new Graphics::TBitmap();
back->Width=Form1->ClientWidth;
back->Height=Form1->ClientHeight;
Ball=new Graphics::TBitmap();
Ball->LoadFromFile("Ball.bmp");
Ball->Transparent=true;
Bita=new Graphics::TBitmap();
Bita->LoadFromFile("Бита.bmp");
Bita->Transparent=true;
dx=Form1->ClientWidth;
dy=Form1->ClientHeight;
LoadBlockPicture();
LoadLevel(CurrentLevel);
LifesCol=3;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
Cls(clSilver);
DrawLevel();
Flip();
MoveBall();
TestBlock();
if(CheckFinish())
        {
        Timer1->Enabled=false;
        ShowMessage("Уровень пройден");
        CurrentLevel++;
        if(CurrentLevel>MAX_LEVEL)
                {
                ShowMessage("Поздравляем,\nВы прошли игру!!!!!!");
                return;
                }
        LoadLevel(CurrentLevel);
        PositionBall();
        Timer1->Enabled=true;
        }
if(LeftKeyDown)BitaX+=-5;
if(RightKeyDown)BitaX+=5;
if(BitaX<0)BitaX=0;
if(BitaX>460)BitaX=460;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key==VK_RIGHT){RightKeyDown=false;}
if(Key==VK_LEFT){LeftKeyDown=false;}
}
//---------------------------------------------------------------------------

void TForm1::TestBlock()
{
int type;
TPoint HitedBlock=GetHitedBlock(type);
if(type!=0)
        {
        if(type==3)Level[HitedBlock.x][HitedBlock.y]=4;
        else
        Level[HitedBlock.x][HitedBlock.y]=0;
        }
}



TPoint TForm1::GetHitedBlock(int&type)
{
type=0;
int BallCenterX;
int BallCenterY;
int BlockCenterX;
int BlockCenterY;
bool popal=false;
int tx=0;int ty=0;
for(int j=0;j<20;j++)
        {
        for(int i=0;i<20;i++,tx+=25)
        {
        popal=false;
         if(Level[i][j]!=0)
                {
                        RECT Rect1=Rect(BallX,BallY,BallX+9,BallY+9);
                        RECT Rect2=Rect(tx,ty,tx+25,ty+15);
                        RECT Rect3=Rect(0,0,0,0);
                        if(IntersectRect(&Rect3,&Rect1,&Rect2))
                        {

                                BallCenterX=BallX+4;
                                BallCenterY=BallY+4;
                                BlockCenterX=tx+12;
                                BlockCenterY=ty+12;

                                if(BallCenterX<BlockCenterX)
                                        {
                                        if(abs(((BallX+9)-tx))<5)
                                                {
                                                popal=true;
                                                BallSpeedX=abs(BallSpeedX);
                                                BallSpeedX*=-1;
                                                }
                                        }

                                if(BallCenterX>BlockCenterX)
                                        {
                                        if(abs(BallX-(tx+25))<5)
                                                {
                                                popal=true;
                                                BallSpeedX=abs(BallSpeedX);
                                                }
                                        }

                                if(BallCenterY<BlockCenterY)
                                        {
                                        if(abs((BallY+9)-ty)<=11)
                                                {
                                                popal=true;
                                                BallSpeedY=abs(BallSpeedY);
                                                BallSpeedY*=-1;
                                                }
                                        }

                                if(BallCenterY>BlockCenterY)
                                        {
                                        if(abs(BallY-(ty+15))<=11)
                                                {
                                                popal=true;
                                                BallSpeedY=abs(BallSpeedY);
                                                }
                                        }



                                if(popal)
                                {
                                TPoint p;
                                p.x=i;
                                p.y=j;
                                type=Level[i][j];
                                return p;
                                }

                        }
                  }
        }
        tx=0;
        ty+=15;
        }
        
        }
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key==VK_RIGHT)
{
RightKeyDown=true;
}
if(Key==VK_LEFT)
{
LeftKeyDown=true;
}        
}
//---------------------------------------------------------------------------

bool __fastcall  TForm1::CheckFinish()
{
for(int j=0;j<20;j++)
        {
        for(int i=0;i<20;i++)
        {
        if(Level[i][j]!=0)return false;
        }
        }
return true;
}

void __fastcall TForm1::PositionBall()
{
BitaX=200;
BallX=220;
BallY=371;
BallSpeedY=-3;
BallSpeedX=random(6)-3;
LeftKeyDown=false,RightKeyDown=false;
}
