#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#define LOG_TAG "maxwin"
#include <utils/Log.h>
#define GPIO_PATH "/sys/class/gpio/gpio"
void write_gpio(char* cmd, char* value);
void write_gpio_int(char* cmd, int value);
int main(void)
{
    ALOGI("gpio daemon start");
    int i=0;
    char* pin_start="163"; // launch pin
    char* pin="171"; // control pin
    char dir[128];
    char opt[64];
    char pin_path[128];
    char pin_path_dir[128];
    char pin_path_value[128];

    printf("HW watchdog initialize!\n");

    strcpy(pin_path, GPIO_PATH);
    strcat(pin_path, pin_start);
    strcpy(pin_path_dir, pin_path);
    strcat(pin_path_dir, "/direction");
    strcpy(pin_path_value, pin_path);
    strcat(pin_path_value, "/value");
    write_gpio_int("/sys/class/gpio/export", atoi(pin_start));
    write_gpio(pin_path_dir, "out");
    usleep(100*1000);
    write_gpio_int(pin_path_value, 0);
    usleep(100*1000);
    write_gpio_int(pin_path_value, 1);
    usleep(100*1000);
    write_gpio_int(pin_path_value, 0);
    usleep(100*1000);

    printf("HW watchdog start!\n");

    strcpy(pin_path, GPIO_PATH);
    strcat(pin_path, pin);

    strcpy(pin_path_dir, pin_path);
    strcat(pin_path_dir, "/direction");

    strcpy(pin_path_value, pin_path);
    strcat(pin_path_value, "/value");

    write_gpio_int("/sys/class/gpio/export", atoi(pin));
    write_gpio(pin_path_dir, "out");
    while(1){
        write_gpio_int(pin_path_value, 1);
        //sleep(1);
        usleep(100*1000);
        write_gpio_int(pin_path_value, 0);
        //sleep(1);
        usleep(100*1000);
    }
    write_gpio_int("/sys/class/gpio/unexport", atoi(pin));

    return 0;
}
void write_gpio(char* cmd, char* value){
    FILE *p=NULL;
    p = fopen(cmd, "w");
    fprintf(p, "%s", value);
    fclose(p);
}
void write_gpio_int(char* cmd, int value){
    FILE *p=NULL;
    p = fopen(cmd, "w");
    fprintf(p, "%d", value);
    fclose(p);
}
