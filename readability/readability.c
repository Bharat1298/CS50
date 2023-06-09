#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int letters(string text);
int words(string text);
int sentences(string text);
int main(void)
{
    string text = get_string("Text: ");

    int letterCount = letters(text);
    int wordCount = words(text);
    int sentenceCount = sentences(text);

    printf("%i\n%i\n%i\n", letterCount, wordCount, sentenceCount);

    double L = (double)letterCount / wordCount * 100.0;

    double S = (double)sentenceCount / wordCount * 100.0;

    printf("%f\n%f\n", L, S);

    int gradeLevel = round(0.0588 * L - 0.296 * S - 15.8);



    if(gradeLevel > 16){
        printf("Grade 16+\n");
    }else if(gradeLevel < 1){
        printf("Before Grade 1\n");
    }else{
        printf("Grade %i\n", gradeLevel);
    }
}

int letters(string text){
    int count = 0;
    for(int i = 0, len = strlen(text); i < len; i++){
        if((text[i] >= 'a' && text[i] <= 'z') ||
           (text[i] >= 'A' && text[i] <= 'Z') ){
                count++;
        }
    }
    return count;
}

int words(string text){
    int count = 0;
    int endingWord = 1;
    for(int i = 0, len = strlen(text); i < len; i++){
        if(text[i] == ' '){
           count++;
        }
    }
    return count + endingWord;
}

int sentences(string text){
    int count = 0;
    for(int i = 0, len = strlen(text); i < len; i++){
        if(text[i] == '.' || text[i] == '!' || text[i] == '?'){
                count++;
        }
    }
    return count;
}