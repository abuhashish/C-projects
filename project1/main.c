#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char name[50];
    char gender[4];
    char dateofadmission[10];
    char dateofbirth[10];
    char illness[100];
    char city[50];
    char bloodtype[5];
    int isDeleted;
    struct node * next;
} pat;
/* A linked list node containing a string and length */
struct bucket_entry
{
    char *str;
    size_t len;
    struct bucket_entry *next;
};
typedef struct bucket_entry bucket_entry;

/* A linked list */
struct bucket
{
    bucket_entry *head;
    bucket_entry *tail;
};
typedef struct bucket bucket;
struct node* MakeEmpty(struct node*);




int main(){

    //Declaring useful variables
    int choice;
     char stname[100][40];
    struct node *l1;
    l1=MakeEmpty(NULL);

    do
    {
        //Asking the user to choose an option
        printf("----------------------------------------------------------------------------\n\n\n\n");
        printf("----------------------------------------------------------------------------\n\n");
        printf("1.Read the data of the patients from the file\n2.Sort data(radix sort)\n");
        printf("3.Add patient.\n");
        printf("4.Update patient's information.\n");
        printf("5.Delete Patient.\n");
        printf("6.Search for patients.\n");
        printf("7.List patients.\n");
        printf("8.Export Medical Report\n9.Exit and Save\n");
        printf("10.Exit\n");
        printf("Please choose an option by entering a number from 1 to 9\nEnter a number: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            read_File(l1);
            break;

        case 2:
        radixsort(l1);

            break;

        case 3:
            addpatient(l1);
            break;

        case 4:
            updatepatient(l1);
            break;

        case 5:
            softdelet(l1);
            break;

        case 6:
            search(l1);
            break;

        case 7:
             Listpatients(l1);
            break;

        case 8:
            report(l1);
            break;
        case 9:
            exitandsave(l1);


        default:
            printf("Please try again,You have to enter a number from 1 to 10 \n\n");
            break;
        }
    }
    while(choice != 10);

    return 0;
}

struct node* MakeEmpty(struct node* L){
if(L != NULL)
DeleteList( L );
L = (struct node*)malloc(sizeof(struct node));
if(L == NULL)
printf("Out of memory!\n");
L->next = NULL;
return L;
}


void add(char name[],char gender[],char dateofadmission[],char dateofbirth[],char illness[],char city[],char bloodtype[],pat* L,pat* P){
pat* temp;
temp = (pat*)malloc(sizeof(pat));
strcpy(temp->name,name);
strcpy(temp->gender,gender);
strcpy(temp->dateofadmission,dateofadmission);
strcpy(temp->dateofbirth,dateofbirth);
strcpy(temp->illness,illness);
strcpy(temp->city,city);
strcpy(temp->bloodtype,bloodtype);
temp->isDeleted=0;
temp->next = P->next;

P->next = temp;
}
void read_File(pat* l1)
{
    //Declaring the variables that will be stored
    char item[100];

    char name[50], gender[4], dateofadmission[10], dateofbirth[10], illness[100],city[50],bloodtype[5];



    FILE *read = fopen("patient.txt", "r");

    if(read == NULL)
    {
        printf("File doesn't exist in the directory!!\n\n");
        return;
    }

    //Keep reading from the file as long as the file doesn't end
    while(fgets(item, 200, read) != NULL)
    {
        //This will separate each line into 5 pieces
        char* piece = strtok(item, "#");
        for(int i = 0; i <= 6&& piece != NULL; i++)
        {
            if (i == 0)
                strcpy(name, piece);
            else if (i == 1)
               strcpy(gender,piece);
            else if (i == 2)
                strcpy(dateofadmission, piece);
            else if (i == 3)
                strcpy(dateofbirth, piece);
            else if(i==4)
                strcpy(illness, piece);

            else if(i==5)
                strcpy(city, piece);
                else
                    strcpy(bloodtype,piece);


            piece = strtok(NULL, "#");


        }


add(name,gender,dateofadmission,dateofbirth,illness,city,bloodtype,l1,l1);


    }

    fclose(read);
}

