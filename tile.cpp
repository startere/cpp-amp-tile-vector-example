#include<iostream>
#include<stdlib.h>
#include <ctime>
#include <chrono>
using namespace std;
#include <amp.h>
using namespace concurrency;

void Tile8() {
    static const int sz = 128;
    static const int tilesz = 8;

    int A[sz * sz], B[sz * sz], C[sz * sz];

    for (int i = 0; i < sz * sz; i++)
    {
        A[i] = (rand() % (sz * 2)) + 1;
        B[i] = (rand() % (sz * 2)) + 1;
        C[i] = 0;
    }


    array_view<int, 2> arrayA(sz, sz, A);
    array_view<int, 2> arrayB(sz, sz, B);
    array_view<int, 2> arrayC(sz, sz, C);


    parallel_for_each(arrayC.extent.tile<tilesz, tilesz>(),
        [=](tiled_index<tilesz, tilesz> thid) restrict(amp)
    {
        int ti = thid.local[0];
        int tj = thid.local[1];

        for (int i = 0; i < sz; i += tilesz) {
            tile_static int tiledarrayA[tilesz][tilesz];
            tile_static int tiledarrayB[tilesz][tilesz];
            tiledarrayA[ti][tj] = arrayA(thid.global[0], tj + i);
            tiledarrayB[ti][tj] = arrayB(ti + i, thid.global[1]);
            thid.barrier.wait();

            for (int k = 0; k < tilesz; k++) {
                arrayC(thid.global[0], thid.global[1]) += tiledarrayA[ti][k] * tiledarrayB[k][tj];
            }

            thid.barrier.wait();
        }

    });

    arrayC.synchronize();
}

void Tile16() {
    static const int sz = 128;
    static const int tilesz = 16;

    int A[sz * sz], B[sz * sz], C[sz * sz];

    for (int i = 0; i < sz * sz; i++)
    {
        A[i] = (rand() % (sz * 2)) + 1;
        B[i] = (rand() % (sz * 2)) + 1;
        C[i] = 0;
    }


    array_view<int, 2> arrayA(sz, sz, A);
    array_view<int, 2> arrayB(sz, sz, B);
    array_view<int, 2> arrayC(sz, sz, C);


    parallel_for_each(arrayC.extent.tile<tilesz, tilesz>(),
        [=](tiled_index<tilesz, tilesz> thid) restrict(amp)
    {
        int ti = thid.local[0];
        int tj = thid.local[1];

        for (int i = 0; i < sz; i += tilesz) {
            tile_static int tiledarrayA[tilesz][tilesz];
            tile_static int tiledarrayB[tilesz][tilesz];
            tiledarrayA[ti][tj] = arrayA(thid.global[0], tj + i);
            tiledarrayB[ti][tj] = arrayB(ti + i, thid.global[1]);
            thid.barrier.wait();

            for (int k = 0; k < tilesz; k++) {
                arrayC(thid.global[0], thid.global[1]) += tiledarrayA[ti][k] * tiledarrayB[k][tj];
            }

            thid.barrier.wait();
        }

    });

    arrayC.synchronize();
}

void Tile32() {
    static const int sz = 128;
    static const int tilesz = 32;

    int A[sz * sz], B[sz * sz], C[sz * sz];

    for (int i = 0; i < sz * sz; i++)
    {
        A[i] = (rand() % (sz * 2)) + 1;
        B[i] = (rand() % (sz * 2)) + 1;
        C[i] = 0;
    }


    array_view<int, 2> arrayA(sz, sz, A);
    array_view<int, 2> arrayB(sz, sz, B);
    array_view<int, 2> arrayC(sz, sz, C);


    parallel_for_each(arrayC.extent.tile<tilesz, tilesz>(),
        [=](tiled_index<tilesz, tilesz> thid) restrict(amp)
    {
        int ti = thid.local[0];
        int tj = thid.local[1];

        for (int i = 0; i < sz; i += tilesz) {
            tile_static int tiledarrayA[tilesz][tilesz];
            tile_static int tiledarrayB[tilesz][tilesz];
            tiledarrayA[ti][tj] = arrayA(thid.global[0], tj + i);
            tiledarrayB[ti][tj] = arrayB(ti + i, thid.global[1]);
            thid.barrier.wait();

            for (int k = 0; k < tilesz; k++) {
                arrayC(thid.global[0], thid.global[1]) += tiledarrayA[ti][k] * tiledarrayB[k][tj];
            }

            thid.barrier.wait();
        }

    });

    arrayC.synchronize();
}


int main() {
    //time_t start,end;
    double time_taken;
    clock_t start, end;
    //time(&start);
    start = clock();
    Tile8();
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "time tile 8 : " << time_taken;
    cout << endl;

    start = clock();
    Tile16();
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "time tile 16 : " << time_taken;
    cout << endl;

    start = clock();
    Tile32();
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "time tile 32 : " << time_taken;


}
