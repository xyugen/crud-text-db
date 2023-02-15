#include <cstdio>
#include <cstring>

typedef struct
{
    int id;
    char name[25], section[25];
    float grade;
} Student;

FILE* openFile(const char* fileName, const char* mode)
{
    FILE* fp = fopen(fileName, mode);
    if (fp == NULL) {
        printf("Failed to open file %s!\n", fileName);
    }
    return fp;
}

bool checkID(int id)
{
    FILE* fp = openFile("records.txt", "r");
    if (fp == NULL) {
        return false;
    }

    Student r;
    while(fread(&r, sizeof(r), 1, fp)) {
        if (r.id == id) {
            fclose(fp);
            return true;
        }
    }

    fclose(fp);
    return false;
}

void create(Student r)
{
    if (checkID(r.id)) {
        printf("ID already exists!\n");
        return;
    }

    FILE* fp = openFile("records.txt", "a");
    if (fp == NULL) {
        return;
    }

    fwrite(&r, sizeof(r), 1, fp);
    printf("Record successfully created!\n");

    fclose(fp);
}

void read()
{
    FILE* fp = openFile("records.txt", "r");
    if (fp == NULL) {
        return;
    }

    Student r;
    printf("ID\t\tName\t\tSection\t\tGrade\n");
    while (fread(&r, sizeof(r), 1, fp)) {
        printf("%d\t%s\t\t%s\t\t%.2f\n", r.id, r.name, r.section, r.grade);
    }
    printf("End of file.\n");

    fclose(fp);
}

void update(Student nR)
{
    FILE* fp = openFile("records.txt", "r");
    if (fp == NULL) {
        return;
    }

    FILE* temp = openFile("records.temp.txt", "w");
    if (temp == NULL) {
        return;
    }

    Student r;
    if (!checkID(nR.id)) {
        printf("Student does not exist!\n");
        return;
    }

    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.id == nR.id) {
            fwrite(&nR, sizeof(nR), 1, temp);
        } else {
            fwrite(&r, sizeof(r), 1, temp);
        }
    }

    printf("Record successfully updated!\n");

    fclose(fp);
    fclose(temp);

    remove("records.txt");
    rename("records.temp.txt", "records.txt");
}

void deleteF(int id)
{
    FILE* fp = openFile("records.txt", "r");
    if (fp == NULL) {
        return;
    }

    FILE* temp = openFile("records.temp.txt", "w");
    if (temp == NULL) {
        return;
    }

    Student r;
    if (!checkID(id)) {
        printf("Student does not exist!\n");
        return;
    }

    char c;
    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.id == id) {
            printf("Are you sure you want to delete student %s?\n"
                   "[1] Yes\n"
                   "[0] No\n", r.name);
            scanf_s(" %c", &c);

            if (c == '1') {
                printf("Student successfully deleted!\n");
            } else {
                printf("Student not deleted!\n");
                fwrite(&r, sizeof(r), 1, temp);
            }
        } else {
            fwrite(&r, sizeof(r), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("records.txt");
    rename("records.temp.txt", "records.txt");
}

void rmNewline(char* input)
{
    int len = strlen(input);
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
}

int main()
{
    int c;
    Student record;

    do {
        printf("\n\n------------------------------------\n"
               "\t\tMenu\n"
               "------------------------------------\n"
               "[1] CREATE\n"
               "[2] READ\n"
               "[3] UPDATE\n"
               "[4] DELETE\n"
               "[0] EXIT\n");
        printf("What is your choice: ");
        scanf_s("%d", &c);

        switch (c) {
            case 1:
                printf("Student ID: ");
                scanf_s("%d", &record.id);
                getchar();

                printf("Student name: ");
                fgets(record.name, 25, stdin);
                rmNewline(record.name);

                printf("Student section: ");
                fgets(record.section, 25, stdin);
                rmNewline(record.section);

                printf("Student grade: ");
                scanf_s("%f", &record.grade);

                create(record);
                break;
            case 2:
                read();
                break;
            case 3:
                printf("Student ID: ");
                scanf_s("%d", &record.id);
                getchar();

                printf("New student name: ");
                fgets(record.name, 25, stdin);
                rmNewline(record.name);

                printf("New student section: ");
                fgets(record.section, 25, stdin);
                rmNewline(record.section);

                printf("New student grade: ");
                scanf_s("%f", &record.grade);

                update(record);
                break;
            case 4:
                printf("Student ID: ");
                scanf_s("%d", &record.id);

                deleteF(record.id);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid input!\n");
                break;
        }
    } while(c != 0);
}