void PrintList(struct node* L){
struct node* P = L;
if( IsEmpty(L))
printf("Empty list\n");
else
do{
P=P->next;

if(P->isDeleted==0)
printf("%s  %s  %s  %s  %s  %s  %s \n", P->name,P->gender,P->dateofadmission,P->dateofbirth,P->illness,P->city,P->bloodtype);


}while( !IsLast(P, L) );
printf("\n");
}
int IsEmpty(struct node* L){
return L->next == NULL;
}
int IsLast(struct node* P, struct node* L){
    return P->next==NULL;
}
void DeleteList(struct node* L){
struct node* P;
struct node* temp;
P = L->next;
L->next = NULL;
while(P != NULL){
temp = P->next;
free(P);
P=temp;
}
}
void addpatient(pat* l1){
char name[50], gender[4], dateofadmission[10], dateofbirth[10], illness[100],city[50],bloodtype[5];

printf("please enter the name of the patient.\n");
scanf("%s",name);

printf("please enter the gender of the patient (m/f)\n");
scanf("%s",gender);

printf("please enter the date of admission\n");
scanf("%s",dateofadmission);

printf("please enter the date of birth\n");
scanf("%s",dateofbirth);

printf("please enter the illness\n");
scanf("%s",illness);

printf("please enter the city\n");
scanf("%s",city);

printf("please enter the bloodtype\n");
scanf("%s",bloodtype);


add(name,gender,dateofadmission,dateofbirth,illness,city,bloodtype,l1,l1);
}


     void report(pat *L){
FILE *f;
    f = fopen("Report.xml", "w");
    struct node* P = L;
    if( IsEmpty(L))
        printf("Empty list\n");
    else
    do{
    P=P->next;
    fprintf(f,"<<patient>\n\tname>%s</name>\n\t<gender>%s</gender>\n\t<admissionDate value=%s/>\n\t<birthDate value=%s />\n\t<diagnosis>%s</diagnosis>\n\t<city>%s</city>\n\t<bloodType>%s</bloodType>\n</patient>",P->name,P->gender,P->dateofadmission,P->dateofbirth,P->illness,P->city,P->bloodtype);
    }while( !IsLast(P, L) );
    printf("\n");
    fclose(f);
}

