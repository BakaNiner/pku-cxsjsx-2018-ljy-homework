#include <cstdio>
#include <cstring>

char mobName[][10] = {"dragon", "ninja", "iceman", "lion", "wolf"};
char weaponName[][10] = {"sword", "bomb", "arrow"};
int mobCost[10] = {0};

class cmd {
public:
	char name[10];
	int health;
	int mobCnt[10];
	int list[10];
	bool stop;
	int mobNumber;
	int lastMobId;

	cmd(const char *s, int h) {
		strcpy(name, s);
		health = h;
		memset(mobCnt, 0, sizeof(mobCnt));
		if(strcmp(name, "red") == 0) {
			list[0] = 2; list[1] = 3; list[2] = 4; list[3] = 1; list[4] = 0;
		} else {
			list[0] = 3; list[1] = 0; list[2] = 1; list[3] = 2; list[4] = 4;
		}
		stop = 0;
		mobNumber = 0;
		lastMobId = -1;
	}

	bool isStop() {
		return stop;
	}

	int getId() {
		for(int i = 0, j = (lastMobId + 1) % 5; i < 5; i++, j = (j + 1) % 5)
			if(mobCost[list[j]] <= health)
				return j;
		return -1;
	}

	void createMob(int id) {
		if(id == 0) {
			printf("It has a %s,and it's morale is %.2f\n", weaponName[mobNumber % 3], health /(double) mobCost[id]);
		}
		else if(id == 1) {
			printf("It has a %s and a %s\n", weaponName[mobNumber % 3], weaponName[(mobNumber + 1) % 3]);
		}
		else if(id == 2) {
			printf("It has a %s\n", weaponName[mobNumber % 3]);
		}
		else if(id == 3) {
			printf("It's loyalty is %d\n", health);
		}
	}

	void update() {
		if(stop)
			return;

		int id = getId();
		if(id == -1) {
			printf("%s headquarter stops making warriors\n", name);
			stop = 1;
			return;
		}
		lastMobId = id;
		id = list[id];

		health -= mobCost[id];
		mobCnt[id]++;
		mobNumber++;
		printf("%s %s %d born with strength %d,%d %s in %s headquarter\n", name, mobName[id], mobNumber, mobCost[id], mobCnt[id], mobName[id], name);
		createMob(id);
	}
};

int main() {
	int T;
	scanf("%d", &T);
	for(int cas = 1; cas <= T; cas++) {
		printf("Case:%d\n", cas);
		int m;
		scanf("%d", &m);
		for(int i = 0; i < 5; i++)
			scanf("%d", &mobCost[i]);

		int clo = 0;
		cmd red("red", m), blue("blue", m);

		while(!red.isStop() || !blue.isStop()) {
			if(!red.isStop()) {
				printf("%03d ", clo);
				red.update();
			}
			if(!blue.isStop()) {
				printf("%03d ", clo);
				blue.update();
			}
			clo++;
		}
	}
	return 0;
}

