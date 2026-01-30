// ...existing code...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[32];
    int hp;
    int max_hp;
    int mp;
    int max_mp;
    int energy;
    int max_energy;
    int def;
    int atk;
    int speed;   // 每循环增加速度条的值
    int gauge;   // 速度条 0..99 (满100行动)
    int potions; // 恢复道具数量
} Character;

int rand_range(int a, int b) { return a + rand() % (b - a + 1); }

// 计算并造成伤害（包含暴击判定），返回实际造成的伤害
int Damage(int base_damage, Character *attacker, Character *target, float crit_chance, float crit_mult) {
    float r = (float)rand() / RAND_MAX;
    int dmg = base_damage;
    if (r < crit_chance) {
        dmg = (int)(dmg * crit_mult);
        printf("暴击！ ");
    }
    dmg -= target->def;
    if (dmg < 1) dmg = 1;
    target->hp -= dmg;
    if (target->hp < 0) target->hp = 0;
    return dmg;
}

void Heal(Character *who, int amount) {
    who->hp += amount;
    if (who->hp > who->max_hp) who->hp = who->max_hp;
}

// 清空输入缓冲
void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// 行动选择：若条件不满足则提示并重新选择，直到选择有效为止
void Action_Choice(Character *player, Character *enemy) {
    while (1) {
        printf("\n你的回合：\n");
        printf("1. 普攻 (伤害 %d ~ %d)\n", player->atk, player->atk + 5);
        printf("2. 技能：烈焰 (耗蓝 10，伤害 30，暴击率10%%，暴击伤害1.5倍)\n");
        printf("3. 药水 (恢复 30 HP，剩余 %d)\n", player->potions);
        printf("4. 大招 (需能量满 %d)\n", player->max_energy);
        printf("选择：");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("输入无效，请重新选择。\n");
            clear_stdin();
            continue;
        }
        clear_stdin();

        if (choice == 1) {
            int base = rand_range(player->atk, player->atk + 5);
            int dealt = Damage(base, player, enemy, 0.08f, 1.5f);
            printf("你使用普攻，对敌人造成 %d 点伤害（敌剩余 HP=%d）\n", dealt, enemy->hp);
            break;
        } else if (choice == 2) {
            int cost = 10;
            if (player->mp < cost) {
                printf("蓝量不足（%d/%d），请重新选择。\n", player->mp, player->max_mp);
                continue; // 重新选择
            }
            player->mp -= cost;
            int dealt = Damage(30, player, enemy, 0.10f, 1.5f);
            printf("你释放烈焰，造成 %d 点伤害（敌剩余 HP=%d），当前蓝量 %d/%d\n",
                   dealt, enemy->hp, player->mp, player->max_mp);
            break;
        } else if (choice == 3) {
            if (player->potions <= 0) {
                printf("没有药水了，请重新选择。\n");
                continue;
            }
            player->potions--;
            Heal(player, 30);
            printf("使用药水，恢复 30 HP（当前 HP=%d），剩余药水 %d\n", player->hp, player->potions);
            break;
        } else if (choice == 4) {
            if (player->energy < player->max_energy) {
                printf("能量不足（%d/%d），请先积攒能量或重新选择。\n", player->energy, player->max_energy);
                continue;
            }
            // 使用大招
            player->energy = 0;
            int dealt = Damage(80, player, enemy, 0.20f, 2.0f);
            printf("你释放大招，造成 %d 点巨额伤害（敌剩余 HP=%d）\n", dealt, enemy->hp);
            break;
        } else {
            printf("无效选项，请重新选择。\n");
            continue;
        }
    }
}

void Enemy_Action(Character *enemy, Character *player) {
    // 简单AI：若HP低且有能量则使用回复道具（若有），否则攻击
    if (enemy->hp < enemy->max_hp / 3 && enemy->potions > 0) {
        enemy->potions--;
        Heal(enemy, 25);
        printf("敌人使用药水，回复 25 HP（敌当前 HP=%d）\n", enemy->hp);
        return;
    }
    int base = rand_range(enemy->atk, enemy->atk + 3);
    int dmg = Damage(base, enemy, player, 0.05f, 1.5f);
    printf("敌人攻击你，造成 %d 点伤害（你当前 HP=%d）\n", dmg, player->hp);
}

int main(void) {
    srand((unsigned)time(NULL));

    Character player;
    strncpy(player.name, "你", sizeof(player.name));
    player.max_hp = player.hp = 120;
    player.max_mp = player.mp = 30;
    player.max_energy = player.energy = 0;
    player.def = 3;
    player.atk = 12;
    player.speed = 70;
    player.gauge = 0;
    player.potions = 2;

    Character enemy;
    strncpy(enemy.name, "怪物", sizeof(enemy.name));
    enemy.max_hp = enemy.hp = 100;
    enemy.max_mp = enemy.mp = 0;
    enemy.max_energy = enemy.energy = 0;
    enemy.def = 2;
    enemy.atk = 10;
    enemy.speed = 50;
    enemy.gauge = 0;
    enemy.potions = 1;

    printf("速度条回合制示例，选择行动时若条件不满足会要求重新选择。\n");

    while (player.hp > 0 && enemy.hp > 0) {
        // 增加速度条
        player.gauge += player.speed;
        enemy.gauge += enemy.speed;

        // 玩家行动（可能连击）
        while (player.hp > 0 && enemy.hp > 0 && player.gauge >= 100) {
            printf("\n--- 速度条触发：你的回合 (条=%d) ---\n", player.gauge);
            Action_Choice(&player, &enemy);
            player.gauge -= 100;
            if (player.gauge < 0) player.gauge = 0;
            // 每行动积攒少量能量
            player.energy += 10;
            if (player.energy > player.max_energy) player.energy = player.max_energy;
            if (enemy.hp <= 0) break;
        }

        // 敌方行动
        while (player.hp > 0 && enemy.hp > 0 && enemy.gauge >= 100) {
            printf("\n--- 速度条触发：敌人回合 (条=%d) ---\n", enemy.gauge);
            Enemy_Action(&enemy, &player);
            enemy.gauge -= 100;
            if (enemy.gauge < 0) enemy.gauge = 0;
            enemy.energy += 10;
            if (enemy.energy > enemy.max_energy) enemy.energy = enemy.max_energy;
            if (player.hp <= 0) break;
        }

        // 防止极端死循环：若双方都低于100则继续循环以推进速度条
    }

    printf("\n战斗结束：\n");
    if (player.hp <= 0) printf("你被击败\n");
    else printf("你获胜\n");

    return 0;
}
// ...existing code...