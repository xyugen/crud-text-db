#include <stdio.h>
#include <string.h>

const char* FORMAT_IN = "%d, %[^,], %[^,], %d";
const char* FORMAT_OUT = "%d, %s, %s, %d\n";
const char* FORMAT_READ = "%d\t%s\t\t%s\t\t%d\n";

// RECORD STRUCTURE
typedef struct
{
    int id;
    char lastName[25], firstName[25];
    int age;
} Student;

// CRUD FUNCTIONS
void create(Student record)
{
    FILE *fp;

    fp = fopen("records.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    } else {
        printf("Record stored successfully.\n");
    }

    fprintf(fp, FORMAT_OUT, record.id, record.lastName, record.firstName, record.age);
    fseek(fp, 0, SEEK_SET);

    fclose(fp);
}

void read()
{
    FILE *fp;
    Student r;

    int oid = NULL; // old id

    fp = fopen("records.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("ID\tLast Name\tFirst Name\tAge\n");
    while (fscanf(fp, FORMAT_IN, &r.id, r.lastName, r.firstName, &r.age) != EOF) {
        if (r.id == oid) // check if it's repeating
        {
            printf("Infinite loop error!");
            return;
        }
        printf(FORMAT_READ, r.id, r.lastName, r.firstName, r.age);
        oid = r.id;
    }

    fclose(fp);
}

void update() {}

void deleteF() {}

// Additional
void rmNewline(char* input)
{
    int length = strlen(input);
    if (input[length - 1] == '\n')
    {
        input[length - 1] = '\0';
    }
}

void about()
{
    printf("\n\n-----------------------------------------"
           "\n|\t\tAbout\t\t\t|"
           "\n-----------------------------------------"
           "\n| A program created by Alex Arias for\t|"
           "\n| their Computer Programming 2 subject.\t|"
           "\n-----------------------------------------");
}

// BETA
/* void menu(char title[12], char text[99])
{
    printf("\n\n-----------------------------------------"
           "\n|\t\t%s\t\t"
           "\"\\n\\n-----------------------------------------\""
           "|\t")
} */

// MAIN FUNCTION

int main()
{
    int c;
    do
    {
        // MAIN MENU
        printf("\n\n-----------------------------------------"
               "\n|\t\tMain Menu\t\t|");
        printf("\n-----------------------------------------"
               "\n|\t1. CREATE\t\t\t|"
               "\n|\t2. READ\t\t\t\t|"
               "\n|\t3. UPDATE\t\t\t|"
               "\n|\t4. DELETE\t\t\t|"
               "\n|\t5. ABOUT\t\t\t|"
               "\n|\t0. EXIT\t\t\t\t|"
               "\n-----------------------------------------");

        printf("\nENTER YOUR CHOICE: ");
        scanf("%d", &c);

        switch (c)
        {
            case 1:
                Student student1;

                printf("Type in the Student id: ");
                scanf("%d", &student1.id);
                getchar();

                printf("Type in the student's last name: ");
                fgets(student1.lastName, 25, stdin);
                rmNewline(student1.lastName);

                printf("Type in the student's  first name: ");
                fgets(student1.firstName, 25, stdin);
                rmNewline(student1.firstName);

                printf("Type in the student's age: ");
                scanf("%d", &student1.age);

                create(student1);
                break;
            case 2:
                read();
                break;
            case 3:
                update();
                break;
            case 4:
                deleteF();
                break;
            case 5:
                about();
                break;
            case 0:
                printf("Exiting...");
                break;
            default:
                printf("Invalid input.");
                break;
        }
    } while (c != 0);

    return 0;
}