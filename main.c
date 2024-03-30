#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node_Meds *tree_ptr ;
typedef struct node_HashMeds *ptr;
int size ;
int nOfElemt;
struct node_Meds
{

    char name [50];
    char active_ingredient [50]; // العنصر النشط
    char category[50] ; // الفئة
    char indication [50] ; //الاعراض المرضيه
    char ex_Date [10];
    int count ;
    char company [60];

    tree_ptr right ;
    tree_ptr left ;

};
struct node_HashMeds
{

    char name [50];
    char info[100];

};
struct hashTabel
{
    int flag ; // check if there is data in index or not if f=0 mean empty index
    int collisions  ;
    tree_ptr data ;
};
typedef struct hashTabel *array;
typedef tree_ptr BST ;

BST insertTree (BST root,char name[50],char activ [50],char category[50],char indication [50],char date[10], int count, char company[60] )
{

    if(root==NULL)
    {


        root = (BST)malloc(sizeof(struct node_Meds));

        strcpy(root->name, name);

        strcpy(root->active_ingredient, activ);

        strcpy(root->category, category);

        strcpy(root->indication, indication);

        strcpy(root->ex_Date,date);

        root->count = count ;
        strcpy(root->company, company);

        root->left=root->right = NULL ;



    }
    if (strcmp(root->name, name)>0)
    {
        root->left = insertTree(root->left,name,activ,category,indication,date,count,company);
    }
    else if (strcmp(root->name, name)<0)
    {
        root->right = insertTree(root->right,name,activ,category,indication,date,count,company);
    }

    return root ;
}
BST makeEmpty(BST root)
{
    if (root != NULL)
    {
        makeEmpty(root->left);
        makeEmpty(root->right);
        free(root);
    }
    return NULL;
}

BST find_Node(BST root, char name[50])
{

    if (root == NULL)
    {
        return NULL ;
    }
    if (strcmp(root->name,name)>0)
    {
        return (find_Node(root->left, name));

    }
    else if (strcmp(root->name,name)<0)
    {
        return (find_Node(root->right, name));
    }
    else
        return root ;

}

BST find_Mim(BST root  )
{

    BST temp ;
    for(temp = root ; temp->left!=NULL ; temp=temp->left);
    return temp ;

}
BST find_Max(BST root)
{

    BST temp ;
    for(temp = root ; temp->right!=NULL ; temp=temp->right);
    return temp ;

}
void pre_Print(BST root )
{

    if (root!=NULL)
    {
        printf("%s : %s : %s : %s : %s : %d : %s\n",root->name,root->active_ingredient,root->category,root->indication,root->ex_Date,root->count,root->company );
        pre_Print(root->left);
        pre_Print(root->right);

    }

}
void sameCategory(BST root,char category[50] )
{

    if(root != NULL)
    {
        if (strcmp(root->category,category)==0)
        {

            if (root->count >0)
            {
                printf(" %s ,is Available \n",root->name);
            }

            else
            {
                printf(" %s is not Available",root->name);
            }
        }
        sameCategory(root->left,category);
        sameCategory(root->right,category);
    }
}
void sameDisease (BST root, char indication [50] )
{
    if(root!=NULL)
    {
        for(char *token = strtok(root->indication, ","); token!=NULL; token = strtok(NULL, ",") )
        {
            if(strcmp(token,indication)==0)
            {
                if (root->count >0)
                {
                    printf(" %s ,is Available \n",root->name);
                }

                else
                {
                    printf(" %s ,is not Available \n",root->name);
                }
            }
        }
        sameDisease (root->left, indication);
        sameDisease (root->right, indication);

    }

}

