#include <newt.h>
#include <stdio.h>

int main(void) {
    newtComponent form, checkbox, rb[3], button;
    char cbValue;
    int i, picked = -1;

    newtInit();
    newtCls();

    newtOpenWindow(10, 3, 40, 11, "Checkbox & Radio");

    checkbox = newtCheckbox(1, 1, "Enable verbose mode", ' ', NULL, &cbValue);

    rb[0] = newtRadiobutton(1, 3, "Round Robin",    1, NULL);   // ตัวแรก = NULL
    rb[1] = newtRadiobutton(1, 4, "FCFS",           0, rb[0]);  // ชี้ตัวก่อนหน้า
    rb[2] = newtRadiobutton(1, 5, "Priority",       0, rb[1]);

    button = newtButton(15, 7, "Ok");

    form = newtForm(NULL, NULL, 0);
    newtFormAddComponent(form, checkbox);
    for (i = 0; i < 3; i++)
        newtFormAddComponent(form, rb[i]);
    newtFormAddComponent(form, button);

    newtRunForm(form);
    newtFinished();

    /* หาว่า radio ตัวไหนถูกเลือก — ต้องทำก่อน destroy form */
    for (i = 0; i < 3; i++)
        if (newtRadioGetCurrent(rb[0]) == rb[i])
            picked = i;

    newtFormDestroy(form);

    printf("scheduler picked: %d\n", picked);
    printf("verbose: %s\n", cbValue == '*' ? "on" : "off");
    return 0;
}