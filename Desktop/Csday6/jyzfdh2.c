#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#define MAX_OBJECTS 9
#define MAX_OBJECT_LENGTH 10

// 定义物体结构体
typedef struct {
    char object[MAX_OBJECT_LENGTH];
    int x;
    int y;
    int color_pair;
} Object;

// 初始化物体
void initObjects(Object *objects) {
    strcpy(objects[0].object, "w");
    objects[0].x = 1;
    objects[0].y = 1;
    objects[0].color_pair = 1;

    strcpy(objects[1].object, "f");
    objects[1].x = 3;
    objects[1].y = 3;
    objects[1].color_pair = 2;
    
    strcpy(objects[2].object, "l");
    objects[2].x = 5;
    objects[2].y = 5;
    objects[2].color_pair = 3;
    
    strcpy(objects[3].object, "b");
    objects[3].x = 7;
    objects[3].y = 7;
    objects[3].color_pair = 4;
    
    strcpy(objects[4].object, "b");
    objects[4].x = 9;
    objects[4].y = 9;
    objects[4].color_pair = 1;

    strcpy(objects[5].object, "s");
    objects[5].x = 11;
    objects[5].y = 11;
    objects[5].color_pair = 2;
    
    strcpy(objects[6].object, "b");
    objects[6].x = 13;
    objects[6].y = 13;
    objects[6].color_pair = 3;
    
    strcpy(objects[7].object, "l");
    objects[7].x = 15;
    objects[7].y = 15;
    objects[7].color_pair = 4;
    
    strcpy(objects[8].object, "l");
    objects[8].x = 17;
    objects[8].y = 17;
    objects[8].color_pair = 5;
    

    // 可以添加更多物体
}

// 绘制物体
void drawObjects(Object *objects, int num_objects) {
    for (int i = 0; i < num_objects; ++i) {
        attron(COLOR_PAIR(objects[i].color_pair));
        mvprintw(objects[i].y, objects[i].x, "%s", objects[i].object);
        attroff(COLOR_PAIR(objects[i].color_pair));
    }
}

// 更新物体位置
void updateObjects(Object *objects, int num_objects) {
    for (int i = 0; i < num_objects; ++i) {
        objects[i].x += 1;  // 每次向右移动一个单位
    }
}

int main() {
    // 初始化 ncurses
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(FALSE);

    // 初始化颜色对
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    
    // 初始化物体
    Object objects[MAX_OBJECTS];
    initObjects(objects);

    // 主循环
    while (1) {
        clear();

        // 绘制物体
        drawObjects(objects, MAX_OBJECTS);

        // 更新屏幕
        refresh();

        // 等待一段时间
        usleep(50000);  // 50毫秒

        // 更新物体位置
        updateObjects(objects, MAX_OBJECTS);
    }

    // 结束 ncurses
    endwin();

    return 0;
}
