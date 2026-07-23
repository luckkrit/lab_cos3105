/*
 * grade_calc.c
 *
 * อ่านคะแนนจาก stdin ทีละบรรทัด รูปแบบ: ชื่อ คะแนน1 คะแนน2 คะแนน3
 * คำนวณค่าเฉลี่ย ตัดเกรด แล้ว print ผลออก stdout
 * บรรทัดที่ format ผิด จะ print error ไป stderr และข้ามบรรทัดนั้น
 *
 * เกณฑ์เกรด A ปรับได้จาก:
 *   1) command-line argument ตัวแรก (argv[1])   -> ./grade_calc 85
 *   2) environment variable GRADE_A_THRESHOLD    -> export GRADE_A_THRESHOLD=85
 *   3) ถ้าไม่ระบุเลย ใช้ค่า default = 80
 *
 * Exit code:
 *   0 = ประมวลผลสำเร็จทุกบรรทัด
 *   1 = พบบรรทัดที่ format ผิดอย่างน้อย 1 บรรทัด (แต่ยังประมวลผลบรรทัดอื่นต่อ)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_NAME 100

int main(int argc, char *argv[]) {
    double bonus = 0.2;   /* ค่า default */

    /* ลำดับความสำคัญ: argv > env var > default */
    if (argc >= 2) {
        bonus = atof(argv[1]);
    } else {
        const char *env_val = getenv("BONUS");
        if (env_val != NULL) {
            bonus = atof(env_val);
        }
    }

    fprintf(stderr, "[info] Using bonus = %.1f\n", bonus);

    char line[MAX_LINE];
    int line_no = 0;
    int had_error = 0;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        line_no++;

        /* ตัด newline ท้ายบรรทัดออก */
        line[strcspn(line, "\n")] = '\0';

        /* ข้ามบรรทัดว่าง */
        if (strlen(line) == 0) {
            continue;
        }

        char name[MAX_NAME];
        double s1;

        int matched = sscanf(line, "%99s %lf", name, &s1);

        if (matched != 2) {
            fprintf(stderr, "[error] line %d: invalid format -> \"%s\"\n",
                    line_no, line);
            had_error = 1;
            continue;
        }

        double addBonus = (s1 * bonus); 
        double paid = addBonus + s1;

        printf("%s %.2f %.2f\n", name, addBonus ,paid);
    }

    if (had_error) {
        fprintf(stderr, "[warn] some lines were skipped due to format errors\n");
        return 1;
    }

    return 0;
}