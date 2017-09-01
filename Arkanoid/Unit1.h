//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
const MAX_LEVEL=2;


class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void Cls(TColor color);
        void Flip();
        void LoadBlockPicture();
        void LoadLevel(int LevelNumber);
        void Draw(int x,int y,int type);
        void DrawLevel();
        void CheckBorders();
        void CheckBita();
        void MoveBall();
        void TestBlock();
        TPoint GetHitedBlock(int &type);
        int Level[20][20];
        Graphics::TBitmap*Block[10];
        Graphics::TBitmap*Ball;
        Graphics::TBitmap*Bita;
        int dx,dy;
        float BallX,BallY;
        float BallSpeedX,BallSpeedY;
        int BitaX;
        int CurrentLevel;
        bool __fastcall CheckFinish();
        int LifesCol;
        void __fastcall PositionBall();
};


//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
