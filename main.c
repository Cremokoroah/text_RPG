#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char name[32];
    int life, attack, defense, magic;
} param;

void act(param* actor, param* target, int command)
{
    int point;
    switch (command)
    {
        case 0:
            point = actor -> attack - target -> defense;
            target -> life -= point;
            printf("%sの攻撃! %s に%d のダメージを与えた!\n", actor -> name, target -> name, point);
            break;
        case 1:
            point = 20;
            actor -> attack += point;
            printf("%s は力を溜めている。 %s は %d 力が溜まった!\n", actor -> name, actor -> name, point);
            break;
        case 2:
            point = 50;
            actor -> life += point;
            printf("%s はヒールを唱えた。 %s の Lifeが %d 回復した!\n", actor -> name, actor -> name, point);
            break;
        case 3:
            point = actor -> magic;
            target -> life -= point;
            printf("%sのファイア! %s に%d のダメージを与えた!\n", actor -> name, target -> name, point);
            /* 違う数字を入力したら無視されて次のターンになってしまう */
    }
}

int GetRandom(int min,int max);

int main(void)
{
    param you = { "勇者", 100, 100, 50, 100 };     /* magicはあえて隠している（変化する値ではないので）*/
    param enemy = { "ゴブリン", 100, 60, 50, 10 };
    printf("%sが現れた!\n", enemy.name);
    for (; ;)             /* (初期化; 継続条件; 再初期化) において継続条件を空にしている */
    {
        int command;
        printf("%s: Life = %d, Attack = %d, Defense = %d\n", you.name, you.life, you.attack, you.defense);
        printf("%s: Life = %d, Attack = %d, Defense = %d\n", enemy.name, enemy.life, enemy.attack, enemy.defense);
        printf("(0) 攻撃\n(1) 力をためる\n(2) 回復魔法\n(3) 攻撃魔法\n");
        printf("Command:");
        scanf("%d", &command);
        if (command < 0 || command > 3)
        {
            printf("『勇者よ、0~3のコマンドを入力するのだ』どこからともなく賢者の声が聞こえた!\n");
        }
        act(&you, &enemy, command); /* 味方側の攻撃 */
        if (enemy.life <= 0)
        {
            printf("%s を倒した!\n", enemy.name);
            return 0; /* これないと無限ループになって敵が死なない */
        }
        
        act(&enemy, &you, GetRandom(1, 3));
        if (you.life <= 0)
        {
            printf("%s は倒れた...\n", you.name);
            return 0;
        }
    }
}

int GetRandom(int min,int max)
{
    srand((unsigned int)time(NULL));
    
    return rand() % 4;  /* 0〜3の乱数を発生させる */
}
