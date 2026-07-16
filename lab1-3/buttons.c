#include <newt.h>
#include <stdlib.h>   // NULL

int main(void) {
    newtComponent form, b1, b2;

    newtInit();
    newtCls();

    newtOpenWindow(10, 5, 40, 6, "Button Sample");

    b1 = newtButton(10, 1, "Ok");
    b2 = newtCompactButton(24, 2, "Cancel");

    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, b1, b2, NULL);

    newtRunForm(form);      // กด Tab สลับปุ่ม, Enter/Space เลือก

    newtFormDestroy(form);
    newtFinished();
    return 0;
}