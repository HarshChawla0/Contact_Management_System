#include<stdio.h>
#include<string.h>
#include<process.h>

struct contact
{
    long ph;
    char name[20], add[20], email[30];
} list;

char query[20], name[20];

FILE *fp, *ft;

int i, ch, l, found;


void main()
{

    main:

        system("cls");    /* ************Main menu ***********************  */
        printf("\n\t **** Welcome to Contact Management System ****");
        printf("\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t[1] Add a new Contact\n\t\t[2] List all Contacts\n\t\t[3] Search for contact\n\t\t[4] Edit a Contact\n\t\t[5] Delete a Contact\n\t\t[0] Exit\n\t\t=================\n\t\t");
        printf("Enter the choice:");
        scanf("%d",&ch);


        switch(ch)
        {

            case 0:

                printf("\n\n\t\tAre you sure you want to exit?");
                break;


            // ADDING NEW CONTACTS

            case 1:

                system("cls");
                printf("\n\t\t\t================================\n\t\t\t\tADD NEW CONTACT\n\t\t\t================================\n\n");
                fp=fopen("contact.dll","a");
                for (;;)
                {
                    fflush(stdin);
                    printf("To exit press ENTER in the 'Name' input\n\nName\t: ");
                    gets(list.name);

                    if(stricmp(list.name,"")==0 || stricmp(list.name," ")==0)
                        break;
                    fflush(stdin);
                    printf("Phone\t: ");
                    scanf("%ld",&list.ph);
                    fflush(stdin);
                    printf("Address\t: ");
                    gets(list.add);
                    fflush(stdin);
                    printf("E-mail\t: ");
                    gets(list.email);
                    printf("\n");
                    fwrite(&list,sizeof(list),1,fp);
                }
                fclose(fp);
                break;


            // LIST OF CONTACTS

            case 2:

                system("cls");
                printf("\n\t\t\t================================\n\t\t\t\tLIST OF CONTACTS\n\t\t\t================================\n\n");

                for(i=65; i<=90; i++)
                {
                    fp=fopen("contact.dll","r");
                    found=0;
                    while(fread(&list,sizeof(list),1,fp))
                    {
                        if(list.name[0] == i || list.name[0] == i+32)
                        {
                            printf("\nName\t: %s\nPhone\t: %ld\nAddress\t: %s\nEmail\t: %s\n",list.name,list.ph,list.add,list.email);
                            found++;
                        }
                    }
                    if(found!=0)
                        printf("------------------------------------------------------------------------ [%c]-(%d)",i,found);
                    fclose(fp);
                }
                break;


            // SEARCHING A CONTACT

            case 3:

                do
                {
                    found=0;
                    system("cls");
                    printf("\n\t\t\t================================\n\t\t\t\tCONTACT SEARCH\n\t\t\t================================\n\nName of contact to be searched: ");
                    fflush(stdin);
                    gets(query);
                    l=strlen(query);
                    fp=fopen("contact.dll","r");
                    system("cls");
                    printf("\n\t\t\tSearch result for '%s'\n\t\t =======================================\n",query);
                    while(fread(&list,sizeof(list),1,fp))
                    {
                        for(i=0; i<l; i++)
                            name[i]=list.name[i];
                        name[l]='\0';
                        if(stricmp(name,query)==0)
                        {
                            printf("\nName\t: %s\nPhone\t: %ld\nAddress\t: %s\nE-mail\t: %s\n",list.name,list.ph,list.add,list.email);
                            found++;
                        }
                    }
                    if(found==0)
                        printf("\nNo match found!");
                    else
                        printf("\n%d match(s) found!",found);
                    fclose(fp);
                    printf("\n\n\n\t\t\t\t Try again?\n\n\t\t\t\[1] Yes\t\t\t[0] No\n\t");
                    scanf("%d",&ch);
                }while(ch==1);
                break;


            // EDIT A CONTACT

            case 4:

                system("cls");
                fp=fopen("contact.dll","r");
                ft=fopen("temp.dat","w");
                fflush(stdin);
                printf("\n\t\t\t================================\n\t\t\t\tEDIT CONTACT\n\t\t\t================================\n\nName of contact to be edited: ");
                gets(name);
                while(fread(&list,sizeof(list),1,fp))
                {
                    if(stricmp(name,list.name)!=0)
                        fwrite(&list,sizeof(list),1,ft);
                }
                fflush(stdin);
                printf("\n\n Editing '%s'\n\n",name);
                printf("Name\t: ");
                gets(list.name);
                fflush(stdin);
                printf("Phone\t: ");
                scanf("%ld",&list.ph);
                fflush(stdin);
                printf("Address\t: ");
                gets(list.add);
                fflush(stdin);
                printf("E-mail\t: ");
                gets(list.email);
                printf("\n");
                fwrite(&list,sizeof(list),1,ft);
                fclose(fp);
                fclose(ft);
                remove("contact.dll");
                rename("temp.dat","contact.dll");
                break;


            // DELETE A CONTACT

            case 5:

                system("cls");
                fflush(stdin);
                printf("\n\t\t\t================================\n\t\t\t\tDELETE CONTACT\n\t\t\t================================\n\nName of contact to be deleted: ");
                gets(name);
                fp=fopen("contact.dll","r");
                ft=fopen("temp.dat","w");
                while(fread(&list,sizeof(list),1,fp)!=0)
                    if (stricmp(name,list.name)!=0)
                        fwrite(&list,sizeof(list),1,ft);
                fclose(fp);
                fclose(ft);
                remove("contact.dll");
                rename("temp.dat","contact.dll");
                break;


            default:

               printf("\n\t\tInvalid choice");
               break;

        }

        haa:
            
            printf("\n\n\nEnter your choice:\n\n[1] Main Menu\t\t[0] Exit\n");
            scanf("%d",&ch);
            switch (ch)
            {

                case 1:   goto main;

                case 0:   break;

                default:

                    printf("Invalid choice");
                    goto haa;

            }
}