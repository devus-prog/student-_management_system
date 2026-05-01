#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[50];
    float marks[3];
    float total;
};

// Calculate total marks
void calculateTotal(struct Student *s) {
    s->total = s->marks[0] + s->marks[1] + s->marks[2];
}

// Add student record
void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter marks for 3 subjects:\n");
    for (int i = 0; i < 3; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%f", &s.marks[i]);
    }

    calculateTotal(&s);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("✅ Student record added successfully!\n");
}

// Display all students
void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n===== Student Records =====\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll Number : %d", s.roll);
        printf("\nName        : %s", s.name);
        printf("\nMarks       : %.2f %.2f %.2f",
               s.marks[0], s.marks[1], s.marks[2]);
        printf("\nTotal Marks : %.2f\n", s.total);
    }

    fclose(fp);
}

// Generate rank list
void generateRankList() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s[100], temp;
    int count = 0;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    // Read records into array
    while (fread(&s[count], sizeof(struct Student), 1, fp)) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("No data available!\n");
        return;
    }

    // Sort in descending order of total marks
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (s[i].total < s[j].total) {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    // Display rank list
    printf("\n===== Rank List =====\n");

    for (int i = 0; i < count; i++) {
        printf("\nRank %d", i + 1);
        printf("\nRoll Number : %d", s[i].roll);
        printf("\nName        : %s", s[i].name);
        printf("\nTotal Marks : %.2f\n", s[i].total);
    }
}

// Main menu
int main() {
    int choice;

    do {
        printf("\n\n===== Student Management System =====");
        printf("\n1. Add Student Record");
        printf("\n2. Display All Records");
        printf("\n3. Generate Rank List");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                generateRankList();
                break;

            case 4:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 4);

    return 0;
}
