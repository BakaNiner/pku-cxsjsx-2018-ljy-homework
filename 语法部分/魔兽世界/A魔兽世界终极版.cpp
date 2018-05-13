#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

char mobName[][10] = {"dragon", "ninja", "iceman", "lion", "wolf"};
char weaponName[][10] = {"sword", "bomb", "arrow"};
int mobCost[5] = {0};
int mobAttack[5] = {0};

int cityFlag[25] = {0}; // 当前城市的旗子情况 0表示无旗子 1表示红方 -1表示蓝方
int cityLastWin[25] = {0}; // 当前城市上次赢的是谁 0表示平局 1表示红方 -1表示蓝方 
int cityHealth[25] = {0}; // 当前城市的生命元 
int cityNumber;
int arrowAttack;
int loyaltyDecay;
int clo;
bool gameStop;

class mob;
vector<mob *> winWarrior[2]; // 0蓝 1红 

vector<string> info[25];

class mob {
public:
	char *color; // 属于哪一方
	int id; // 生物类型 
	int number; // 编号 
	int health; // 血量 
	int attack; // 攻击力 
	int sword; // sword攻击力 
	int bomb; // bomb个数 
	int arrow; // 等价arrow个数 
	double morale; // 如果是dragon 那么有士气 
	int loyalty; // 如果是lion 那么有忠诚度 
	int city; // 当前在哪个城市
	int predamage; // 战斗前受的伤害 

	mob(char *_color, int _id, int _number, int _health, int _attack, int _weapon = -1, int _weapon2 = -1, int _loyalty = -1, double _morale = -1)
	   : color(_color), id(_id), number(_number), health(_health), attack(_attack), sword(0), bomb(0), arrow(0), loyalty(_loyalty), morale(_morale), predamage(0) {
		if(_weapon == 0)
			sword = attack / 5;
		else if(_weapon == 1)
			bomb = 1;
		else if(_weapon == 2)
			arrow += 3;
		if(_weapon2 == 0)
			sword = attack / 5;
		else if(_weapon2 == 1)
			bomb = 1;
		else if(_weapon2 == 2)
			arrow += 3;

		if(color[0] == 'r')
			city = 0;
		else
			city = cityNumber + 1;
	}

	bool arrived() {
		if(color[0] == 'r' && city == cityNumber + 1)
			return 1;
		if(color[0] == 'b' && city == 0)
			return 1;
		return 0;
	}

	void move() {
		if(city == -1)
			return;

		if(color[0] == 'r')
			if(city == cityNumber + 1)
				city = -1;
			else
				city = min(city + 1, cityNumber + 1);
		else
			if(city == 0)
				city = -1;
			else
				city = max(city - 1, 0);

		if(city == -1)
			return;

		if(id == 2) {
			int dis = 0;
			if(color[0] == 'r')
				dis = city;
			else
				dis = cityNumber + 1 - city;

			if(~dis & 1) {
				health = max(health - 9, 1);
				attack += 20;
			}
		}
	}

	void loot(mob &x) {
		if(sword == 0 && x.sword > 0)
			sword = x.sword;
		if(arrow == 0 && x.arrow > 0)
			arrow = x.arrow;
		if(bomb == 0 && x.bomb > 0)
			bomb = x.bomb;
	}