BST upDate (BST root,char name[50],char activ [50],char category[50],char indication [50],char date[10], int count, char company[60] )
{
    if (root==NULL)
    {
        printf("====NOT FOUND=======\n");
    }
    else
    {
        if (strcmp(root->name,name)!=0)
        {
            strcpy(root->name,name);
        }
        if (strcmp(root->category,category)!=0)
        {
            strcpy(root->category,category);
        }
        if (strcmp(root->indication,indication)!=0)
        {
            strcpy(root->indication,indication);
        }
        if (strcmp(root->ex_Date,date)!=0)
        {
            strcpy(root->ex_Date,date);
        }
        if (root->count!=count)
        {
            root->count = count;
        }
        if (strcmp(root->company,company)!=0)
        {
            strcpy(root->company,company);
        }
    }
    return root ;


}
BST delete_Meds  (BST root, char name[50])
{
    BST temp, child ;
    if (root==NULL)
    {

        printf("======meds %s is not found=======",name);
    }
    else if (strcmp(root->name,name)>0)
    {
        root->left =delete_Meds(root->left,name);
    }
    else if (strcmp(root->name,name)<0)
    {
        root->right =delete_Meds(root->right,name);
    }
    else

    {
        if(root->left==NULL && root->right==NULL)
            return NULL;
        if (root->left && root->right)
        {
            temp = find_Mim(root->right);
            strcpy(root->name, temp->name);
            strcpy(root->active_ingredient, temp->active_ingredient);
            strcpy(root->category, temp->category);
            strcpy(root->indication, temp->indication);
            strcpy(root->ex_Date, temp->ex_Date);
            root->count = temp->count ;
            strcpy(root->company, temp->company);
            root->right=delete_Meds(root->right, temp->name);
        }
        else
        {
            temp = root ;
            if (root->left==NULL)
            {
                child =root->right;
            }
            if (root->right == NULL)
            {
                child = root->left;
            }
            free(temp);
            return child ;
        }
    }
    return root ;

}
BST deleteUesCompanyInfo (BST rootTree,BST root, char company[])
{
    if (root!= NULL)
    {
        printf("\n_____deleteCompany_____%s__%s___\n",root->company,company );

        if (strcmpi(root->company,company)==0)
        {
            return delete_Meds(rootTree,root->name);
        }
        deleteUesCompanyInfo(rootTree,root->left, company);
        deleteUesCompanyInfo(rootTree,root->right,company);

    }

    return rootTree;
}
BST read_Meds(BST root )
{


    FILE *fMed = fopen("meds.txt","r");
    char string[200];

    if(fMed==NULL)
    {

        printf("====ERROR IN OPNING FILE=======");
    }
    else

        while (fgets(string,200,fMed)!=NULL)
        {



            char n[50];
            char ac[50];
            char ca [50];
            char in [50];
            char d[10];
            char  co [60];
            int cu;

            char *token = strtok(string, ":");
            strcpy(n,token);

            token =strtok(NULL,":");

            strcpy(ac,token);
            //4
            token =strtok(NULL,":");
            strcpy(ca,token);

            token =strtok(NULL,":");
            strcpy(in,token);


            token =strtok(NULL,":");
            strcpy(d,token);

            token =strtok(NULL,":");
            cu =atoi(token);
            token =strtok(NULL,":\n");
            strcpy(co,token);
            root= insertTree(root,n,ac,ca,in,d,cu,co);
            size++ ;
        }

    fclose(fMed);

    return root;

}
void preOrdre(BST root, FILE *in)
{
    if (root!= NULL)
    {
        fprintf(in,"%s:%s:%s:%s:%s:%d:%s\n",root->name,root->active_ingredient,root->category,root->indication,root->ex_Date,root->count,root->company);
        preOrdre(root->left,in);
        preOrdre(root->right,in);
    }

}
void writeInFile (BST root)
{
    FILE *in =fopen("Pharmacy.txt","w");
    if (root!=NULL)
    {
        preOrdre(root,in);
    }
    fclose(in);
}
int isPrime(int x)
{
    int flag ;
    if (x==0 || x==1)
    {
        return 0 ; //0 if not prime
    }
    for (int i=2; i<x/2 ; i++)
    {
        if(x%i==0)
        {
            flag =1; //is not peime
            break ;
        }
    }
    if (flag==1)
    {
        return 0;
    }
    else
    {
        return 1;//is a prime
    }
}
int getPrime(int x)
{
    if (isPrime(x)==1)
    {
        return x;
    }

    return getPrime(x+1);
}
int getsize (int n)
{
    size = (int) (n/0.6) ;
    size =getPrime(size);
    return size ;
}

