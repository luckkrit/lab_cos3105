// entry.c
#include <newt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#define PAD_Y 2
#define PAD_X 2
#define MAX_QUESTIONS 7

int main(void) {

    int cols, rows;
    int X = 1, Y = 1;
    newtComponent form, saveButton;
    newtComponent entries[MAX_QUESTIONS*2];
    const char *values[MAX_QUESTIONS];
    memset(values, NULL, MAX_QUESTIONS);

    newtInit();
    newtCls();

    newtGetScreenSize(&cols, &rows);

    newtCenteredWindow(cols-10, rows-10, "Employee Form");
    form = newtForm(NULL, NULL, 0);


    char buffer[100];
    // clear buffer
    memset(buffer, 0, sizeof(buffer));
    char ch;
    long fd;
    long bytes;
    int pos = 0;
    int line_num = 0;

    fd = syscall(SYS_open, "questions.txt", O_RDONLY);

    if (fd < 0) {
        syscall(SYS_write, 2, "Error opening file\n", 19);
        return 1;
    }

    // Read character by character
    while ((bytes = syscall(SYS_read, fd, &ch, 1)) > 0) {

        
        if (ch == '\n') {
            
            
            // Read Line
            if(line_num < MAX_QUESTIONS){
                
                char labelText[pos-1]; 
                strcpy(labelText, buffer);                  
                entries[line_num] = newtLabel(X, Y, labelText);
                newtFormAddComponent(form, entries[line_num]);
                
                entries[line_num+1] = newtEntry(X + strlen(labelText) + PAD_X, Y, "", 20, &values[line_num],
                        NEWT_FLAG_SCROLL | NEWT_FLAG_RETURNEXIT);
                newtFormAddComponent(form, entries[line_num+1]);
                
                Y += PAD_Y;
                
            }
            // clear buffer
            memset(buffer, 0, sizeof(buffer));
            pos = 0;
            line_num++;
        } else {
            buffer[pos++] = ch;
        }
    }

    
    syscall(SYS_close, fd);

    // Add Save Button
    Y += PAD_Y;
    saveButton = newtButton(X, Y, "Ok");
    newtFormAddComponent(form, saveButton);
    
    newtRunForm(form);
    newtFinished();


    for(int i=0;i<sizeof(values)/sizeof(values[0]);i++){
        if(values[i]==NULL){
            switch (i)
            {
            case 0:
                
                break;
            
            default:
                break;
            }            
            
            break;
        }
    }

    long fdWrite;

    fdWrite = syscall(SYS_open, "employees.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fdWrite < 0) {
        syscall(SYS_write, 2, "Cannot create file\n", 19);
        return 1;
    }

    // Write multiple lines
    for(int i=0;i<sizeof(values)/sizeof(values[0]);i++){
        syscall(SYS_write, fdWrite, values[i], strlen(values[i]));
        if(i<sizeof(values)/sizeof(values[0])-1){
            syscall(SYS_write, fdWrite, ",", 1);    
        }                
    }
    syscall(SYS_write, fdWrite, "\n", 1);
    syscall(SYS_close, fdWrite);

    destroy_form:
    /* ต้องใช้ค่า firstName ให้เสร็จก่อนค่อย destroy form
       เพราะ newtFormDestroy จะ free memory ของ string นี้ด้วย */
        newtFormDestroy(form);
    return 0;
}