	// 返回1代表自己要使用bomb 返回-1代表对方要使用bomb 
	int battle(mob &x) {
		health -= predamage;
		predamage = 0;
		x.health -= x.predamage;
		x.predamage = 0;
		int who = color[0] == 'r' ? 1 : -1;

		int blood1 = 0, blood2 = 0;
		if(id == 3)
			blood1 = max(0, health);
		if(x.id == 3)
			blood2 = max(0, x.health);

		if(health <= 0 && x.health <= 0)
			return 0;
		else if(health > 0 && x.health <= 0) { 
			if(id == 0) {
				morale += 0.2;
				if(morale > 0.8) {
					char tmp[500] = {0};
					sprintf(tmp, "%03d:40 %s dragon %d yelled in city %d\n", clo / 60, color, number, city);
					info[city].push_back(string(tmp));
				}
			}
			else if(id == 4)
				loot(x);

			health += blood2;
			winWarrior[who == 1].push_back(this);
			return 0;
		}
		else if(health <= 0 && x.health > 0) {
			if(x.id == 0)
				x.morale += 0.2;
			else if(x.id == 4)
				x.loot(*this);

			x.health += blood1;
			winWarrior[-who == 1].push_back(&x);
			return 0;
		}

		x.health -= attack + sword;
		sword = sword * 4 / 5;
		{
			char tmp[500] = {0};
			sprintf(tmp, "%03d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", clo / 60, color, mobName[id], number, x.color, mobName[x.id], x.number, city, health, attack);
			info[city].push_back(string(tmp));
		}

		if(x.health <= 0) {
			char tmp[500] = {0};
			sprintf(tmp, "%03d:40 %s %s %d was killed in city %d\n", clo / 60, x.color, mobName[x.id], x.number, city);
			info[city].push_back(string(tmp));
			if(id == 0) {
				morale += 0.2;
				if(morale > 0.8) {
					char tmp[500] = {0};
					sprintf(tmp, "%03d:40 %s dragon %d yelled in city %d\n", clo / 60, color, number, city);
					info[city].push_back(string(tmp));
				}
			}
			else if(id == 4)
				loot(x);

			health += blood2;
			winWarrior[who == 1].push_back(this);
			return -1;
		}

		if(x.id == 1) {
			if(id == 0) {
				morale -= 0.2;
				if(morale > 0.8) {
					char tmp[500] = {0};
					sprintf(tmp, "%03d:40 %s dragon %d yelled in city %d\n", clo / 60, color, number, city);
					info[city].push_back(string(tmp));
				}
			}
			return 0;
		}

		health -= x.attack / 2 + x.sword;
		x.sword = x.sword * 4 / 5;
		{
			char tmp[500] = {0};
			sprintf(tmp, "%03d:40 %s %s %d fought back against %s %s %d in city %d\n", clo / 60, x.color, mobName[x.id], x.number, color, mobName[id], number, city);
			info[city].push_back(string(tmp));
		}

		if(health <= 0) {
			char tmp[500] = {0};
			sprintf(tmp, "%03d:40 %s %s %d was killed in city %d\n", clo / 60, color, mobName[id], number, city);
			info[city].push_back(string(tmp));
			if(x.id == 0)
				x.morale += 0.2;
			else if(x.id == 4)
				x.loot(*this);

			x.health += blood1;
			winWarrior[-who == 1].push_back(&x);
			return 1;
		}

		if(id == 0)
			morale -= 0.2;
		if(x.id == 0)
			x.morale -= 0.2;

		if(id == 0 && morale > 0.8) {
			char tmp[500] = {0};
			sprintf(tmp, "%03d:40 %s dragon %d yelled in city %d\n", clo / 60, color, number, city);
			info[city].push_back(string(tmp));
		}

		if(id == 3)
			loyalty -= loyaltyDecay;
		if(x.id == 3)
			x.loyalty -= loyaltyDecay;

		return 0;	
	}

	void report() {
		printf("%03d:55 %s %s %d has ", clo / 60, color, mobName[id], number);
		if(sword == 0 && arrow == 0 && bomb == 0) {
			printf("no weapon\n");
			return;
		}
		bool flag = 0;
		if(arrow > 0) {
			printf("arrow(%d)", arrow);
			flag = 1;
		}
		if(bomb > 0) {
			if(flag)
				printf(",");
			printf("bomb");
			flag = 1;
		}
		if(sword > 0) {
			if(flag)
				printf(",");
			printf("sword(%d)", sword);
		}
		printf("\n");
	}
};

class cmd {
public:
	char name[5]; // 司令部颜色 
	int health; // 生命元 
	int list[5]; // 造兵序列 
	int mobNumber; // 士兵个数 
	int lastMobId; // 上次造兵在序列中的id 
	int beToken; // 被几个敌军占领了司令部 如果有2个那么游戏结束 
	vector<mob> warrior; // 士兵们 

