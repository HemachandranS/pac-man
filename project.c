#include <stdio.h> // printf()
#include <conio.h> // getch()
#include <windows.h>//sleep()

#define H 30
#define W 60
#define NR_GHOSTS 15
int gameover=1;


struct coord
{
    int x;
    int y;
};

struct PacMan
{
    struct coord position;
    int vx;
    int vy;
    int lives;
    int food_collected;
};


struct Ghost
{
    struct coord position;
    char character;
};

struct Ghost allGhosts[NR_GHOSTS];


struct PacMan myPacMan = {
    {
        .x = 1,
        .y = 1,
    },
    .vx = 0,
    .vy = 0,
    .lives=3,
    .food_collected = 0};

char playfield_1[H][W] =
{
{"####################################################"},
{"#               ###               ###              #"},
{"#   #####################   ####################   #"},
{"#                     ###   ###                    #"},
{"###################   ###   ###   ##################"},
{"#               ###               ###              #"},
{"#   #####################   ####################   #"},
{"#         ###                          ###         #"},
{"#   ###############   #########   ##############   #"},
{"#                     ###   ###                    #"},
{"#   ###############   #########   ##############   #"},
{"#         ###                          ###         #"},
{"#   #####################   ####################   #"},
{"#               ###               ###              #"},
{"###################   ###   ###   ##################"},
{"#                     ###   ###                    #"},
{"#   #####################   ####################   #"},
{"#               ###               ###              #"},
{"####################################################"}};
char playfield_2[H][W] =
{
{"#####################################################"},
{"#            ###                     ###            #"},
{"#   ###   #########   #########   #########   ###   #"},
{"#   ###         ###               ###         ###   #"},
{"#   ###   ###   #########   #########   ###   ###   #"},
{"#   ###   ###   ###               ###   ###   ###   #"},
{"#         ###   ###   #########   ###   ###         #"},
{"#   ###   ###   ###               ###   ###   ###   #"},
{"#   ###   ###   #########   #########   ###   ###   #"},
{"#   #########                           #########   #"},
{"#   ###   ###   #########   #########   ###   ###   #"},
{"#   ###   ###   ###               ###   ###   ###   #"},
{"#         ###   ###   #########   ###   ###         #"},
{"#   ###   ###   ###               ###   ###   ###   #"},
{"#   ###   ###   #########   #########   ###   ###   #"},
{"#   ###         ###               ###         ###   #"},
{"#   ###   #########   #########   #########   ###   #"},
{"#            ###                     ###            #"},
{"#####################################################"}};
char playfield_3[H][W]=
{   
{"#####################################################"},
{"#                        ###                        #"},
{"#   ###   #########   #########   #########   ###   #"},
{"#   ###         ###               ###         ###   #"},
{"#######   ###   #########   #########   ###   #######"},
{"#   ###   ###   ###               ###   ###   ###   #"},
{"#         ###   ###   #########   ###   ###         #"},
{"#   ###   ###   ###      ###      ###   ###   ###   #"},
{"#   ###   ###            ###            ###   ###   #"},
{"#   #########   #####################   #########   #"},
{"#   ###   ###            ###      ###   ###   ###   #"},
{"#   ###   ###   ###      ###      ###   ###   ###   #"},
{"#         ###   ###   #########   ###   ###         #"},
{"#   ###   ###   ###               ###   ###   ###   #"},
{"#######   ###   #########   #########   ###   #######"},
{"#   ###         ###               ###         ###   #"},
{"#   ###   #########   #########   #########   ###   #"},
{"#                        ###                        #"},
{"#####################################################"}};
char playfield_4[H][W]=
{
{"#####################################################"},
{"#         ###                           ###         #"},
{"#   #########   #########   #########   #########   #"},
{"#               ###               ###               #"},
{"#######   ###############   ###############   #######"},
{"#                     ###   ###                     #"},
{"#   ###############   ###   ###   ###############   #"},
{"#   ###                                       ###   #"},
{"#   #####################   #####################   #"},
{"#                     ###   ###                     #"},
{"#   #####################   #####################   #"},
{"#                                                   #"},
{"#   ###############   ###   ###   ###############   #"},
{"#   ###               ###   ###               ###   #"},
{"#   ###   ###############   ###############   ###   #"},
{"#               ###               ###               #"},
{"#   #########   #########   #########   #########   #"},
{"#         ###                           ###         #"},
{"#####################################################"}};
char playfield_5[H][W]=
{
{"#####################################################"},
{"#         ###         ###   ###         ###         #"},
{"#   ###############   #########   ###############   #"},
{"#         ###            ###            ###         #"},
{"#   ###   ###   #####################   ###   ###   #"},
{"#   ###                  ###                  ###   #"},
{"#   ##################   ###   ##################   #"},
{"#         ###                           ###         #"},
{"#   ###   #########   #########   #########   ###   #"},
{"#   ###                  ###                  ###   #"},
{"#   ###   #########   #########   #########   ###   #"},
{"#         ###                           ###         #"},
{"#   ##################   ###   ##################   #"},
{"#   ###                  ###                  ###   #"},
{"#   ###   ###   #####################   ###   ###   #"},
{"#         ###            ###            ###         #"},
{"#   ###############   #########   ###############   #"},
{"#         ###         ###   ###         ###         #"},
{"#####################################################"}};