void PrintListcity(struct node* L){
struct node* P = L;
printf("Enter city-name:");
char x[50];
scanf("%s",&x);
if( IsEmpty(L))
printf("Empty list\n");
else
do{
P=P->next;
if(strcmp(P->city,x)==0){
        if(P->isDeleted==0)
printf("%s  %s  %s  %s  %s  %s  %s\n", P->name,P->gender,P->dateofadmission,P->dateofbirth,P->illness,P->city,P->bloodtype);

}
}while( !IsLast(P, L) );
printf("\n");
}
void PrintListgender(struct node* L){
struct node* P = L;
printf("Enter gender:");
char x[50];
scanf("%s",&x);
if( IsEmpty(L))
printf("Empty list\n");
else
do{
P=P->next;
if(strcmp(P->gender,x)==0){
        if(P->isDeleted==0)
printf("%s  %s  %s  %s  %s  %s  %s\n", P->name,P->gender,P->dateofadmission,P->dateofbirth,P->illness,P->city,P->bloodtype);
}
}while( !IsLast(P, L) );
printf("\n");
}
void PrintListDischarged(struct node* L){
struct node* P = L;

if( IsEmpty(L))
printf("Empty list\n");
else
do{
P=P->next;
if(P->isDeleted==1)
printf("%s  %s  %s  %s  %s  %s  %s\n", P->name,P->gender,P->dateofadmission,P->dateofbirth,P->illness,P->city,P->bloodtype);
}while( !IsLast(P, L) );
printf("\n");
}
void Listpatients(pat *l1){
    int x=0;
printf("1.list all patients \n2.list patients by gender\n3.list patients by city.\n4.list discharged patients.\nenter a number:");
scanf("%d",&x);
if(x==1)
PrintList(l1);
if(x==2)
PrintListgender(l1);
if(x==3)
    PrintListcity(l1);
if(x==4)
    PrintListDischarged(l1);
}
void updatepatient(pat *l1){
    int x=0;
    printf("1.update patient city\n2.update patient illness.\nEnter a number:");
    scanf("%d",&x);
    if(x==1)
        updatecity(l1);
    if(x==2)
    updateillness(l1);
}
void updatecity(pat *L){
struct node* P = L;
printf("Enter patient name:");
char x[50];
char k[50];
scanf("%s",&x);
if( IsEmpty(L))
printf("Empty list\n");
else
while(P->next!=NULL){
P=P->next;
if(strcmp(P->name,x)==0)
printf("enter the new city:");
scanf("%s",k);
strcpy(P->city,k);
printf("information is updated\n");
break;
}
}
void updateillness(pat *L){
struct node* P = L;
printf("Enter patient name:");
char x[50];
char k[50];
scanf("%s",&x);
if( IsEmpty(L))
printf("Empty list\n");
else
while(P->next!=NULL){
P=P->next;
if(strcmp(P->name,x)==0)
printf("enter the new illness:");
scanf("%s",k);
strcpy(P->illness,k);
printf("information is updated");
break;
}
}
void softdelet(pat *L){
struct node* P = L;
printf("Enter patient name:");
char x[50];
scanf("%s",&x);
if( IsEmpty(L))
printf("Empty list\n");
else
while(P->next!=NULL){
P=P->next;
if(strcmp(P->name,x)==0)
P->isDeleted=1;
printf("%d\n",P->isDeleted);
printf("patient is discharged\n");
break;
}
}
void searchbyname(pat* L){
struct node* P = L;
printf("Enter patient name:");
char x[50];
scanf("%s",&x);
if( IsEmpty(L))
printf("Empty list\n");
else
while(P->next!=NULL){
P=P->next;
if(strcmp(P->name,x)==0){
printf("that patient has been found\n");
printf("%s  %s  %s  %s  %s  %s  %s\n", P->name,P->gender,P->dateofadmission,P->dateofbirth,P->illness,P->city,P->bloodtype);
break;
}
else
    printf("the patient is not found\n");
break;
}
}
void searchbydate(pat* L){
struct node* P = L;
printf("Enter patient name:");
char x[50];
scanf("%s",&x);
if( IsEmpty(L))
printf("Empty list\n");
else
while(P->next!=NULL){
P=P->next;
if(strcmp(P->dateofbirth,x)==0){
printf("that patient has been found\n");
printf("%s  %s  %s  %s  %s  %s  %s\n", P->name,P->gender,P->dateofadmission,P->dateofbirth,P->illness,P->city,P->bloodtype);
break;
}
else
    printf("the patient is not found\n");
break;
}
}
void search(pat*l1){
int x=0;
printf("1.Search by Name \n2.search by Birth date.\n");
printf("Enter a number:");
scanf("%d",&x);
if(x!=1&&x!=2)
    printf("Error in input");
if(x==1)
searchbyname(l1);
if(x==2)
searchbydate(l1);

}

void radixsort (pat* l1) {

    struct node* s = l1->next;
   int g= lines(l1);
    int i = 0;
    char* strings[g];

    size_t len = g;

    while (s != NULL) {
        strings[i] = s->name;
        s = s->next;
        i++;
    }
  radix_sort_string(strings,len,l1,g);

}

/* Initialise buckets */
static void init_buckets(bucket *buckets)
{
    unsigned int b;
    for (b = 0; b < 256; b++) {
        buckets[b].head = NULL;
        buckets[b].tail = NULL;
    }
}

/*
 * Turn entries into a linked list of words with their lengths
 * Return the length of the longest word
 */
