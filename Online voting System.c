
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

struct voter{
    char name[50];
    char dob[20];
    char address[100];
    char voting_area[50];
    char voting_position[50];
    char id[10];
    int age;
    int voted;
};

void register_voter(){
    struct voter v;
    FILE *fp;

    printf("\nEnter Your Name: ");
    gets(v.name);
    printf("\nEnter Your Date of Birth (dd/mm/yyyy): ");
    gets(v.dob);
    printf("\nEnter Your Address: ");
    gets(v.address);
    printf("\nEnter Your Voting Area: ");
    gets(v.voting_area);
    printf("\nEnter Your Voting Position: ");
    gets(v.voting_position);
    printf("\nEnter Your Age: ");
    scanf("%d",&v.age);
    fflush(stdin);

    //check age of voter
    if(v.age < 18){
        printf("\nSorry, You are not eligible to vote.");
        return;
    }

    //generate unique voter ID
    srand(time(0));
    int r = rand();
    sprintf(v.id,"%d",r);

    //store the data in file
    fp = fopen("voters.txt","a");
    fprintf(fp,"%s,%s,%s,%s,%s,%s,%d,%d\n",v.name,v.dob,v.address,v.voting_area,v.voting_position,v.id,v.age,0);
    fclose(fp);

    printf("\nRegistration Successful. Your voter ID is: %d", r);
}

void login(){
    char id[10];
    struct voter v;
    FILE *fp;
    int found = 0;

    printf("\nEnter Your Voter ID: ");
    gets(id);

    //search for voter ID in file
    fp = fopen("voters.txt","r");
    while(fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d\n",v.name,v.dob,v.address,v.voting_area,v.voting_position,v.id,&v.age,&v.voted)!=EOF){
        if(strcmp(v.id,id)==0){
            found = 1;
            break;
        }
    }
    fclose(fp);

    if(found == 0){
        printf("\nInvalid Voter ID.");
        return;
    }

    //check if the voter has already voted
    if(v.voted == 1){
        printf("\nYou have already voted.");
        return;
    }

    //display the available candidates for the voter's area and position
    printf("\nWelcome %s.",v.name);
    printf("\nAvailable Candidates:");
    if(1){
        printf("\n1. Group1");
        printf("\n2. Group2");
        printf("\nEnter Your Choice: ");
        int choice;
        scanf("%d",&choice);
        fflush(stdin);

        //store the vote and update the database
        if(choice == 1 || choice == 2){
            fp = fopen("voters.txt","r+");
            while(fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d\n",v.name,v.dob,v.address,v.voting_area,v.voting_position,v.id,&v.age,&v.voted)!=EOF){
                if(strcmp(v.id,id)==0){
                    v.voted = 1;
                    fseek(fp,-2,SEEK_CUR);
                    fprintf(fp,"%d",v.voted);
                    break;
                }
            }
            fclose(fp);

            printf("\nThank You for Voting.");
        }
        else{
            printf("\nInvalid Choice.");
            return;
        }
    }
    else{
        printf("\nNo Candidates Available for Your Area and Position.");
        return;
    }
}

int main(){
    int choice;

    while(1){
        printf("\n\n**********College Online Voting System**********");
        printf("\n1. Register Voter");
        printf("\n2. Login");
        printf("\n3. Exit");
        printf("\nEnter Your Choice: ");
        scanf("%d",&choice);
        fflush(stdin);

        switch(choice){
            case 1: register_voter();
                    break;
            case 2: login();
                    break;
            case 3: exit(0);
            default: printf("\nInvalid Choice.");
        }
    }

    return 0;
}
