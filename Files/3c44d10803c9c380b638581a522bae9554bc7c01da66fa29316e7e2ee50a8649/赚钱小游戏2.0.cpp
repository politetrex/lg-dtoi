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

    int choice;
    cout << "===== 选择难度 =====\n";
    cout << "1. 简单\n";
    cout << "2. 普通\n";
    cout << "3. 困难\n";
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

    int tech1 = 0, tech1_cost = 500;
    int tech2 = 0, tech2_cost = 800;
    int tech3 = 0, tech3_cost = 1200;

    int task_target = 5000;
    int task_reward = 600;
    int task_done = 0;

    int event_cd = 0;

    while (1) {
        system("cls");

        if (money < warehouse) {
            money += gold_per_sec;
            if (money > warehouse) money = warehouse;
        }

        upkeep_cd++;
        if (upkeep_cd >= 5) {
            upkeep = (mine + farm + wood + stone) * 2 * upkeep_mul;
            if (tech2) upkeep *= 0.8;
            money -= upkeep;
            if (money < 0) money = 0;
            upkeep_cd = 0;
        }

        event_cd++;
        if (event_cd >= 4) {
            int r = rand() % 100;
            if (r < bad_event_rate) {
                int e = rand() % 2;
                if (e == 0) {
                    int b = rand() % 4;
                    if (b == 0 && mine > 0) { mine--; gold_per_sec -= mine_add; cout << "【火灾】金矿降级\n"; }
                    else if (b == 1 && farm > 0) { farm--; gold_per_sec -= farm_add; cout << "【火灾】农场降级\n"; }
                    else if (b == 2 && wood > 0) { wood--; gold_per_sec -= wood_add; cout << "【火灾】伐木场降级\n"; }
                    else if (b == 3 && stone > 0) { stone--; gold_per_sec -= stone_add; cout << "【火灾】采石场降级\n"; }
                } else {
                    int loss = rand() % 100 + 50;
                    money -= loss;
                    if (money < 0) money = 0;
                    cout << "【盗贼】被偷走 " << loss << " 金币\n";
                }
            } else {
                int e = rand() % 3;
                if (e == 0) {
                    gold_per_sec *= 1.5;
                    cout << "【丰收】收益提升\n";
                    Sleep(700);
                    gold_per_sec /= 1.5;
                } else if (e == 1) {
                    money += 200;
                    if (money > warehouse) money = warehouse;
                    cout << "【商人】获得 200 金币\n";
                } else {
                    money += 150;
                    cout << "【暴雨】作物增产\n";
                }
            }
            event_cd = 0;
            Sleep(700);
        }

        if (money >= task_target && !task_done) {
            money += task_reward;
            task_done = 1;
            cout << "【任务完成】奖励 " << task_reward << " 金币！\n";
            Sleep(700);
        }

        cout << "======= 经营游戏 =======\n";
        cout << "金币: " << money << " / " << warehouse << "\n";
        cout << "每秒收益: " << gold_per_sec << " | 维护费: " << upkeep << "/5s\n";
        cout << "目标: " << win_money << " 金币通关\n";
        cout << "任务: 赚到 " << task_target << " (完成: " << (task_done ? "是" : "否") << ")\n\n";

        cout << "1 金矿 Lv" << mine << " 价格" << mine_cost << "\n";
        cout << "2 农场 Lv" << farm << " 价格" << farm_cost << "\n";
        cout << "3 伐木场 Lv" << wood << " 价格" << wood_cost << "\n";
        cout << "4 采石场 Lv" << stone << " 价格" << stone_cost << "\n";
        cout << "5 升级仓库 价格" << warehouse/2 << "\n";
        cout << "6 科技1:收益+20% " << (tech1?"已学":"未学") << " 价格" << tech1_cost << "\n";
        cout << "7 科技2:维护-20% " << (tech2?"已学":"未学") << " 价格" << tech2_cost << "\n";
        cout << "8 科技3:仓库+50% " << (tech3?"已学":"未学") << " 价格" << tech3_cost << "\n";
        cout << "9 等待\n";
        cout << "========================\n";

        if (money >= win_money) {
            cout << "\n?? 恭喜通关！\n";
            system("pause");
            return 0;
        }

        int op;
        cin >> op;

        if (op == 1 && money >= mine_cost) {
            money -= mine_cost; mine++; gold_per_sec += mine_add; mine_cost *= 1.5;
        } else if (op == 2 && money >= farm_cost) {
            money -= farm_cost; farm++; gold_per_sec += farm_add; farm_cost *= 1.6;
        } else if (op == 3 && money >= wood_cost) {
            money -= wood_cost; wood++; gold_per_sec += wood_add; wood_cost *= 1.7;
        } else if (op == 4 && money >= stone_cost) {
            money -= stone_cost; stone++; gold_per_sec += stone_add; stone_cost *= 1.8;
        } else if (op == 5 && money >= warehouse/2) {
            money -= warehouse/2; warehouse *= 1.5;
        } else if (op == 6 && !tech1 && money >= tech1_cost) {
            money -= tech1_cost; tech1=1; gold_per_sec *= 1.2;
        } else if (op == 7 && !tech2 && money >= tech2_cost) {
            money -= tech2_cost; tech2=1;
        } else if (op == 8 && !tech3 && money >= tech3_cost) {
            money -= tech3_cost; tech3=1; warehouse *= 1.5;
        }

        Sleep(1000);
    }
    return 0;
}
