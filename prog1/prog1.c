#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float salary;
} Record;

// Store n records in binary file
void storeRecords(int n) {
    FILE *fp = fopen("data.bin", "wb");
    if (!fp) { perror("Error"); return; }

    for (int i = 0; i < n; i++) {
        Record r;
        printf("Enter id, name, salary: ");
        scanf("%d %s %f", &r.id, r.name, &r.salary);
        fwrite(&r, sizeof(Record), 1, fp);
    }
    fclose(fp);
}

// Get mth record (1-based) using fseek
void getRecord(int m) {
    FILE *fp = fopen("data.bin", "rb");
    if (!fp) { perror("Error"); return; }

    Record r;
    fseek(fp, (m - 1) * sizeof(Record), SEEK_SET);
    if (fread(&r, sizeof(Record), 1, fp))
        printf("ID: %d, Name: %s, Salary: %.2f\n", r.id, r.name, r.salary);
    else
        printf("Record not found.\n");
    fclose(fp);
}

// Delete mth record by rewriting file without it
void deleteRecord(int m) {
    FILE *fp = fopen("data.bin", "rb");
    FILE *tmp = fopen("temp.bin", "wb");
    if (!fp || !tmp) { perror("Error"); return; }

    Record r;
    int pos = 1;
    while (fread(&r, sizeof(Record), 1, fp)) {
        if (pos != m)
            fwrite(&r, sizeof(Record), 1, tmp);
        pos++;
    }
    fclose(fp); fclose(tmp);
    remove("data.bin");
    rename("temp.bin", "data.bin");
    printf("Record %d deleted.\n", m);
}

int main() {
    int n, m;
    printf("How many records? ");
    scanf("%d", &n);
    storeRecords(n);

    printf("Which record to retrieve? ");
    scanf("%d", &m);
    getRecord(m);

    printf("Which record to delete? ");
    scanf("%d", &m);
    deleteRecord(m);

    return 0;
}