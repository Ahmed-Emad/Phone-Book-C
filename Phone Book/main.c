#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char lstname[50], fstname[50], saddress[50], city[50], phoneno[50];
}phone_contact;

phone_contact contact[500];

void read(char path[], int *contactcounterptr);
void query(int contactcounter);
void add(int *contactcounter);
void delete(int *contactcounter);
void modify(int contactcounter);
void print(int contactcounter);
void save(char path[], int contactcounter);
void contactswap(phone_contact *contact1, phone_contact *contact2);
void name_alpha(phone_contact contact[], int contactcounter);
int substring(char name[], char search[]);
int fullstring(char name[], char search[]);

int main(int argc, const char * argv[])
{
    int contactcounter=0, choice=0;
    char path[100], blank[2];
    while (choice != 8) {
        do {
            choice = 0;
            printf("\nPlease Enter No to Choose:\n1- LOAD.\n2- QUERY.\n3- ADD.\n4- DELETE.\n5- MODIFY.\n6- PRINT.\n7- SAVE.\n8- QUIT.\n");
            scanf("%d", &choice);
        } while (choice!=1 && choice!=2 && choice!=3 && choice!=4 && choice!=5 && choice!=6 && choice!=7 && choice!= 8);
        switch (choice) {
            case 1:
                read(path, &contactcounter);
                printf("\nPress Enter to Continue");
                getchar();
                gets(blank);
                choice = 0;
                continue;
                
            case 2:
                query(contactcounter);
                printf("\nPress Enter to Continue");
                gets(blank);
                choice = 0;
                continue;
                
            case 3:
                add(&contactcounter);
                printf("\nPress Enter to Continue");
                getchar();
                gets(blank);
                choice = 0;
                continue;
                
            case 4:
                delete(&contactcounter);
                printf("\nPress Enter to Continue");
                getchar();
                gets(blank);
                choice = 0;
                continue;
                
            case 5:
                modify(contactcounter);
                printf("\nPress Enter to Continue");
                gets(blank);
                choice = 0;
                continue;
                
            case 6:
                print(contactcounter);
                printf("\nPress Enter to Continue");
                getchar();
                gets(blank);
                choice = 0;
                continue;
                
            case 7:
                save(path, contactcounter);
                printf("\nPress Enter to Continue");
                getchar();
                gets(blank);
                choice = 0;
                continue;
                
            case 8:
                break;
                
            default:
                break;
        }
    }
    return 0;
}

void read(char path[], int *contactcounterptr)
{
    int i, j, contactcounter=0;
    printf("Enter The Path of the File: ");
    scanf("%s", path);
    FILE *freader;
    freader = fopen(path,"r");
    if (freader != NULL){
        printf("\nFile exist !\n");
        while(!(feof(freader))){
            fscanf(freader,"%[^,], %[^,], %[^,], %[^,], %[^\n]",contact[contactcounter].fstname, contact[contactcounter].lstname, contact[contactcounter].saddress, contact[contactcounter].city, contact[contactcounter].phoneno);
            contactcounter++;
            fscanf(freader, "\n");
        }
        for (i=0; i<contactcounter; i++) {
            for (j=0; j<50; j++) {
                contact[i].fstname[j] = toupper(contact[i].fstname[j]);
                contact[i].lstname[j] = toupper(contact[i].lstname[j]);
            }
        }
        
        printf("Successfully loaded %d contacts !\n", contactcounter);
        *contactcounterptr = contactcounter;
        name_alpha(contact, contactcounter);
    }
    else
        printf("Error reading file");
    fclose(freader);
}

void query(int contactcounter)
{
    char contactsearch[50], result[contactcounter];
    int i, resultcounter=0;
    printf("\nEnter Contact Last Name to search: ");
    getchar();
    gets(contactsearch);
    for (i=0; i<50; i++) {
        contactsearch[i] = toupper(contactsearch[i]);
    }
    for (i=0; i<contactcounter; i++) {
        if (substring(contact[i].lstname, contactsearch) == 1) {
            result[resultcounter]=i;
            resultcounter++;
        }
    }
    printf("\nFound %d Matches\n", resultcounter);
    for (i=0; i<resultcounter; i++) {
        printf("\nFirst Name: %s,  Last Name: %s, Street Address: %s, City: %s, Phone No: %s \n", contact[result[i]].fstname, contact[result[i]].lstname, contact[result[i]].saddress, contact[result[i]].city, contact[result[i]].phoneno);
    }
}