int hashCode(char a,char b, char c)
{
    int key ;
    key = ((int)a+b+c);

    return  key%size ;
}
array init_array(array h )
{


    for (int i=0 ; i<size; i++)
    {
        h[i].flag =0;
        h[i].collisions=0 ;
        h[i].data =NULL;
        //  printf("\n %s",h[i].data);
    }

    return h ;
}
void insertHash (array h, char name[50],char activ [50],char category[50],char indication [50],char date[10], int count, char company[60] )
{
    int index = hashCode(name[0],name[1],name[2]);
    int i = index ;
    tree_ptr newData = (tree_ptr)malloc(sizeof(struct node_Meds));
    strcpy(newData->name,name);
    strcpy(newData->active_ingredient,activ);
    strcpy(newData->category,category);
    strcpy(newData->indication,indication);
    strcpy(newData->ex_Date,date);
    newData->count = count;
    strcpy(newData->company,company);
    while(h[i].flag ==1)
    {


        if (strcmp(h[i].data->name,name)==0) //check if it same data
        {
            printf("the data already exists \n");
            return;
        }
        i = (i+1)%size ;
        if (i == index )//that mean that he return to first index do not found an empty index
        {
            printf("the table is full \n");
            return;
        }
    }
    h[i].flag = 1 ;
    h[i].data = newData;
    nOfElemt++ ;
}
void read_ph (array h)
{



    FILE *fph = fopen("Pharmacy.txt","r");
    char string [200];
    while(fgets(string,200,fph)!=NULL)
    {
        char n[50];
        char ac[50];
        char ca [50];
        char in [50];
        char d[10];
        char  co [60];
        int cu;
        char *token = strtok(string, ":");
        strcpy(n,token);
        token =strtok(NULL,":");
        strcpy(ac,token);
        token =strtok(NULL,":");
        strcpy(ca,token);
        token =strtok(NULL,":");
        strcpy(in,token);
        token =strtok(NULL,":");
        strcpy(d,token);
        token =strtok(NULL,":");
        cu =atoi(token);
        token =strtok(NULL,":\n");
        strcpy(co,token);
        insertHash(h,n,ac,ca,in,d,cu,co);
    }
    fclose(fph);
}
void SearchHash (array h, char name [50])
{
    int index = hashCode(name[0],name[1],name[2]);
    int i = index ;
    while(h[i].flag != 0)
    {
        if (h[i].flag==1 && strcmp(h[i].data->name,name)==0)
        {
            printf("\n ===============================================================\n");
            printf("\n fond the mdes in index %d \n",i);
            printf("  name : %s\n info :%s:%s:%s:%s:%d:%s \n ",h[i].data->name,h[i].data->active_ingredient,h[i].data->category,h[i].data->indication,h[i].data->ex_Date,h[i].data->count,h[i].data->company);
            printf("Number of collisions is %d", h[i].collisions);
            printf("\n ===============================================================\n");
            return ;
        }
        i = (i+1)%size ;
        h[i].collisions++;
        if (i==index)
        {
            break ;
        }
    }
    printf("\n ===============================================================\n");
    printf(" This mdes does not exist \n");
    printf("\n ===============================================================\n");
}
void deleteHash (array h,char name [50])
{
    int index = hashCode(name[0],name[1],name[2]);
    int i = index;
    while(h[i].flag !=0)
    {
        if (h[i].flag==1 && strcmp(h[i].data->name,name)==0 )
        {
            h[i].flag =0 ;
            h[i].data = NULL ;
            nOfElemt-- ;
            printf("\n ===============================================================\n");
            printf("meds %s in index %d has been deleted \n ",name,i);
            printf("\n ===============================================================\n");
            return ;
        }
        i = (i+1)%size ;
        if (i==index)
        {
            break ;
        }
    }
    printf("\n ===============================================================\n");
    printf(" This mdes does not exist \n");
    printf("\n ===============================================================\n");
}
void printHash (array h)
{

    for (int i=0 ; i<size ; i++)
    {
        tree_ptr temp = h[i].data;
        if (temp==NULL)
        {
            printf("\n ===============================================================\n");
            printf("hash [%d] has no elements \n",i);
            printf("\n ===============================================================\n");
        }
        else
        {
            printf("\n ===============================================================\n");
            printf("hash [%d] has elements  name : %s\n info :%s:%s:%s:%s:%d:%s \n ",i,h[i].data->name,h[i].data->active_ingredient,h[i].data->category,h[i].data->indication,h[i].data->ex_Date,h[i].data->count,h[i].data->company);
            printf("\n ===============================================================\n");
        }
    }

}
void writeInFileHash(array h)
{
    FILE *in = fopen("Pharmacy.txt","w");
    for (int i=0; i<size; i++)
    {
        if (h[i].data != NULL)
        {
            fprintf(in,"%s:%s:%s:%s:%s:%d:%s",h[i].data->name,h[i].data->active_ingredient,h[i].data->category,h[i].data->indication,h[i].data->ex_Date,h[i].data->count,h[i].data->company);
        }
    }
    fclose(in);
}


