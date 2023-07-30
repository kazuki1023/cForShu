#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 4桁の数を生成する関数
void generate_numbers(int *numbers) {
  // 現在の時間に基づいて乱数生成器のシードを設定。これにでrand() が毎回異なる値を返すようにな　り、4桁の数が毎回異なる値になる。
    srand(time(NULL));
    for(int i = 0; i < 4; i++) {
        int temp;
        // 同じ数字がないようにする
        // つまり9999とかはありえない
        do {
            temp = rand() % 10;
            for(int j = 0; j < i; j++) {
                if(numbers[j] == temp) {
                    temp = -1;
                }
            }
        } while(temp == -1);
        numbers[i] = temp;
    }
}

// ヒットとブローを計算する関数
void calculate_hit_and_blow(int *numbers, int *guess, int *hit, int *blow) {
    *hit = 0;
    *blow = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(guess[i] == numbers[j]) {
                if(i == j) {
                    (*hit)++;
                } else {
                    (*blow)++;
                }
            }
        }
    }
}

// 答えを表示する関数
void print_answer(int *numbers) {
    printf("答えは: ");
    for(int i = 0; i < 4; i++) {
        printf("%d", numbers[i]);
    }
    printf("\n");
}

// メイン関数
int main() {
    int numbers[4];
    generate_numbers(numbers);

    int attempts = 0;

    while(1) {
        int guess[4];
        printf("4桁の数字を入力してください (ギブアップする場合は9999を入力): ");
        for(int i = 0; i < 4; i++) {
            scanf("%1d", &guess[i]);
        }
        attempts++;

        // ギブアップの判定
        if(guess[0] == 9 && guess[1] == 9 && guess[2] == 9 && guess[3] == 9) {
            print_answer(numbers);
            break;
        }

        int hit, blow;
        calculate_hit_and_blow(numbers, guess, &hit, &blow);

        if(hit == 4) {
            printf("おめでとう！ %d回目で正解しました。\n", attempts);
            break;
        } else {
            printf("HIT: %d, BLOW: %d\n", hit, blow);
        }
    }

    return 0;
}