static size_t init_entries(char **strings, size_t len, bucket_entry *entries)
{
    unsigned int s;
    size_t maxlen = 0;
    for (s = 0; s < len; s++) {
        entries[s].str = strings[s];
        entries[s].len = strlen(strings[s]);
        if (entries[s].len > maxlen) {
            maxlen = entries[s].len;
        }
        if (s < len - 1) {
            entries[s].next = &entries[s + 1];
        }
        else {
            entries[s].next = NULL;
        }
    }
    return maxlen;
}

/* Put strings into buckets according to the character c from the right */
void bucket_strings(bucket_entry *head, bucket *buckets, unsigned int c)
{
    bucket_entry *current = head;
    while (current != NULL) {
        bucket_entry * next = current->next;
        current->next = NULL;
        int pos = current->len - 1 - c;
        unsigned char ch;
        if (pos < 0) {
            ch = 0;
        }
        else {
            ch = current->str[pos];
        }
        if (buckets[ch].head == NULL) {
            buckets[ch].head = current;
            buckets[ch].tail = current;
        }
        else {
            buckets[ch].tail->next = current;
            buckets[ch].tail = buckets[ch].tail->next;
        }
        current = next;
    }
}

/* Merge buckets into a single linked list */
bucket_entry *merge_buckets(bucket *buckets)
{
    bucket_entry *head = NULL;
    bucket_entry *tail;
    unsigned int b;
    for (b = 0; b < 256; b++) {
        if (buckets[b].head != NULL) {
            if (head == NULL) {
                head = buckets[b].head;
                tail = buckets[b].tail;
            }
            else {
                tail->next = buckets[b].head;
                tail = buckets[b].tail;
            }
        }
    }
    return head;
}





void copy_list(const bucket_entry *head, char **strings)
{
    const bucket_entry *current;
    unsigned int s;
    for (current = head, s = 0; current != NULL; current = current->next, s++) {
        strings[s] = current->str;
    }
}

void radix_sort_string(char **strings, size_t len,pat* l1,int g)
{
    size_t maxlen;
    unsigned int c;
    bucket_entry *head;
    bucket_entry *entries = malloc(len * sizeof(bucket_entry));
    bucket *buckets = malloc(256 * sizeof(bucket));
    if (!entries || !buckets) {
        free(entries);
        free(buckets);
        return;
    }
    init_buckets(buckets);
    maxlen = init_entries(strings, len, entries);
    head = &entries[0];
    /* Main loop */
    for (c = 0; c < maxlen; c++) {

        bucket_strings(head, buckets, c);

        head = merge_buckets(buckets);

        init_buckets(buckets);
    }
    /* Copy back into array */
    copy_list(head, strings);

    free(buckets);
    free(entries);

    sortednode(strings,l1,g);
}
void sortednode(char **strings,pat* l1,int g){
struct node *l2;
l2=MakeEmpty(NULL);
for(int i=g-1;i>=0;i--){
addtonewlist(l1,l2,strings,i);
}

*l1=*l2;
printf("*************the Data Is Sorted***************\n");
}

void addtonewlist(pat* l1,pat* l2,char **strings,int i){
while(l1->next!=NULL){
l1=l1->next;
if(strcmp(l1->name,strings[i])==0)
    add(l1->name,l1->gender,l1->dateofadmission,l1->dateofbirth,l1->illness,l1->city,l1->bloodtype,l2,l2);

}
}
int lines(pat* l1){
int k=0;
l1=l1->next;
while(l1!=NULL){
    l1=l1->next;
    k++;
}
return k;
}
void exitandsave(struct node* l1){
    clearfile("patient.txt");
   FILE *out_file=fopen("patient.txt","w");
while(l1->next!=NULL){
    l1=l1->next;
fprintf(out_file,"%s#%s#%s#%s#%s#%s#%s\n",l1->name,l1->gender,l1->dateofadmission,l1->dateofbirth,l1->illness,l1->city,l1->bloodtype);
}
fclose(out_file);
exit(0);
}
void clearfile(const char *filename)
{
    FILE *output = fopen(filename, "w");
    fclose(output);
}

