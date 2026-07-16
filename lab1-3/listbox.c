#include <newt.h>
#include <stdio.h>
#include <stdint.h>

int main(void) {
    newtComponent form, list, button;
    intptr_t choice;

    newtInit();
    newtCls();

    newtCenteredWindow(30, 12, "Main Menu");

    list = newtListbox(1, 1, 6, NEWT_FLAG_BORDER | NEWT_FLAG_RETURNEXIT);
    newtListboxAppendEntry(list, "Show processes",  (void *) 1);
    newtListboxAppendEntry(list, "Show memory",     (void *) 2);
    newtListboxAppendEntry(list, "Show disk usage", (void *) 3);
    newtListboxAppendEntry(list, "Exit",            (void *) 4);

    button = newtButton(10, 8, "Ok");

    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, list, button, NULL);

    newtRunForm(form);

    choice = (intptr_t) newtListboxGetCurrent(list);

    newtFormDestroy(form);
    newtFinished();

    printf("You picked menu item: %ld\n", (long) choice);
    return 0;
}