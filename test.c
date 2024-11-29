#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define FOLDER "pdf.txt"

typedef struct{
    int Date;
    char Title[1000];
    char Category[1000];
    float Amount;
} menu;

void addfn(){
    menu exp;
    FILE* file=fopen("pdf.txt","a");
    printf("    Enter Date(ddmmyyyy): ");
    scanf("%d",&exp.Date);
    printf("    Enter Title: ");
    scanf("%s",&exp.Title);
    printf("    Enter Category: ");
    scanf("%s",&exp.Category);
    printf("    Enter Amount: ");
    scanf("%f",&exp.Amount);

    fprintf(file,"%d, %s, %s, %.2f\n",exp.Date,exp.Title,exp.Category,exp.Amount);
    fclose(file);
    printf("----Expense Added----\n");
}

void viewfn(){
    menu exp;
    FILE* file=fopen("pdf.txt","r");
    if (file == NULL) {
        printf("Error: Not found\n");
        return;
    }
    printf("\n--- Expense List ---\n");
    while (fscanf(file,"%d, %[^,], %[^,], %f\n",&exp.Date, exp.Title, exp.Category, &exp.Amount)!=EOF){
        printf("\nDate: %d\n    Title: %s\n    Category: %s\n    Amount: %.2f\n", exp.Date, exp.Title, exp.Category, exp.Amount);
    }
    printf("\n--- List Ends ---\n");
    fclose(file);
}
void find(){
    menu exp;
    FILE* file=fopen("pdf.txt","r");
    if (file == NULL) {
        printf("Error: Not found\n");
        return;
    }
    int target,found=0;
    printf("Enter the mmyyyy: ");
    scanf("%d",&target);
        printf("\n--- Expenses for %d ---\n",target);
    while (fscanf(file,"%d, %[^,], %[^,], %f\n",&exp.Date, exp.Title, exp.Category, &exp.Amount)!=EOF){
        int mmyyyy=exp.Date%1000000;
        if(mmyyyy==target){
            printf("\nDate: %d\n    Title: %s\n    Category: %s\n    Amount: %.2f\n", exp.Date, exp.Title, exp.Category, exp.Amount);
            found=1;
    }
    }
    fclose(file);
    if(!found){
        printf("No Expense");
    }
}

void update() {
    menu exp;
    FILE* file = fopen("pdf.txt", "r");
    FILE* temp = fopen("temp.txt", "w");
    if (file == NULL) {
        printf("Error: File not found.\n");
        return;
    }
    int found = 0;
    int target_date;
    char target_title[100]; // Adjust the size as per your Title field max size
    printf("Enter the date of the expense to edit (ddmmyyyy): ");
    scanf("%d", &target_date);
    printf("Enter the title of the expense to edit: ");
    scanf(" %[^\n]", target_title); // Reads the entire line including spaces

    while (fscanf(file, "%d, %[^,], %[^,], %f\n", &exp.Date, exp.Title, exp.Category, &exp.Amount) != EOF) {
        if (exp.Date == target_date && strcmp(exp.Title, target_title) == 0) {
            found = 1;
            printf("Editing record for Date: %d, Title: %s\n", target_date, exp.Title);
            printf("    Enter new Category: ");
            scanf("%s", exp.Category);
            printf("    Enter new Amount: ");
            scanf("%f", &exp.Amount);
        }
        fprintf(temp, "%d, %s, %s, %.2f\n", exp.Date, exp.Title, exp.Category, exp.Amount);
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("pdf.txt");
        rename("temp.txt", "pdf.txt");
        printf("Expense updated successfully.\n");
    } else {
        printf("Expense not found.\n");
        remove("temp.txt");
    }
}


int main() {
    int choice;
    do {
        printf("\n--- Expense Tracker ---\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Search Monthly Expenses\n");
        printf("4. Edit Expense\n");
        printf("5. Sort Expenses (1- Ascending, 2- Descending)\n");
        printf("6. Generate Percentage by Category\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addfn();
                break;
            case 2:
                viewfn();
                break;
            case 3:
                find();
                break;
            case 4:
                update();
                break;
            /*case 5:
                printf("Enter sorting order (1 for Ascending, 2 for Descending): ");
                int order;
                scanf("%d", &order);
                sortExpenses(order);
                break;
            case 6:
                generatePercentageByCategory();
                break;*/
            case 7:
                printf("Exiting Expense Tracker. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }while (choice != 7);

    return 0;
}


