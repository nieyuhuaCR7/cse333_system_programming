#include <stdio.h>
#include <dirent.h>

int main(void) {
    DIR *dir;
    struct dirent *ent;

    // 打开目录
    dir = opendir("./");

    if (dir != NULL) {
        // 遍历目录中的所有文件
        while ((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent->d_name);
        }
        closedir(dir);
    } else {
        // 如果打开目录失败
        perror("");
        return 1;
    }

    return 0;
}
