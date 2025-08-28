#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct BorrowNode {
    char studentID[MAX];
    char bookID[MAX];
    char bookTitle[MAX];
    char dateOfIssue[MAX];
    struct BorrowNode* next;
} BorrowNode;

typedef struct Department {
    char name[MAX];
    BorrowNode* head;
    struct Department* next;
} Department;

Department* deptHead = NULL;

BorrowNode* createBorrowNode(char* sid, char* bid, char* title, char* date) {
    BorrowNode* node = (BorrowNode*)malloc(sizeof(BorrowNode));
    strcpy(node->studentID, sid);
    strcpy(node->bookID, bid);
    strcpy(node->bookTitle, title);
    strcpy(node->dateOfIssue, date);
    node->next = NULL;
    return node;
}

Department* getDepartment(char* deptName) {
    Department* temp = deptHead;
    while (temp != NULL) {
        if (strcmp(temp->name, deptName) == 0)
            return temp;
        temp = temp->next;
    }

    Department* newDept = (Department*)malloc(sizeof(Department));
    strcpy(newDept->name, deptName);
    newDept->head = NULL;
    newDept->next = deptHead;
    deptHead = newDept;
    return newDept;
}

void issueBook(char* deptName, char* sid, char* bid, char* title, char* date) {
    Department* dept = getDepartment(deptName);
    BorrowNode* newNode = createBorrowNode(sid, bid, title, date);
    newNode->next = dept->head;
    dept->head = newNode;
    printf("book issued successfully.\n");
}

void returnBook(char* deptName, char* sid, char* bid) {
    Department* dept = getDepartment(deptName);
    BorrowNode* curr = dept->head;
    BorrowNode* prev = NULL;

    while (curr != NULL) {
        if (strcmp(curr->studentID, sid) == 0 && strcmp(curr->bookID, bid) == 0) {
            if (prev == NULL)
                dept->head = curr->next;
            else
                prev->next = curr->next;
            free(curr);
            printf("book returned successfully.\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf(" Book not found.\n");
}

void searchByStudent(char* deptName, char* sid) {
    Department* dept = getDepartment(deptName);
    BorrowNode* curr = dept->head;
    int found = 0;

    while (curr != NULL) {
        if (strcmp(curr->studentID, sid) == 0) {
            printf(" Book ID: %s | Title: %s | Date: %s\n",
                   curr->bookID, curr->bookTitle, curr->dateOfIssue);
            found = 1;
        }
        curr = curr->next;
    }
    if (!found)
        printf("no books found for this student in department %s.\n", deptName);
}

void displayHistory(char* sid) {
    Department* dept = deptHead;
    int found = 0;

    while (dept != NULL) {
        BorrowNode* curr = dept->head;
        while (curr != NULL) {
            if (strcmp(curr->studentID, sid) == 0) {
                printf("[Dept: %s] Book ID: %s | Title: %s | Date: %s\n",
                       dept->name, curr->bookID, curr->bookTitle, curr->dateOfIssue);
                found = 1;
            }
            curr = curr->next;
        }
        dept = dept->next;
    }

    if (!found)
        printf(" No borrowing history found for student %s.\n", sid);
}

int countTotalBooks(char* deptName) {
    int count = 0;
    if (deptName != NULL) {
        Department* dept = getDepartment(deptName);
        BorrowNode* curr = dept->head;
        while (curr != NULL) {
            count++;
            curr = curr->next;
        }
    } else {
        Department* dept = deptHead;
        while (dept != NULL) {
            BorrowNode* curr = dept->head;
            while (curr != NULL) {
                count++;
                curr = curr->next;
            }
            dept = dept->next;
        }
    }
    return count;
}

void menu() {
    printf("\n Library Borrowing System\n");
    printf("1. Issue Book\n");
    printf("2. Return Book\n");
    printf("3. Search by Student ID (Department)\n");
    printf("4. Display Full Borrowing History\n");
    printf("5. Count Total Borrowed Books\n");
    printf("0. Exit\n");
    printf("Your choice: ");
}

int main() {
    int choice;
    char sid[MAX], bid[MAX], title[MAX], date[MAX], dept[MAX];

    while (1) {
        menu();
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                printf("Enter Department: "); fgets(dept, MAX, stdin); dept[strcspn(dept, "\n")] = '\0';
                printf("Enter Student ID: "); fgets(sid, MAX, stdin); sid[strcspn(sid, "\n")] = '\0';
                printf("Enter Book ID: "); fgets(bid, MAX, stdin); bid[strcspn(bid, "\n")] = '\0';
                printf("Enter Book Title: "); fgets(title, MAX, stdin); title[strcspn(title, "\n")] = '\0';
                printf("Enter Date of Issue: "); fgets(date, MAX, stdin); date[strcspn(date, "\n")] = '\0';
                issueBook(dept, sid, bid, title, date);
                break;

            case 2:
                printf("Enter Department: "); fgets(dept, MAX, stdin); dept[strcspn(dept, "\n")] = '\0';
                printf("Enter Student ID: "); fgets(sid, MAX, stdin); sid[strcspn(sid, "\n")] = '\0';
                printf("Enter Book ID: "); fgets(bid, MAX, stdin); bid[strcspn(bid, "\n")] = '\0';
                returnBook(dept, sid, bid);
                break;

            case 3:
                printf("Enter Department: "); fgets(dept, MAX, stdin); dept[strcspn(dept, "\n")] = '\0';
                printf("Enter Student ID: "); fgets(sid, MAX, stdin); sid[strcspn(sid, "\n")] = '\0';
                searchByStudent(dept, sid);
                break;

            case 4:
                printf("Enter Student ID: "); fgets(sid, MAX, stdin); sid[strcspn(sid, "\n")] = '\0';
                displayHistory(sid);
                break;

            case 5:
                printf("Total Books Borrowed: %d\n", countTotalBooks(NULL));
                break;

            case 0:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
