#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};

struct node *headc = NULL,*newnode,*tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;

void adminmenu()
{
    printf("\n\t1 >>> VIEW TOTAL SALES\n");
    printf("\t2 >>> ADD NEW ITEMS IN MENU\n");
    printf("\t3 >>> REMOVE ITEMS FROM MENU\n");
    printf("\t4 >>> DISPLAY MENU\n");
    printf("\t5 >>> Back To Home page \n\n");
    printf("\t>>> ");
}

void customermenu()
{
    printf("\n 1 >>> Place your order\n\n");
    printf(" 2 >>> View your cart\n\n");
    printf(" 3 >>> Delete order from cart\n\n");
    printf(" 4 >>> Final bill amount to be paid\n\n");
    printf(" 5 >>> Back To Main Menu \n\n");
    printf("\n\n\t Enter Your Choice >>> ");
}

struct node* createadmin(struct node *head,int data, char foodname[25], float price)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;

    if(temp==NULL)
        heada = taila = newnode;
    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newnode;
        newnode->prev = taila;
        taila = newnode;
    }

    return heada;
}

struct node* createcustomer(struct node *head,int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    struct node *temp1 = heada;
    int flag = 0;
    while(temp1!=NULL)
    {
        if(temp1->data==data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if(flag==1)
    {
        newnode->data = data;
        newnode->price = quantity*(temp1->price);
        newnode-> quantity = quantity;
        strcpy(newnode->foodname,temp1->foodname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if(temp==NULL)
            headc = tailc = newnode;
        else
        {
            while(temp->next!=NULL)
                temp=temp->next;

            temp->next=newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }


    }
    else
    {
        printf("\nThis item is not present in the menu!\n");
    }
    return headc;
}

void displayList(struct node *head)
{
    system("cls");
    struct node *temp1 = head;
    if(temp1==NULL)
    {
        printf("\n\n***NO ORDERS YET.\n\n");
        getch();
    }
    else
    {
        printf("\n");
        while(temp1!=NULL)
        {
            if(temp1->quantity==0)
            {
                printf("\n\n\t\t\t\t%d\t%s\t\t%0.2f\n",temp1->data,temp1->foodname,temp1->price);
            }
            else
            {
                printf("\n\n\t\t\t\t\t%d\t%s\t\t%d\t\t%0.2f\n",temp1->data,temp1->foodname,temp1->quantity,temp1->price);
            }

            temp1 = temp1->next;
        }
        printf("\n");
    }

}

struct node* totalsales(int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = heada;
    while(temp1->data!=data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity*(temp1->price);
    newnode-> quantity = quantity;
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if(temp==NULL)
        head_s = newnode;
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                flag = 1;
                break;
            }
            temp=temp->next;
        }

        if(flag==1)
        {
            temp->quantity += newnode-> quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
        }
    }

    return head_s;
}

void calculatetotsales()
{
    struct node *temp = headc;
    while(temp!=NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp=temp->next;
    }
}

struct node* delete(int data,struct node *head, struct node* tail)
{
    if(head==NULL)
    {
        printf("\nList is empty\n");
    }
    else
    {
        struct node* temp;
        if(data==head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if(data==tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while(data!=temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}

int deleteadmin()
{
    printf("\nEnter S.NO of food item to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=heada;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            heada = delete(num, heada, taila);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

int deletecustomer()
{
    printf("\nEnter S.NO of the food item to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=headc;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            headc = delete(num, headc, tailc);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

void displaybill()
{
    displayList(headc);
    struct node *temp = headc;
    float total_price = 0;
    while (temp!=NULL)
    {
        total_price +=temp->price;
        temp = temp->next;
    }

    printf("\nTotal price: %0.02f\n",total_price);

}

struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void admin()
{
    system("cls");
    printf("\n\n\t\tADMIN SECTION\n");
    while(1)
    {
        adminmenu();

        int opt;
        scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(head_s);
                break;
            case 2:
                system("cls");
                printf("\nS.NO of the item: ");
                int num,flag = 0;
                char name[50];
                float price;
                scanf("%d",&num);

                struct node *temp = heada;

                while(temp!=NULL)
                {
                    if(temp->data==num)
                    {
                        printf("\nFood item with given S.NO already exists!!\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(flag==1)
                    break;

                printf("\nEnter food item name: ");
                scanf("%s",name);
                printf("\n\nEnter price: ");
                scanf("%f",&price);
                heada = createadmin(heada, num, name, price);
                printf("\nNew food item added to the list!!\n");
                break;
            case 3:
                if(deleteadmin())
                {
                    printf("\nUPDATED MENU LIST\n");
                    displayList(heada);
                }
                else
                    printf("\nFood item with given S.NO doesn't exist!\n");

                break;
            case 4:
                printf("------ ROYAL BAKERS DELIGHT MENU ------\n");
                displayList(heada);
                break;

            default:
                printf("\nPlease choose valid option\n");
                break;
        }
    }
}

void customer()
{
    int flag=0,j=1;
    char ch;
    system("cls");
    printf("\n\tCUSTOMER SECTION\n");
    while(1)
    {
        customermenu();

        int opt;
        scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(heada);
                printf("\n\nEnter S.NO of the food item >>> ");
                int n;
                scanf("%d",&n);
                printf("\n\nEnter quantity: ");
                int quantity;
                scanf("%d",&quantity);
                printf("\n\nOrder placed!\n\n");
                getch();
                headc = createcustomer(headc, n, quantity);
                break;
            case 2:
                printf("\nList of ordered items\n");
                displayList(headc);
                break;
            case 3:
                if(deletecustomer())
                {
                    printf("\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n");
                    displayList(headc);
                }
                else
                    printf("\nFood item with given serial number doesn't exist!!\n");
                break;
            case 4:
                calculatetotsales();
                printf("\n Final Bill \n");
                displaybill();
                headc = deleteList(headc);
                printf("\nPress any key to return to main menu \n");
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;

            default:
                printf("\nWrong Input !! PLease choose valid option\n");
                break;
        }
        if(flag==1)
            break;
    }
}

void mainnenu()
{
    system("cls");
    printf("\t****************************");
    printf("\n\t    ROYAL BAKER'S DELIGHT\n");
    printf("\t\tWELCOMES YOU\n");
    printf("\t****************************");
    printf("\n\n\t1 >>>  ADMIN SECTION\n\n");
    printf("\t2 >>>  CUSTOMER SECTION\n\n");
    printf("\t3 >>>  Exit\n\n");
    printf("\n\n\t>>> ");
}

int main()
{

    heada = createadmin(heada,1,"CREAM BUN",100);
    heada = createadmin(heada,2,"CHOCLATE MUFFIN",200);
    heada = createadmin(heada,3,"JAM ROLL",150);
    heada = createadmin(heada,4,"BUTTER PASTERY",180);
    heada = createadmin(heada,5,"VANILLA ROLL",80);
    heada = createadmin(heada,6,"WALNUT CAKE",80);

    while(1)
    {
        mainnenu();
        int choice;
        scanf("%d",&choice);

        switch (choice)
        {
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                system("cls");
                printf("\n\n\t\t\tThank you!\n");
                getch();
                exit(0);
                break;

            default:
                printf("Enter valid choice\n");
                break;
        }
    }
}
