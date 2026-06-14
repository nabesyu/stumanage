#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "student.h"


// =========================
// 内部関数宣言
// =========================
void swap(Student *a,
          Student *b);

int getCharType(const char *str);

int isValidName(const char *str);


// =========================
// 数値入力
// =========================
int inputNumber(const char *message) {

    char buffer[100];

    char *endptr;

    long value;

    while (1) {

        printf("%s", message);

        if (fgets(buffer,
                  sizeof(buffer),
                  stdin) == NULL) {

            continue;
        }

        buffer[strcspn(buffer,
                       "\n")] = '\0';

        value = strtol(buffer,
                       &endptr,
                       10);

        if (*endptr != '\0') {

            printf("数字を入力してください。\n");

            continue;
        }

        return (int)value;
    }
}


// =========================
// 名前チェック
// =========================
int isValidName(const char *str) {

    int i = 0;

    while (str[i] != '\0') {

        unsigned char c =
            (unsigned char)str[i];

        if (c < 128) {

            i++;

            continue;
        }

        if ((c & 0xF0) == 0xE0) {

            unsigned char c2 =
                (unsigned char)str[i + 1];

            unsigned char c3 =
                (unsigned char)str[i + 2];

            // ひらがな
            if (c == 0xE3 &&
                (
                    c2 == 0x81 ||
                    (c2 == 0x82 &&
                     c3 <= 0x9F)
                )) {

                i += 3;

                continue;
            }

            // カタカナ
            if (c == 0xE3 &&
                (
                    (c2 == 0x82 &&
                     c3 >= 0xA0)
                    ||
                    c2 == 0x83
                )) {

                i += 3;

                continue;
            }

            return 0;
        }

        return 0;
    }

    return 1;
}


// =========================
// 情報入力
// =========================
void inputStudent(Student students[],
                  int *count) {

    if (*count >= MAX_STUDENTS) {

        printf("これ以上登録できません。\n");

        return;
    }

   while (1) {

    char *newline;

    int ch;

    printf("名前を入力してください: ");

    if (fgets(students[*count].name,
              sizeof(students[*count].name),
              stdin) == NULL) {

        printf("入力エラー\n");

        return;
    }

    newline =
        strchr(students[*count].name,
               '\n');

    // 改行が無い = 文字数オーバー
    if (newline == NULL) {

        printf("文字数オーバーです。\n");

        // 入力バッファをクリア
        while ((ch = getchar()) != '\n' &&
               ch != EOF);

        continue;
    }

    *newline = '\0';

    if (strlen(students[*count].name) == 0) {

        printf("空入力です。\n");

        continue;
    }

    if (!isValidName(
            students[*count].name)) {

        printf("使用できない文字が含まれています。\n");

        continue;
    }

    break;
}

    if (!isValidName(
            students[*count].name)) {

        printf("使用できない文字が含まれています。\n");

        return;
    }

    students[*count].score =
        inputNumber(
            "点数を入力してください: ");

    (*count)++;

    printf("登録しました。\n");
}


// =========================
// 一覧表示
// =========================
void displayStudents(Student students[],
                     int count) {

    int i;

    if (count == 0) {

        printf("データなし\n");

        return;
    }

    printf("\n===== 一覧 =====\n");

    for (i = 0; i < count; i++) {

        printf("%d. %s : %d\n",
               i + 1,
               students[i].name,
               students[i].score);
    }
}


// =========================
// 平均点
// =========================
void displayAverage(Student students[],
                    int count) {

    int i;

    int sum = 0;

    if (count == 0) {

        printf("データなし\n");

        return;
    }

    for (i = 0; i < count; i++) {

        sum += students[i].score;
    }

    printf("平均点: %.2f\n",
           (double)sum / count);
}


// =========================
// 名前検索
// =========================
void searchStudent(Student students[],
                   int count) {

    char search[100];

    int i;

    int found = 0;

    if (count == 0) {

        printf("データなし\n");

        return;
    }

    printf("検索する名前: ");

    fgets(search,
          sizeof(search),
          stdin);

    search[strcspn(search,
                   "\n")] = '\0';

    for (i = 0; i < count; i++) {

        if (strcmp(students[i].name,
                   search) == 0) {

            printf("見つかりました\n");

            printf("%s : %d\n",
                   students[i].name,
                   students[i].score);

            found = 1;
        }
    }

    if (!found) {

        printf("見つかりません\n");
    }
}


// =========================
// 最大点・最低点
// =========================
void displayMaxMin(Student students[],
                   int count) {

    int i;

    int max;

    int min;

    if (count == 0) {

        printf("データなし\n");

        return;
    }

    max = students[0].score;

    min = students[0].score;

    for (i = 1; i < count; i++) {

        if (students[i].score > max) {

            max = students[i].score;
        }

        if (students[i].score < min) {

            min = students[i].score;
        }
    }

    printf("最大点: %d\n", max);

    printf("最低点: %d\n", min);
}


