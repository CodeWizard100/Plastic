#include <iostream>
int get_key_bychar(char key)
{
    if (key == ' ') return GLFW_KEY_SPACE;
    if (toupper(key) == 'Q') return GLFW_KEY_Q;
    if (toupper(key) == 'W') return GLFW_KEY_W;
    if (toupper(key) == 'E') return GLFW_KEY_E;
    if (toupper(key) == 'R') return GLFW_KEY_R;
    if (toupper(key) == 'T') return GLFW_KEY_T;
    if (toupper(key) == 'Y') return GLFW_KEY_Y;
    if (toupper(key) == 'U') return GLFW_KEY_U;
    if (toupper(key) == 'I') return GLFW_KEY_I;
    if (toupper(key) == 'O') return GLFW_KEY_O;
    if (toupper(key) == 'P') return GLFW_KEY_P;
    if (toupper(key) == 'A') return GLFW_KEY_A;
    if (toupper(key) == 'S') return GLFW_KEY_S;
    if (toupper(key) == 'D') return GLFW_KEY_D;
    if (toupper(key) == 'F') return GLFW_KEY_F;
    if (toupper(key) == 'G') return GLFW_KEY_G;
    if (toupper(key) == 'H') return GLFW_KEY_H;
    if (toupper(key) == 'J') return GLFW_KEY_J;
    if (toupper(key) == 'K') return GLFW_KEY_K;
    if (toupper(key) == 'L') return GLFW_KEY_L;
    if (toupper(key) == 'Z') return GLFW_KEY_Z;
    if (toupper(key) == 'X') return GLFW_KEY_X;
    if (toupper(key) == 'C') return GLFW_KEY_C;
    if (toupper(key) == 'V') return GLFW_KEY_V;
    if (toupper(key) == 'B') return GLFW_KEY_B;
    if (toupper(key) == 'N') return GLFW_KEY_N;
    if (toupper(key) == 'M') return GLFW_KEY_M;
    if (toupper(key) == '1') return GLFW_KEY_1;
    if (toupper(key) == '2') return GLFW_KEY_2;
    if (toupper(key) == '3') return GLFW_KEY_3;
    if (toupper(key) == '4') return GLFW_KEY_4;
    if (toupper(key) == '5') return GLFW_KEY_5;
    if (toupper(key) == '6') return GLFW_KEY_6;
    if (toupper(key) == '7') return GLFW_KEY_7;
    if (toupper(key) == '8') return GLFW_KEY_8;
    if (toupper(key) == '9') return GLFW_KEY_9;
    if (toupper(key) == '0') return GLFW_KEY_0;
    

    return GLFW_KEY_UNKNOWN; // Invalid toupper(key)
}