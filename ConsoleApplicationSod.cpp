// ConsoleApplicationSod.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <assert.h>

#include <sodium.h>


static unsigned char      x[65536];
static unsigned long long freq[256];



static int randombytes_tests(void)
{
    static const unsigned char seed[randombytes_SEEDBYTES] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
        0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
        0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };
    unsigned char out[100];
    unsigned int  f = 0U;
    unsigned int  i;
    uint32_t      n;
    uint32_t      n_bounded;

    randombytes(x, 1U);

    n = randombytes_random();

    printf("Random number: %02x \r\n", n);
    randombytes_close(); //This deallocates the global resources used by the pseudo-random number generator. 
    n_bounded = randombytes_uniform(10); //function returns an unpredictable value between 0 and upper_bound(excluded).
    printf("Random number bounded: %02x\r\n", n_bounded);
 

    randombytes_buf_deterministic(out, sizeof out, seed); //The randombytes_buf_deterministic function stores size bytes into buf indistinguishable from random bytes without knowing seed.

    for (i = 0; i < sizeof out; ++i) {
    printf("%02x", out[i]);
    }
    printf(" random deterministic buffer)\r\n");

    randombytes_close();

    randombytes(x, 1U);
    randombytes_close();

    assert(randombytes_SEEDBYTES > 0);
    assert(randombytes_seedbytes() == randombytes_SEEDBYTES);

    return 0;
}



int main()
{
    if (sodium_init() < 0) {
        /* panic! the library couldn't be initialized; it is not safe to use */
        return -1;
    }
    randombytes_tests();
    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
