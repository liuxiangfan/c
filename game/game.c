#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PLAYER_HP 100
#define MONSTER_HP 80
#define PLAYER_SPEED 70   // 越高越快
#define MONSTER_SPEED 50

typedef struct {
    int hp;
    int speed;
    int gauge; // 速度条（0~100+）
    int isPlayer;
} Character;

void displayStatus(Character *player, Character *monster) {
    printf("\n--- 状态 ---\n");
    printf("你: HP=%d, 速度条=%.1f%%\n", player->hp, player->gauge);
    printf("怪物: HP=%d, 速度条=%.1f%%\n", monster->hp, monster->gauge);
    printf("-------------\n\n");
}

int getPlayerAction() {
    int choice;
    printf("请选择行动:\n");
    printf("1. 攻击（造成 10~20 伤害）\n");
    printf("2. 防御（本回合受击减半）\n");
    printf("你的选择: ");
    scanf("%d", &choice);
    return (choice == 1 || choice == 2) ? choice : 1; // 默认攻击
}

void applyDamage(Character *target, int damage, int isDefending) {
    if (isDefending) {
        damage = damage / 2;
    }
    target->hp -= damage;
    if (target->hp < 0) target->hp = 0;
}

int main() {
    srand((unsigned int)time(NULL));

    Character player = {PLAYER_HP, PLAYER_SPEED, 0, 1};
    Character monster = {MONSTER_HP, MONSTER_SPEED, 0, 0};

    printf("⚔️ 欢迎来到速度条回合制战斗！\n");
    printf("你的速度: %d，怪物速度: %d\n", PLAYER_SPEED, MONSTER_SPEED);
    printf("速度条满 100% 即可行动！高速者可能连击！\n\n");

    int playerDefending = 0;
    int monsterDefending = 0;

    while (player.hp > 0 && monster.hp > 0) {
        // 双方同时增加速度条
        player.gauge += player.speed;
        monster.gauge += monster.speed;

        // 检查谁可以行动（可能多次行动）
        int acted = 0;

        // 如果玩家速度条满，行动
        while (player.hp > 0 && monster.hp > 0 && player.gauge >= 100) {
            displayStatus(&player, &monster);
            printf(">>> 轮到你行动！\n");

            int action = getPlayerAction();
            playerDefending = (action == 2);

            if (action == 1) {
                int dmg = rand() % 11 + 10;
                applyDamage(&monster, dmg, monsterDefending);
                printf("你对怪物造成 %d 点伤害！\n", dmg);
            } else {
                printf("你进入防御姿态！\n");
            }

            player.gauge -= 100; // 保留溢出（如 130 → 30）
            monsterDefending = 0; // 怪物防御只持续一回合
            acted = 1;
        }

        // 如果怪物速度条满，行动
        while (player.hp > 0 && monster.hp > 0 && monster.gauge >= 100) {
            displayStatus(&player, &monster);
            printf(">>> 怪物行动！\n");

            // 怪物总是攻击（可扩展AI）
            int dmg = rand() % 11 + 5; // 5~15
            applyDamage(&player, dmg, playerDefending);
            printf("怪物对你造成 %d 点伤害！\n", dmg);

            monster.gauge -= 100;
            playerDefending = 0; // 防御仅一回合有效
            acted = 1;
        }

        // 安全退出：防止无限循环（理论上不会发生）
        if (!acted) {
            // 强制推进（极端情况）
            player.gauge = 100;
            monster.gauge = 100;
        }
    }

    // 结算
    printf("\n========== 战斗结束 ==========\n");
    if (player.hp <= 0) {
        printf("💀 你被击败了...\n");
    } else {
        printf("🎉 你战胜了怪物！\n");
    }
    printf("最终状态:\n");
    printf("你: HP=%d\n", player.hp);
    printf("怪物: HP=%d\n", monster.hp);

    return 0;
}