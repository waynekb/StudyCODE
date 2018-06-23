#include "foo.h"
#include "string.h"
#include "stdio.h"
// #include "foo.h"

char **mSplit(const char *str, char *sep, int max_strs, int *toks, char meta)
{
    char **retstr;      /* 2D array which is returned to caller */
    char *idx;          /* index pointer into str */
    char *end;          /* ptr to end of str */
    char *sep_end;      /* ptr to end of seperator string */
    char *sep_idx;      /* index ptr into seperator string */
    int len = 0;        /* length of current token string */
    int curr_str = 0;       /* current index into the 2D return array */
    char last_char = 0xFF;
    /*
     * find the ends of the respective passed strings so our while() loops
     * know where to stop
     */
    sep_end =(char*)sep + strlen(sep);
    end = (char*)str + strlen(str);

    /* remove trailing whitespace */
    while(isspace((int) *(end - 1)) && ((end - 1) >= str))
        *(--end) = '\0';    /* -1 because of NULL */

    /* set our indexing pointers */
    sep_idx = (char*)sep;
    idx = (char*)str;

    /*
     * alloc space for the return string, this is where the pointers to the
     * tokens will be stored
     */
    if((retstr = (char **) malloc((sizeof(char **) * max_strs))) == NULL)

    max_strs--;
    /* loop thru each letter in the string being tokenized */
    while(idx < end)
    {
        /* loop thru each seperator string char */
        while(sep_idx < sep_end)
        {
            /*
             * if the current string-indexed char matches the current
             * seperator char...
             */
            if((*idx == *sep_idx) && (last_char != meta))
            {
                /* if there's something to store... */
                if(len > 0)
                {
                    if(curr_str <= max_strs)
                    {
                        /* allocate space for the new token */
                        if((retstr[curr_str] = (char *)
                            malloc((sizeof(char) * len) + 1)) == NULL)

                        /* copy the token into the return string array */
                        memcpy(retstr[curr_str], (idx - len), len);
                        retstr[curr_str][len] = 0;
                        /* twiddle the necessary pointers and vars */
                        len = 0;
                        curr_str++;
                        last_char = *idx;
                        idx++;
                    }

                    /*
                     * if we've gotten all the tokens requested, return the
                     * list
                     */
                    if(curr_str >= max_strs)
                    {
                        while(isspace((int) *idx))
                            idx++;

                        len = end - idx;
                        if((retstr[curr_str] = (char *)
                            malloc((sizeof(char) * len) + 1)) == NULL)

                        memcpy(retstr[curr_str], idx, len);
                        retstr[curr_str][len] = 0;

                        *toks = curr_str + 1;

                        return retstr;
                    }
                }
                else
                /*
                 * otherwise, the previous char was a seperator as well,
                 * and we should just continue
                 */
                {
                    last_char = *idx;
                    idx++;
                    /* make sure to reset this so we test all the sep. chars */
                    sep_idx = sep;
                    len = 0;
                }
            }
            else
            {
                /* go to the next seperator */
                sep_idx++;
            }
        }

        sep_idx = sep;
        len++;
        last_char = *idx;
        idx++;
    }

    /* put the last string into the list */

    if(len > 0)
    {

        if((retstr[curr_str] = (char *)
             malloc((sizeof(char) * len) + 1)) == NULL)

        memcpy(retstr[curr_str], (idx - len), len);
        retstr[curr_str][len] = 0;

        *toks = curr_str + 1;
    }

    /* return the token list */
    return retstr;
}

// void deletespace(const char* oldstr,char* newstr ,int len){
//     int count=strlen(oldstr);
//     char* oldindex=oldstr;
//     char* newindex=newstr;

//     int i=0;
//     while(*oldindex!='\0' && i<len-1){
//         if( *oldindex != ' ' && *oldindex!= '\t'){
//             *newindex=*oldindex;
//             newindex++;
//             i++;
//         }
//         if(*oldindex == ' '){
//             printf("**\n");
//         }
//         oldindex++;        
//     }
//     newstr[len-1]=0;
// }


void deletespace(const char* oldstr,char* newstr ,int len){
    int count=strlen(oldstr);
    int old=0;
    int new=0;
    for(;old<count && new<len-1;old++){
        if(*(oldstr+old) != ' ' && *(oldstr+old) != '\t'){
            *(newstr+new)=*(oldstr+old);
            new++;
        }
    }
    newstr[len-1]=0;
}

// int main(){
//     foo();
// }


#include <stdio.h>

int main(){
    char str[10]="a bd gg ";
    // gets(str);
    char str1[10]={0};
    deletespace(str,str1,10);
    printf("%s count = %d \n",str,strlen(str));
    printf("%s count = %d \n",str1,strlen(str1));
    union rec{
        char buf[4];
        int a;
    };

    union rec r;
    r.a=0x12345678;
    r.buf[1]=0x32;
    printf("%x\n",r.a);
}