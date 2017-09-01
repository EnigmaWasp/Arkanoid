//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int GameField[15][25];
Graphics::TBitmap*back;
TPoint ActiveXY;  //это кординаты падающего элемента
int FigureData[3];
int Score;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
randomize();
New();
back=new Graphics::TBitmap();
back->Width =300;
back->Height=500;
CreateNewFigure();
}
//---------------------------------------------------------------------------
TForm1::New()
{
        for(int j=0;j<25;j++)
                for(int i=0;i<15;i++)
                GameField[i][j]=-1;
Score=0;

}
TForm1::ClearScreen()
{
        back->Canvas->Brush->Color=clSilver;
        back->Canvas->FillRect(Rect(0,0,300,500));
}
TForm1::CopyToScreen()
{
        Form1->Canvas->Draw(0,0,back);
}
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
FindComplite();
ClearScreen();
DrawStaticElement();
DrawActiveFigure();
if(!MoveActive())
        {
        Timer1->Enabled=false;
        ShowMessage("Вы проиграли");
        ShowMessage("Вы набрали "+IntToStr(Score)+" очков");
        New();
        CreateNewFigure();
        Timer1->Enabled=true;
        Timer1->Interval=300;
        }
CopyToScreen();
Caption="Цвета          Очки:"+IntToStr(Score);
}
//---------------------------------------------------------------------------


TForm1::DrawActiveFigure()
{
for(int i=0;i<3;i++)
        {
        switch(FigureData[i])
                {
                case 0:back->Canvas->Brush->Color=clBlue;break;
                case 1:back->Canvas->Brush->Color=clRed;break;
                case 2:back->Canvas->Brush->Color=clYellow;break;
                case 3:back->Canvas->Brush->Color=clGreen;break;
                case 4:back->Canvas->Brush->Color=clBlack;break;
                case 5:back->Canvas->Brush->Color=clWhite;break;
                }
        back->Canvas->FillRect(Rect(ActiveXY.x*20,(ActiveXY.y+i)*20,ActiveXY.x*20+20,(ActiveXY.y+i)*20+20));
        }
}

TForm1::DrawStaticElement()     //Элементы которые упали я называю статическими
{
for(int j=0;j<25;j++)
        for(int i=0;i<15;i++)
                {
                switch(GameField[i][j])
                {
                case -1:back->Canvas->Brush->Color=clSilver;break;
                case 0:back->Canvas->Brush->Color=clBlue;break;
                case 1:back->Canvas->Brush->Color=clRed;break;
                case 2:back->Canvas->Brush->Color=clYellow;break;
                case 3:back->Canvas->Brush->Color=clGreen;break;
                case 4:back->Canvas->Brush->Color=clBlack;break;
                case 5:back->Canvas->Brush->Color=clWhite;break;
                }
                back->Canvas->FillRect(Rect(i*20,j*20,i*20+20,j*20+20));
                }
}

TForm1::ActiveToStatic()      //Активная фигура становится статической
{
for(int i=0;i<3;i++)
        {
        GameField[ActiveXY.x][ActiveXY.y+i]=FigureData[i];
        }
}

TForm1::TransformFigura()
{
       int t;
       t=FigureData[0];
       FigureData[0]=FigureData[1];
       FigureData[1]=FigureData[2];
       FigureData[2]=t;
}
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key==VK_DOWN)Timer1->Interval=50;
if(Key==VK_UP)TransformFigura();
if(Key==VK_LEFT)
        {
        ActiveXY.x--;
        if(HitTestActive())ActiveXY.x++;
        }
if(Key==VK_RIGHT)
        {
        ActiveXY.x++;
        if(HitTestActive())ActiveXY.x--;
        }
if(ActiveXY.x>14)ActiveXY.x=14;
if(ActiveXY.x<0)ActiveXY.x=0;

ClearScreen();
DrawStaticElement();
DrawActiveFigure();
CopyToScreen();
}
//---------------------------------------------------------------------------


TForm1::HitTestActive()
{
for(int k=0;k<3;k++)
       if(GameField[ActiveXY.x][ActiveXY.y+k]!=-1)return 1;

if((ActiveXY.y+2)>24)return 2;
return 0;


}

TForm1::MoveActive()
{
        ActiveXY.y++;
        if(HitTestActive())
        {
        ActiveXY.y--;
        ActiveToStatic();
        if(!CreateNewFigure())return 0;
        }
return 1;
}

TForm1::CreateNewFigure()
{
     ActiveXY=Point(5,0);
        for(int i=0;i<3;i++)
        {
        FigureData[i]=random(6);
        }
if(HitTestActive())return 0;
return 1;
}
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key==VK_DOWN)Timer1->Interval=300;
}
//---------------------------------------------------------------------------

TForm1::FindComplite()
{
int l=0;
int pos=0;
int c;
int er=0;
for(int j=24;j>=0;j--,l=0,pos=0)
        {c=GameField[0][j];
        for(int i=1;i<15;i++)
                {

                if(GameField[i][j]==c)
                        {
                        l++;
                        }else
                        {
                        if((l>=3)&&(c!=-1))
                                {
                                er=1;
                                Score+=(l*10);
                                for(int k=0;k<l+1;k++)
                                        {
                                        GameField[k+pos][j]=-1;
                                        }
                                }
                        pos=i;
                        l=0;
                        c=GameField[i][j];
                        }
                if((l>=3)&&(c!=-1))
                                {
                                er=1;
                                Score+=(l*10);
                                for(int k=0;k<l+1;k++)
                                        {
                                        GameField[k+pos][j]=-1;
                                        }
                                }

                }
        }

if(er)
{
c=0;
pos=0;
        for(int i=0;i<15;i++)
        {c=0;
                for(int j=0;j<25;j++)
                {
                if( GameField[i][j]!=-1)c=1;
                if((GameField[i][j]==-1)&&(c==1))
                        {
                        for(int k=j;k>=0;k--)
                                {
                                if(k>0)GameField[i][k]=GameField[i][k-1];
                                else   GameField[i][k]=-1;
                               // i=0;
                                }
                        }
                }
        }
}
}
void __fastcall TForm1::N1Click(TObject *Sender)
{
New();
CreateNewFigure();
}
//---------------------------------------------------------------------------