int main()
{

    BST root =makeEmpty(NULL) ;
    root=read_Meds(root);
    pre_Print(root);
    writeInFile(root);
    size = getsize(size);
    array h  = (array)malloc(size*sizeof(struct hashTabel));
    h = init_array(h);
    read_ph(h);

    int choice,choice_1 ;
    char name [50];
    char active_ingredient [50]; // العنصر النشط
    char category[50] ; // الفئة
    char indication [50] ; //الاعراض المرضيه
    char ex_Date [10];
    int count ;
    int num ;
    char company [60];
    tree_ptr foundNode ;


    do
    {
        printf("1) Display medicines in in alphabetical order\n"
               "2) Add new medicines \n"
               "3) Find a medicine \n"
               "4) Medicines of same category \n"
               "5) medicines that treat a specific disease  \n"
               "6) Delete a medicine \n"
               "7) Delete all medicines from a specific company\n"
               "8) Save in a file\n"
               "9) Hash\n"
               "10) End the program \n"
               "Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {

        case 1:
            printf("\n ===============================================================\n");
            pre_Print(root);
            printf("\n ===============================================================\n");

            break;
        case 2:
            printf("\n ===============================================================\n");

            printf("Enter the information of new Meds in order name,active ingredient,category,indication,Ex Date,count,company \n");
            scanf("%s",name);
            scanf("%s",active_ingredient);
            scanf("%s",category);
            scanf("%s",indication);
            scanf("%s",ex_Date);
            scanf("%d",&count);
            scanf("%s",company);
            insertTree(root,name,active_ingredient,category,indication,ex_Date,count,company);
            printf("\nDon\n");
            printf("\n ===============================================================\n");

            break;
        case 3:
            printf("\n ===============================================================\n");

            printf("Enter the name of meds that you want to found \n");
            scanf("%s",name);
            foundNode = find_Node(root,name);
            if (foundNode==NULL)
            {

                printf("not found \n");
                printf("\n ===============================================================\n");

            }
            else
            {
                printf("\n ===============================================================\n");
                printf("\n the meds is found \n");
                printf("If you want to up date the info of meds enter 1 if not enter 0 \n");
                scanf("%d",&num);
                if (num==1)
                {
                    printf("Enter the information of new Meds in order name,active ingredient,category,indication,Ex Date,count,company \n");
                    scanf("%s",name);
                    scanf("%s",active_ingredient);
                    scanf("%s",category);
                    scanf("%s",indication);
                    scanf("%s",ex_Date);
                    scanf("%d",&count);
                    scanf("%s",company);
                    upDate(root,name,active_ingredient,category,indication,ex_Date,count,company);
                    printf("\nDon\n");
                    printf("\n ===============================================================\n");

                }
                else
                {
                    printf("\n ===============================================================\n");

                    printf("\nDon\n");
                    printf("\n ===============================================================\n");

                }
            }
            break;
        case 4:
            printf("\n ===============================================================\n");

            printf("Enter the category\n");
            scanf("%s",category);
            printf("Mdes that have same category \n");
            sameCategory(root,category);
            printf("\n ===============================================================\n");


            break;
        case 5:
            printf("\n ===============================================================\n");

            printf("Enter the disease \n");
            scanf("%s",indication);
            printf("Mdes that have same disease \n");
            sameDisease(root,indication);
            printf("\n ===============================================================\n");

            break;
        case 6:
            printf("\n ===============================================================\n");

            printf("Enter the name of meds \n");
            scanf("%s",name);
            root = delete_Meds(root,name);
            pre_Print(root);

            printf("\n ===============================================================\n");
            break;
        case 7:
            printf("\n ===============================================================\n");

            printf("Enter the name of company\n");
            getchar();
            gets(company);
            root=deleteUesCompanyInfo(root,root,company);
            pre_Print(root);
            printf("\n ===============================================================\n");
            break;
        case 8:
            printf("\n ===============================================================\n");

            writeInFile(root);
            printf("\nDon\n");
            printf("\n ===============================================================\n");

            break;
        case 9 :
            printf("\n ===============================================================\n");

            do
            {
                printf("1) Print hashed table \n"
                       "2) Print the size of hash table\n"
                       "3) Print the used hash function \n"
                       "4) Insert a new record into the hash table\n"
                       "5) Search for a medicine \n"
                       "6) Delete a  record \n"
                       "7) Save in file Pharmacy \n"
                       "8) BACK \n"
                       "Enter your choice: ");
                scanf("%d", &choice_1);

                switch(choice_1)
                {
                case 1:
                    printHash(h);

                    break;
                case 2:
                    printf("\n ===============================================================\n ");
                    printf("\n size of table is %d\n",size);

                    break;
                case 3:
                    printf("\n ===============================================================\n");
                    printf("\n Hi(key)=[h(key)+i]mod size \n");
                    break;
                case 4:
                    printf("\n ===============================================================\n");
                    printf("Enter the information of new Meds in order name,active ingredient,category,indication,Ex Date,count,company \n");
                    scanf("%s",name);
                    scanf("%s",active_ingredient);
                    scanf("%s",category);
                    scanf("%s",indication);
                    scanf("%s",ex_Date);
                    scanf("%d",&count);
                    scanf("%s",company);
                    insertHash(h,name,active_ingredient,category,indication,ex_Date,count,company);

                    printf("\nDon\n");
                    printf("\n ===============================================================\n");
                    break;
                case 5:
                    printf("\n ===============================================================\n");
                    printf("Enter the name of meds \n");
                    scanf("%s",name);
                    SearchHash(h,name);
                    printf("\n ===============================================================\n");
                    break;
                case 6:
                    printf("\n ===============================================================\n");
                    printf("Enter the name of meds \n");
                    scanf("%s",name);
                    deleteHash(h,name);
                    printf("\n ===============================================================\n");
                    break;
                case 7:
                    printf("\n ===============================================================\n");
                    writeInFileHash(h);
                    printf("\nDon\n");
                    printf("\n ===============================================================\n");
                    break;


                }
            }
            while(choice_1 != 8);

            printf("\n ===============================================================\n");
            break;


        }
    }
    while(choice != 10);
    printf("\n ===============================================================\n");
    printf("Alhamdulillah");





    return 0;
}
