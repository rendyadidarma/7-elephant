#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct userdata
{
    char username[30];
    char password[30];
    userdata *next, *prev;
} * head, *tail;

userdata *createNode(char username[30], char password[30])
{
    userdata *temp = (userdata *)malloc(sizeof(userdata));
    strcpy(temp->username, username);
    strcpy(temp->password, password);
    temp->next = temp->prev = NULL;
    return temp;
}

void pushHead(char username[30], char password[30])
{
    userdata *temp = createNode(username, password);

    if (!head)
    {
        head = tail = temp;
    }
    else
    {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
}

void pushTail(char username[30], char password[30])
{
    userdata *temp = createNode(username, password);

    if (!head)
    {
        head = tail = temp;
    }
    else
    {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

int main()
{
    while (1)
    {
        printf("Oo=====================================oO\nSTUDY NETWORK\nOo=====================================oO\n");
        puts("[All User]");
        puts("No. Username");
        puts("-----------------------------------------");
        puts("[1] Register");
        puts("[2] Login");
        puts("[3] Exit");
        printf("-----------------------------------------\nPress 0 and enter to abort an operation\n-----------------------------------------\n");

        int n;
        printf(">>");
        scanf("%d", &n);
        getchar();

        switch (n)
        {
        case 1:
        {
            puts("");

            char userTemp[255];
            char passTemp[255];
            int userFlag = 0;

            //validasi username
            while (userFlag != 1)
            {
                printf("Please type in your username [lowercase || 1..24]:");
                scanf("%[^\n]", userTemp);
                getchar();

                //variabel penanda jika ada huruf besar
                int caps = 0;
                for (int i = 0; userTemp[i] != '\0'; i++)
                {
                    if (!(userTemp[i] >= 'a' && userTemp[i] <= 'z'))
                    {
                        caps++;
                    }
                }
                int len = strlen(userTemp);

                //variabel penanda, username pernah digunakan sebelumnya
                int dupe = 0;
                userdata *temp = head;
                while (temp)
                {
                    if (strcmp(userTemp, temp->username) == 0)
                    {
                        dupe = 1;
                    }
                    temp = temp->next;
                }
                if (caps == 0 && len <= 24 && dupe == 0)
                    userFlag = 1;
            }

            //flag buat password
            int passFlag = 0;
            while (passFlag != 1)
            {
                printf("Please type in your password [lowercase || 1..24]:");
                scanf("%[^\n]", passTemp);
                getchar();
                //variabel penanda jika ada huruf besar
                int caps = 0;
                for (int i = 0; passTemp[i] != '\0'; i++)
                {
                    if (!(passTemp[i] >= 'a' && passTemp[i] <= 'z'))
                    {
                        caps++;
                    }
                }

                int len = strlen(passTemp);

                //variabel penanda, password pernah digunakan sebelumnya
                int dupe = 0;
                userdata *temp = head;
                while (temp)
                {
                    if (strcmp(userTemp, temp->username) == 0)
                    {
                        dupe = 1;
                    }
                    temp = temp->next;
                }
                if (caps == 0 && len <= 24 && dupe == 0)
                    passFlag = 1;
            }
            puts("password validasi");

            if (passFlag == 1 && userFlag == 1)
            {
                pushHead(userTemp, passTemp);
                puts("Username Added Succesfully!\nPress enter to continue");
                getchar();
            }
            else
            {
                printf("Username invalid\nPress enter to continue");
                getchar();
                break;
            }

            break;
        }

        case 2:
        {
            // login
            break;
        }

        case 3:
            return 0;
        }
    }
    return 0;
}