#include "../adv.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

using namespace adv;

// Global variables
std::string lastEventMessage = "None";
int eventMessageTimer = 0;
bool gameWon = false;

struct ColoredMessage {
    std::string text;
    color textColor;
};

ColoredMessage currentMessage;

// Poker checksum conversion
std::string checksumToPokerCard(int checksum) {
    switch(checksum) {
        case 0: return "K";
        case 1: return "A";
        case 2: return "2";
        case 3: return "3";
        case 4: return "4";
        case 5: return "5";
        case 6: return "6";
        case 7: return "7";
        case 8: return "8";
        case 9: return "9";
        case 10: return "X";
        case 11: return "J";
        case 12: return "Q";
        default: return "?";
    }
}

int pokerCardToChecksum(const std::string& card) {
    if (card == "K" || card == "k") return 0;
    if (card == "A" || card == "a") return 1;
    if (card == "2") return 2;
    if (card == "3") return 3;
    if (card == "4") return 4;
    if (card == "5") return 5;
    if (card == "6") return 6;
    if (card == "7") return 7;
    if (card == "8") return 8;
    if (card == "9") return 9;
    if (card == "X" || card == "x") return 10;
    if (card == "J" || card == "j") return 11;
    if (card == "Q" || card == "q") return 12;
    return -1;
}

int calculateChecksum(const std::string& data) {
    int sum = 0;
    for (char c : data) {
        if (isdigit(c)) sum += (c - '0');
    }
    return sum % 13;
}

std::string encodeSave(const std::vector<int>& values) {
    std::stringstream data;
    for (size_t i = 0; i < values.size(); i++) {
        if (i > 0) data << "N";
        data << values[i];
    }
    return "SV3A0DTA" + data.str() + "END" + checksumToPokerCard(calculateChecksum(data.str()));
}

bool decodeSave(const std::string& saveString, std::vector<int>& values) {
    size_t dtaPos = saveString.find("DTA");
    size_t endPos = saveString.find("END");
    if (dtaPos == std::string::npos || endPos == std::string::npos) return false;
    if (saveString.substr(0, 5) != "SV3A0") return false;
    
    std::string dataPart = saveString.substr(dtaPos + 3, endPos - dtaPos - 3);
    std::string pokerCard = saveString.substr(endPos + 3);
    int expectedChecksum = pokerCardToChecksum(pokerCard);
    if (expectedChecksum == -1) return false;
    if (calculateChecksum(dataPart) != expectedChecksum) return false;
    
    std::stringstream ss(dataPart);
    std::string token;
    values.clear();
    while (std::getline(ss, token, 'N')) {
        values.push_back(std::stoi(token));
    }
    return true;
}

std::string generateSaveString(int money, int gold_per_sec, int warehouse, int upkeep_mul, 
                                int bad_event_rate, int win_money, int mine, int mine_cost,
                                int farm, int farm_cost, int wood, int wood_cost, 
                                int stone, int stone_cost, int tech1, int tech2, int tech3,
                                int task_done, int level, int task_target, int task_reward) {
    std::vector<int> values = {
        money, gold_per_sec, warehouse, upkeep_mul, bad_event_rate, win_money,
        mine, mine_cost, farm, farm_cost, wood, wood_cost, stone, stone_cost,
        tech1, tech2, tech3, task_done, level, task_target, task_reward
    };
    return encodeSave(values);
}

bool loadFromSaveString(const std::string& saveData, int& money, int& gold_per_sec, int& warehouse, 
                        int& upkeep_mul, int& bad_event_rate, int& win_money, int& mine, int& mine_cost,
                        int& farm, int& farm_cost, int& wood, int& wood_cost, 
                        int& stone, int& stone_cost, int& tech1, int& tech2, int& tech3,
                        int& task_done, int& level, int& task_target, int& task_reward) {
    std::vector<int> values;
    if (!decodeSave(saveData, values)) return false;
    if (values.size() != 21) return false;
    
    int idx = 0;
    money = values[idx++];
    gold_per_sec = values[idx++];
    warehouse = values[idx++];
    upkeep_mul = values[idx++];
    bad_event_rate = values[idx++];
    win_money = values[idx++];
    mine = values[idx++];
    mine_cost = values[idx++];
    farm = values[idx++];
    farm_cost = values[idx++];
    wood = values[idx++];
    wood_cost = values[idx++];
    stone = values[idx++];
    stone_cost = values[idx++];
    tech1 = values[idx++];
    tech2 = values[idx++];
    tech3 = values[idx++];
    task_done = values[idx++];
    level = values[idx++];
    task_target = values[idx++];
    task_reward = values[idx++];
    return true;
}

