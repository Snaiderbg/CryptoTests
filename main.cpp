#include <Arduino.h>
#include "sodium.h"

static void test_crypto_stream(void)
{
  unsigned char key[crypto_stream_chacha20_KEYBYTES];
  unsigned char nonce[crypto_stream_chacha20_NONCEBYTES];
  unsigned char m[128], c[128];
  char out[256];
  const char test_str[] = "Seguridad en sistemas embebidos";

  /* Simple encrypt/decrypt test */
  memcpy(m, test_str, sizeof(test_str));

  randombytes_buf(key, sizeof(key));
  randombytes_buf(nonce, sizeof(nonce));

  crypto_stream_chacha20_xor(c, m, sizeof(test_str), nonce, key);
  sodium_bin2hex(out, sizeof(out), c, sizeof(test_str));

  Serial.printf("Chacha20 encryption: %s\n", out);

  crypto_stream_chacha20_xor(m, c, sizeof(test_str), nonce, key);

  sodium_bin2hex(out, sizeof(out), m, sizeof(test_str));
  Serial.printf("Chacha20 decryption: %s (%s)\n", m, out);
}
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hola");
  test_crypto_stream();
}

void loop()
{
  // put your main code here, to run repeatedly:
}