void add(int *contactcounter)
{
    int i;
    printf("Enter new Contact's First Name: ");
    scanf("%s", contact[*contactcounter].fstname);
    for (i=0; i<50; i++)
        contact[*contactcounter].fstname[i] = toupper(contact[*contactcounter].fstname[i]);
    printf("Enter new Contact's Last Name: ");
    getchar();
    scanf("%s", contact[*contactcounter].lstname);
    for (i=0; i<50; i++)
        contact[*contactcounter].lstname[i] = toupper(contact[*contactcounter].lstname[i]);
    printf("Enter new Contact's Street Address: ");
    getchar();
    gets(contact[*contactcounter].saddress);
    printf("Enter new Contact's City: ");
    scanf("%s", contact[*contactcounter].city);
    printf("Enter new Contact Phone NO: ");
    scanf("%s", contact[*contactcounter].phoneno);
    printf("Contact added successfully");
    *contactcounter = *contactcounter + 1;
}

void delete(int *contactcounter)
{
    char fst_name_search[50], lst_name_search[50], result[*contactcounter];
    int i, j, choice = 0, resultcounter=0, deletecounter=0;
    printf("\nEnter Contact First Name to search: ");
    getchar();
    gets(fst_name_search);
    printf("\nEnter Contact Last Name to search: ");
    gets(lst_name_search);
    for (i=0; i<50; i++) {
        fst_name_search[i] = toupper(fst_name_search[i]);
        lst_name_search[i] = toupper(lst_name_search[i]);
    }
    for (i=0; i<*contactcounter; i++) {
        if ((fullstring(contact[i].fstname, fst_name_search) == 1) && (fullstring(contact[i].lstname, lst_name_search) == 1)) {
            result[resultcounter]=i;
            resultcounter++;
        }
    }
    printf("\nFound %d Matches\n", resultcounter);
    if (resultcounter == 1) {
        printf("\nThis Contact is deleted:\nFirst Name: %s,  Last Name: %s, Street Address: %s, City: %s, Phone No: %s\n", contact[result[0]].fstname, contact[result[0]].lstname, contact[result[0]].saddress, contact[result[0]].city, contact[result[0]].phoneno);
        for ( i = result[0] ; i < *contactcounter-1 ; i++ )
            contact[i] = contact[i+1];
        strcpy(contact[*contactcounter-1].fstname, "zzzzzzzzzzzzzzzzzzzz");
        *contactcounter = *contactcounter-1;
    }
    else if (resultcounter>1){
        printf("1- Delete All");
        for (i=0; i<resultcounter; i++) {
            printf("\n%d- Delte : First Name: %s,  Last Name: %s, Street Address: %s, City: %s, Phone No: %s", i+2, contact[result[i]].fstname, contact[result[i]].lstname, contact[result[i]].saddress, contact[result[i]].city, contact[result[i]].phoneno);
        }
        do {
            printf("\nEnter Choose Contact to Delete: ");
            scanf("%d", &choice);
        } while (choice > i+1 && (choice<1));
        if (choice == 1) {
            printf("All These Contacts are Deleted:\n");
            for (i=0; i<resultcounter; i++) {
                printf("First Name: %s,  Last Name: %s, Street Address: %s, City: %s, Phone No: %s\n", contact[result[i]].fstname, contact[result[i]].lstname, contact[result[i]].saddress, contact[result[i]].city, contact[result[i]].phoneno);
            }
            for (i=0 ; i < resultcounter; i++) {
                for ( j = result[i]- deletecounter; j < *contactcounter-1 ; j++ )
                    contact[j] = contact[j+1];
                strcpy(contact[*contactcounter-1].fstname, "zzzzzzzzzzzzzzzzzzzz");
                *contactcounter = *contactcounter-1;
                deletecounter++;
            }
        }
        else{
            for (i=0 ; i <= resultcounter; i++) {
                if (i == choice-2) {
                    printf("\nThis Contact is deleted:\nFirst Name: %s,  Last Name: %s, Street Address: %s, City: %s, Phone No: %s\n", contact[result[i]].fstname, contact[result[i]].lstname, contact[result[i]].saddress, contact[result[i]].city, contact[result[i]].phoneno);
                    for ( i = result[i] ; i < *contactcounter-1 ; i++ )
                        contact[i] = contact[i+1];
                    strcpy(contact[*contactcounter-1].fstname, "zzzzzzzzzzzzzzzzzzzz");
                    *contactcounter = *contactcounter-1;
                }
            }
        }
    }
}

