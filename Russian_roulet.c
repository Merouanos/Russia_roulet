
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void Create_Game(int **gun, int size, int bullets_nb, bool if_first)
{
    int i, bullet_pos;
    if (if_first)
        *gun = (int *)malloc(size * sizeof(int));
    for (i = 0; i < size; i++)
        gun[0][i] = 0;
    srand(time(NULL));
    for (i = 0; i < bullets_nb; i++)
    {
        bullet_pos = rand() % (size);
        gun[0][bullet_pos]--;
    }
}

bool Shoot(int *gun, int *size)
{

    bool ifbullet;
    if (gun[0] == -1)
    {
        ifbullet = true;
        printf("%c", 7);
    }
    else
        ifbullet = false;
    for (int i = 0; i < *(size)-1; i++)
        gun[i] = gun[i + 1];
    (*size)--;
    return ifbullet;
}

void Generate_Gamemode(int *Player, int *Enemy, int *size, int *bullets, short gamemode)
{
    if (gamemode == 1)
    {
        *Player = 3;
        *Enemy = 3;
        *size = 3;
        *bullets = 1;
    }
    else
    {
        *Player = 3;
        *Enemy = 5;
        *size = 6;
        *bullets = 2;
    }
}
void Display(int player, int enemy)
{
    system("cls");
    const int farspace = 100, downspace = 10, space = 60;
    printf("      %d", player);
    for (int i = 1; i < farspace; i++)
        printf(" ");
    printf("%d", enemy);
    for (int i = 1; i < downspace; i++)
        printf("\n");
    for (int i = 1; i < space; i++)
        printf(" ");
    printf("(-_-)");
    for (int i = 1; i < downspace; i++)
        printf("\n");
    for (int i = 1; i < space; i++)
        printf(" ");
    printf("(.)\n\n");
}
void Waiting()
{
    for (int j = 0; j < 10; j++)
    {
        Sleep(100);
        printf(".");
    }
    printf("\n");
    Sleep(1000);
}
void CheckGame(int player_health, int enemy_health, bool *game_finished, int *size, int fixed_size, int bullets, int *gun)
{
    if (enemy_health == 0 || player_health == 0)
        *game_finished = true;

    else if (*size == 0)
    {
        *size = fixed_size;
        printf("Reloading Gun");
        Waiting();
        Create_Game(&gun, *size, bullets, false);
    }
}

int main()
{

    bool game_finished = false, right;
    short game_dif, choise;
    int *gun, player_health, enemy_health, fixed_size, size, bullets;
    srand(time(NULL));
    do
    {
        right = true;
        printf("Please choose game diffuclity :\n1-Easy       2-Mediume ");
        scanf("%d", &game_dif);
        if (game_dif > 2 || game_dif < 1)
        {
            printf("Please choose carefully\n ");
            right = false;
        }

    } while (!right);

    Generate_Gamemode(&player_health, &enemy_health, &size, &bullets, game_dif);
    fixed_size = size;
    Create_Game(&gun, size, bullets, true);

    while (!game_finished)
    {

        Display(player_health, enemy_health);
        do
        {
            right = true;
            printf("Choose who do you want to shoot:\n1-Yourself              2-The enemy ");
            scanf("%d", &choise);
            if (choise < 0 || choise > 2)
            {
                printf("Please choose carefully\n ");
                right = false;
            }
        } while (!right);
        Display(player_health, enemy_health);
        printf("Shooting");
        Waiting();
        if (Shoot(gun, &size))

            if (choise == 1)
            {
                player_health--;
                Display(player_health, enemy_health);
                printf("You've shot yourself\n");
            }
            else
            {
                enemy_health--;
                Display(player_health, enemy_health);
                printf("You've shot the enemy\n");
            }
        else
            printf("You missed\n");
        Sleep(1000);
        Display(player_health, enemy_health);
        CheckGame(player_health, enemy_health, &game_finished, &size, fixed_size, bullets, gun);
        if (!game_finished)
        {
            printf("Enemy's turn\n");
            Sleep(500);
            do
                choise = rand() % 3;
            while (choise == 0);
            if (choise == 1)

                printf("The enemy is poiting the gun at you\n");
            else
                printf("The enemy is poiting the gun at himself\n");
            Sleep(1000);
            printf("Shooting");
            Waiting();
            if (Shoot(gun, &size))
                if (choise == 1)
                {
                    player_health--;
                    Display(player_health, enemy_health);
                    printf("The enemy shoot  you\n");
                }
                else
                {
                    
                    enemy_health--;
                    Display(player_health, enemy_health);
                    printf("The enemy shoot himself\n");
                }
            else
                printf("He missed\n");
            Sleep(1500);
            CheckGame(player_health, enemy_health, &game_finished, &size, fixed_size, bullets, gun);
        }
    }
}