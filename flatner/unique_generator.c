// #include <string.h>
// #include <stdlib.h>

// int isPresent(char *str, char **list, int count)
// {
//     for (int i = 0; i < count; i++)
//     {
//         if (!strcmp(str, list[i]))
//         {
//             return 1;
//         }
//     }
//     return 0;
// }

// char *generateNext(char *s)
// {
//     int len = strlen(s);
//     char last = s[len - 1];
//     char *newStr;

//     if (last == 'z')
//     {
//         newStr = malloc(len + 2);
//         strcpy(newStr, s);
//         newStr[len - 1] = '_';
//         newStr[len] = 'a';
//         newStr[len + 1] = '\0';
//     }
//     else
//     {
//         newStr = malloc(len + 1);
//         strcpy(newStr, s);
//         newStr[len - 1]++;
//     }

//     return newStr;
// }

// char *getUniqueString(char **list, int count)
// {
//     char *smallest = "a";

//     while (isPresent(smallest, list, count))
//     {
//         smallest = generateNext(smallest);
//     }

//     return smallest;
// }