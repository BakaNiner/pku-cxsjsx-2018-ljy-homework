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
int cityNumber;
int loyaltyDecay;
int clo;
bool gameStop;

int pickUpWeapon(int *myWeapon, int myLen, int myNow) {
	if(myLen == 0) return -1;

	myNow = (myNow + 1) % myLen;
	for(int i = 0; i < myLen; i++, myNow = (myNow + 1) % myLen)
		if(myWeapon[myNow] != -1)
			break;
	if(myWeapon[myNow] == -1)
		myNow = -1;
	return myNow;
}

class mob {
public:
	char *color; // 属于哪一方
	int id; // 生物类型 
	int number; // 编号 
	int health; // 血量 
	int attack; // 攻击力 
	int sword; // sword个数 
	int bomb; // bomb个数 
	int arrow; // arrow个数 
	int oldArrow; // 用过一次的arrow个数 
	int loyalty; // 如果是lion 那么有忠诚度 
	int city; // 当前在哪个城市

	mob(char *_color, int _id, int _number, int _health, int _attack, int _weapon = -1, int _weapon2 = -1, int _loyalty = -1) : color(_color), id(_id), number(_number), health(_health), attack(_attack), sword(0), bomb(0), arrow(0), oldArrow(0), loyalty(_loyalty) {
		if(_weapon == 0)
			sword++;
		else if(_weapon == 1)
			bomb++;
		else if(_weapon == 2)
			arrow++;
		if(_weapon2 == 0)
			sword++;
		else if(_weapon2 == 1)
			bomb++;
		else if(_weapon2 == 2)
			arrow++;

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
		if(color[0] == 'r')
			city = min(city + 1, cityNumber + 1);
		else
			city = max(city - 1, 0);

		if(id == 2)
			health -= health / 10;
		else if(id == 3)
			loyalty -= loyaltyDecay;
	}

	void loot(mob &x, bool wolf = 0) {
		int tot = sword + bomb + arrow + oldArrow;
		if(tot >= 10)
			return;

		tot = 10 - tot;

		if(wolf) {
			int which = -1, res = 0;
			if(x.sword > 0) {
				which = 0;
				res += min(x.sword, tot);
				sword += min(x.sword, tot);
				x.sword = max(x.sword - tot, 0);
			}
			else if(x.bomb > 0) {
				which = 1;
				res += min(x.bomb, tot);
				bomb += min(x.bomb, tot);
				x.bomb = max(x.bomb - tot, 0);
			}
			else if(x.arrow + x.oldArrow > 0) {
				which = 2;
				res += min(x.arrow, tot);
				arrow += min(x.arrow, tot);
				int tmp = x.arrow;
				x.arrow = max(x.arrow - tot, 0);
				tot = max(tot - tmp, 0);
	
				res += min(x.oldArrow, tot);
				oldArrow += min(x.oldArrow, tot);
				x.oldArrow = max(x.oldArrow - tot, 0);
			}
			if(which != -1)
				printf("%03d:35 %s wolf %d took %d %s from %s %s %d in city %d\n", clo / 60, color, number, res, weaponName[which], x.color, mobName[x.id], x.number, city);
		} else {
			if(x.sword > 0) {
				sword += min(x.sword, tot);
				int tmp = x.sword;
				x.sword = max(x.sword - tot, 0);
				tot = max(tot - tmp, 0);
			}
			if(x.bomb > 0) {
				bomb += min(x.bomb, tot);
				int tmp = x.bomb;
				x.bomb = max(x.bomb - tot, 0);
				tot = max(tot - tmp, 0);
			}
			if(x.arrow + x.oldArrow > 0) {
				arrow += min(x.arrow, tot);
				int tmp = x.arrow;
				x.arrow = max(x.arrow - tot, 0);
				tot = max(tot - tmp, 0);
	
				oldArrow += min(x.oldArrow, tot);
				x.oldArrow = max(x.oldArrow - tot, 0);
			}
		}
	}

	void hit(mob &x, int weaponID) {
		int damage;
		if(weaponID == 0) damage = attack / 5;
		else if(weaponID == 1) damage = attack * 2 / 5;
		else damage = attack * 3 / 10;

		x.health -= damage;
		// bomb 并且不是ninja 
		if(weaponID == 1 && id != 1)
			health -= damage / 2;
	}