void initialize_1()
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (playfield_1[i][j] == ' ')//replace the empty space in the maze with food pieces
                playfield_1[i][j] = '.';
        }
    }

    for (int i = 0; i < NR_GHOSTS; i++)
    {
        // try to find a (x,y) coordinate randomly where a food piece is
        int x, y;
        do
        {
            x = 1 + rand() % (W - 1);
            y = 1 + rand() % (H - 1);
        } while (playfield_1[y][x] != '.');
        allGhosts[i].position.x = x;
        allGhosts[i].position.y = y;
        playfield_1[y][x] = '&';//replace a food piece with ghost in a random position inside the maze
        //& is the ghost character
    }

}
void initialize_2()
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (playfield_2[i][j] == ' ')
                playfield_2[i][j] = '.';
        }
    }

    for (int i = 0; i < NR_GHOSTS; i++)
    {
      
        // try to find a (x,y) coordinate randomly where a food piece is
        int x, y;
        do
        {
            x = 1 + rand() % (W - 1);
            y = 1 + rand() % (H - 1);
        } while (playfield_2[y][x] != '.');
        allGhosts[i].position.x = x;
        allGhosts[i].position.y = y;
        playfield_2[y][x] = '&';
    }
}
void initialize_3() 
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (playfield_3[i][j] == ' ')
                playfield_3[i][j] = '.';
        }
    }

    for (int i = 0; i < NR_GHOSTS; i++)
    {
        // try to find a (x,y) coordinate randomly where a food piece is
        int x, y;
        do
        {
            x = 1 + rand() % (W - 1);
            y = 1 + rand() % (H - 1);
        } while (playfield_3[y][x] != '.');
        allGhosts[i].position.x = x;
        allGhosts[i].position.y = y;
        playfield_3[y][x] = '&';
    }
}
void initialize_4() 
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (playfield_4[i][j] == ' ')
                playfield_4[i][j] = '.';
        }
    }

    for (int i = 0; i < NR_GHOSTS; i++)
    {
      
        // try to find a (x,y) coordinate randomly where a food piece is
        int x, y;
        do
        {
            x = 1 + rand() % (W - 1);
            y = 1 + rand() % (H - 1);
        } while (playfield_4[y][x] != '.');
        allGhosts[i].position.x = x;
        allGhosts[i].position.y = y;
        playfield_4[y][x] = '&';
    }
}
void initialize_5()
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (playfield_5[i][j] == ' ')
                playfield_5[i][j] = '.';
        }
    }

    for (int i = 0; i < NR_GHOSTS; i++)
    {
        // try to find a (x,y) coordinate randomly where a food piece is
        int x, y;
        do
        {
            x = 1 + rand() % (W - 1);
            y = 1 + rand() % (H - 1);
        } while (playfield_5[y][x] != '.');
        allGhosts[i].position.x = x;
        allGhosts[i].position.y = y;
        playfield_5[y][x] = '&';
    }
}