	cmd(const char *s, int h) {
		strcpy(name, s);
		health = h;
		if(name[0] == 'r') {
			list[0] = 2; list[1] = 3; list[2] = 4; list[3] = 1; list[4] = 0;
		} else {
			list[0] = 3; list[1] = 0; list[2] = 1; list[3] = 2; list[4] = 4;
		}
		mobNumber = 0;
		lastMobId = -1;
		beToken = 0;
	}

	int getId() {
		int i = (lastMobId + 1) % 5;
		if(mobCost[list[i]] <= health) return i;
		return -1;
	}

	void createMob() {
		int id = getId();
		if(id == -1) return;
		lastMobId = id;
		id = list[id];

		health -= mobCost[id];
		mobNumber++;
		printf("%03d:00 %s %s %d born\n", clo / 60, name, mobName[id], mobNumber);
		// dragon
		if(id == 0) {
			mob x(name, id, mobNumber, mobCost[id], mobAttack[id], mobNumber % 3, -1, -1, health /(double) mobCost[id]);
			warrior.push_back(x);
			printf("Its morale is %.2f\n", health /(double) mobCost[id]);
		}
		// ninja
		else if(id == 1) {
			mob x(name, id, mobNumber, mobCost[id], mobAttack[id], mobNumber % 3, (mobNumber + 1) % 3);
			warrior.push_back(x);
		}
		// iceman
		else if(id == 2) {
			mob x(name, id, mobNumber, mobCost[id], mobAttack[id], mobNumber % 3);
			warrior.push_back(x);
		}
		// lion
		else if(id == 3) {
			mob x(name, id, mobNumber, mobCost[id], mobAttack[id], -1, -1, health);
			warrior.push_back(x);
			printf("Its loyalty is %d\n", health);
		}
		// wolf
		else if(id == 4) {
			mob x(name, id, mobNumber, mobCost[id], mobAttack[id]);
			warrior.push_back(x);
		}
	}

	void lionUpdateAt(int p) {
		for(mob &x : warrior)
			if(x.id == 3 && x.health > 0 && x.loyalty <= 0 && !x.arrived() && x.city == p) {
				x.health = 0;
				printf("%03d:05 %s lion %d ran away\n", clo / 60, name, x.number);
			}
	}

	void moveWarrior() {
		for(mob &x : warrior)
			if(x.health > 0)
				x.move();
	}

	int selectWarriorAt(int p) {
		int a = 0;
		for(; a < warrior.size(); a++)
			if(warrior[a].health > 0 && warrior[a].city == p)
				break;
		if(a == warrior.size())
			a = -1;
		return a;
	}

	void reportHealth() {
		printf("%03d:50 %d elements in %s headquarter\n", clo / 60, health, name);
	}
};

void createMob(cmd &red, cmd &blue) {
	if(gameStop) return;
	red.createMob();
	blue.createMob();
}

void lionUpdate(cmd &red, cmd &blue) {
	if(gameStop) return;
	for(int i = 0; i <= cityNumber + 1; i++) {
		red.lionUpdateAt(i);
		blue.lionUpdateAt(i);
	}
}

void moveWarrior(cmd &red, cmd &blue) {
	if(gameStop) return;
	red.moveWarrior();
	blue.moveWarrior();
	for(int i = 0; i <= cityNumber + 1; i++) {
		for(mob &x : red.warrior)
			if(x.health > 0 && x.city == i) {
				printf("%03d:10 %s %s %d ", clo / 60, x.color, mobName[x.id], x.number);
				if(x.arrived()) {
					printf("reached blue headquarter ");
					blue.beToken++;
				}
				else
					printf("marched to city %d ", x.city);
				printf("with %d elements and force %d\n", x.health, x.attack);
			}
		for(mob &x : blue.warrior)
			if(x.health > 0 && x.city == i) {
				printf("%03d:10 %s %s %d ", clo / 60, x.color, mobName[x.id], x.number);
				if(x.arrived()) {
					printf("reached red headquarter ");
					red.beToken++;
				}
				else
					printf("marched to city %d ", x.city);
				printf("with %d elements and force %d\n", x.health, x.attack);
			}

		if(i == 0)
			if(red.beToken >= 2) {
				printf("%03d:10 red headquarter was taken\n", clo / 60);
				gameStop = 1;
			}
		if(i == cityNumber + 1)
			if(blue.beToken >= 2) {
				printf("%03d:10 blue headquarter was taken\n", clo / 60);
				gameStop = 1;
			}
	}
}

