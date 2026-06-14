#include <stdio.h>

#include "student.h"

int main() {

    Student students[MAX_STUDENTS];

    int count = 0;

    int choice;

    while (1) {

        printf("\n===== 学生データ管理 =====\n");

        printf("1. 情報入力\n");
        printf("2. 一覧表示\n");
        printf("3. 名前検索\n");
        printf("4. 平均点表示\n");
        printf("5. 最大点・最低点表示\n");
        printf("6. 名前順表示\n");
        printf("7. 点数順表示\n");
        printf("8. ファイル保存\n");
        printf("9. ファイル読み込み\n");
        printf("10. Exit\n");

        choice =
            inputNumber(
                "選択してください: ");

        switch (choice) {

            case 1:

                inputStudent(students,
                             &count);

                break;

            case 2:

                displayStudents(students,
                                count);

                break;

            case 3:

                searchStudent(students,
                              count);

                break;

            case 4:

                displayAverage(students,
                               count);

                break;

            case 5:

                displayMaxMin(students,
                              count);

                break;

            case 6:

                sortByName(students,
                           count);

                displayStudents(students,
                                count);

                break;

            case 7:

                sortByScore(students,
                            count);

                displayStudents(students,
                                count);

                break;

            case 8:

                saveStudents(students,
                             count);

                break;

            case 9:

                loadStudents(students,
                             &count);

                break;

            case 10:

                printf("終了します。\n");

                return 0;

            default:

                printf("1〜10を入力してください。\n");
        }
    }
}
