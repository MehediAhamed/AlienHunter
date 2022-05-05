//Created By Mehedi Ahamed


#include<iostream>
#include<conio.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define Aliens_DIF 45

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int AliensY[3];
int AliensX[3];
int AliensFlag[3];

//shape of ship
char Ship[3][5] = { ' ',' ',4,' ',' ',
					'[',']',4,'[',']',
					'=',4,4,4,'=' };
int ShipPos = WIN_WIDTH/2;
int scoreAH = 0;
int bullets[22][4];
int bulletsLife[20];
int bIndex = 0;

//cursor shift

void gotoxy(int x, int y);
void setcursor(bool visible, DWORD size);
void drawBorderAH();
void genAliens(int ind);
void drawAliens(int ind);
void eraseAliens(int ind);
void resetAliens(int ind);
void genBullet();
void moveBullet();
void drawBullets();
void eraseBullets();
void eraseBullet(int i);

void drawShip();
void eraseShip();

int bulletHit();
void gameoverAH();
void updateScoreAH();
void instructionsAH();

void playAH();
int serialAH(int x, FILE *fp);

int deserialAH(int x,FILE *fp);




int main()
{
	setcursor(0,0);
	srand( (unsigned)time(NULL));

	do{
		system("cls");
		system("color 1E");
		gotoxy(43,9); cout<<" --------------------- ";
		gotoxy(43,10); cout<<" |    ALIEN HUNTER   |     ";
		gotoxy(43,11); cout<<" ---------------------";
		 gotoxy(45, 13);
        cout << "1. START GAME";
        gotoxy(45, 15);
        cout << "2. INSTRUCTIONS";
        gotoxy(45, 17);
        cout << "3. QUIT";
        gotoxy(45, 19);
        cout << "Select an Option- ";
		char op = getch();

		if( op=='1')
        {
             Beep(1459,105);
           playAH();
        }
		else if( op=='2')
        {
             Beep(1459,105);
          instructionsAH();
        }

		else if( op=='3')
            {
            system("cls");
            system("color 1");

            Beep(1459,105);
            exit(0);
        }



	}while(1);

	return 0;
}

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

// set bool visible = 0(invisible), bool visible = 1(visible)

void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}


void drawBorderAH(){


	//for(int i=22; i<=SCREEN_WIDTH; i++){
		//gotoxy(i,0);
		//printf("%c",193);

	//}

	for(int i=22; i<=SCREEN_WIDTH; i++){
		gotoxy(i,SCREEN_HEIGHT+2);
		printf("%c",193);

	}

	for(int i=2; i<=SCREEN_HEIGHT+1; i++){
		gotoxy(22,i);
		printf("%c",208);

		gotoxy(SCREEN_WIDTH,i);
		printf("%c",208);

	}
	for(int i=2; i<=SCREEN_HEIGHT+1; i++){
		gotoxy(WIN_WIDTH,i);

		printf("%c",208);
	}
}


//generate alien
void genAliens(int ind){
	AliensX[ind] = 23 + rand()%(44);
}

//Alien Shape
void drawAliens(int ind){
	if( AliensFlag[ind] == true ){
		gotoxy(AliensX[ind], AliensY[ind]+1);
        cout<<"---";
		gotoxy(AliensX[ind], AliensY[ind]+2);
		printf("%c%c%c",92,32,47);

		gotoxy(AliensX[ind], AliensY[ind]+3);
		printf("%c%c%c",234,232,234);

		gotoxy(AliensX[ind], AliensY[ind]+4);
		printf(" %c",157);

	}
}
//vanish Alien
void eraseAliens(int ind){
	if( AliensFlag[ind] == true ){
		gotoxy(AliensX[ind], AliensY[ind]+1);
		cout<<"    ";
		gotoxy(AliensX[ind], AliensY[ind]+2);
		cout<<"    ";
		gotoxy(AliensX[ind], AliensY[ind]+3);
		cout<<"    ";
		gotoxy(AliensX[ind], AliensY[ind]+4);
		cout<<"    ";
	}
}
void resetAliens(int ind){
	eraseAliens(ind);
	AliensY[ind] = 4;
	genAliens(ind);

}