void setMessage(const std::string& msg, color msgColor) {
    currentMessage.text = msg;
    currentMessage.textColor = msgColor;
    eventMessageTimer = 3;
}

void showHomeScreen(int selectedIndex) {
    advout.clearScreen();  // Instead of advcsr.clear()
    advout.setForegroundColor(YELLOW);
    advout.printline("|= Management Game 3.0  [Q] Quit [A] About =|");
    advout.reset();
    advout.printline("|                                           |");
    advout.setAttribute(BOLD);
    advout.printline("|  Home                                     |");
    advout.reset();
    advout.printline("|  Management Game is an idle/management    |");
    advout.printline("|  game where you build an economic empire. |");
    advout.printline("|                                           |");
    advout.printline("|                                           |");
    advout.printline("|  Select difficulty... [S/D]               |");
    
    if (selectedIndex == 0) {
        advout.printline("|  [Easy]   Normal   Hard                   |");
        advout.reset();
    } else if (selectedIndex == 1) {
        advout.printline("|  Easy   [Normal]   Hard                   |");
        advout.reset();
    } else if (selectedIndex == 2) {
        advout.printline("|  Easy   Normal   [Hard]                   |");
        advout.reset();
    } else {
        advout.printline("|  Easy    Normal    Hard                   |");
    }
    
    advout.printline("|                                           |");
    advout.printline("|  Or paste save string [press P]...        |");
    advout.printline("|                                           |");
    advout.printline("|                                           |");
    advout.printline("|===========================================|");
    advout.flush();
}

void showInputScreen() {
    advout.clearScreen();  // Instead of advcsr.clear()
    advout.setForegroundColor(YELLOW);
    advout.printline("|= Input save string... - Management Game ==|");
    advout.reset();
    advout.printline("| >>> ");
    advout.flush();
}

void showAboutScreen() {
    advout.clearScreen();  // Instead of advcsr.clear()
    advout.setForegroundColor(YELLOW);
    advout.printline("|= About - Management Game =================|");
    advout.reset();
    advout.printline("|                                           |");
    advout.setAttribute(BOLD);
    advout.printline("|  Intro                                    |");
    advout.reset();
    advout.printline("|  Management Game is an idle/management    |");
    advout.printline("|  game where you build an economic empire. |");
    advout.printline("|                                           |");
    advout.setAttribute(BOLD);
    advout.printline("|  Developers                               |");
    advout.reset();
    advout.printline("|  [Idea]        Houyc11                    |");
    advout.printline("|  [Improved by] politetrex                 |");
    advout.printline("|                                           |");
    advout.printline("|  Version 3.0                              |");
    advout.printline("|                           Press E to exit |");
    advout.printline("|                                           |");
    advout.printline("|===========================================|");
    advout.flush();
}

