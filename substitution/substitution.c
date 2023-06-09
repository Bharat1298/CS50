#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid(string key);
char cipher(string message, string argv);
int main(int argc, string argv[])
{
    if(argc != 2){
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if(!valid(argv[1])){
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string message = get_string("plaintext: ");

    cipher(message, argv[1]);

    return 0;

}

bool valid(string key){

    int len = strlen(key);
    if (len != 26){
        return false;
    }

    for(int i = 0; i < len; i++){
        if(!isalpha(key[i])){
            return false;
        }else{
            for(int j = i + 1; j < len; j++){
                if(key[i] == key[j]){
                    return false;
                }
            }
        }
    }
    return true;
}

char cipher(string message, string argv){
    printf("ciphertext: ");
    for(int i = 0; i < strlen(message); i++){
        if(islower(message[i])){
            printf("%c", tolower(argv[message[i] - 'a']));
        }else if(isupper(message[i])){
            printf("%c", toupper(argv[message[i] - 'A']));
        }else{
            printf("%c", message[i]);
        }
    }
    printf("\n");
    return false;
}