void genBullet(){
	bullets[bIndex][0] = 25;  //windows height minus ship height
	bullets[bIndex][1] = ShipPos;
	bullets[bIndex][2] = 25;
	bullets[bIndex][3] = ShipPos+4;
	bIndex++;
	if( bIndex == 10)  //windows height minus ship height
		bIndex = 0;
}
void moveBullet(){
	for(int i=0; i<20; i++){
		if( bullets[i][0] > 2 )
			bullets[i][0]--;
		else
			bullets[i][0] = 0;

		if( bullets[i][2] > 2 )
			bullets[i][2]--;
		else
			bullets[i][2] = 0;
	}
}
void drawBullets(){
	for(int i=0; i<20; i++){
		if( bullets[i][0] > 1){
			gotoxy(bullets[i][1],bullets[i][0]); cout<<"^";
			gotoxy(bullets[i][3],bullets[i][2]); cout<<"^";
		}
	}
}
void eraseBullets(){
	for(int i=0; i<20; i++){
		if( bullets[i][0] >= 1 ){
			gotoxy(bullets[i][1],bullets[i][0]); cout<<" ";
			gotoxy(bullets[i][3],bullets[i][2]); cout<<" ";
		}
	}
}
void eraseBullet(int i){
	gotoxy(bullets[i][1],bullets[i][0]); cout<<" ";
	gotoxy(bullets[i][3],bullets[i][2]); cout<<" ";
}
void drawShip(){
	for(int i=0; i<3; i++){
		for(int j=0; j<5; j++){
			gotoxy(j+ShipPos, i+25); cout<<Ship[i][j];
		}
	}
}
void eraseShip(){
	for(int i=0; i<3; i++){
		for(int j=0; j<5; j++){
			gotoxy(j+ShipPos, i+25); cout<<" ";
		}
	}
}