void redrawGame(int money, int warehouse, int gold_per_sec, int upkeep, int win_money, 
                int level, int task_target, int task_done, int mine, int mine_cost,
                int farm, int farm_cost, int wood, int wood_cost, int stone, int stone_cost,
                int tech1, int tech2, int tech3, int tech1_cost, int tech2_cost, int tech3_cost) {
    
    advout.clearScreen();  // Clear the entire screen
    
    advout.setForegroundColor(YELLOW);
    advout.printline("|= Management Game 3.0 ========= [A] About =|");
    advout.reset();
    
    // Message line
    advout << "| Messages: ";
    if (eventMessageTimer > 0 && !currentMessage.text.empty()) {
        advout.setForegroundColor(currentMessage.textColor);
        advout << currentMessage.text;
        advout.reset();
        int len = 12 + currentMessage.text.length();
        for (int i = len; i < 43; i++) advout << " ";
    } else {
        advout<<"None                           ";
    }
    advout << " |\n";
    
    // Gold line
    advout << "| Gold: ";
    int remaining = warehouse - money;
    if (money >= warehouse) {
        advout.setForegroundColor(RED);
    } else if (remaining <= 256) {
        advout.setForegroundColor(YELLOW);
    }
    advout << money << "/" << warehouse;
    advout.reset();
    advout << " Inc:" << gold_per_sec;
    
    int goldLen = 7 + std::to_string(money).length() + std::to_string(warehouse).length() + 5 + std::to_string(gold_per_sec).length() + 1;
    for (int i = goldLen; i < 42; i++) advout << " ";
    advout << " |\n";
    
    // Upkeep line
    std::string upkeepStr = "Upkeep: " + std::to_string(upkeep) + "/5s   Task:" + std::to_string(task_target);
    advout << "| " << upkeepStr;
    for (int i = (int)upkeepStr.length(); i < 41; i++) advout << " ";
    advout << " |\n";
    
    // Target line
    std::string targetStr = "Target: " + std::to_string(win_money) + "   [LVL " + std::to_string(level) + "]";
    advout << "| " << targetStr;
    for (int i = (int)targetStr.length(); i < 41; i++) advout << " ";
    advout << " |\n";
    
    advout.printline("|-------------------------------------------|");
    
    // Buildings
    std::string mineStr = "1.Mine  [Lv" + std::to_string(mine) + "] Cost:" + std::to_string(mine_cost);
    advout << "| " << mineStr;
    for (int i = (int)mineStr.length(); i < 41; i++) advout << " ";
    advout << " |\n";
    
    std::string farmStr = "2.Farm  [Lv" + std::to_string(farm) + "] Cost:" + std::to_string(farm_cost);
    advout << "| " << farmStr;
    for (int i = (int)farmStr.length(); i < 41; i++) advout << " ";
    advout << " |\n";
    
    std::string woodStr = "3.Lumber[Lv" + std::to_string(wood) + "] Cost:" + std::to_string(wood_cost);
    advout << "| " << woodStr;
    for (int i = (int)woodStr.length(); i < 41; i++) advout << " ";
    advout << " |\n";
    
    std::string stoneStr = "4.Quarry[Lv" + std::to_string(stone) + "] Cost:" + std::to_string(stone_cost);
    advout << "| " << stoneStr;
    for (int i = (int)stoneStr.length(); i < 41; i++) advout << " ";
    advout << " |\n";
    
    // Warehouse
    int newCap = warehouse * 3 / 2;
    std::string wareStr = "5.Warehouse Cost:" + std::to_string(warehouse/2) + " ->" + std::to_string(newCap);
    advout << "| " << wareStr;
    for (int i = (int)wareStr.length(); i < 41; i++) advout << " ";
    advout << " |\n";
    
    advout.printline("|-------------------------------------------|");
    
    // Tech1
    if (!tech1) advout.setForegroundColor(YELLOW);
    else advout.setForegroundColor(GREEN);
    std::string tech1Str = "6.Tech1 +20% Inc  [" + std::string(tech1 ? "LEARNED" : "Cost  " + std::to_string(tech1_cost)) + "]";
    advout << "| " << tech1Str;
    for (int i = (int)tech1Str.length(); i < 41; i++) advout << " ";
    advout << " |\n";
    advout.reset();
    
    // Tech2
    if (!tech2) advout.setForegroundColor(YELLOW);
    else advout.setForegroundColor(GREEN);
    std::string tech2Str = "7.Tech2 -20% Upk  [" + std::string(tech2 ? "LEARNED" : "Cost  " + std::to_string(tech2_cost)) + "]";
    advout << "| " << tech2Str;
    for (int i = (int)tech2Str.length(); i < 41; i++) advout << " ";
    advout << " |\n";
    advout.reset();
    
    // Tech3
    if (!tech3) advout.setForegroundColor(YELLOW);
    else advout.setForegroundColor(GREEN); 
    std::string tech3Str = "8.Tech3 +50% Cap  [" + std::string(tech3 ? "LEARNED" : "Cost " + std::to_string(tech3_cost)) + "]";
    advout << "| " << tech3Str;
    for (int i = (int)tech3Str.length(); i < 41; i++) advout << " ";
    advout << " |\n";
    advout.reset();
    
    advout.printline("|-------------------------------------------|");
    advout.setForegroundColor(YELLOW);
    advout.printline("| 9.Wait 0.Exit S.Save A.About              |");
    advout.printline("|===========================================|");
    advout.reset();
    
    advout << "\nChoice: ";
    advout.flush();
}
int main() {
    srand(time(nullptr));
    
    int money, gold_per_sec, warehouse;
    int upkeep_mul;
    int bad_event_rate;
    int win_money;
    int level = 1;
    int task_target = 5000;
    int task_reward = 600;
    
    int mine = 0, mine_cost = 50, mine_add = 2;
    int farm = 0, farm_cost = 80, farm_add = 3;
    int wood = 0, wood_cost = 120, wood_add = 5;
    int stone = 0, stone_cost = 150, stone_add = 7;
    int tech1 = 0, tech2 = 0, tech3 = 0;
    int tech1_cost = 500, tech2_cost = 800, tech3_cost = 1200;
    int task_done = 0;
    
    int upkeep = 0;
    int upkeep_cd = 0;
    int event_cd = 0;
    int temp_bonus = 0;
    bool game_running = true;
    bool gameWonFlag = false;
    bool inGame = false;
    
    advcsr.hide();
    
    while (game_running) {
        if (!inGame) {
            int selectedIndex = 1;
            showHomeScreen(selectedIndex);
            
            while (true) {
                char key = advin.wait_press_char();
                
                if (key == 'A' || key == 'a') {
                    showAboutScreen();
                    while (true) {
                        char c = advin.wait_press_char();
                        if (c == 'E' || c == 'e') break;
                    }
                    showHomeScreen(selectedIndex);
                } else if (key == 'Q' || key == 'q') {\
                    advout.clearScreen();
                    advout<<"|= Management Game 3.0 =====================|\n";
                    advout<<"|                                           |\n";
                    advout<<"| Do you really want to quit?               |\n";
                    advout<<"| Press Y or y if you're certain to quit.   |\n";
                    advout<<"|                                           |\n";
                    advout<<"|===========================================|\n";
                    advout.flush();
                    char c = advin.wait_press_char();
                    if (c == 'Y' || c == 'y'){
                        advout.clearScreen();
                        advout<<"Quitting game...";
                        advout.flush();

                        // Full set of resetting before quit
                        advcsr.show();
                        advout.reset();
                        advin.clear_buffer();
                        
                        return 0;
                    }
                    showHomeScreen(selectedIndex);
                } else if (key == 'S' || key == 's') {
                    selectedIndex = (selectedIndex + 2) % 3;
                    showHomeScreen(selectedIndex);
                } else if (key == 'D' || key == 'd') {
                    selectedIndex = (selectedIndex + 1) % 3;
                    showHomeScreen(selectedIndex);
                } else if (key == 'P' || key == 'p') {
                    showInputScreen();
                    std::string saveString;
                    std::cin >> saveString;
                    
                    if (loadFromSaveString(saveString, money, gold_per_sec, warehouse, upkeep_mul, 
                                            bad_event_rate, win_money, mine, mine_cost, farm, farm_cost,
                                            wood, wood_cost, stone, stone_cost, tech1, tech2, tech3,
                                            task_done, level, task_target, task_reward)) {
                        inGame = true;
                        setMessage("Game loaded", GREEN);
                        break;
                    } else {
                        showHomeScreen(selectedIndex);
                        advout.setForegroundColor(RED);
                        advout.printline("|  Invalid save string!                 |");
                        advout.reset();
                        wait_s(1);
                        showHomeScreen(selectedIndex);
                    }
                } else if (key == '\r' || key == '\n') {
                    if (selectedIndex == 0) {
                        money = 500; gold_per_sec = 2; warehouse = 8000;
                        upkeep_mul = 1; bad_event_rate = 20; win_money = 20000;
                    } else if (selectedIndex == 1) {
                        money = 300; gold_per_sec = 1; warehouse = 5000;
                        upkeep_mul = 2; bad_event_rate = 40; win_money = 30000;
                    } else {
                        money = 150; gold_per_sec = 1; warehouse = 3000;
                        upkeep_mul = 3; bad_event_rate = 70; win_money = 50000;
                    }
                    
                    level = 1;
                    mine = 0; mine_cost = 50;
                    farm = 0; farm_cost = 80;
                    wood = 0; wood_cost = 120;
                    stone = 0; stone_cost = 150;
                    tech1 = 0; tech2 = 0; tech3 = 0;
                    tech1_cost = 500; tech2_cost = 800; tech3_cost = 1200;
                    task_done = 0;
                    temp_bonus = 0;
                    upkeep_cd = 0;
                    event_cd = 0;
                    inGame = true;
                    setMessage("New game started", GREEN);
                    break;
                }
            }
        }
        
        while (inGame && game_running) {
            // Calculate current income with tech1 and temp bonus
            int now_income = gold_per_sec + temp_bonus;
            if (tech1) now_income = now_income * 6 / 5;
            
            if (money < warehouse) {
                money += now_income;
                if (money > warehouse) money = warehouse;
            }
            if (money < 0) money = 0;
            
            temp_bonus = 0;
            
            // Upkeep system
            upkeep_cd++;
            if (upkeep_cd >= 5) {
                upkeep = (mine + farm + wood + stone) * 2 * upkeep_mul;
                if (tech2) upkeep = upkeep * 4 / 5;
                money -= upkeep;
                if (money < 0) money = 0;
                upkeep_cd = 0;
            }
            
            // Event system
            event_cd++;
            if (event_cd >= 4) {
                int r = rand() % 100;
                if (r < bad_event_rate) {
                    int e = rand() % 2;
                    if (e == 0) {
                        int b = rand() % 4;
                        if (b == 0 && mine > 0) {
                            mine--;
                            gold_per_sec -= mine_add;
                            setMessage("Fire! Mine downgraded", RED);
                        } else if (b == 1 && farm > 0) {
                            farm--;
                            gold_per_sec -= farm_add;
                            setMessage("Fire! Farm destroyed", RED);
                        } else if (b == 2 && wood > 0) {
                            wood--;
                            gold_per_sec -= wood_add;
                            setMessage("Fire! Lumber burned", RED);
                        } else if (b == 3 && stone > 0) {
                            stone--;
                            gold_per_sec -= stone_add;
                            setMessage("Fire! Quarry collapsed", RED);
                        } else {
                            setMessage("Fire! False alarm", YELLOW);
                        }
                    } else {
                        int loss = rand() % 100 + 50;
                        money -= loss;
                        if (money < 0) money = 0;
                        setMessage("Thief stole " + std::to_string(loss) + " gold", RED);
                    }
                } else {
                    int e = rand() % 3;
                    if (e == 0) {
                        temp_bonus = gold_per_sec / 2;
                        setMessage("Harvest! Income boosted", GREEN);
                    } else if (e == 1) {
                        money += 200;
                        if (money > warehouse) money = warehouse;
                        setMessage("Merchant gave 200 gold", GREEN);
                    } else {
                        money += 150;
                        if (money > warehouse) money = warehouse;
                        setMessage("Rain! Extra 150 gold", GREEN);
                    }
                }
                event_cd = 0;
            }
            
            if (eventMessageTimer > 0) {
                eventMessageTimer--;
                if (eventMessageTimer == 0) currentMessage.text = "";
            }
            
            if (money >= task_target && !task_done) {
                money += task_reward;
                if (money > warehouse) money = warehouse;
                task_done = 1;

                // Show checkpoint reached message
                advout.clearScreen();
                redrawGame(money, warehouse, gold_per_sec, upkeep, win_money, level, 
                           task_target, task_done, mine, mine_cost, farm, farm_cost, 
                           wood, wood_cost, stone, stone_cost, tech1, tech2, tech3,
                           tech1_cost, tech2_cost, tech3_cost);
                advout.setForegroundColor(YELLOW);
                advout.printline("\n\n        +============================+");
                advout.printline("        |      CHECKPOINT REACHED!    |");
                advout.printline("        +============================+");
                advout.printline("        |    Task: " + std::to_string(task_target) + " gold      |");
                advout.printline("        |    Reward: +" + std::to_string(task_reward) + " gold    |");
                advout.printline("        +============================+");
                advout.reset();
                advout.flush();
                wait_s(2);
                
                setMessage("Checkpoint reached! +" + std::to_string(task_reward) + " gold", CYAN);
            }
            
            // Win condition with goal doubling
            if (money >= win_money && !gameWonFlag) {
                gameWonFlag = true;
                advout.clearScreen();
                advout.setForegroundColor(YELLOW);
                advout.printline("");
                advout.printline("+=========================================================================+");
                advout.printline("|                          CONGRATULATIONS!                              |");
                advout.printline("+=========================================================================+");
                advout.printline("|                                                                         |");
                advout.printline("|                      You have reached " + std::to_string(win_money) + " gold!                      |");
                advout.printline("|                                                                         |");
                advout.printline("+=========================================================================+");
                advout.reset();
                advout.printline("");
                advout.setForegroundColor(CYAN);
                advout.printline("Continue playing? (Y/N)");
                advout.printline("(Goal will double to " + std::to_string(win_money * 2) + " gold)");
                advout.reset();
                advout.flush();

                char continueChoice;
                std::cin >> continueChoice;

                if (continueChoice == 'Y' || continueChoice == 'y') {
                    win_money = win_money * 2;  // Goal doubles
                    level++;
                    task_target = task_target + 5000;  // Task target increases by 5000 each checkpoint
                    task_reward = task_reward + 200;    // Reward increases each checkpoint
                    task_done = 0;  // Reset task for next checkpoint
                    gameWonFlag = false;
                    setMessage("New goal: " + std::to_string(win_money) + " gold, Task: " + std::to_string(task_target), CYAN);
                } else {
                    inGame = false;
                    gameWonFlag = false;
                    break;
                }
            }
            
            redrawGame(money, warehouse, gold_per_sec, upkeep, win_money, level, 
                       task_target, task_done, mine, mine_cost, farm, farm_cost, 
                       wood, wood_cost, stone, stone_cost, tech1, tech2, tech3,
                       tech1_cost, tech2_cost, tech3_cost);
            
            char opStr = advin.wait_press_char();
            
            if (opStr == '1' && money >= mine_cost) {
                money -= mine_cost;
                mine++;
                gold_per_sec += mine_add;
                mine_cost = mine_cost * 3 / 2;
                setMessage("Mine upgraded to Lv" + std::to_string(mine), GREEN);
            } else if (opStr == '2' && money >= farm_cost) {
                money -= farm_cost;
                farm++;
                gold_per_sec += farm_add;
                farm_cost = farm_cost * 8 / 5;
                setMessage("Farm upgraded to Lv" + std::to_string(farm), GREEN);
            } else if (opStr == '3' && money >= wood_cost) {
                money -= wood_cost;
                wood++;
                gold_per_sec += wood_add;
                wood_cost = wood_cost * 17 / 10;
                setMessage("Lumber upgraded to Lv" + std::to_string(wood), GREEN);
            } else if (opStr == '4' && money >= stone_cost) {
                money -= stone_cost;
                stone++;
                gold_per_sec += stone_add;
                stone_cost = stone_cost * 9 / 5;
                setMessage("Quarry upgraded to Lv" + std::to_string(stone), GREEN);
            } else if (opStr == '5' && money >= warehouse/2) {
                money -= warehouse/2;
                warehouse = warehouse * 3 / 2;
                setMessage("Warehouse expanded to " + std::to_string(warehouse), GREEN);
            } else if (opStr == '6' && !tech1 && money >= tech1_cost) {
                money -= tech1_cost;
                tech1 = 1;
                setMessage("Tech1 learned: Income +20%", CYAN);
            } else if (opStr == '7' && !tech2 && money >= tech2_cost) {
                money -= tech2_cost;
                tech2 = 1;
                setMessage("Tech2 learned: Upkeep -20%", CYAN);
            } else if (opStr == '8' && !tech3 && money >= tech3_cost) {
                money -= tech3_cost;
                tech3 = 1;
                warehouse = warehouse * 3 / 2;
                setMessage("Tech3 learned: Warehouse +50%", CYAN);
            } else if (opStr == '9') {
                // Just wait
            } else if (opStr == '0') {
                inGame = false;
                break;
            } else if (opStr == 'S' || opStr == 's') {
                std::string saveString = generateSaveString(money, gold_per_sec, warehouse, upkeep_mul, 
                                                             bad_event_rate, win_money, mine, mine_cost,
                                                             farm, farm_cost, wood, wood_cost, 
                                                             stone, stone_cost, tech1, tech2, tech3,
                                                             task_done, level, task_target, task_reward);
                advcsr.clear();
                advout.setForegroundColor(CYAN);
                advout.printline("\n+=========================================================================+");
                advout.printline("|                             SAVE STRING                                 |");
                advout.printline("+=========================================================================+");
                advout.reset();
                advout.setForegroundColor(YELLOW);
                advout.printline(saveString);
                advout.reset();
                advout.setForegroundColor(CYAN);
                advout.printline("+=========================================================================+");
                advout.reset();
                advout.printline("\nCopy this string to load your game later!");
                advout.printline("Press any key to continue...");
                advout.flush();
                advin.wait_press_char();
            } else if (opStr == 'A' || opStr == 'a') {
                showAboutScreen();
                while (true) {
                    char c = advin.wait_press_char();
                    if (c == 'E' || c == 'e') break;
                }
            } else {
                setMessage("Invalid choice!", RED);
            }
            wait_ms(128); // to prevent spamming 9s
        }
    }
    
    advcsr.show();
    return 0;
}