void updateCityHealth() {
	if(gameStop) return;
	for(int i = 1; i <= cityNumber; i++)
		cityHealth[i] += 10;
}

void takenHealth(cmd &red, cmd &blue) {
	if(gameStop) return;
	for(int i = 1; i <= cityNumber; i++) {
		int a = red.selectWarriorAt(i);
		int b =	blue.selectWarriorAt(i);

		if(a != -1 && b == -1) {
			red.health += cityHealth[i];
			printf("%03d:30 red %s %d earned %d elements for his headquarter\n", clo / 60, mobName[red.warrior[a].id], red.warrior[a].number, cityHealth[i]);
			cityHealth[i] = 0;
		}
		if(a == -1 && b != -1) {
			blue.health += cityHealth[i];
			printf("%03d:30 blue %s %d earned %d elements for his headquarter\n", clo / 60, mobName[blue.warrior[b].id], blue.warrior[b].number, cityHealth[i]);
			cityHealth[i] = 0;
		}
	}
}

void shootArrow(cmd &red, cmd &blue) {
	if(gameStop) return;
	for(int i = 1; i <= cityNumber; i++) {
		int a = red.selectWarriorAt(i);
		int b = blue.selectWarriorAt(i);

		if(a != -1 && i != cityNumber && red.warrior[a].arrow > 0) {
			int c = blue.selectWarriorAt(i + 1);
			if(c != -1) {
				blue.warrior[c].predamage += arrowAttack;
				red.warrior[a].arrow--;
				printf("%03d:35 red %s %d shot", clo / 60, mobName[red.warrior[a].id], red.warrior[a].number);
				if(blue.warrior[c].health - blue.warrior[c].predamage <= 0)
					printf(" and killed blue %s %d\n", mobName[blue.warrior[c].id], blue.warrior[c].number);
				else
					printf("\n");
			}
		}
		if(b != -1 && i != 0 && blue.warrior[b].arrow > 0) {
			int c = red.selectWarriorAt(i - 1);
			if(c != -1) {
				red.warrior[c].predamage += arrowAttack;
				blue.warrior[b].arrow--;
				printf("%03d:35 blue %s %d shot", clo / 60, mobName[blue.warrior[b].id], blue.warrior[b].number);
				if(red.warrior[c].health - red.warrior[c].predamage <= 0)
					printf(" and killed red %s %d\n", mobName[red.warrior[c].id], red.warrior[c].number);
				else
					printf("\n");
			}
		}
	}
}