	void updateWeapon(int *myWeapon, int myNow) {
		if(myWeapon[myNow] == 1) {
			myWeapon[myNow] = -1;
			bomb--;
		}
		else if(myWeapon[myNow] == 2) {
			myWeapon[myNow] = 3;
			arrow--;
			oldArrow++;
		}
		else if(myWeapon[myNow] == 3) {
			myWeapon[myNow] = -1;
			oldArrow--;
		}
	}

	void battle(mob &x) {
		int myWeapon[10], myLen = 0;
		memset(myWeapon, -1, sizeof(myWeapon));
		for(int i = 0; i < sword; i++)
			myWeapon[myLen++] = 0;
		for(int i = 0; i < bomb; i++)
			myWeapon[myLen++] = 1;
		for(int i = 0; i < oldArrow; i++)
			myWeapon[myLen++] = 3;
		for(int i = 0; i < arrow; i++)
			myWeapon[myLen++] = 2;

		int hisWeapon[10], hisLen = 0;
		memset(hisWeapon, -1, sizeof(hisWeapon));
		for(int i = 0; i < x.sword; i++)
			hisWeapon[hisLen++] = 0;
		for(int i = 0; i < x.bomb; i++)
			hisWeapon[hisLen++] = 1;
		for(int i = 0; i < x.oldArrow; i++)
			hisWeapon[hisLen++] = 3;
		for(int i = 0; i < x.arrow; i++)
			hisWeapon[hisLen++] = 2;

		bool flag = 1;
		int myNow = -1, hisNow = -1;
		while(flag) {
			flag = 0;

			myNow = pickUpWeapon(myWeapon, myLen, myNow);
			hisNow = pickUpWeapon(hisWeapon, hisLen, hisNow);

			if(myNow != -1) {
				int tmp = x.health;

				hit(x, myWeapon[myNow]);
				updateWeapon(myWeapon, myNow);

				if(tmp != x.health)
					flag = 1;
				if(bomb + arrow + oldArrow > 0)
					flag = 1;
			}
			if(x.health > 0 && hisNow != -1) {
				int tmp = health;

				x.hit(*this, hisWeapon[hisNow]);
				x.updateWeapon(hisWeapon, hisNow);

				if(tmp != health)
					flag = 1;
				if(x.bomb + x.arrow + x.oldArrow > 0)
					flag = 1;
			}

			if(health > 0 && x.health <= 0) {
				printf("%03d:40 %s %s %d killed %s %s %d in city %d remaining %d elements\n", clo / 60, color, mobName[id], number, x.color, mobName[x.id], x.number, city, health);
				if(id == 0)
					printf("%03d:40 %s dragon %d yelled in city %d\n", clo / 60, color, number, city);
				loot(x);
				break;
			}
			if(x.health > 0 && health <= 0) {
				printf("%03d:40 %s %s %d killed %s %s %d in city %d remaining %d elements\n", clo / 60, x.color, mobName[x.id], x.number, color, mobName[id], number, x.city, x.health);
				if(x.id == 0)
					printf("%03d:40 %s dragon %d yelled in city %d\n", clo / 60, x.color, x.number, x.city);
				x.loot(*this);
				break;
			}
			if(health <= 0 && x.health <= 0) {
				if(color[0] == 'r')
					printf("%03d:40 both red %s %d and blue %s %d died in city %d\n", clo / 60, mobName[id], number, mobName[x.id], x.number, city);
				else
					printf("%03d:40 both red %s %d and blue %s %d died in city %d\n", clo / 60, mobName[x.id], x.number, mobName[id], number, x.city);
				break;
			}
			if(!flag) {
				if(color[0] == 'r')
					printf("%03d:40 both red %s %d and blue %s %d were alive in city %d\n", clo / 60, mobName[id], number, mobName[x.id], x.number, city);
				else
					printf("%03d:40 both red %s %d and blue %s %d were alive in city %d\n", clo / 60, mobName[x.id], x.number, mobName[id], number, x.city);
				if(id == 0 && color[0] == 'r')
					printf("%03d:40 %s dragon %d yelled in city %d\n", clo / 60, color, number, city);
				if(x.id == 0 && x.color[0] == 'r')
					printf("%03d:40 %s dragon %d yelled in city %d\n", clo / 60, x.color, x.number, x.city);
				if(id == 0 && color[0] == 'b')
					printf("%03d:40 %s dragon %d yelled in city %d\n", clo / 60, color, number, city);
				if(x.id == 0 && x.color[0] == 'b')
					printf("%03d:40 %s dragon %d yelled in city %d\n", clo / 60, x.color, x.number, x.city);
				break;
			}
		}
	}
};

