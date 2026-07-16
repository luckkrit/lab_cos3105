#include <newt.h>
#include <unistd.h>

int main(void) {
    newtComponent form, scale, label;
    int i;

    newtInit();
    newtCls();

    newtCenteredWindow(40, 5, "Working...");

    label = newtLabel(1, 1, "Copying file:");
    scale = newtScale(1, 3, 36, 100);   // เต็มที่ 100

    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, label, scale, NULL);
    newtDrawForm(form);                 // วาด form โดยไม่รอ input

    for (i = 0; i <= 100; i += 5) {
        newtScaleSet(scale, i);
        newtRefresh();                  // ต้อง refresh เอง เพราะไม่ได้รอ input
        usleep(100000);                 // 0.1 วินาที
    }

    newtFormDestroy(form);
    newtFinished();
    return 0;
}