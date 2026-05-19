#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int id;
    char name[50];
    float marks;
};

// Function to display a record using seek position
void displayRecord(FILE *fp, long pos)
{
    struct Student s;

    // Move to required position
    fseek(fp, pos, SEEK_SET);

    // Read one record
    fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks);

    printf("\nRecord Details:\n");
    printf("ID    : %d\n", s.id);
    printf("Name  : %s\n", s.name);
    printf("Marks : %.2f\n", s.marks);
}

// Function to create array of seek positions
void createSeekPositions(FILE *fp, long positions[], int n)
{
    struct Student s;
    int i;

    rewind(fp);

    for(i = 0; i < n; i++)
    {
        // Store current position
        positions[i] = ftell(fp);

        // Read one record
        fscanf(fp, "%d %s %f", &s.id, s.name, &s.marks);
    }
}

int main()
{
    FILE *fp;
    struct Student s;

    int n, i, choice;
    long positions[100];

    // Open file in write mode
    fp = fopen("students.txt", "w");

    if(fp == NULL)
    {
        printf("File cannot be opened.\n");
        return 1;
    }

    printf("Enter number of records: ");
    scanf("%d", &n);

    // Store records in ASCII format
    for(i = 0; i < n; i++)
    {
        printf("\nEnter details for student %d\n", i + 1);

        printf("Enter ID: ");
        scanf("%d", &s.id);

        printf("Enter Name: ");
        scanf("%s", s.name);

        printf("Enter Marks: ");
        scanf("%f", &s.marks);

        // Store in text format
        fprintf(fp, "%d %s %f\n", s.id, s.name, s.marks);
    }

    fclose(fp);

    // Open file in read mode
    fp = fopen("students.txt", "r");

    if(fp == NULL)
    {
        printf("File cannot be opened.\n");
        return 1;
    }

    // Create seek positions array
    createSeekPositions(fp, positions, n);

    printf("\nSeek Positions:\n");
    for(i = 0; i < n; i++)
    {
        printf("Record %d starts at position %ld\n", i + 1, positions[i]);
    }

    // Display required record
    printf("\nEnter record number to display: ");
    scanf("%d", &choice);

    if(choice >= 1 && choice <= n)
    {
        displayRecord(fp, positions[choice - 1]);
    }
    else
    {
        printf("Invalid record number.\n");
    }

    fclose(fp);

    return 0;
}