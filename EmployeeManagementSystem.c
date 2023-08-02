#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct employee
{
    int id;
    char name[20];
    float salary;
    int age;
    struct employee *next;
};
struct employee *head = NULL;
struct employee *tail = NULL;
void create_department();
void insert();
void delete();
void search();
void update();
void sort();
void display();
void merge();
int main()
{
    int choice;
    while (1)
    {
        printf("\nEmployee Management System\n");
        printf("1. Create\n2. Insert\n3. Delete\n4. Search\n5. Update\n6. Sort\n7. Display\n8. Merge\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            create_department();
            break;
        case 2:
            insert();
            break;
        case 3:
            delete ();
            break;
        case 4:
            search();
            break;
        case 5:
            update();
            break;
        case 6:
            sort();
            break;
        case 7:
            display();
            break;
        case 8:
            merge();
            break;
        case 9:
            exit(0);
        default:
            printf("Invalid choice!\n");
            break;
        }
    }
}
void create_department()
{
    printf("Enter the name of the department: ");
    char dept[20];
    scanf("%s", dept);
    strcat(dept, ".dat");
    FILE *dept_file = fopen(dept, "wb");
    if (dept_file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fclose(dept_file);
    printf("Department created successfully!\n");
}
void insert()
{
    struct employee *temp = (struct employee *)malloc(sizeof(struct employee));
    printf("Enter employee id: ");
    scanf("%d", &temp->id);
    printf("Enter employee name: ");
    scanf("%s", temp->name);
    printf("Enter employee age: ");
    scanf("%d", &temp->age);
    printf("Enter employee salary: ");
    scanf("%f", &temp->salary);
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
    FILE *fp = fopen("employee.dat", "ab");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fwrite(temp, sizeof(struct employee), 1, fp);
    fclose(fp);
    printf("Employee record added successfully!\n");
}
void delete()
{
    int id;
    printf("Enter employee id to delete: ");
    scanf("%d", &id);
    struct employee *temp = head;
    struct employee *prev = NULL;
    FILE *fp = fopen("employee.dat", "r+b");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            if (prev == NULL)
            {
                head = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            if (temp == tail)
            {
                tail = prev;
            }
            free(temp);
            printf("Employee record deleted successfully!\n");
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    fclose(fp);
    fp = fopen("employee.dat", "wb");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    temp = head;
    while (temp != NULL)
    {
        fwrite(temp, sizeof(struct employee), 1, fp);
        temp = temp->next;
    }
    fclose(fp);
}
void search()
{
    int id;
    printf("Enter employee id to search: ");
    scanf("%d", &id);
    struct employee *temp = head;
    if (temp == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            printf("ID: %d\nName: %s\nSalary: %.2f\nAge: %d\n", temp->id, temp->name, temp->salary, temp->age);
            return;
        }
        temp = temp->next;
    }
    printf("Employee not found!\n");
}
void update()
{
    int id;
    printf("Enter employee id to update: ");
    scanf("%d", &id);
    struct employee *temp = head;
    FILE *fp = fopen("employee.dat", "r+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            printf("Enter new name: ");
            scanf("%s", temp->name);
            printf("Enter new age: ");
            scanf("%d", &temp->age);
            printf("Enter new salary: ");
            scanf("%f", &temp->salary);
            fseek(fp, -sizeof(struct employee), SEEK_CUR);
            fwrite(temp, sizeof(struct employee), 1, fp);
            printf("Employee record updated successfully!\n");
            break;
        }
        temp = temp->next;
    }
    fclose(fp);
    if (temp == NULL)
    {
        printf("Employee not found!\n");
    }
}
void sort()
{
    struct employee *temp1, *temp2;
    int swapped;
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    do
    {
        swapped = 0;
        temp1 = head;
        while (temp1->next != NULL)
        {
            temp2 = temp1->next;
            if (temp1->id > temp2->id)
            {
                int temp_id = temp1->id;
                temp1->id = temp2->id;
                temp2->id = temp_id;
                float temp_salary = temp1->salary;
                temp1->salary = temp2->salary;
                temp2->salary = temp_salary;
                int temp_age = temp1->age;
                temp1->age = temp2->age;
                temp2->age = temp_age;
                char temp_name[20];
                strcpy(temp_name, temp1->name);
                strcpy(temp1->name, temp2->name);
                strcpy(temp2->name, temp_name);
                swapped = 1;
            }
            temp1 = temp1->next;
        }
    } while (swapped);
    printf("List sorted successfully!\n");
}
void display()
{
    struct employee *temp = head;
    if (temp == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    printf("Employee List:\n");
    while (temp != NULL)
    {
        printf("ID: %d\nName: %s\nSalary: %.2f\nAge: %d\n", temp->id, temp -> name, temp->salary, temp->age);
        temp = temp->next;
    }
}
void merge()
{
    char dept1[20], dept2[20];
    printf("Enter the names of the two departments to merge: ");
    scanf("%s %s", dept1, dept2);
    strcat(dept1, ".dat");
    strcat(dept2, ".dat");
    FILE *dept_file1 = fopen(dept1, "rb");
    FILE *dept_file2 = fopen(dept2, "rb");
    if (dept_file1 == NULL || dept_file2 == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    struct employee *temp;
    while (fread(&temp, sizeof(struct employee), 1, dept_file2))
    {
        struct employee *new_employee = (struct employee *)malloc(sizeof(struct employee));
        memcpy(new_employee, temp, sizeof(struct employee));
        new_employee->next = NULL;
        if (head == NULL)
        {
            head = new_employee;
            tail = new_employee;
        }
        else
        {
            tail->next = new_employee;
            tail = new_employee;
        }
    
    }
    fclose(dept_file2);
    dept_file2 = fopen(dept2, "wb");
    if (dept_file2 == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fclose(dept_file2);
    printf("Departments merged successfully!\n");
}
