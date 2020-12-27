# include "iGraphics2.h"

int i, j, im, jm; //loop index
int point1_row, point1_col, point2_row, point2_col; //conncting line indicators
int mat[6][7], prev_mat[6][7]; //one single element differs which is to be filled with the falling ball animation
double  circles_x[6][7], circles_y[6][7]; //two 2D arrays for x & y co-ordintes of circles
int arrow_j = 0; //arow position indicator ( 0 to 6 )
int dy = 550; //height for ball in animation with initial value
double arrow_x, ar_x[7]; //arrow position x-axis value -> arrow_x . to draw the hollow arrow -> ar_x
double ar1_x[4], ar2_x[3]; //to draw the arrow FILLED -> 1 rectangle (ar1) + 1 triangle (ar2)
int height[7] = {0,0,0,0,0,0,0}; //how many balls are already inserted in the columns
int endGame = 0; //game ending flag

int turn = 0; //turn 0 means 1st player's turn, 1 means 2nd
int k;
int window=1; //window denotes which window to draw
int sound = 1, prev_sound = 0; //  sound = 1, play music & sound = 0, stop music
int anime = 0; //anime determines if there is an animation running
/* window 1: Main menu(includes play, sound/music, how to  play, exit)
                2: Game play,
                3: how to play,  */

void playmusic1()
{
    /*
        if prev_sound and sound holds the same value, no change needed
        when sound changes to 1 -> play music and then make prev_sound 1
        when sound changes to 0 -> stop music and then make prev_sound 0
        change the music when game ends
    */
    if(prev_sound == 0 && sound == 1 && endGame==0) PlaySound("Winter_Wonder.wav", NULL, SND_ASYNC | SND_LOOP);
    if(prev_sound == 0 && sound == 1 && endGame) PlaySound("Busy_Bee.wav", NULL, SND_ASYNC | SND_LOOP);
    if(prev_sound == 1 && sound == 0) PlaySound(NULL, 0,0); //stop music
}

texture mytexture, starttexture, bricks, gmover1, gmover2, gmover3, wood;
void iTextureInit()
{
    mytexture.Create("back2.bmp");
    starttexture.Create("mainMenuback.bmp");
    bricks.Create("bricks.bmp");
    gmover1.Create("GameOver1.bmp");
    gmover2.Create("GameOver2.bmp");
    gmover3.Create("GameOver3.bmp");
    wood.Create("blue.bmp");
    /*
    back2.bmp - PLAY Window background
    bricks.bmp - how to play window
    mainMenuback.bmp - main menu background
    GameOver1.bmp - player 1 wins message
    GameOver2.bmp - player 2 wins message
    GameOver3.bmp - Match draw message
    blue.bmp (texture name - wood) - wall of play window alternavite to the boxes
    */
}


