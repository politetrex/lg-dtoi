#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    int money, gold_per_sec, warehouse;
    int upkeep_mul;
    int bad_event_rate;
    int win_money;

    cout << "===== 选择难度 =====\n";
    cout << "1. 简单\n";
    cout << "2. 普通\n";
    cout << "3. 困难\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        money = 500;
        gold_per_sec = 2;
        warehouse = 8000;
        upkeep_mul = 1;
        bad_event_rate = 20;
        win_money = 20000;
    } else if (choice == 2) {
        money = 300;
        gold_per_sec = 1;
        warehouse = 5000;
        upkeep_mul = 2;
        bad_event_rate = 40;
        win_money = 30000;
    } else {
        money = 150;
        gold_per_sec = 1;
        warehouse = 3000;
        upkeep_mul = 3;
        bad_event_rate = 70;
        win_money = 50000;
    }

    int mine = 0, mine_cost = 50, mine_add = 2;
    int farm = 0, farm_cost = 80, farm_add = 3;
    int wood = 0, wood_cost = 120, wood_add = 5;
    int stone = 0, stone_cost = 150, stone_add = 7;

    int upkeep = 0;
    int upkeep_cd = 0;

    bool tech1 = false, tech2 = false, tech3 = false;
    int tech1_cost = 500;
    int tech2_cost = 800;
    int tech3_cost = 1200;

    int task_target = 5000;
    int task_reward = 600;
    bool task_done = false;

    int event_cd = 0;
    int temp_bonus = 0;

    while (1) {
        system("cls");

        // 1. 自动产钱 + 严格锁仓库上限
        int now_income = gold_per_sec + temp_bonus;
        if (tech1) now_income = now_income * 6 / 5;

        if (money < warehouse) {
            money += now_income;
            if (money > warehouse) money = warehouse;
        }
        if (money < 0) money = 0;

        // 临时丰收增益只持续一回合
        temp_bonus = 0;

        // 2. 维护费结算 纯整数
        upkeep_cd++;
        if (upkeep_cd >= 5) {
            upkeep = (mine + farm + wood + stone) * 2 * upkeep_mul;
            if (tech2) upkeep = upkeep * 4 / 5;

            money -= upkeep;
            if (money < 0) money = 0;
            upkeep_cd = 0;
        }

        // 3. 随机事件
        event_cd++;
        if (event_cd >= 4) {
            int r = rand() % 100;
            if (r < bad_event_rate) {
                // 坏事件
                int e = rand() % 2;
                if (e == 0) {
                    bool hasLoss = false;
                    int b = rand() % 4;
                    if (b == 0 && mine > 0) { mine--; gold_per_sec -= mine_add; hasLoss = true; }
                    else if (b == 1 && farm > 0) { farm--; gold_per_sec -= farm_add; hasLoss = true; }
                    else if (b == 2 && wood > 0) { wood--; gold_per_sec -= wood_add; hasLoss = true; }
                    else if (b == 3 && stone > 0) { stone--; gold_per_sec -= stone_add; hasLoss = true; }
                    if (hasLoss) cout << "【火灾】建筑降级！\n";
                    else cout << "【火灾】有惊无险，无建筑受损\n";
                } else {
                    int loss = rand() % 100 + 50;
                    money -= loss;
                    if (money < 0) money = 0;
                    cout << "【盗贼】被偷走 " << loss << " 金币\n";
                }
            } else {
                // 好事件
                int e = rand() % 3;
                if (e == 0) {
                    temp_bonus = gold_per_sec / 2;
                    cout << "【丰收】本回合收益临时提升！\n";
                } else if (e == 1) {
                    money += 200;
                    if (money > warehouse) money = warehouse;
                    cout << "【商人】获得 200 金币\n";
                } else {
                    money += 150;
                    if (money > warehouse) money = warehouse;
                    cout << "【暴雨】作物增产，额外获得金币\n";
                }
            }
            event_cd = 0;
            Sleep(800);
        }

        // 4. 任务判定 只触发一次
        if (money >= task_target && !task_done) {
            money += task_reward;
            if (money > warehouse) money = warehouse;
            task_done = true;
            cout << "【任务完成】奖励 " << task_reward << " 金币！\n";
            Sleep(800);
        }

        // 5. 界面显示
        cout << "======= 经营游戏 =======\n";
        cout << "金币: " << money << " / " << warehouse << "\n";
        cout << "每秒基础收益: " << gold_per_sec << " | 维护费: " << upkeep << "/5s\n";
        cout << "通关目标: " << win_money << " 金币\n";
        cout << "任务: 赚到 " << task_target << " (完成: " << (task_done ? "是" : "否") << ")\n\n";

        cout << "1 金矿 Lv" << mine << " 升级价:" << mine_cost << "\n";
        cout << "2 农场 Lv" << farm << " 升级价:" << farm_cost << "\n";
        cout << "3 伐木场 Lv" << wood << " 升级价:" << wood_cost << "\n";
        cout << "4 采石场 Lv" << stone << " 升级价:" << stone_cost << "\n";
        cout << "5 升级仓库 费用:" << warehouse / 2 << "\n";
        cout << "6 科技1:收益+20% " << (tech1?"已学":"未学") << " 价格:" << tech1_cost << "\n";
        cout << "7 科技2:维护-20% " << (tech2?"已学":"未学") << " 价格:" << tech2_cost << "\n";
        cout << "8 科技3:仓库+50% " << (tech3?"已学":"未学") << " 价格:" << tech3_cost << "\n";
        cout << "9 等待\n";
        cout << "========================\n";

        // 通关判断
        if (money >= win_money) {
            cout << "\n?? 恭喜通关！\n";
            system("pause");
            return 0;
        }

        // 操作输入
        int op;
        cin >> op;

        // 建筑升级 全程整数
        if (op == 1) {
            if (money >= mine_cost) {
                money -= mine_cost;
                mine++;
                gold_per_sec += mine_add;
                mine_cost = mine_cost * 3 / 2;
            }
        } else if (op == 2) {
            if (money >= farm_cost) {
                money -= farm_cost;
                farm++;
                gold_per_sec += farm_add;
                farm_cost = farm_cost * 8 / 5;
            }
        } else if (op == 3) {
            if (money >= wood_cost) {
                money -= wood_cost;
                wood++;
                gold_per_sec += wood_add;
                wood_cost = wood_cost * 17 / 10;
            }
        } else if (op == 4) {
            if (money >= stone_cost) {
                money -= stone_cost;
                stone++;
                gold_per_sec += stone_add;
                stone_cost = stone_cost * 9 / 5;
            }
        } else if (op == 5) {
            int cost = warehouse / 2;
            if (money >= cost) {
                money -= cost;
                warehouse = warehouse * 3 / 2;
            }
        } else if (op == 6) {
            if (!tech1 && money >= tech1_cost) {
                money -= tech1_cost;
                tech1 = true;
            }
        } else if (op == 7) {
            if (!tech2 && money >= tech2_cost) {
                money -= tech2_cost;
                tech2 = true;
            }
        } else if (op == 8) {
            if (!tech3 && money >= tech3_cost) {
                money -= tech3_cost;
                tech3 = true;
                warehouse = warehouse * 3 / 2;
            }
        } else if (op == 9) {
            // 等待 无操作
        } else {
            cout << "输入无效，请输入 1~9 的数字！\n";
            Sleep(600);
        }

        Sleep(1000);
    }
    return 0;
}