void useBomb(cmd &red, cmd &blue) {
	if(gameStop) return;
	for(int i = 1; i <= cityNumber; i++) {
		int a = red.selectWarriorAt(i);
		int b = blue.selectWarriorAt(i);

		if(a != -1 && b != -1) {
			mob rw = red.warrior[a];
			mob bw = blue.warrior[b];
			if(cityFlag[i] == 1 || cityFlag[i] == 0 && (i & 1)) {
				int flag = rw.battle(bw);
				if(flag == 1 && red.warrior[a].bomb > 0) {
					red.warrior[a].health = blue.warrior[b].health = 0;
					printf("%03d:38 red %s %d used a bomb and killed blue %s %d\n", clo / 60, mobName[red.warrior[a].id], red.warrior[a].number, mobName[blue.warrior[b].id], blue.warrior[b].number);
				}
				else if(flag == -1 && blue.warrior[b].bomb > 0) {
					red.warrior[a].health = blue.warrior[b].health = 0;
					printf("%03d:38 blue %s %d used a bomb and killed red %s %d\n", clo / 60, mobName[blue.warrior[b].id], blue.warrior[b].number, mobName[red.warrior[a].id], red.warrior[a].number);
				}
			} else {
				int flag = bw.battle(rw);
				if(flag == -1 && red.warrior[a].bomb > 0) {
					red.warrior[a].health = blue.warrior[b].health = 0;
					printf("%03d:38 red %s %d used a bomb and killed blue %s %d\n", clo / 60, mobName[red.warrior[a].id], red.warrior[a].number, mobName[blue.warrior[b].id], blue.warrior[b].number);
				}
				else if(flag == 1 && blue.warrior[b].bomb > 0) {
					red.warrior[a].health = blue.warrior[b].health = 0;
					printf("%03d:38 blue %s %d used a bomb and killed red %s %d\n", clo / 60, mobName[blue.warrior[b].id], blue.warrior[b].number, mobName[red.warrior[a].id], red.warrior[a].number);
				}
			}
		}
	}
}

void battleUpdate(cmd &red, cmd &blue) {
	if(gameStop) return;

	winWarrior[0].clear();
	winWarrior[1].clear();
	for(int i = 1; i <= cityNumber; i++)
		info[i].clear();
	bool fighted[25] = {0};

	for(int i = 1; i <= cityNumber; i++) {
		int a = red.selectWarriorAt(i);
		int b =	blue.selectWarriorAt(i);

		if(a != -1 && b != -1) {
			fighted[i] = 1;
			if(cityFlag[i] == 1 || cityFlag[i] == 0 && (i & 1))
				red.warrior[a].battle(blue.warrior[b]);
			else
				blue.warrior[b].battle(red.warrior[a]);
		}
		else if(a != -1 && b == -1) {
			red.warrior[a].health -= red.warrior[a].predamage;
			red.warrior[a].predamage = 0;
		}
		else if(a == -1 && b != -1) {
			blue.warrior[b].health -= blue.warrior[b].predamage;
			blue.warrior[b].predamage = 0;
		}
	}

	for(int i = winWarrior[1].size() - 1; i >= 0; i--)
		if(red.health >= 8) {
			winWarrior[1][i]->health += 8;
			red.health -= 8;
		}
	for(int i = 0; i < winWarrior[0].size(); i++)
		if(blue.health >= 8) {
			winWarrior[0][i]->health += 8;
			blue.health -= 8;
		}

	for(int i = 0, j = 0; i < winWarrior[1].size() || j < winWarrior[0].size(); )
		if(i < winWarrior[1].size() && (j == winWarrior[0].size() || winWarrior[1][i]->city < winWarrior[0][j]->city)) {
			mob x = *winWarrior[1][i];
			if(x.color[0] == 'r')
				red.health += cityHealth[x.city];
			else
				blue.health += cityHealth[x.city];
			char tmp[500] = {0};
			sprintf(tmp, "%03d:40 %s %s %d earned %d elements for his headquarter\n", clo / 60, x.color, mobName[x.id], x.number, cityHealth[x.city]);
			info[x.city].push_back(string(tmp));
			cityHealth[x.city] = 0;
			i++;
		}
		else if(j < winWarrior[0].size() && (i == winWarrior[1].size() || winWarrior[0][j]->city < winWarrior[1][i]->city)) {
			mob x = *winWarrior[0][j];
			if(x.color[0] == 'r')
				red.health += cityHealth[x.city];
			else
				blue.health += cityHealth[x.city];
			char tmp[500] = {0};
			sprintf(tmp, "%03d:40 %s %s %d earned %d elements for his headquarter\n", clo / 60, x.color, mobName[x.id], x.number, cityHealth[x.city]);
			info[x.city].push_back(string(tmp));
			cityHealth[x.city] = 0;
			j++;
		}

	for(int i = 1; i <= cityNumber; i++) {
		if(!fighted[i])
			continue;
		int a = red.selectWarriorAt(i);
		int b =	blue.selectWarriorAt(i);	

		if(a != -1 && b != -1)
			cityLastWin[i] = 0;
		else if(a != -1 && b == -1)
			if(cityLastWin[i] == 1 && cityFlag[i] != 1) {
				cityFlag[i] = 1;
				char tmp[500] = {0};
				sprintf(tmp, "%03d:40 red flag raised in city %d\n", clo / 60, i);
				info[i].push_back(string(tmp));
			}
			else
				cityLastWin[i] = 1;
		else if(a == -1 && b != -1)
			if(cityLastWin[i] == -1 && cityFlag[i] != -1) {
				cityFlag[i] = -1;
				char tmp[500] = {0};
				sprintf(tmp, "%03d:40 blue flag raised in city %d\n", clo / 60, i);
				info[i].push_back(string(tmp));
			}
			else
				cityLastWin[i] = -1;
	}

	for(int i = 1; i <= cityNumber; i++)
		for(string &s : info[i])
			printf("%s", s.c_str());
}

