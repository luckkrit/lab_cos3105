#include <newt.h>
#include <stdlib.h>

int main(void) {
    // 1. เริ่มต้นระบบ Newt
    newtInit();
    newtCls();

    // กำหนดข้อความยาวๆ สำหรับแสดงผล
    const char *long_text = 
        "Welcome to the Newt Textbox demo. Newt is a programming library for text-mode user interfaces. "
        "It is based on the slang library. This specific component is a Textbox, which is incredibly useful "
        "for displaying long paragraphs of text, readmes, licenses, or logs in a terminal window. "
        "Notice how the text wraps dynamically based on the width provided, and how the scrollbar appears "
        "on the right when the text exceeds the component's visible height.";

    // 2. สร้าง Form หลัก
    newtComponent form = newtForm(NULL, NULL, 0);

    // 3. สร้าง Textbox แบบธรรมดา (ระบุกว้าง 50 สูง 6 ตัวอักษร)
    // ใช้ธง WRAP (ตัดบรรทัด) และ SCROLL (มีแถบเลื่อนด้านข้าง)
    newtComponent label1 = newtLabel(2, 1, "=== Standard Textbox (with Scrollbar) ===");
    newtComponent textbox1 = newtTextbox(2, 2, 50, 6, NEWT_FLAG_WRAP | NEWT_FLAG_SCROLL);
    newtTextboxSetText(textbox1, long_text);

    // 4. สร้าง Textbox แบบ Reflowed (จัดย่อหน้าและคำนวณความสูงให้อัตโนมัติ)
    newtComponent label2 = newtLabel(2, 9, "=== Reflowed Textbox (Auto-height) ===");
    
    // newtTextboxReflowed จะรับข้อความธรรมดาแล้วแปลงการจัดรูปเล่มให้พอดีกับความกว้าง
    // flexDown และ flexUp ตั้งเป็น 0 คือไม่ยืดหยุ่นเกินความจำเป็น
    newtComponent textbox2 = newtTextboxReflowed(2, 10, (char *)long_text, 50, 0, 0, NEWT_FLAG_WRAP);

    // 5. สร้างปุ่ม OK เพื่อกดปิดโปรแกรม
    newtComponent button = newtButton(22, 16, "OK");

    // 6. เพิ่ม Component ทั้งหมดเข้าไปใน Form
    newtFormAddComponents(form, label1, textbox1, label2, textbox2, button, NULL);

    // 7. รัน Form และรอจนกว่าผู้ใช้จะกดปุ่ม OK หรือปุ่ม Enter
    newtRunForm(form);

    // 8. คืนหน่วยความจำและปิดหน้าจอระบบ Newt
    newtFormDestroy(form);
    newtFinished();

    return 0;
}