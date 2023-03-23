#include <stdio.h>
#include <stdbool.h>
void menu();

typedef struct account {
    char name[50];
    char date_of_birth[11];
    unsigned int citizenship;
    char address[100];
    unsigned int phone_number;
    int age;
    bool deleted;
    int type_of_account;
    char date_of_deposit[11];
    float amount_of_interest;
    float money;
    unsigned int acc_num;
    /*1- saving 2-current 3-investment*/
} acc;
void viewlist(acc l);
void new_account(acc l);
void see(acc l);
void transact(acc l);
void edit (acc l);
void erase(acc l);
void exit();
int clear_input_buffer() {
    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n'));
    return ch;
}

int main() {


    menu();
    return 0;


}

void menu() {
    acc l;
  unsigned int option;
  printf("\n\t\t\t\tWelcome to our system\n\n");
  printf("\t\t1-to create new account please press:1 \n\t\t2-to Edit your phone number,your address or both please press:2\n\t\t3-to withdraw or deposit(transact) please press:3\n\t\t4-to delete your account please press:4\n\t\t5-to see your account information please press:5\n\t\t6-to EXIT the program please press:6 :(\n");
  scanf("%u", &option);
    switch (option) {

        case 1:
            new_account(l);
            break;
            case 2:
            edit(l);
             break;
        case 3:
            transact(l);
            break;
case 4:
erase(l);
 break;
        case 5:
            see(l);
            break;
            case 6 :
                exit();
                break;
            default:
                printf("please enter a number from 1 to 6 ");
                menu();
                break;

    }
}

void new_account(acc l) {
    FILE *accptr;
    int n;
    accptr = fopen("clients.txt", "ab");
    fseek(accptr, 0, SEEK_END);
    n = ftell(accptr);
    l.acc_num = (n / sizeof (acc)) + 1;
    printf("Please enter some of personal information to create a new account!\n");
    printf("your name!: ");
    clear_input_buffer();
    gets(l.name);
    printf("date of birth!: ");
    scanf("%s", l.date_of_birth);
    printf("Your citizenship number!: ");
    scanf("%u", &l.citizenship);
    printf("Your address!: ");
    clear_input_buffer();
    gets(l.address);
    printf("Your phone number!:+20");
    scanf("%u", &l.phone_number);
    printf("How much money you want to deposit? ");
    scanf("%f", &l.money);
    printf("What is the type of account you want?\n1-save account.\n2-current account.\n3-investment account.\n choose 1 or 2 or 3: ");
    scanf("%d", &l.type_of_account);
    fwrite(&l, sizeof (l), 1, accptr);
    printf("You're successfully created an account!\n");
    l.deleted=false;
    fclose(accptr);
    viewlist(l);
  menu();
}

void viewlist(acc l) {
    int c ;
    printf("\nyour account number is :%u\n", l.acc_num);
    printf("your account phone number is +20- :%u\n", l.phone_number);
    printf("your account address is :%s\n", l.address);
    printf("your account name is :%s\n", l.name);
}

void see(acc l) {
    FILE *accptr;
    accptr = fopen("clients.txt", "rb");
    int x, n, offset;
    x = (sizeof (acc));
    printf("enter your account number\n");
    scanf("%d", &n);
    offset = x * (n - 1);
    fseek(accptr, offset, SEEK_SET);
    fread(&l, sizeof (l), 1, accptr);

      if (l.acc_num==0){
        l.deleted=true;

      }
      if(l.deleted==false){
      printf("your account number is : %u , \nyour name is : %s , \nyour date of birth is : %s , \nyour account citizenship is : %u , \nyour account address is : %s , \nyour account phone number is : +20-%u , \nyour account balance is : %f , \n", l.acc_num, l.name, l.date_of_birth, l.citizenship, l.address, l.phone_number, l.money);
      if(l.type_of_account==1)
      {
          printf("your account type is save account.\n\n\n");
      }
      if(l.type_of_account==2)
      {
          printf("your account type is current account\n\n\n");
      }
      if(l.type_of_account==3)
      {
          printf("your account type is investment account\n\n\n");
      }
      fclose(accptr);
      menu();
      }
    else{
        printf("this account doesn't exist\n\n");
        menu();

    }


}