class cmd {
public:
	char name[5]; // 司令部颜色 
	int health; // 生命元 
	int list[5]; // 造兵序列 
	int mobNumber; // 士兵个数 
	int lastMobId; // 上次造兵在序列中的id 
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
			mob x(name, id, mobNumber, mobCost[id], mobAttack[id], mobNumber % 3);
			warrior.push_back(x);
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
			mob x(name, id, mobNumber, mobCost[id], mobAttack[id], mobNumber % 3, -1, health);
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
				if(x.arrived())
					printf("reached blue headquarter ");
				else
					printf("marched to city %d ", x.city);
				printf("with %d elements and force %d\n", x.health, x.attack);
			}
		for(mob &x : blue.warrior)
			if(x.health > 0 && x.city == i) {
				printf("%03d:10 %s %s %d ", clo / 60, x.color, mobName[x.id], x.number);
				if(x.arrived())
					printf("reached red headquarter ");
				else
					printf("marched to city %d ", x.city);
				printf("with %d elements and force %d\n", x.health, x.attack);
			}

		if(i == 0) {
			for(mob &x : blue.warrior)
				if(x.health > 0 && x.city == 0) {
					printf("%03d:10 red headquarter was taken\n", clo / 60);
					gameStop = 1;
					break;
				}
		}
		if(i == cityNumber + 1) {
			for(mob &x : red.warrior)
				if(x.health > 0 && x.city == cityNumber + 1) {
					printf("%03d:10 blue headquarter was taken\n", clo / 60);
					gameStop = 1;
					break;
				}
		}
	}
}

void wolfUpdate(cmd &red, cmd &blue) {
	if(gameStop) return;
	for(int i = 1; i <= cityNumber; i++) {
		int a = red.selectWarriorAt(i);
		int b =	blue.selectWarriorAt(i);

		if(a != -1 && red.warrior[a].id == 4) {
			if(b == -1 || b != -1 && blue.warrior[b].id == 4)
				continue;
			red.warrior[a].loot(blue.warrior[b], 1);
		}
		else if(a != -1 && b != -1 && blue.warrior[b].id == 4)
			blue.warrior[b].loot(red.warrior[a], 1);
	}
}

void battleUpdate(cmd &red, cmd &blue) {
	if(gameStop) return;
	for(int i = 1; i <= cityNumber; i++) {
		int a = red.selectWarriorAt(i);
		int b =	blue.selectWarriorAt(i);

		if(a == -1 || b == -1)
			continue;

		if(i & 1) red.warrior[a].battle(blue.warrior[b]);
		else blue.warrior[b].battle(red.warrior[a]);
	}
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
		int b =	blue.selectWarriorAt(i);

		if(a != -1)
			printf("%03d:55 red %s %d has %d sword %d bomb %d arrow and %d elements\n", clo / 60, mobName[red.warrior[a].id], red.warrior[a].number, red.warrior[a].sword, red.warrior[a].bomb, red.warrior[a].arrow + red.warrior[a].oldArrow, red.warrior[a].health);
		if(b != -1)
			printf("%03d:55 blue %s %d has %d sword %d bomb %d arrow and %d elements\n", clo / 60, mobName[blue.warrior[b].id], blue.warrior[b].number, blue.warrior[b].sword, blue.warrior[b].bomb, blue.warrior[b].arrow + blue.warrior[b].oldArrow, blue.warrior[b].health);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int cas = 1; cas <= T; cas++) {
		printf("Case %d:\n", cas);
		int m, t;
		scanf("%d%d%d%d", &m, &cityNumber, &loyaltyDecay, &t);
		for(int i = 0; i < 5; i++)
			scanf("%d", &mobCost[i]);
		for(int i = 0; i < 5; i++)
			scanf("%d", &mobAttack[i]);

		cmd red("red", m), blue("blue", m);

		for(clo = gameStop = 0; clo <= t; ) {
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
			// 35
			clo += 25;
			if(clo > t) break;
			// wolf抢夺
			wolfUpdate(red, blue);
			// 40
			clo += 5;
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

