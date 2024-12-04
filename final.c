#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define FOLDER "view.txt"

typedef struct{
    int Date;
    char Title[1000];
    char Category[1000];
    float Amount;
} menu;

float salary = 0;
float remainingBalance = 0;

void setSalary(){
    printf("Enter your Salary: ");
    scanf("%f", &salary);
    remainingBalance = salary;
    printf("You Have %.2f amount with you\n", salary);
}

void addfn(){
    menu exp;
    FILE* file=fopen("view.txt","a");
    printf("    Enter Date(ddmmyyyy): ");
    scanf("%d",&exp.Date);
    printf("    Enter Title: ");
    scanf("%s",exp.Title);
    printf("    Enter Category: ");
    scanf("%s",exp.Category);
    printf("    Enter Amount: ");
    scanf("%f",&exp.Amount);

    if(exp.Amount>remainingBalance){
        printf("Warning: Expense exceeds your remaining balance!\n");
        remainingBalance -= exp.Amount;
    }else{
        remainingBalance -= exp.Amount;
    }

    fprintf(file,"%d, %s, %s, %.2f\n",exp.Date,exp.Title,exp.Category,exp.Amount);
    fclose(file);
    printf("----Expense Added----\n");
    printf("Remaining Balance : %.2f\n", remainingBalance);
}

void viewfn(){
    menu exp;
    FILE* file=fopen("view.txt","r");
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
    FILE* file=fopen("view.txt","r");
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
    FILE* file = fopen("view.txt", "r");
    FILE* temp = fopen("temp.txt", "w");
    if (file == NULL) {
        printf("Error: File not found.\n");
        return;
    }
    int found = 0;
    int target_date;
    char target_title[100];
    printf("Enter the date of the expense to edit (ddmmyyyy): ");
    scanf("%d", &target_date);
    printf("Enter the title of the expense to edit: ");
    scanf(" %[^\n]", target_title);

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
        remove("view.txt");
        rename("temp.txt", "view.txt");
        printf("Expense updated successfully.\n");
    } else {
        printf("Expense not found.\n");
        remove("temp.txt");
    }
}

void generatePercentageByAllCategories() {
    typedef struct {
        char Title[100];
        float Amount;
    } TitleInfo;

    typedef struct {
        char Category[100];
        float TotalAmount;
        TitleInfo Titles[100];
        int TitleCount;
    } CategoryInfo;

    CategoryInfo categories[100];
    int category_count = 0;
    float total = 0;w
    menu exp;

    FILE *file = fopen("view.txt", "r");
    if (file == NULL) {
        printf("No expenses found.\n");
        return;
    }

    while (fscanf(file, "%d, %[^,], %[^,], %f\n", &exp.Date, exp.Title, exp.Category, &exp.Amount) != EOF) {
        total += exp.Amount;

        int foundCategory = -1;
        for (int i = 0; i < category_count; i++) {
            if (strcmp(categories[i].Category, exp.Category) == 0) {
                foundCategory = i;
                break;
            }
        }

        if (foundCategory == -1) {
            strcpy(categories[category_count].Category, exp.Category);
            categories[category_count].TotalAmount = exp.Amount;
            categories[category_count].TitleCount = 0;

            strcpy(categories[category_count].Titles[0].Title, exp.Title);
            categories[category_count].Titles[0].Amount = exp.Amount;
            categories[category_count].TitleCount++;
            category_count++;
        } else {

            categories[foundCategory].TotalAmount += exp.Amount;

            int foundTitle = -1;
            for (int j = 0; j < categories[foundCategory].TitleCount; j++) {
                if (strcmp(categories[foundCategory].Titles[j].Title, exp.Title) == 0) {
                    foundTitle = j;
                    break;
                }
            }

            if (foundTitle == -1) {
 
                int titleIndex = categories[foundCategory].TitleCount;
                strcpy(categories[foundCategory].Titles[titleIndex].Title, exp.Title);
                categories[foundCategory].Titles[titleIndex].Amount = exp.Amount;
                categories[foundCategory].TitleCount++;
            } else {

                categories[foundCategory].Titles[foundTitle].Amount += exp.Amount;
            }
        }
    }
    fclose(file);

    if (total > 0) {
        printf("Category-wise percentage breakdown:\n");
        for (int i = 0; i < category_count; i++) {
            float categoryPercentage = (categories[i].TotalAmount / total) * 100;
            printf("%s: %.2f%%\n", categories[i].Category, categoryPercentage);

            for (int j = 0; j < categories[i].TitleCount; j++) {
                float titlePercentage = (categories[i].Titles[j].Amount / categories[i].TotalAmount) * 100;
                printf("    %s: %.2f%%\n", categories[i].Titles[j].Title, titlePercentage);
            }
        }
    } else {
        printf("No expenses to calculate percentage.\n");
    }
}

int compareCategory(const void *a, const void *b)
{
    menu *expA = (menu *)a;
    menu *expB = (menu *)b;
    return strcmp(expA->Category, expB->Category);
}

void ascendingorder()
{
    menu exparr[1000];
    FILE *file = fopen("view.txt", "r");
    if(file == NULL){
        printf("Error: File not found.\n");
        return;
    }
    int count = 0;
    
    while(fscanf(file, "%d, %[^,], %[^,], %f\n", &exparr[count].Date, exparr[count].Title, exparr[count].Category, &exparr[count].Amount) != EOF){
        count++;
    }
    fclose(file);
    qsort(exparr, count, sizeof(menu), compareCategory);
    printf("\n--- Sorted Expenses by Category ---\n");
    for (int i = 0; i < count; i++){
        printf("\nDate: %d\n Title: %s\n Category: %s\n Amount: %.2f\n", exparr[i].Date, exparr[i].Title, exparr[i].Category, exparr[i].Amount);
    }
    printf("\n--- Sorting Complete ---\n");
}



int main() {
    int choice;
    setSalary();
    do {
        printf("\n--- Expense Tracker ---\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Search Monthly Expenses\n");
        printf("4. Edit Expense\n");
        printf("5. Sort Expenses\n");
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
            case 5:
                ascendingorder();
                break;
            case 6:
                generatePercentageByAllCategories();
                break;
            case 7:
                printf("Exiting Expense Tracker. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }while (choice != 7);

    return 0;
}