void user_input()
{
    if (_kbhit())
    {   
        char c1 = _getch();

        if (c1 == -32)
        {
            char c2 = _getch();

            switch (c2)
            {
            case 72:
                myPacMan.vy = -1;
                break; // cursor up
            case 80:
                myPacMan.vy = +1;
                break; // cursor down
            case 75:
                myPacMan.vx = -1;
                break; // cursor left
            case 77:
                myPacMan.vx = +1;
                break; // cursor right
            }
        }
        if(c1 == 27)
        {
            system("cls");
            printf("Game terminated\n");
            exit(0);
        }

    }
}

void move_figures_1()
{
    playfield_1[myPacMan.position.y][myPacMan.position.x] = ' ';//clear the pacaman's path

    int nx = myPacMan.vx + myPacMan.position.x;//compute the new position of the pacman
    int ny = myPacMan.vy + myPacMan.position.y;

    if (playfield_1[ny][nx] == '#')//check whether there is a wall
    {
        myPacMan.vx = 0;//if wall is present stop the pacman
        myPacMan.vy = 0;
    }
    
    myPacMan.position.x += myPacMan.vx;//updating the pacman's position
    myPacMan.position.y += myPacMan.vy;
    
    if (playfield_1[ny][nx] == '.')//if food present
    {
        myPacMan.food_collected++;//increment the score
    }

    playfield_1[myPacMan.position.y][myPacMan.position.x] = 'C';//place the pacman back to the maze
    //C is the character for pacman
}
void move_figures_2()
{
    playfield_2[myPacMan.position.y][myPacMan.position.x] = ' ';

    int nx = myPacMan.vx + myPacMan.position.x;
    int ny = myPacMan.vy + myPacMan.position.y;

    if (playfield_2[ny][nx] == '#')
    {
        myPacMan.vx = 0;
        myPacMan.vy = 0;
    }
    
    myPacMan.position.x += myPacMan.vx;
    myPacMan.position.y += myPacMan.vy;
    
    if (playfield_2[ny][nx] == '.')
    {
        myPacMan.food_collected++;
    }

    playfield_2[myPacMan.position.y][myPacMan.position.x] = 'C';
}
void move_figures_3()
{
    playfield_3[myPacMan.position.y][myPacMan.position.x] = ' ';

    
    int nx = myPacMan.vx + myPacMan.position.x;
    int ny = myPacMan.vy + myPacMan.position.y;

    
    if (playfield_3[ny][nx] == '#')
    {
        
        myPacMan.vx = 0;
        myPacMan.vy = 0;
    }
    
    
    myPacMan.position.x += myPacMan.vx;
    myPacMan.position.y += myPacMan.vy;
    
    
    if (playfield_3[ny][nx] == '.')
    {
        myPacMan.food_collected++;
    }

    
    playfield_3[myPacMan.position.y][myPacMan.position.x] = 'C';
}
void move_figures_4()
{
    playfield_4[myPacMan.position.y][myPacMan.position.x] = ' ';

    
    int nx = myPacMan.vx + myPacMan.position.x;
    int ny = myPacMan.vy + myPacMan.position.y;

    
    if (playfield_4[ny][nx] == '#')
    {
        
        myPacMan.vx = 0;
        myPacMan.vy = 0;
    }
    
    
    myPacMan.position.x += myPacMan.vx;
    myPacMan.position.y += myPacMan.vy;
    
    
    if (playfield_4[ny][nx] == '.')
    {
        myPacMan.food_collected++;
    }

    
    playfield_4[myPacMan.position.y][myPacMan.position.x] = 'C';
}
void move_figures_5()
{
    playfield_5[myPacMan.position.y][myPacMan.position.x] = ' ';

    
    int nx = myPacMan.vx + myPacMan.position.x;
    int ny = myPacMan.vy + myPacMan.position.y;

    
    if (playfield_5[ny][nx] == '#')
    {
        
        myPacMan.vx = 0;
        myPacMan.vy = 0;
    }
    
    
    myPacMan.position.x += myPacMan.vx;
    myPacMan.position.y += myPacMan.vy;
    
    
    if (playfield_5[ny][nx] == '.')
    {
        myPacMan.food_collected++;
    }

    
    playfield_5[myPacMan.position.y][myPacMan.position.x] = 'C';
}

int check_for_collisions()
{
    for(int i=0;i<NR_GHOSTS;i++)
    {
        if(allGhosts[i].position.x==myPacMan.position.x && allGhosts[i].position.y==myPacMan.position.y)//checking for collision
        {
            gameover=0;    
        }
    }
}

