#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longestCommonPrefixHelper(char *str1, char *str2)
{
       char *result = malloc((strlen(str1)+1) * sizeof(char));
       int i=0;
       while(str1[i]!='\0' && str2[i]!='\0')
       {
              if(str1[i]==str2[i])
              {
                result[i] = str1[i];
                i++;
              }
              else{
                break;
              }
       }
       result[i] = '\0'; // null-terminate the result string
       printf("%s",result);
       return result;
}
char *longestCommonPrefix(char **strs, int start, int end)
{
    if (start == end)
    {
        return strs[start];
    }
    int mid = (start + end) / 2;
    char *left = longestCommonPrefix(strs, start, mid);
    char *right = longestCommonPrefix(strs, mid + 1, end);
    return longestCommonPrefixHelper(left, right);
}


void main()
{
    int n;
    printf("ENTER THE NUMBER OF INPUT STRINGS: ");
    scanf("%d",&n);
    char *str[n];
    for(int i=0;i<n;i++)
    {
        printf("ENTER THE STRING %d: ", i+1);
        str[i] = malloc(1024 * sizeof(char)); // allocate memory for each string
        scanf("%s",str[i]); // read string into allocated memory
    }   
    char *prefix = longestCommonPrefix(str,0,n-1);
    printf("The longest common prefix is: %s\n", prefix);
    free(prefix);
    for(int i=0;i<n;i++)
    {
        free(str[i]); // free allocated memory
    }
}