void iDraw()
{
    iClear();

    playmusic1();
    prev_sound=sound;
    /*though the function is called again and again
    its conditions inside allow it to change music when needed*/

    //MAIN MENU WINDOW
    if(window==1)
    {
        //place code for the Main Menu window;
        drawTexture(0,0,starttexture); //background

        //design buttons in MAIN MENU

        //PLAY BUTTON
        iSetColor(255,0,0);
        iFilledRectangle(280,395,140,50); //outer box
        iSetColor(0,255,0);
        iFilledRectangle(285,400,130,40); //inner box

        iSetColor(255,255,255);
        iText(325,413, "PLAY", GLUT_BITMAP_HELVETICA_18);

        //SOUND BUTTON
        iSetColor(255,0,0);
        iFilledRectangle(280,295,140,50); //outer box
        iSetColor(0,255,0);
        iFilledRectangle(285,300,130,40); //inner box

        iSetColor(255,255,255);
        if(sound) iText(298,313, "MUSIC : ON", GLUT_BITMAP_HELVETICA_18);
        else iText(294,313, "MUSIC : OFF", GLUT_BITMAP_HELVETICA_18);

        //HOW TO PLAY BUTTON
        iSetColor(255,0,0);
        iFilledRectangle(280,195,140,50); //outer box
        iSetColor(0,255,0);
        iFilledRectangle(285,200,130,40); //inner box

        iSetColor(255,255,255);
        iText(285,213, "HOW TO PLAY", GLUT_BITMAP_HELVETICA_18);

        //exit BUTTON
        iSetColor(255,0,0);
        iFilledRectangle(280,95,140,50); //outer box
        iSetColor(0,255,0);
        iFilledRectangle(285,100,130,40); //inner box

        iSetColor(255,255,255);
        iText(298,113, "QUIT GAME", GLUT_BITMAP_HELVETICA_18);
    }

    //GAME WINDOW
    if(window==2)
    {
        drawTexture(0,0,mytexture); //background

        //draw black circles
        iSetColor(0, 0, 0);
        for(i=0; i<6; i++)
        {
            for(j=0; j<7; j++)
            {
                circles_x[i][j] = 140 + j * 70;
                circles_y[i][j] = 140 + i * 70;
            }
        }
        for(i=0; i<6; i++)
        {
            for(j=0; j<7; j++)
            {
                iFilledCircle(circles_x[i][j], circles_y[i][j], 30);
            }
        }

        //put ball
        for(im=0; im<6; im++)
        {
            for(jm=0; jm<7; jm++)
            {
                if(mat[im][jm]==1)
                {
                    //green ball
                    iSetColor(20,200,20);
                    if(!prev_mat[im][jm]){
                        //latest changed element
                        anime = 1; //started falling ball animation
                        iFilledCircle(circles_x[im][jm], dy, 30);
                        dy--;
                        if(dy <=  circles_y[im][jm]){
                            prev_mat[im][jm] = 1;
                            dy = 550;
                            anime = 0; //stop falling ball animation
                        }
                    }
                    else iFilledCircle(circles_x[im][jm], circles_y[im][jm], 30);
                }
                if(mat[im][jm]==2)
                {
                    //white ball
                    iSetColor(200,200,200);
                    if(!prev_mat[im][jm]){
                        //latest changed element
                        anime = 1; //started falling ball animation
                        iFilledCircle(circles_x[im][jm], dy, 30);
                        dy--;
                        if(dy <=  circles_y[im][jm]){
                            prev_mat[im][jm] = 2;
                            dy = 550;
                            anime = 0; //stop falling ball animation
                        }
                    }
                    else iFilledCircle(circles_x[im][jm], circles_y[im][jm], 30); //direct draw unchanged elements
                }
            }
        }

        //who's turn it is
        if(!endGame)
        {
            iSetColor(100, 20, 200);
            iCircle(50, 315, 40, 4); //diamond shaped player indicator - player 1

            //turn 0 means 1st player's turn, 1 means 2nd
            if(!turn)
            {
                iSetColor(10, 255, 10);
                iFilledCircle(51, 315, 38, 4);
            }
            iSetColor(255,255,255);
            iText(45,305, "1", GLUT_BITMAP_TIMES_ROMAN_24);

            iSetColor(100, 20, 200);
            iCircle(650, 315, 40, 4); //diamond shaped player indicator - player 2
            if(turn)
            {
                iSetColor(255,255,255);
                iFilledCircle(651, 315, 38, 4);
            }
            iSetColor(10, 255, 10);
            iText(645,305, "2", GLUT_BITMAP_TIMES_ROMAN_24);
        }

        //MAIN MENU BUTTON
        iSetColor(255,0,0);
        iFilledRectangle(500,20,155,50); //outer box
        iSetColor(0,100,200);
        iFilledRectangle(505,25,145,40); //inner box

        iSetColor(255,255,255);
        iText(525,40, "MAIN MENU", GLUT_BITMAP_HELVETICA_18);

        //RESTART BUTTON
        iSetColor(255,0,0);
        iFilledRectangle(45,20,155,50); //outer box
        iSetColor(0,100,200);
        iFilledRectangle(50,25,145,40); //inner box

        iSetColor(255,255,255);
        iText(75,40, " RESTART ", GLUT_BITMAP_HELVETICA_18);

        //texture show
        drawTexture(94,95,wood); //box with holes

        //draw the arrow
        arrow_x = 140 + arrow_j * 70; //arrow_x is the x co-ordinate of the center of the indicator

        ar1_x[0] = arrow_x-20;
        ar1_x[1] = arrow_x+20;
        ar1_x[2] = arrow_x+20;
        ar1_x[3] = arrow_x-20;

        ar2_x[0] = arrow_x+35;
        ar2_x[1] = arrow_x;
        ar2_x[2] = arrow_x-35;

        ar_x[0] = arrow_x-20;
        ar_x[1] = arrow_x+20;
        ar_x[2] = arrow_x+20;
        ar_x[3] = arrow_x+35;
        ar_x[4] = arrow_x;
        ar_x[5] = arrow_x-35;
        ar_x[6] = arrow_x-20;

        //y axis values of the arrow remains same for all positions as follows
        double ar1_y[] = {595, 595, 560, 560}, ar2_y[] = {560, 525, 560};
        double ar_y[] = {595, 595, 560, 560, 525, 560, 560};

        iSetColor(255, 0, 0);
        iFilledPolygon(ar1_x, ar1_y, 4);
        iFilledPolygon(ar2_x, ar2_y, 3);

        iSetColor(255, 255, 255);
        iPolygon(ar_x, ar_y, 7);

        //endgame actions
        if(endGame==1 && !anime)
        {
            //player 1 wins
            drawTexture(105,530,gmover1);
        }
        if(endGame==2 && !anime)
        {
            //player 2 wins
            drawTexture(105,530,gmover2);
        }
        if(endGame==3 && !anime)
        {
            //match draw
            drawTexture(105,530,gmover3);
        }

        if(endGame==1 || endGame==2)
        {
            //draw the connecting line if anyone wins
            iSetColor(200, 20, 20);

            if(!anime){
                    //if anime = 0 (after stopping the falling ball animation)
                    iLine(circles_x[point1_row][point1_col], circles_y[point1_row][point1_col], circles_x[point2_row][point2_col], circles_y[point2_row][point2_col]);
            }
        }

    }

    //HOW TO PLAY
    if(window==3)
    {
        drawTexture(0,0,bricks); //background containing the instructions
        //RETURN TO MAIN MENU OPTION
        iSetColor(255,0,0);
        iFilledRectangle(200,50,265,50); //outer box
        iSetColor(0,255,0);
        iFilledRectangle(205,55,255,40); //inner box

        iSetColor(255,255,255);
        iText(225,70, "RETURN TO MAIN MENU", GLUT_BITMAP_HELVETICA_18);
    }

}

    /*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n",mx,my);
}

    /*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //FOR PRESSING A BUTTON IN MAIN MENU WINDOW
        if(window==1)
        {
            if(mx>285 && mx<415 && my>400 && my<440) window = 2; //PLAY - game starts
            if(mx>285 && mx<415 && my>300 && my<340)
            {
                //music on-off
                prev_sound = sound;
                sound = (!sound);
            }
            if(mx>285 && mx<415 && my>200 && my<240) window = 3; // shpw HOW TO PLAY
            if(mx>285 && mx<415 && my>100 && my<140) exit(1);
        }
        //returning to main menu from how to play
        if(window==3)
        {
            if(mx>205 && mx<460 && my>55 && my<95) window = 1;
        }
        //game window options
        if(window==2)
        {
            //return to main menu
            if(mx>505 && mx<650 && my>25 && my<65)
            {
                //reset some values to clear the session before returning to main menu
                prev_sound = 0;
                arrow_j = 0;
                for(i=0; i<7; i++) height[i] = 0;
                for(i=0; i<6; i++)
                {
                    for(j=0; j<7; j++)
                    {
                        mat[i][j] = 0;
                        prev_mat[i][j] = 0;
                    }
                }
                endGame = 0;
                turn = 0;
                window = 1;
            }
            //restart
            if(mx>50 && mx<195 && my>25 && my<65)
            {
                //reset some values to restart
                prev_sound = 0;
                arrow_j = 0;
                for(i=0; i<7; i++) height[i] = 0;
                for(i=0; i<6; i++)
                {
                    for(j=0; j<7; j++)
                    {
                        mat[i][j] = 0;
                        prev_mat[i][j] = 0;
                    }
                }
                endGame = 0;
                turn = 0;
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //no task
    }
}

    /*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
    if(!endGame)
    {
        //put balls only if the game is not terminated yet
        if(key == '\r' && height[arrow_j]<6 && !anime)
        {
            if(!turn)
            {
                mat[height[arrow_j]][arrow_j] = 1; //player 1's ball
            }
            else
            {
                mat[height[arrow_j]][arrow_j] = 2; //player 2's ball
            }
            turn = !turn; //turn changes
            height[arrow_j]++; //height of the column increases
        }
    }

    int nonzero_count = 0;
    for(i=0; i<6 && (!endGame); i++)
    {
        for(j=0; j<7; j++)
        {
            //now check for 1st player
            if(mat[i][j]==1 && turn)
            {
                //right check
                for(k=1; k<4 && (j+k)<7; k++)
                {
                    if(mat[i][j+k] != 1) break;
                }
                if(k==4)
                {
                    point1_row = i;
                    point1_col = j;
                    point2_row = i;
                    point2_col = j+k-1;

                    endGame = 1;
                    break;
                }

                //down check
                for(k=1; k<4 && (i-k)>=0; k++)
                {
                    if(mat[i-k][j] != 1) break;
                }
                if(k==4)
                {
                    point1_row = i;
                    point1_col = j;
                    point2_row = i-k+1;
                    point2_col = j;

                    endGame = 1;
                    break;
                }

                //down right check
                for(k=1; k<4 && (i-k)>=0 && (j+k)<7; k++)
                {
                    if(mat[i-k][j+k] != 1) break;
                }
                if(k==4)
                {
                    point1_row = i;
                    point1_col = j;
                    point2_row = i-k+1;
                    point2_col = j+k-1;

                    endGame = 1;
                    break;
                }

                //down left check
                for(k=1; k<4 && (i-k)>=0 && (j-k)>=0; k++)
                {
                    if(mat[i-k][j-k] != 1) break;
                }
                if(k==4)
                {
                    point1_row = i;
                    point1_col = j;
                    point2_row = i-k+1;
                    point2_col = j-k+1;

                    endGame = 1;
                    break;
                }
            }

            //now check for the 2nd player
            if(mat[i][j]==2 && !turn)
            {
                //right check
                for(k=1; k<4 && (j+k)<7; k++)
                {
                    if(mat[i][j+k] != 2) break;
                }
                if(k==4)
                {
                    point1_row = i;
                    point1_col = j;
                    point2_row = i;
                    point2_col = j+k-1;

                    endGame = 2;
                    break;
                }

                //down check
                for(k=1; k<4 && (i-k)>=0; k++)
                {
                    if(mat[i-k][j] != 2) break;
                }
                if(k==4)
                {
                    point1_row = i;
                    point1_col = j;
                    point2_row = i-k+1;
                    point2_col = j;

                    endGame = 2;
                    break;
                }

                //down right check
                for(k=1; k<4 && (i-k)>=0 && (j+k)<7; k++)
                {
                    if(mat[i-k][j+k] != 2) break;
                }
                if(k==4)
                {
                    point1_row = i;
                    point1_col = j;
                    point2_row = i-k+1;
                    point2_col = j+k-1;

                    endGame = 2;
                    break;
                }

                //down left check
                for(k=1; k<4 && (i-k)>=0 && (j-k)>=0; k++)
                {
                    if(mat[i-k][j-k] != 2) break;
                }
                if(k==4)
                {
                    point1_row = i;
                    point1_col = j;
                    point2_row = i-k+1;
                    point2_col = j-k+1;

                    endGame = 2;
                    break;
                }
            }
            if(mat[i][j]) nonzero_count++;
        }
    }
    if(nonzero_count==42) endGame = 3; //all holes filled but no one won - DRAW
    if(endGame) prev_sound = 0; //make prev_sound zero to play termination music
}

    /*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{

    if (key == GLUT_KEY_END)
    {
        exit(0);
    }
    if(!endGame)
    {
        if(key == GLUT_KEY_RIGHT)
        {
            if(arrow_j<6) arrow_j++; //arow goes right
        }
        if(key == GLUT_KEY_LEFT)
        {
            if(arrow_j>0) arrow_j--; //arrow goes left
        }
    }
}


int main()
{
    iInitialize(700, 630, "Connect Four The Game");

    int I, J;
    for(I=0; I<6; I++)
    {
        for(J=0; J<7; J++)
        {
            mat[I][J] = 0;
            prev_mat[I][J] = 0;
        }
    }
    return 0;
}
