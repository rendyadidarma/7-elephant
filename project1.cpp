#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct userFriend
{
    char username[30];
    userFriend *next, *prev;
};
struct userdata
{
    char username[30];
    char password[30];
    userdata *next, *prev;
    userFriend *friendHead, *friendTail, *inboxHead, *inboxTail, *viewHead, *viewTail, *dummy;
} *head, *tail;

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
void printUsername() {
    if(!head) 
        return;
    userdata *temp = head;
    int count = 1;
    while(temp) {
        printf("%d  %s\n",count++,temp->username);
        temp = temp->next;
    }
}

void printFriend(userdata **userNode) {
    if(!(*userNode)->friendHead){
        printf("-\n");
        return;
    }
    userFriend *temp = (*userNode)->friendHead;
    int count = 1;
    while(temp) {
        printf("%d %s\n",count++,temp->username);
        temp = temp->next;
    }
}

void addFriend(char *user) {
    puts("User Available\n");
    userdata *temp = head;
    int count = 1;
    while(temp) {
        if(strcmp(temp->username,user) != 0) {
            printf("%d %s\n",count++, temp->username);
        }
        temp = temp->next;
    }
    
    printf("Which user you want to add? \n >>");
    char name[50];
    scanf("%s", name);
    temp = head;
    int flag = 0;
    while(temp) {
        if(strcmp(temp->username,name) == 0) {
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if(!temp) {
        printf("No person with that name\n");
        return;
    } else {
        temp->dummy = (userFriend*) malloc(sizeof(userFriend));
        strcpy(temp->dummy->username,user);
        temp->dummy->next = temp->dummy->prev = NULL;
        
        if(!temp->inboxHead){ // inbox penerima kosong
            temp->inboxHead = temp->inboxTail = temp->dummy;
        } else { // inbox yg mau di add tidak kosong
            temp->inboxTail->next = temp->dummy;
            temp->dummy->prev = temp->inboxTail;
            temp->inboxTail = temp->dummy;
        } // ini berarti inbox orang yg di add jadi ada isi nama yg tukang add

        userdata *tempo = head;
        while(strcmp(tempo->username,user)!= 0) {
            tempo = tempo->next;
        }
        if(tempo) { // masukin ke viewbox(udah kirim ke siapa aja) dari user saat ini
            tempo->dummy = (userFriend*) malloc(sizeof(userFriend));
            strcpy(tempo->dummy->username,name);
            tempo->dummy->next = tempo->dummy->prev = NULL;
            if(!tempo->viewHead) {
                tempo->viewHead = tempo->viewTail = tempo->dummy;
            } else { // misalnya viewInbox dari pengirim ga kosong
                tempo->viewTail->next = tempo->dummy;
                tempo->dummy->prev = tempo->viewTail;
                tempo->viewTail = tempo->dummy;
                }
        }
    }
}

userFriend *createDummy(userdata **node, char *string) {
    (*node)->dummy = (userFriend*) malloc(sizeof(userFriend));
    strcpy((*node)->dummy->username,string);
    (*node)->dummy->next = (*node)->dummy->prev = NULL;
    return (*node)->dummy;
}

void popSearch(userdata **node, char *name, int x ) {// name = yang mau dihapus
// node ni yang pointer yg letaknya ditempat mau kita hapus
if(x == 1) {
    userdata *temp;
    temp->dummy = (*node)->inboxHead;
    int isTrue = 0;
    while(temp->dummy) {
        if(strcmp(name,temp->dummy->username) == 0) {
            isTrue = 1;
            break;
        }
        temp->dummy = temp->dummy->next;
    }
    
    if(isTrue) { // brarti ada

        userFriend *freeuserFriend = temp->dummy;
        if(temp->inboxHead == temp->inboxTail) {
            temp->inboxHead = temp->inboxTail = NULL;
        } else if (temp->dummy == temp->inboxHead) {
            temp->inboxHead = temp->inboxHead->next;
            temp->inboxHead->prev = NULL;
        } else if( temp->dummy == temp->inboxTail) {
            temp->inboxTail = temp->inboxTail->prev;
            temp->inboxTail->next = NULL;
        } else {
            temp->dummy->prev->next = temp->dummy->next;
            temp->dummy->next->prev = temp->dummy->prev;
        } free(freeuserFriend);
    }
} else if(x == -1) { // pop view name

}
}

void inboxSee(char *user) {
    userdata *temp = head;
    while(strcmp(temp->username,user) != 0) {
        temp = temp->next;
    } // cari node user

    userFriend *tempv2 = temp->inboxHead;
    printf("All friend request of %s\n",user);
    while(tempv2) {
        printf("%s\n", tempv2->username);
        tempv2 = tempv2->next;
    }
    printf("Which user you want to accept? \n >>");
    char name[50];
    scanf("%s", name);
    temp = head;
    int flag = 0;
    while(temp) {
        if(strcmp(temp->username,name) == 0) {
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if(!temp) {
        printf("No person with that name\n");
        return;
    } else {
        userFriend *createFriend = createDummy(&temp,name);
        temp = head;
        while(strcmp(temp->username,user) != 0) {
        temp = temp->next;
        }
        if(!temp->friendHead)
            temp->friendHead = temp->friendTail = createFriend;
        else {
            temp->friendTail->next = createFriend;
            createFriend->prev = temp->friendTail;
            temp->friendTail = createFriend;
        } 

        temp = head;
        while(strcmp(temp->username,name) != 0) {
        temp = temp->next;
        }
        userFriend *createFriend2 = createDummy(&temp,user);
        if(!temp->friendHead)
            temp->friendHead = temp->friendTail = createFriend2;
        else {
            temp->friendTail->next = createFriend2;
            createFriend2->prev = temp->friendTail;
            temp->friendTail = createFriend2;
        } 
        
        // temp = head;
        // while(strcmp(temp->username,user) != 0) {
        // temp = temp->next;
        // }
        // popSearch(&temp,name,1);

    }
}

void viewReq(char *name) {
    userdata *node = head;
    while(strcmp(node->username,name) != 0) {
        node = node->next;
    }
    
    while(node->viewHead) {
        printf("%s [pending]\n", node->viewHead);
        node->viewHead = node->viewHead->next;
    }
    printf("Press enter to back to menu.."); getchar();

}

void loginSuccess(char *user) {
    while(1) {
    printf("Welcome , %s\n", user);
    printf("Friend List of [%s]\n",user);
    userdata *temp = head;
    while(strcmp(temp->username,user) != 0){
        temp = temp->next;
    }
    if(temp) {
        printFriend(&temp);
    }
        puts("Menu");
        puts("1. Add Friend");
        puts("2. Remove Friend");
        puts("3. View Inbox");
        puts("4. View Sent Request");
        puts("5. Add Edit Announce Delete Node");
        puts("6. Log Out");
        printf(">>"); int n;
        scanf("%d",&n); getchar();
        switch(n) {
            case 1: 
                addFriend(user);
                break;
            case 2:

                break;
            case 3:
                inboxSee(user);
                break;
            case 4:
                viewReq(user);
                break;
            case 5:

                break;
            case 6:
                return;
        }
    }
}


int main()
{
    while (1)
    {
        printf("Oo=====================================oO\nSTUDY NETWORK\nOo=====================================oO\n");
        puts("[All User]");
        puts("No. Username");
        printUsername();
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
            
            int flag = 0;
            char username[50];
            char password[50];
        while(1){
            userdata *temp = head;
            flag = 0;
            printf("Username : ");
            scanf("%s", username);
            printf("Password : ");
            scanf("%s", password);
            while(temp) {
                if(strcmp(temp->username,username) == 0){
                    if(strcmp(temp->password,password) == 0){
                        flag = 1;
                    }
                }
                temp = temp->next;
            }
            if(flag == 1){
                break;
            }
        }
        if(flag == 1) {
            printf("Login Success\nPress Enter to Continue..");
            getchar();getchar();
            loginSuccess(username);
        }
            break;
        }

        case 3:
            return 0;
        }
    }
    return 0;
}