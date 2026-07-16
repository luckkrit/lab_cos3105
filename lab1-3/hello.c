#include <newt.h>
#include <unistd.h>   // sleep()

int main(void) {
    newtInit();     // เริ่มระบบ newt + สั่ง terminal เข้า raw mode
    newtCls();      // เคลียร์หน้าจอ (ไม่บังคับ แต่ทำแล้วสวยกว่า)

    // เขียนข้อความลงบน root window (พื้นหลัง)
    newtDrawRootText(0, 0, "COS3105 - Hello newt!");

    // ค่าติดลบ = นับจากขอบอีกด้าน (-1 คือบรรทัด/คอลัมน์สุดท้าย)
    newtDrawRootText(-30, -3, "text at bottom-right corner");

    // help line = บรรทัดล่างสุดของจอ, NULL = ใช้ข้อความ default ของ newt
    newtPushHelpLine(NULL);

    newtRefresh();  // บังคับให้วาดหน้าจอทันที
    sleep(3);

    newtFinished(); // คืนสภาพ terminal กลับเป็นปกติ *สำคัญมาก*
    return 0;
}