void modify(int contactcounter)
{
    char contactsearch[50], result[contactcounter];
    int i, j, choice=0, resultcounter=0;
    printf("\nEnter Contact Last Name to search: ");
    getchar();
    gets(contactsearch);
    for (i=0; i<50; i++) {
        contactsearch[i] = toupper(contactsearch[i]);
    }
    for (i=0; i<contactcounter; i++) {
        if (substring(contact[i].lstname, contactsearch) == 1) {
            result[resultcounter]=i;
            resultcounter++;
        }
    }
    printf("\nFound %d Matches\n", resultcounter);
    for (i=0; i<resultcounter; i++) {
        printf("%d- First Name: %s,  Last Name: %s, Street Address: %s, City: %s, Phone No: %s\n", i+1, contact[result[i]].fstname, contact[result[i]].lstname, contact[result[i]].saddress, contact[result[i]].city, contact[result[i]].phoneno);
    }
    do {
        printf("\nChoose Contact to Modify: ");
        scanf("%d", &choice);
    } while (choice > i && (choice<1));
    for (i=0; i<=resultcounter; i++) {
        if (i == choice-1) {
            printf("Enter New First Name: ");
            getchar();
            gets(contact[result[i]].fstname);
            printf("Enter New Last Name: ");
            gets(contact[result[i]].lstname);
            for (j=0; j<50; j++) {
                contact[result[i]].fstname[j] = toupper(contact[result[i]].fstname[j]);
                contact[result[i]].lstname[j] = toupper(contact[result[i]].lstname[j]);
            }
            printf("Enter New Street  Address: ");
            gets(contact[result[i]].saddress);
            printf("Enter New City: ");
            gets(contact[result[i]].city);
            printf("Enter New First Phone No: ");
            gets(contact[result[i]].phoneno);
        }
    }
}

void print(int contactcounter)
{
    name_alpha(contact, contactcounter);
    int i;
    printf("\nYou Have %d Contacts in Your PhoneBook.\n", contactcounter);
    for (i=0; i<contactcounter; i++) {
        printf("\nFirst Name: %s, Last Name: %s, Street Address: %s, City: %s, Phone NO: %s \n", contact[i].fstname, contact[i].lstname, contact[i].saddress, contact[i].city, contact[i].phoneno);
    }
    
}

void save(char path[], int contactcounter)
{
    FILE * freader;
    freader = fopen(path,"w");
    name_alpha(contact, contactcounter);
    int i;
    if (freader != NULL) {
        for (i = 0; i < contactcounter; i++)
            fprintf(freader,"%s, %s, %s, %s, %s\n", contact[i].fstname, contact[i].lstname, contact[i].saddress, contact[i].city, contact[i].phoneno);
        printf("Saved Successfully %d Contacts", contactcounter);
        fclose(freader);
    }
    else
        printf("Not Saved");
}

int substring(char name[], char search[])
{
    int i, j=0, f, yes=0;
    for (i=0; i<strlen(name); i++) {
        if (search[j] == name[i]) {
            yes=1;
            for (f=0; f<strlen(search); f++) {
                if (search[j+f] != name[i+f]) {
                    yes = 0;
                }
            }
            if (yes==1)
                break;
        }
    }
    return yes;
}

int fullstring(char name[], char search[])
{
    int i, j=0, yes=0;
    if (strlen(name) == strlen(search)){
        yes = 1;
        for (i=0; i<strlen(name); i++) {
            if (search[i] != name[j]) {
                yes = 0;
            }
            j++;
        }
    }
    return yes;
}

void name_alpha(phone_contact contact[], int contactcounter)
{
    int i,j;
    for(i=0;i<contactcounter;i++)
    {
        for(j=0;j<contactcounter;j++)
        {
            if (strcmp(contact[j].fstname, contact[i].fstname) > 0 )
                contactswap(&contact[i], &contact[j]);
            else if (strcmp(contact[j].fstname, contact[i].fstname) == 0 ){
                if (strcmp(contact[j].lstname, contact[i].lstname) > 0 )
                    contactswap(&contact[i], &contact[j]);
            }
        }
    }
    
}

void contactswap(phone_contact *contact1, phone_contact *contact2)
{
    phone_contact contact3 = *contact1;
    *contact1 = *contact2;
    *contact2 = contact3;
}