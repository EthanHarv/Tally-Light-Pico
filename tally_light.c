#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#define true 1

int onlineCam = 0;
int previewCam = 0;

#define L 5
unsigned char str[L+1];
unsigned char *readLine() {
  unsigned char u, *p;
  for(p=str, u=getchar(); u!='\r' && p-str<L; u=getchar())  putchar(*p++=u);
  *p = 0;  return str;
}

// Camera 1
//    Online - Pin 0
//    Preview - Pin 1
// Camera 2
//    Online - Pin 2
//    Preview - Pin 3
// etc... 
//
//     o,  p
// 1. (0,  1 )
// 2. (2,  3 )
// 3. (4,  5 )
// 4. (6,  7 )
// 5. (8,  9 )
// 6. (10, 11)
// 7. (12, 13)
// 8. (14, 15)
void refreshLEDConfig()
{
    // Reset all LEDs
    for (int i = 0; i <= 15; i++)
    {
        gpio_put(i, 0);
    };
    // Set online cam
    if (onlineCam > 0) 
    {
        gpio_put((onlineCam - 1) * 2, 1);
    };
    if (previewCam > 0)
    {
        gpio_put(((previewCam - 1) * 2) + 1, 1);
    };
}

int main() {
    stdio_init_all();
    sleep_ms(1000); // Required for proper connection for some reason. Thanks, windows. Might be able to remove on MAC version.
    printf("Connection Success\n");


    // Init first 12 GPIO (0-11)
    for (int i = 0; i <= 15; i++)
    {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
        gpio_put(i, 0);
    }

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    while (true) {
        int input = atoi(readLine());

        printf("Got input %d\n", input);

        // 0 = Online Camera Deadspace
        // 1-8 = Online Cameras 1-6
        // 9 = Preview Camera Deadspace
        // 10-18 = Preview Cameras 1-6
        if (input <= 8) // An online camera
        {
            onlineCam = input;
            printf("Set online cam %d\n", onlineCam);
        }
        else if (input <= 18)
        {
            previewCam = input - 10;
            printf("Set preview cam %d\n", previewCam);
        }
        else
        {
            printf("Your input value was not between 0 and 18.\n"); // The current online camera is " + onlineCam + " and the preview cam is " + previewCam);
        }
        refreshLEDConfig();
    }
    return 0;
}