// =========================
// 保存機能
// =========================
void saveStudents(Student students[],
                  int count) {

    FILE *fp;

    int i;

    char filename[100];

    printf("保存ファイル名を入力してください: ");

    fgets(filename,
          sizeof(filename),
          stdin);

    filename[strcspn(filename,
                     "\n")] = '\0';

    fp = fopen(filename,
               "w");

    if (fp == NULL) {

        printf("ファイルを開けません。\n");

        return;
    }

    for (i = 0; i < count; i++) {

        fprintf(fp,
                "%s,%d\n",
                students[i].name,
                students[i].score);
    }

    fclose(fp);

    printf("%s に保存しました。\n",
           filename);
}


// =========================
// 読み込み機能
// 既存データに追加
// =========================
void loadStudents(Student students[],
                  int *count) {

    FILE *fp;

    char line[200];

    char filename[100];

    printf("読み込むファイル名を入力してください: ");

    fgets(filename,
          sizeof(filename),
          stdin);

    filename[strcspn(filename,
                     "\n")] = '\0';

    fp = fopen(filename,
               "r");

    if (fp == NULL) {

        printf("ファイルを開けません。\n");

        return;
    }

    while (fgets(line,
                 sizeof(line),
                 fp) != NULL) {

        if (*count >= MAX_STUDENTS) {

            printf("登録上限です。\n");

            break;
        }

    char tempName[100];

    int tempScore;

    char extra;

    line[strcspn(line,
                "\n")] = '\0';


    // =========================
    // 形式チェック
    // 「名前,点数」以外を拒否
    // =========================
    if (sscanf(line,
            "%99[^,],%d%c",
            tempName,
            &tempScore,
            &extra) != 2) {

        printf("誤った書き方: %s\n",
            line);

        continue;
    }


    // =========================
    // 空入力チェック
    // =========================
    if (strlen(tempName) == 0) {

        printf("空入力エラー: %s\n",
            line);

        continue;
    }


    // =========================
    // 文字数オーバーチェック
    // =========================
    if (strlen(tempName) >=
        sizeof(students[*count].name) - 1) {

        printf("文字数オーバー: %s\n",
            line);

        continue;
    }


    // =========================
    // 使用文字チェック
    // =========================
    if (!isValidName(tempName)) {

        printf("使用不可文字エラー: %s\n",
            line);

        continue;
    }


    // =========================
    // 正常データを登録
    // =========================
    strcpy(students[*count].name,
        tempName);

    students[*count].score =
        tempScore;

    (*count)++;
    }

    fclose(fp);

    printf("%s を読み込みました。\n",
           filename);
}


// =========================
// 交換
// =========================
void swap(Student *a,
          Student *b) {

    Student temp;

    temp = *a;

    *a = *b;

    *b = temp;
}


// =========================
// 点数順ソート
// =========================
void sortByScore(Student students[],
                 int count) {

    int i;

    int j;

    for (i = 0; i < count - 1; i++) {

        for (j = 0;
             j < count - i - 1;
             j++) {

            if (students[j].score <
                students[j + 1].score) {

                swap(&students[j],
                     &students[j + 1]);
            }
        }
    }

    printf("点数順(高い順)に\n");
    printf("並べ替えました。\n");
}


// =========================
// 文字種判定
// =========================
int getCharType(const char *str) {

    unsigned char c =
        (unsigned char)str[0];

    if (isalpha(c)) {

        return 2;
    }

    if (isdigit(c)) {

        return 3;
    }

    if (c == 0xE3) {

        unsigned char c2 =
            (unsigned char)str[1];

        unsigned char c3 =
            (unsigned char)str[2];

        // ひらがな
        if (
            c2 == 0x81 ||
            (c2 == 0x82 &&
             c3 <= 0x9F)
        ) {

            return 0;
        }

        // カタカナ
        if (
            (c2 == 0x82 &&
             c3 >= 0xA0)
            ||
            c2 == 0x83
        ) {

            return 1;
        }
    }

    return 4;
}


// =========================
// 名前順ソート
// =========================
void sortByName(Student students[],
                int count) {

    int i;

    int j;

    for (i = 0; i < count - 1; i++) {

        for (j = 0;
             j < count - i - 1;
             j++) {

            int type1 =
                getCharType(
                    students[j].name);

            int type2 =
                getCharType(
                    students[j + 1].name);

            // 文字種優先
            if (type1 > type2) {

                swap(&students[j],
                     &students[j + 1]);
            }

            // 同種なら比較
            else if (
                type1 == type2 &&
                strcmp(students[j].name,
                       students[j + 1].name) > 0
            ) {

                swap(&students[j],
                     &students[j + 1]);
            }
        }
    }

    printf("\n名前順で表示します\n");

    printf("並び順:\n");

    printf("ひらがな");
    printf(" → ");

    printf("カタカナ");
    printf(" → ");

    printf("アルファベット");
    printf(" → ");

    printf("数字");
    printf(" → ");

    printf("記号\n");
}
