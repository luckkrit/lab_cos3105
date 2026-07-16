// entry.c
#include <newt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#define PAD_Y 2
#define PAD_X 2

int main(void)
{

    int cols, rows;
    int X = 1, Y = 1;
    newtComponent form,
        labelFirstName, entryFirstName,
        labelLastName, entryLastName,
        labelAddress, entryAddress,
        labelPhone, entryPhone,
        labelEmail, entryEmail,
        labelSalary, entrySalary,
        labelPosition, entryPosition,
        saveButton;

    const char *firstName = NULL,
               *lastName = NULL, *address = NULL,
               *email = NULL, *phone = NULL, *salary = NULL,
               *position = NULL;

    newtInit();
    newtCls();

    newtGetScreenSize(&cols, &rows);

    newtCenteredWindow(cols - 10, rows - 10, "Employee Form");
    form = newtForm(NULL, NULL, 0);

    char *labelFirstNameText = "Enter your first name:";
    labelFirstName = newtLabel(X, Y, labelFirstNameText);
    entryFirstName = newtEntry(X + strlen(labelFirstNameText) + PAD_X, Y, "", 20, &firstName,
                               NEWT_FLAG_SCROLL | NEWT_FLAG_RETURNEXIT);
    newtFormAddComponent(form, labelFirstName);
    newtFormAddComponent(form, entryFirstName);

    char *labelLastNameText = "Enter your last name:";
    Y += PAD_Y;
    labelLastName = newtLabel(X, Y, labelLastNameText);
    entryLastName = newtEntry(X + strlen(labelLastNameText) + PAD_X, Y, "", 20, &lastName,
                              NEWT_FLAG_SCROLL | NEWT_FLAG_RETURNEXIT);
    newtFormAddComponent(form, labelLastName);
    newtFormAddComponent(form, entryLastName);

    char *labelAddressText = "Enter your address:";
    Y += PAD_Y;
    labelAddress = newtLabel(X, Y, labelAddressText);
    entryAddress = newtEntry(X + strlen(labelAddressText) + PAD_X, Y, "", 20, &address,
                             NEWT_FLAG_SCROLL | NEWT_FLAG_RETURNEXIT);
    newtFormAddComponent(form, labelAddress);
    newtFormAddComponent(form, entryAddress);

    char *labelPhoneText = "Enter your phone:";
    Y += PAD_Y;
    labelPhone = newtLabel(X, Y, labelPhoneText);
    entryPhone = newtEntry(X + strlen(labelPhoneText) + PAD_X, Y, "", 20, &phone,
                           NEWT_FLAG_SCROLL | NEWT_FLAG_RETURNEXIT);
    newtFormAddComponent(form, labelPhone);
    newtFormAddComponent(form, entryPhone);

    char *labelEmailText = "Enter your email:";
    Y += PAD_Y;
    labelEmail = newtLabel(X, Y, labelEmailText);
    entryEmail = newtEntry(X + strlen(labelEmailText) + PAD_X, Y, "", 20, &email,
                           NEWT_FLAG_SCROLL | NEWT_FLAG_RETURNEXIT);
    newtFormAddComponent(form, labelEmail);
    newtFormAddComponent(form, entryEmail);

    char *labelSalaryText = "Enter your salary:";
    Y += PAD_Y;
    labelSalary = newtLabel(X, Y, labelSalaryText);
    entrySalary = newtEntry(X + strlen(labelSalaryText) + PAD_X, Y, "", 20, &salary,
                            NEWT_FLAG_SCROLL | NEWT_FLAG_RETURNEXIT);
    newtFormAddComponent(form, labelSalary);
    newtFormAddComponent(form, entrySalary);

    char *labelPositionText = "Enter your position:";
    Y += PAD_Y;
    labelPosition = newtLabel(X, Y, labelPositionText);
    entryPosition = newtEntry(X + strlen(labelPositionText) + PAD_X, Y, "", 20, &position,
                              NEWT_FLAG_SCROLL | NEWT_FLAG_RETURNEXIT);
    newtFormAddComponent(form, labelPosition);
    newtFormAddComponent(form, entryPosition);

    Y += PAD_Y;
    saveButton = newtButton(X, Y + PAD_Y, "Ok");
    newtFormAddComponent(form, saveButton);

    newtRunForm(form);
    newtFinished();

    const char *errorText = NULL;
    if (firstName == NULL || strlen(firstName)==0)
    {
        errorText = "firstName is NULL or Empty\n";
        syscall(SYS_write, 2, errorText, strlen(errorText));
        return 1;
    }
    else if (lastName == NULL || strlen(lastName)==0)
    {
        errorText = "lastName is NULL or Empty\n";
        syscall(SYS_write, 2, errorText, strlen(errorText));
        return 1;
    }
    else if (address == NULL || strlen(address)==0)
    {
        errorText = "address is NULL or Empty\n";
        syscall(SYS_write, 2, errorText, strlen(errorText));
        return 1;
    }
    else if (phone == NULL || strlen(phone)==0)
    {
        errorText = "phone is NULL or Empty\n";
        syscall(SYS_write, 2, errorText, strlen(errorText));
        return 1;
    }
    else if (email == NULL || strlen(email)==0)
    {
        errorText = "email is NULL or Empty\n";
        syscall(SYS_write, 2, errorText, strlen(errorText));
        return 1;
    }
    else if (salary == NULL || strlen(salary)==0)
    {
        errorText = "salary is NULL or Empty\n";
        syscall(SYS_write, 2, errorText, strlen(errorText));
        return 1;
    }
    else if (position == NULL || strlen(position)==0)
    {
        errorText = "position is NULL or Empty\n";
        syscall(SYS_write, 2, errorText, strlen(errorText));
        return 1;
    }
    else
    {
        // Data is valid
        printf("%s\n", firstName);
        printf("%s\n", lastName);
        printf("%s\n", address);
        printf("%s\n", phone);
        printf("%s\n", email);
        printf("%s\n", salary);
        printf("%s\n", position);

        long fdWrite;

        fdWrite = syscall(SYS_open, "employees.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

        if (fdWrite < 0)
        {
            syscall(SYS_write, 2, "Cannot create file\n", 19);
            return 1;
        }

        // Write multiple lines
        char line[500];
        int lineSize = 0;

        strcat(line, firstName);
        strcat(line, ",");
        lineSize += strlen(firstName);
        lineSize++;

        strcat(line, lastName);
        strcat(line, ",");
        lineSize += strlen(lastName);
        lineSize++;

        strcat(line, address);
        strcat(line, ",");
        lineSize += strlen(address);
        lineSize++;

        strcat(line, phone);
        strcat(line, ",");
        lineSize += strlen(phone);
        lineSize++;

        strcat(line, email);
        strcat(line, ",");
        lineSize += strlen(email);
        lineSize++;

        strcat(line, salary);
        strcat(line, ",");
        lineSize += strlen(salary);
        lineSize++;

        strcat(line, position);
        strcat(line, "\n");
        lineSize += strlen(position);
        lineSize++;

        syscall(SYS_write, fdWrite, line, lineSize);

        syscall(SYS_close, fdWrite);
    }

    /* ต้องใช้ค่า firstName ให้เสร็จก่อนค่อย destroy form
       เพราะ newtFormDestroy จะ free memory ของ string นี้ด้วย */
    newtFormDestroy(form);
    return 0;
}