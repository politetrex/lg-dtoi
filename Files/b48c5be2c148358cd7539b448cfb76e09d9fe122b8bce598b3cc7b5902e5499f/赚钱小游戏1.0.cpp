#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0)); // 初始化随机事件种子

    // 核心资源
    int money = 200;          // 初始金币
    int gold_per_sec = 1;     // 每秒总收益
    int warehouse_max = 5000; // 仓库上限（金币存满就不产钱）

    // 4种建筑：金矿、农场、伐木场、采石场（各有收益和成本）
    int mine_lv = 0, mine_cost = 50, mine_add = 2;
    int farm_lv = 0, farm_cost = 80, farm_add = 3;
    int wood_lv = 0, wood_cost = 120, wood_add = 5;
    int stone_lv = 0, stone_cost = 150, stone_add = 7;

    // 随机事件冷却（3秒触发一次）
    int event_cd = 0;

    cout << "======= 小镇经营·第二阶段 =======" << endl;
    cout << "目标：赚到 20000 金币 + 仓库升级至满级！" << endl;
    cout << "提示：仓库有上限，满了会停止产钱；每3秒有随机事件！" << endl;
    cout << "----------------------------------" << endl;
    Sleep(2000); // 等待2秒，让玩家看清提示

    while (true) {
        system("cls");

        // 1. 自动产钱（判断仓库是否未满）
        if (money < warehouse_max) {
            money += gold_per_sec;
            // 防止金币超出仓库上限
            if (money > warehouse_max) money = warehouse_max;
        }

        // 2. 随机事件（每3秒触发一次）
        event_cd++;
        if (event_cd >= 3) {
            int event = rand() % 4; // 0-3 四种事件
            switch (event) {
                case 0: // 丰收：所有收益+50%（持续1秒）
                    cout << "\n?? 【丰收事件】1秒内收益翻倍！" << endl;
                    gold_per_sec *= 1.5;
                    Sleep(1000);
                    gold_per_sec /= 1.5;
                    break;
                case 1: // 火灾：随机一个建筑降级（最低0级）
                {
                    int build = rand() % 4;
                    if (build == 0 && mine_lv > 0) { mine_lv--; gold_per_sec -= mine_add; cout << "\n?? 【火灾事件】金矿降级！" << endl; }
                    else if (build == 1 && farm_lv > 0) { farm_lv--; gold_per_sec -= farm_add; cout << "\n?? 【火灾事件】农场降级！" << endl; }
                    else if (build == 2 && wood_lv > 0) { wood_lv--; gold_per_sec -= wood_add; cout << "\n?? 【火灾事件】伐木场降级！" << endl; }
                    else if (build == 3 && stone_lv > 0) { stone_lv--; gold_per_sec -= stone_add; cout << "\n?? 【火灾事件】采石场降级！" << endl; }
                    else cout << "\n?? 【火灾事件】幸运！没有建筑受损！" << endl;
                    Sleep(1000);
                    break;
                }
                case 2: // 商人：高价回收（金币+200）
                    money += 200;
                    if (money > warehouse_max) money = warehouse_max;
                    cout << "\n?? 【商人事件】获得200金币！" << endl;
                    Sleep(1000);
                    break;
                case 3: // 无事发生
                    break;
            }
            event_cd = 0; // 重置冷却
        }

        // 3. 状态展示（清晰显示所有信息）
        cout << "======= 经营状态 =======" << endl;
        cout << "当前金币：" << money << " / " << warehouse_max << "（仓库上限）" << endl;
        cout << "每秒总收益：" << gold_per_sec << endl;
        cout << endl;
        cout << "建筑列表：" << endl;
        cout << "1. 金矿 LV" << mine_lv << " | 升级价：" << mine_cost << " | 每级+2收益" << endl;
        cout << "2. 农场 LV" << farm_lv << " | 升级价：" << farm_cost << " | 每级+3收益" << endl;
        cout << "3. 伐木场 LV" << wood_lv << " | 升级价：" << wood_cost << " | 每级+5收益" << endl;
        cout << "4. 采石场 LV" << stone_lv << " | 升级价：" << stone_cost << " | 每级+7收益" << endl;
        cout << "5. 等待收益（仓库未满时生效）" << endl;
        cout << "6. 升级仓库（当前上限：" << warehouse_max << "，升级价：" << warehouse_max / 2 << "）" << endl;
        cout << "========================" << endl;

        // 4. 胜利条件（难度提升，更有挑战性）
        if (money >= 20000 && warehouse_max >= 10000) {
            cout << "\n?? 恭喜！达成终极目标，小镇经营圆满成功！" << endl;
            break;
        }

        // 5. 操作菜单
        cout << "请选择操作（1-6）：";
        int op;
        cin >> op;

        // 建筑升级逻辑
        switch (op) {
            case 1: // 升级金矿
                if (money >= mine_cost) {
                    money -= mine_cost;
                    mine_lv++;
                    gold_per_sec += mine_add;
                    mine_cost *= 1.5; // 升级涨价
                    cout << "? 金矿升级成功！" << endl;
                } else cout << "? 金币不足！" << endl;
                break;
            case 2: // 升级农场
                if (money >= farm_cost) {
                    money -= farm_cost;
                    farm_lv++;
                    gold_per_sec += farm_add;
                    farm_cost *= 1.6;
                    cout << "? 农场升级成功！" << endl;
                } else cout << "? 金币不足！" << endl;
                break;
            case 3: // 升级伐木场
                if (money >= wood_cost) {
                    money -= wood_cost;
                    wood_lv++;
                    gold_per_sec += wood_add;
                    wood_cost *= 1.7;
                    cout << "? 伐木场升级成功！" << endl;
                } else cout << "? 金币不足！" << endl;
                break;
            case 4: // 升级采石场
                if (money >= stone_cost) {
                    money -= stone_cost;
                    stone_lv++;
                    gold_per_sec += stone_add;
                    stone_cost *= 1.8;
                    cout << "? 采石场升级成功！" << endl;
                } else cout << "? 金币不足！" << endl;
                break;
            case 5: // 等待收益
                cout << "? 等待收益中..." << endl;
                break;
            case 6: // 升级仓库（解决仓库满了不产钱的问题）
                if (money >= warehouse_max / 2) {
                    money -= warehouse_max / 2;
                    warehouse_max *= 1.5; // 仓库上限提升50%
                    cout << "? 仓库升级成功！新上限：" << warehouse_max << endl;
                } else cout << "? 金币不足！升级仓库需要" << warehouse_max / 2 << "金币" << endl;
                break;
            default:
                cout << "? 无效操作，请重新选择！" << endl;
                break;
        }

        Sleep(1000); // 每秒刷新一次
    }

    return 0;
}
