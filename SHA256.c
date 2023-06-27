#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char *stringToBinary(const char *s);
char *intToBinary(const u_int64_t integer);
void rotateLeft(char **string, const u_int32_t rotation);
void rotateRight(char **string, const u_int32_t rotation);

char *SHA256(const char *inputString);
char *PRE_PROCESS(const char* inputString);

const u_int32_t H[8] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19, };

const u_int32_t K[64] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };


int main()
{
    char *jd = "JEBAĆ DISA SYNA DIABŁA";
    for (u_int32_t i = 0; i < strlen(jd); i++) {
        rotateRight(&jd, i);
        puts(jd);
    }
    return 0;
    /* getting user input */
    u_int32_t len = 0;
    printf("Please enter the length of Your message: ");
    scanf("%u", &len);
    char* input = malloc(sizeof(char) * (len + 1));
    printf("Please input a string: ");
    scanf("%s", input);
    input[len] = '\0';

    /* freeing excess allocated memory */
    size_t bits = strlen(input) * 8;
    char *temp = malloc(bits + 1);
    temp[bits] = '\0';
    strcat(temp, input);
    free(input);

    SHA256(temp);
    
    return 0;

}

char *PRE_PROCESS(const char* inputString)
{
    u_int64_t L = strlen(inputString) * 8;
    u_int32_t K = 448 - (L + 1) % 512;
    char *binStr = stringToBinary(inputString);
    char *binL = intToBinary(L);

    size_t outputBits = (strlen(binStr) + strlen(binL) + K + 1) * 8;
    char *output = malloc(outputBits + 1);
    strcat(output, binStr);
    strcat(output, "1");
    for (u_int32_t i = 0; i < K; i++)
        strcat(output, "0");
    strcat(output, binL);
    output[outputBits] = '\0';
    free(binStr);
    free(binL);
    return output;
}

char *SHA256(const char* inputString)
{
    char *PRE_ProcessedString = PRE_PROCESS(inputString);
    return PRE_ProcessedString;
}

char *stringToBinary(const char* string) {
    if(string == NULL) return 0; /* no input string */
    size_t len = strlen(string);
    char *binary = malloc(len*8 + 1); /* each char is one byte (8 bits) and + 1 at the end for null terminator */
    binary[0] = '\0';
    for(size_t i = 0; i < len; ++i) {
        char ch = string[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}

char *intToBinary(const u_int64_t integer)
{
    size_t bits = sizeof(integer) * 8;
    char *binStr = malloc(bits + 1);
    size_t temp = integer;
    for (int i = bits - 1; i >= 0; i--) {
        binStr[i] = (temp & 1) + '0';
        temp >>= 1;
    }
    binStr[bits] = '\0';
    return binStr;
}

void rotateLeft(char **string, const u_int32_t rotation)
{
    u_int32_t len = strlen(*string);
    char *temp = malloc(sizeof(char) * (len + 1));
    for (u_int32_t i=0; i < len; i++) {
        temp[i] = string[0][(i + rotation) % len];
    }
    temp[len] = '\0';
    *string = realloc(temp, (sizeof(temp) * 8));
    free(temp);
}

void rotateRight(char **string, const u_int32_t rotation)
{
    u_int32_t len = strlen(*string);
    char *temp = malloc(sizeof(char) * (len + 1));
    for (u_int32_t i=0; i < len; i++) {
        temp[(i + rotation) % len] = string[0][i];
    }
    temp[len] = '\0';
    *string = realloc(temp, (sizeof(temp) * 8));
    free(temp);
}