void reportHealth(cmd &red, cmd &blue) {
	if(gameStop) return;
	red.reportHealth();
	blue.reportHealth();
}

void reportWarrior(cmd &red, cmd &blue) {
	if(gameStop) return;
	for(int i = 1; i <= cityNumber; i++) {
		int a = red.selectWarriorAt(i);
		if(a != -1)
			red.warrior[a].report();
	}
	for(int a = 0; a < red.warrior.size(); a++)
		if(red.warrior[a].health > 0 && (red.warrior[a].city == cityNumber + 1 || red.warrior[a].city == -1))
			red.warrior[a].report();

	for(int b = 0; b < blue.warrior.size(); b++)
		if(blue.warrior[b].health > 0 && (blue.warrior[b].city == 0 || blue.warrior[b].city == -1))
			blue.warrior[b].report();
	for(int i = 1; i <= cityNumber; i++) {
		int b = blue.selectWarriorAt(i);
		if(b != -1)
			blue.warrior[b].report();
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int cas = 1; cas <= T; cas++) {
		printf("Case %d:\n", cas);
		int m, t;
		scanf("%d%d%d%d%d", &m, &cityNumber, &arrowAttack, &loyaltyDecay, &t);
		for(int i = 0; i < 5; i++)
			scanf("%d", &mobCost[i]);
		for(int i = 0; i < 5; i++)
			scanf("%d", &mobAttack[i]);

		gameStop = 0;
		memset(cityFlag, 0, sizeof(cityFlag));
		memset(cityLastWin, 0, sizeof(cityLastWin));
		memset(cityHealth, 0, sizeof(cityHealth));
		cmd red("red", m), blue("blue", m);

		for(clo = 0; clo <= t; ) {
			// 造兵 
			createMob(red, blue);

			// 05
			clo += 5;
			if(clo > t) break;
			// lion的逃跑 
			lionUpdate(red, blue);

			// 10
			clo += 5;
			if(clo > t) break;
			// 进军
			moveWarrior(red, blue);

			// 20
			clo += 10;
			if(clo > t) break;
			// 更新城市生命元 
			updateCityHealth();

			// 30
			clo += 10;
			if(clo > t) break;
			// 士兵取走生命元
			takenHealth(red, blue); 

			// 35
			clo += 5;
			if(clo > t) break;
			// 有arrow的士兵弓箭 
			shootArrow(red, blue);

			// 38
			clo += 3;
			if(clo > t) break;
			// 士兵是否使用bomb
			useBomb(red, blue);

			// 40
			clo += 2;
			if(clo > t) break;
			// 战斗
			battleUpdate(red, blue);

			// 50
			clo += 10;
			if(clo > t) break;
			// 报告生命元
			reportHealth(red, blue);

			// 55
			clo += 5;
			if(clo > t) break;
			// 报告士兵情况 
			reportWarrior(red, blue);

			// 60
			clo += 5; 
		}
	}
	return 0;
}