int collision(){
	if( AliensY[0]+2 >= 21 ){
		if( AliensX[0] + 2 - ShipPos >= 0 && AliensX[0] + 2 - ShipPos <=13  ){
			return 1;
		}
	}
	return 0;
}
int bulletHit(){
	for(int i=0; i<20; i++){
		for(int j=0; j<4; j+=2){
			if( bullets[i][j] != 0 ){
				if( bullets[i][j] >= AliensY[0] && bullets[i][j] <= AliensY[0]+4 ){
					if( bullets[i][j+1] >= AliensX[0] && bullets[i][j+1] <= AliensX[0]+4 ){
						eraseBullet(i);
						bullets[i][j] = 0;
						resetAliens(0);
						return 1;
					}
				}
				if( bullets[i][j] >= AliensY[1] && bullets[i][j] <= AliensY[1]+4 ){
					if( bullets[i][j+1] >= AliensX[1] && bullets[i][j+1] <= AliensX[1]+4 ){
						eraseBullet(i);
						resetAliens(1);
						bullets[i][j] = 0;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
void gameoverAH(){

    Beep(6059,80);

    system("cls");
    system("color 4F");
    char ch;
	cout<<endl;
	 cout << endl;
    gotoxy(44, 10);
    cout << "---->>>> Game Over <<<<----" << endl;
    gotoxy(44, 11);
    cout << "___________________________" ;

	FILE *fp=fopen("hunter.txt","r");
	int hs=deserialAH(scoreAH,fp);

	gotoxy(45,14);
	cout<<"Your score :"<<scoreAH<<endl;
	gotoxy(45,15);
	cout<<"High score :"<<hs<<endl;
	gotoxy(45,18);
	cout << "Retry?(y/n) = ";                      //if wannna playAH agian
    cin >> ch;
    ch=tolower(ch);
    if(ch=='y')
    {
        playAH();

    }

    else
        exit(0);
	getch();
}
void updateScoreAHAH(){
	gotoxy(WIN_WIDTH+5, 10);
	cout<<"score: "<<scoreAH<<endl;

     Beep(700,80);

     FILE *fp=fopen("hunter.txt","a+");
         serialAH(scoreAH,fp);


}
void instructionsAH(){

	system("cls");
    gotoxy(43,9);
	system("color 27");
	cout<<"INSTRUCTION";
	gotoxy(41,10);
	cout<<"----------------";
	gotoxy(41,12);
	cout<<"1. Shoot aliens by tapping space bar ";
	gotoxy(41,13);
	cout<<"2. Press '<-' to move left";
	gotoxy(41,14);
	cout<<"3. Press '->' to move right";
	gotoxy(41,15);
	cout<<"4. Press 'escape' to exit";
	gotoxy(41,17);
	cout<<"Press any key to go back to menu";
	getch();
}


void playAH(){

    system("cls");
    system("color 6");

	ShipPos = 10 + WIN_WIDTH/2;
	scoreAH = 0;
	AliensFlag[0] = 1;
	AliensFlag[1] = 1;
	AliensY[0] = AliensY[1] = 1;

	for(int i=0; i<20; i++){
		bullets[i][0] = bullets[i][1] = 0;
	}

	system("cls");
	drawBorderAH();

	updateScoreAHAH();
	genAliens(0);
	genAliens(1);
	genAliens(2);

	gotoxy(WIN_WIDTH + 5, 13);cout<<"Control ";
	gotoxy(WIN_WIDTH + 5, 14);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 5, 15);cout<<"<- Key - Left";
	gotoxy(WIN_WIDTH + 5, 16);cout<<"-> Key - Right";

	gotoxy(36, 13);cout<<"Press any key to start";
	getch();
	gotoxy(36, 13);cout<<"                      ";

	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch==75 ){
				if( ShipPos > 26 )
					ShipPos -= 5;
			}
			if( ch==77){
				if( ShipPos <62 )
					ShipPos += 5;
			}
			if(ch==32){
				genBullet();
				//drawBullets();

			}
			if(ch==27){
				break;
			}
		}

		drawShip();
		drawAliens(0);
		drawAliens(1);
		drawAliens(2);
		drawBullets();
		if( collision() == 1  ){
			gameoverAH();
			return;
		}
		if(  bulletHit() == 1 ){
			scoreAH++;
			updateScoreAHAH();
		}
		Sleep(108);

		eraseShip();
		eraseAliens(0);
		eraseAliens(1);

		eraseBullets();
		moveBullet();

		if( AliensFlag[0] == 1 )
			AliensY[0] += 1;

		if( AliensFlag[1] == 1 )
			AliensY[1] += 1;

		if( AliensY[0] > SCREEN_HEIGHT-4 ){
			resetAliens(0);
		}
		if( AliensY[1] > SCREEN_HEIGHT-4 ){
			resetAliens(1);
		}
	}
}


int serialAH(int x, FILE *fp)
{
    fp=fopen("hunter.txt","a+");
    fprintf(fp,"%d ",x);
    fclose(fp);

}
//show data
int deserialAH(int x,FILE *fp)
{
    int i=0;
    int num[100];
    char ch;

    fp=fopen("hunter.txt","r");


    while(!feof(fp))
    {
         fscanf(fp,"%d ",&num[i]);

         i++;

    }
    remove("hunter.txt");
    fclose(fp);



   for(int k=0;k<i-1;k++)
    {

        for(int j=0;j<i-k-1;j++)
        {

            if(num[j+1]>num[j])
            {
                int temp=num[j];
                num[j]=num[j+1];
                num[j+1]=temp;
            }
        }
    }

   FILE *fp1=fopen("hunter.txt","w");
   for(int k=0;k<i;k++)
   {
        fprintf(fp1,"%d ",num[k]);
   }



    fclose(fp1);
    return num[0];
}

