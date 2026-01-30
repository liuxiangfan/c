#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h> /* Sleep(ms), system("cls") */
#else
#include <unistd.h>
#define Sleep(ms) usleep((ms)*1000)
#endif

typedef struct {
    char name[32];
    int hp, max_hp;
    int atk, def;
    int potions;
    int speed;   /* 每 tick 增加的条数 */
    int bar;     /* 0..100 进度条 */
    int defending; /* 防御状态（本回合减伤标志） */
} Actor;

void clamp_hp(Actor *a) { if (a->hp < 0) a->hp = 0; if (a->hp > a->max_hp) a->hp = a->max_hp; }

void draw_bar(const char *label, Actor *a) {
    int len = 30;
    int filled = a->bar * len / 100;
    printf("%-8s HP:%3d/%3d |", label, a->hp, a->max_hp);
    for (int i = 0; i < len; i++) putchar(i < filled ? '=' : ' ');
    printf("| %3d%%  SPD:%2d POT:%d\n", a->bar, a->speed, a->potions);
}

void show_ui(Actor *p, Actor *e) {
    system("cls");
    puts("=== 回合制（速度条）战斗 ===");
    draw_bar(p->name, p);
    draw_bar(e->name, e);
    puts("----------------------------------------");
    puts("提示：当速度条满（100%）时即可行动。");
}

int calc_damage(int atk, int def, int defending) {
    int base = atk - def/2;
    if (base < 1) base = 1;
    int var = rand() % 5 - 2; /* +-2 随机 */
    int dmg = base + var;
    if (defending) dmg = (dmg+1)/2; /* 防御减半 */
    if (dmg < 0) dmg = 0;
    return dmg;
}

void player_turn(Actor *p, Actor *e) {
    p->defending = 0;
    printf("\n%s 的回合：\n", p->name);
    printf("1) 普通攻击  2) 强力攻击  3) 防御(减伤)  4) 使用药水\n选择: ");
    int choice = 0;
    if (scanf("%d", &choice) != 1) { while (getchar()!='\n'); choice = 1; }
    while (getchar() != '\n'); /* 清除余下输入 */
    if (choice == 1) {
        int dmg = calc_damage(p->atk, e->def, e->defending);
        e->hp -= dmg;
        printf("你普通攻击，造成 %d 点伤害。\n", dmg);
    } else if (choice == 2) {
        int dmg = calc_damage(p->atk + 4, e->def, e->defending);
        e->hp -= dmg;
        printf("你使出强力一击，造成 %d 点伤害。\n", dmg);
    } else if (choice == 3) {
        p->defending = 1;
        printf("你进入防御姿态，下一次受到的伤害减半。\n");
    } else if (choice == 4) {
        if (p->potions > 0) {
            int heal = 12 + rand()%8;
            p->hp += heal; clamp_hp(p);
            p->potions--;
            printf("你使用药水，恢复 %d 点生命。\n", heal);
        } else {
            printf("没有药水了，回合无效。\n");
        }
    } else {
        printf("无效选择，回合跳过。\n");
    }
    p->bar -= 100; if (p->bar < 0) p->bar = 0;
    Sleep(600);
}

void enemy_turn(Actor *e, Actor *p) {
    e->defending = 0;
    int act = rand()%100;
    if (e->hp < e->max_hp/3 && e->potions > 0 && act < 40) {
        int heal = 8 + rand()%8;
        e->hp += heal; clamp_hp(e);
        e->potions--;
        printf("%s 使用药水，恢复 %d 点生命。\n", e->name, heal);
    } else if (act < 65) {
        int dmg = calc_damage(e->atk, p->def, p->defending);
        p->hp -= dmg;
        printf("%s 普通攻击，造成 %d 点伤害。\n", e->name, dmg);
    } else if (act < 90) {
        int dmg = calc_damage(e->atk + 3, p->def, p->defending);
        p->hp -= dmg;
        printf("%s 强力攻击，造成 %d 点伤害。\n", e->name, dmg);
    } else {
        e->defending = 1;
        printf("%s 进入防御姿态（减伤）。\n", e->name);
    }
    e->bar -= 100; if (e->bar < 0) e->bar = 0;
    Sleep(700);
}

int main(void) {
    srand((unsigned)time(NULL));
    Actor player = {"PLAYER", 80, 80, 14, 6, 2, 30, 0, 0}; /* speed 30/tick */
    Actor enemy  = {"ENEMY", 60, 60, 12, 4, 1, 25, 0, 0}; /* speed 25/tick */

    show_ui(&player, &enemy);
    printf("按回车开始...");
    getchar();

    while (player.hp > 0 && enemy.hp > 0) {
        /* tick */
        player.bar += player.speed;
        if (player.bar > 200) player.bar = 200; /* 防止无限累积 */
        enemy.bar  += enemy.speed;
        if (enemy.bar > 200) enemy.bar = 200;

        /* 如果双方都满，比较优先级 */
        if (player.bar >= 100 && enemy.bar >= 100) {
            if (player.bar > enemy.bar) {
                show_ui(&player, &enemy);
                player_turn(&player, &enemy);
                clamp_hp(&enemy);
                if (enemy.hp <= 0) break;
                show_ui(&player, &enemy);
                enemy_turn(&enemy, &player);
                clamp_hp(&player);
            } else if (enemy.bar > player.bar) {
                show_ui(&player, &enemy);
                enemy_turn(&enemy, &player);
                clamp_hp(&player);
                if (player.hp <= 0) break;
                show_ui(&player, &enemy);
                player_turn(&player, &enemy);
                clamp_hp(&enemy);
            } else { /* 平手：速度高者先；若仍平则随机 */
                if (player.speed > enemy.speed) {
                    show_ui(&player, &enemy);
                    player_turn(&player, &enemy); clamp_hp(&enemy);
                    if (enemy.hp<=0) break;
                    show_ui(&player, &enemy);
                    enemy_turn(&enemy, &player); clamp_hp(&player);
                } else if (enemy.speed > player.speed) {
                    show_ui(&player, &enemy);
                    enemy_turn(&enemy, &player); clamp_hp(&player);
                    if (player.hp<=0) break;
                    show_ui(&player, &enemy);
                    player_turn(&player, &enemy); clamp_hp(&enemy);
                } else {
                    if (rand()%2) { player_turn(&player,&enemy); clamp_hp(&enemy); if (enemy.hp<=0) break; enemy_turn(&enemy,&player); clamp_hp(&player); }
                    else { enemy_turn(&enemy,&player); clamp_hp(&player); if (player.hp<=0) break; player_turn(&player,&enemy); clamp_hp(&enemy); }
                }
            }
        } else if (player.bar >= 100) {
            show_ui(&player, &enemy);
            player_turn(&player, &enemy);
            clamp_hp(&enemy);
        } else if (enemy.bar >= 100) {
            show_ui(&player, &enemy);
            enemy_turn(&enemy, &player);
            clamp_hp(&player);
        }

        /* 每 tick 更新 UI（轻刷新） */
        show_ui(&player, &enemy);

        /* 小睡以控制“时间流逝”速度 */
        Sleep(120);
    }

    show_ui(&player, &enemy);
    if (player.hp <= 0) printf("\n你被击败了。\n");
    else if (enemy.hp <= 0) printf("\n你赢了！敌人被击败。\n");
    else printf("\n战斗结束。\n");

    return 0;
}