void transact(acc l) {
    FILE *accptr;
    accptr = fopen("clients.txt", "rb+");
    int x, n, offset;
    x = (sizeof (acc));
    printf("enter your account number\n");
    scanf("%d", &n);
    offset = x * (n - 1);
    fseek(accptr, offset, SEEK_SET);
    fread(&l, sizeof (l), 1, accptr);
    int i;
    float wit;
    float dep;
    if (l.acc_num==0){
      l.deleted=true;

    }
    if(l.deleted==false){
    do {
        printf("if you want to deposit money press '1' and to withdraw press '2'\n");
        scanf("%d", &i);
        if (i == 1) {
            printf("please enter your deposit value\n");
            scanf("%f", &dep);
            l.money = l.money + dep;
        }
        if (i == 2) {
            printf("please enter your deposit value\n");
            scanf("%f", &wit);
            if (wit > l.money) {

                printf("your balance less than this value%f", wit);
            }
            else {
                l.money = l.money - wit;
            }
        }
    } while (i != 1 && i != 2);
    fseek(accptr, offset, SEEK_SET);
    fwrite(&l, sizeof (l), 1, accptr);
    printf("your balance now is :%f\n\n", l.money);
    fclose(accptr);
          menu();

    }
    else{
      printf("this account doesn't exist \n ");
      menu();

    }
}
void edit(acc l){
  unsigned int accountnumber;
  int n,x;
  n=sizeof(l);
printf("please enter your account number\n");
scanf("%d",&accountnumber);
  x=(accountnumber-1)*n;
FILE *accptr;
accptr = fopen("clients.txt","rb+");
fseek(accptr, x , SEEK_SET);
fread(&l,n,1,accptr);
if (l.deleted==false){
  unsigned int g ;

  do{
printf("for changing your phone number please enter 1 \n for changing your address please enter 2\nfor changing both of them please enter 3 \n  ");
   scanf("%u",&g);

  if (g==1){

    printf("enter your new phone number:+20- ");
    scanf("%u",&l.phone_number);
    printf("you have successfully changed your phone number\n\n\n ");

    }
    if (g==2){
      printf("enter your new address: ");
      clear_input_buffer();
        gets(l.address);
        printf("you have successfully changed  your address\n\n\n");

      }

      if (g==3){
        printf("enter your new phone number:+20- ");
          scanf("%u",&l.phone_number);
        printf("enter your new address: ");
        clear_input_buffer();
          gets(l.address);
  printf("you have successfully changed your phone number and your address\n\n\n");
        }

      }
      while(g!=1&&g!=2&&g!=3);

      fseek(accptr,x,SEEK_SET);
      fwrite(&l,n,1,accptr);
          fclose(accptr);
        menu();
}

else {
  printf("this account doesn't exist\n ");
  menu();

}
    }
    void erase(acc l){
      unsigned int acc_num,x ;
    printf("please enter your account number to erase it : ");
    scanf("%u",&acc_num);
    x=(acc_num-1)*sizeof(l);
    FILE *accptr ;
    accptr=fopen("clients.txt","rb+");
    fseek(accptr,x,SEEK_SET);
    fread(&l,sizeof(l),1,accptr);

    if (l.acc_num==0){
      l.deleted=true;
      printf("this account doesn't exist\n ");
      menu();
    }
      else{
        l.deleted=true;
        printf("\nyour account has been deleted successfully.\n");
        fseek(accptr,x,SEEK_SET);
        fwrite(&l,sizeof(l),1,accptr);
        fclose(accptr);
       menu();
      }

    }
