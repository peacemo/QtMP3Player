#include "loadGUI.h"

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    initProgress();
    gtk_main();

    return 0;
}
