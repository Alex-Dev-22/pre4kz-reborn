
#include "raylib.h"
#include <RtMidi.h>
#include <vector>
#include <iostream>


int main() {

    InitWindow(1280, 720, "Pre4Kz - 2026");
    InitAudioDevice();

    RtMidiIn *midiin = new RtMidiIn();
    if (midiin->getPortCount() > 0) 
    {
        midiin->openPort(0);
        std::cout << "MIDI abierto: " << midiin->getPortName(0) << "\n";
    }

    while (!WindowShouldClose()) 
    {
        std::vector<unsigned char> msg;
        double delta = 0;
        while (midiin->getMessage(&msg) > 0){
            if (msg.size() >= 3 && msg[0] == 144 && msg[2] > 0) {
                std::cout << "Nota: " << (int)msg[1] << "\n";
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("hola mundo XD", 640, 360, 3, BLACK);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    delete midiin;
    return 0;
}