void show_playfield_1()
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            printf("%c", playfield_1[i][j]);//printing all the characters inside the maze and the maze
        }
        printf("\n");
    }

    printf("Score: %d\n", myPacMan.food_collected);//score
}
void show_playfield_2()
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            printf("%c", playfield_2[i][j]);
        }
        printf("\n");
    }

    printf("Score: %d\n", myPacMan.food_collected);
}
void show_playfield_3()

{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            printf("%c", playfield_3[i][j]);
        }
        printf("\n");
    }

    printf("Score: %d\n", myPacMan.food_collected);
}
void show_playfield_4()

{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            printf("%c", playfield_4[i][j]);
        }
        printf("\n");
    }

    printf("Score: %d\n", myPacMan.food_collected);
}
void show_playfield_5()
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            printf("%c", playfield_5[i][j]);
        }
        printf("\n");
    }

    printf("Score: %d\n", myPacMan.food_collected);
}
void set_cursor_position(int x, int y)
{
    
    COORD coord = {x, y};//initialising the cursor
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;//hiding the cursor
    SetConsoleCursorInfo(consoleHandle, &info);
}
int main()
{   
    printf("PACMAN\n");
    printf("To start game press -ENTER\n");
    printf("To end game press-ESC\n");
    char c=_getch();
    if(c!=27)
    {
        int level;

        printf("Available levels are from 1-5\n");
        printf("Enter the level number you want to play:");
        scanf("%d",&level);
            switch (level)
            {
            case 1:
                myPacMan.vx=1;
                myPacMan.vy=1;
                break;
            case 2:
                myPacMan.vx=2;
                myPacMan.vy=2;
                break;
            case 3:
                myPacMan.vx=4;
                myPacMan.vy=3;
                break;
            case 4:
                myPacMan.vx=5;
                myPacMan.vy=6;
                break;
            case 5:
                myPacMan.vx=8;
                myPacMan.vy=9;
            default:
                printf("Enter a valid level number\n");
                break;
            }
        
        system("cls");

        if(level==1)
        {
            hidecursor();
            initialize_1();
            

            while (gameover!=0)
            {
                user_input();
                move_figures_1();
                check_for_collisions();
                show_playfield_1();
                Sleep(1000 / 30);
                if(check_for_collisions()==1){myPacMan.lives--;}
                
                set_cursor_position(0, 0);
            }
            system("cls");
            printf("Game Over");
        }
        else if(level==2)
        {
            hidecursor();
            initialize_2();
            
            while (gameover!=0)
            {
            user_input();
            move_figures_2();
            check_for_collisions();
            show_playfield_2();
            Sleep(1000 / 30);
            if(check_for_collisions()==1){myPacMan.lives--;}
            
            set_cursor_position(0, 0);
            }
        system("cls");
        printf("Game Over");
        }
        else if(level==3)
        {
            hidecursor();
            initialize_3();
            
            while (gameover!=0)
            {
            user_input();
            move_figures_3();
            check_for_collisions();
            show_playfield_3();
            Sleep(1000 / 30);
            if(check_for_collisions()==1){myPacMan.lives--;}
            
            set_cursor_position(0, 0);
            }
        system("cls");
        printf("Game Over");
        }
        else if(level==4)
        {
            hidecursor();
            initialize_4();
            
            while (gameover!=0)
            {
            user_input();
            move_figures_4();
            check_for_collisions();
            show_playfield_4();
            Sleep(1000 / 30);
            if(check_for_collisions()==1){myPacMan.lives--;}
            
            set_cursor_position(0, 0);
            }
        system("cls");
        printf("Game Over");
        }
        else if(level==5)
        {
            hidecursor();
            initialize_5();
            
            while (gameover!=0)
            {
            user_input();
            move_figures_5();
            check_for_collisions();
            show_playfield_5();
            Sleep(1000 / 30);
            if(check_for_collisions()==1){myPacMan.lives--;}
            
            set_cursor_position(0, 0);
            }
            system("cls");
            printf("Game Over");
        }
        system("cls");
        printf("Game over");
    }
    else
    {
        system("cls");
        printf("game terminated");
    }
    return 0;
}