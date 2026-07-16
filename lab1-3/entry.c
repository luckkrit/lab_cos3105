#include <newt.h>
#include <stdio.h>

int main(void) {
    newtComponent form, label, entry, button;
    const char *entryValue;   // ต้องเป็น const char * (ดูหมายเหตุด้านบน)

    newtInit();
    newtCls();

    newtOpenWindow(10, 5, 42, 8, "Entry Sample");

    label  = newtLabel(1, 1, "Enter your name:");
    entry  = newtEntry(18, 1, "", 20, &entryValue,
                       NEWT_FLAG_SCROLL | NEWT_FLAG_RETURNEXIT);
    button = newtButton(17, 3, "Ok");

    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, label, entry, button, NULL);

    newtRunForm(form);
    newtFinished();

    printf("Hello, %s!\n", entryValue);

    /* ต้องใช้ค่า entryValue ให้เสร็จก่อนค่อย destroy form
       เพราะ newtFormDestroy จะ free memory ของ string นี้ด้วย */
    newtFormDestroy(form);
    return 0;
}