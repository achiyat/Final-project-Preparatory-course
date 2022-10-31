#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

/*******   בכוכביות המוסתרות למטה יש תרגילים בווריציות שונה שעשיתי עד שהגעתי לתשובה   ********/
/*
     1+1=2
     10+20=30
     10-8=2
     10-7-1=2
     10-5+4+4-7-1=5

     תרגיל 1
     1+34-6+456-22+876-12+100-2+4=1429

     7*5=35
     10*5=50
     90/9=10

     תרגיל 2
     1+34*6+56/5+6*3+9456+876-12/100-2+4=10568

     1+34*(6+56)+5=2114
     11+5*(3+2)-1=35
     11+5*(3-2)-1=15
     11-5*(3-2)-1=5
     11+5*(8-5+4)-30=16
     11-5*(8-5+1)+30=21
     11-5+(8-5+1)*5+30=56
     30/(3+2)-1=5
     5+(10+20)/6+10=20

    // תרגיל 3
    // 1+34*(6+56)-5+6*(3+9456)+876-12/100-2+4  //59,736
*/

int main()
{
    char str[1000];
    char num[100];
    char numMD[100]; // Mult_div


    printf("please enter a str: \n");
    gets(str);

    int sum = 0; // לחישוב סכום פשוט 
    int sumMD = 0;  // לחישוב סכומים של כפל וחילוק בגלל שיש צורך בקדימות 
    int sumBrack = 0; // לחישוב סכומים שבתוך הסוגריים בגלל שיש צורך בקדימות
    int action = '+';  //  זוכר את הפעולה האחרונה - מתחיל בפלוס כי מובטח לנו שהמספר הראשון תמיד יהיה חיובי 
    int actionMD = 0;  // משמש בעיקר לזיכרון, אבל בהמשך זוכר את פעולה אחרונה לפני הכפל - אם המספר במינוס או בפלוס
    int actionBrack = 0; // משמש בעיקר לזיכרון, אבל בהמשך זוכר את פעולה אחרונה לפני הסוגריים - אם המספר במינוס או בפלוס
    char* ptr = str;  // מצביע על הכתובת הנוכחית
    char* start = str;  // מצביע על הכתובת הראשונה

    int len = strlen(str);

    int lennumber;    // כמה תווים יש למספר
    int lennumberMD;  // כאשר יש כפל מחפש כמה תווים נלקחו (1*2) כדי להפריד אותם בהמשך
    int number;       // מקבל ערך מהמערך בעל כמה תווים שמציינים את אותו הערך 
    int MorD = 0;         // מסמל כפל או חילוק למטרת תנאי מסובך יותר

    for (int i = 0; i < len; i++)
    {
        // מורה דרך למספר פעולות בנפרד כאשר הפעולה חיובית
        if (*ptr == '+')
        {
            // מחשב את כל הסכום שיש בסוגריים כולל את הכפל או החילוק 
            // כאשר הכפל והחילוק נמצאים בצד הימני של הסוגריים
            if ((actionMD == '/' || actionMD == '*') && actionBrack == ')' && MorD == 1)
            {
                lennumber = ptr - start;
                strncpy(num, start, lennumber);
                num[lennumber] = 0;
                number = atoi(num);

                if (actionMD == '*')
                {
                    sum = sum + (sumMD * sumBrack * number);
                }
                else if (actionMD == '/')
                {
                    sum = sum + (sumMD * sumBrack / number);
                }

                start = start + lennumber + 1;

                actionBrack = 0;
                actionMD = 0;
                sumBrack = 0;
                sumMD = 0;
                MorD = 0;
            }

            // מחשב את כל הסכום שיש בסוגריים כולל את הכפל או החילוק שלפני
            else if (actionBrack == ')')
            {
                if (action == '+')
                {
                    lennumber = ptr - start;
                    strncpy(num, start, lennumber - 1);
                    num[lennumber] = 0;
                    number = atoi(num);

                    if (actionMD == '*')
                    {
                        sum = sum + (sumMD * (sumBrack + number));
                    }
                    else if (actionMD == '/')
                    {
                        sum = sum + (sumMD / (sumBrack + number));
                    }

                    start = start + lennumber + 1;
                }
                // איפוס זיכרון נצרך
                actionBrack = 0;
                actionMD = 0;
                sumBrack = 0;
            }

            // ביצוע כפל רגיל, כלומר כאשר הוא לא בתוך סוגריים
            else if (actionMD == '*' && actionBrack != '(')
            {
                lennumber = ptr - start;
                lennumberMD = lennumberMD + lennumber;
                strncpy(num, start, lennumber);
                num[lennumber] = 0;
                number = atoi(num);

                sum = sum + (number * sumMD);

                start = start + lennumber + 1;
                actionMD = 0;
            }

            // ביצוע חילוק רגיל, כלומר כאשר הוא לא בתוך סוגריים
            else if (actionMD == '/' && actionBrack != '(')
            {
                lennumber = ptr - start;
                lennumberMD = lennumberMD + lennumber;
                strncpy(num, start, lennumber);
                num[lennumber] = 0;
                number = atoi(num);

                sum = sum + (sumMD / number);

                start = start + lennumber + 1;
                actionMD = 0;
            }

            // חישוב חיבור רגיל שנמצא בתוך סוגריים
            else if (*ptr == '+' && actionBrack == '(')
            {
                lennumber = ptr - start;
                strncpy(num, start, lennumber);
                num[lennumber] = 0;
                number = atoi(num);

                if (action == '+')
                {
                    sumBrack = sumBrack + number;
                }
                else if (action == '-')
                {
                    sumBrack = sumBrack - number;
                }

                start = start + lennumber + 1;
            }

            // ביצוע חישוב רגיל
            else if (*ptr == '+')
            {
                lennumber = ptr - start;

                strncpy(num, start, lennumber);
                num[lennumber] = 0;
                number = atoi(num);

                if (action == '+')
                {
                    sum = sum + number;
                }
                else if (action == '-')
                {
                    sum = sum - number;
                }

                start = start + lennumber + 1;
            }
            action = '+';
        }

        // מורה דרך למספר פעולות בנפרד כאשר הפעולה שלילית
        else if (*ptr == '-')
        {
            // מחשב את כל הסכום שיש בסוגריים כולל את הכפל או החילוק 
            // כאשר הכפל והחילוק נמצאים בצד הימני של הסוגריים
            if ((actionMD == '/' || actionMD == '*') && actionBrack == ')' && MorD == 1)
            {
                lennumber = ptr - start;
                strncpy(num, start, lennumber);
                num[lennumber] = 0;
                number = atoi(num);

                if (actionMD == '*')
                {
                    sum = sum + (sumMD * sumBrack * number);
                }
                else if (actionMD == '/')
                {
                    sum = sum + (sumMD * sumBrack / number);
                }

                start = start + lennumber + 1;

                actionBrack = 0;
                actionMD = 0;
                sumBrack = 0;
                sumMD = 0;
                MorD = 0;
            }

            // מחשב את כל הסכום שיש בסוגריים כולל את הכפל שלפני
            else if (actionBrack == ')')
            {
                if (action == '+')
                {
                    lennumber = ptr - start;
                    strncpy(num, start, lennumber - 1);
                    num[lennumber] = 0;
                    number = atoi(num);

                    if (actionMD == '*')
                    {
                        sum = sum + (sumMD * (sumBrack + number));
                    }
                    else if (actionMD == '/')
                    {
                        sum = sum + (sumMD / (sumBrack + number));
                    }

                    start = start + lennumber + 1;
                }
                else if (action == '-')
                {
                    lennumber = ptr - start;
                    strncpy(num, start, lennumber - 1);
                    num[lennumber] = 0;
                    number = atoi(num);

                    if (actionMD == '*')
                    {
                        sum = sum + (sumMD * (sumBrack - number));
                    }
                    else if (actionMD == '/')
                    {
                        sum = sum + (sumMD / (sumBrack - number));
                    }

                    start = start + lennumber + 1;
                }
                // איפוס זיכרון נצרך
                actionBrack = 0;
                actionMD = 0;
                sumBrack = 0;
            }

            // ביצוע כפל רגיל, כלומר כאשר הוא לא בתוך סוגריים
            else if (actionMD == '*' && actionBrack != '(')
            {
                lennumber = ptr - start; //1
                lennumberMD = lennumberMD + lennumber;  //2
                strncpy(num, start, lennumber);  // "*6"
                num[lennumber] = 0; // "6"/0
                number = atoi(num); //6

                sum = sum + (number * sumMD);

                //action = '-';

                start = start + lennumber + 1;
                actionMD = 0;
            }

            // ביצוע חילוק רגיל, כלומר כאשר הוא לא בתוך סוגריים
            else if (actionMD == '/' && actionBrack != '(')
            {
                lennumber = ptr - start; //1
                lennumberMD = lennumberMD + lennumber;  //2
                strncpy(num, start, lennumber);  // "*6"
                num[lennumber] = 0; // "6"/0
                number = atoi(num); //6

                sum = sum + (sumMD / number);

                //action = '-';

                start = start + lennumber + 1;
                actionMD = 0;
            }

            // חישוב חישוב שנמצא בתוך סוגריים כאשר הפעולה האחרונה הייתה חיובית והבאה תהיה שלילית
            //לדוגמא: (3-2) אז הוא דואג לחיבור של המספר 3
            else if (action == '+' && actionBrack == '(')
            {
                lennumber = ptr - start;
                strncpy(num, start, lennumber);
                num[lennumber] = 0;
                number = atoi(num);

                if (action == '+')
                {
                    sumBrack = sumBrack + number;
                }

                start = start + lennumber + 1;
            }

            // ביצוע חיבור רגיל כאשר הפעולה האחרונה הייתה חיובית והבאה תהיה שלילית
            // לדוגמא כמו המספר הראשון בתרגיל ולאחר מינוס - הוא דואג לחיבור של המספר החיובי
            else if (action == '+')
            {
                lennumber = ptr - start;
                strncpy(num, start, lennumber);
                num[lennumber] = 0;
                number = atoi(num);

                sum = sum + number;
                start = start + lennumber + 1;
            }

            // ביצוע חיסור בתוך הסוגריים
            else if (*ptr == '-' && actionBrack == '(')
            {
                lennumber = ptr - start;
                strncpy(num, start, lennumber);
                num[lennumber] = 0;
                number = atoi(num);

                sumBrack = sumBrack - number;

                start = start + lennumber + 1;
            }

            // ביצוע חיסור רגיל
            else if (*ptr == '-')
            {
                lennumber = ptr - start;
                strncpy(num, start, lennumber);
                num[lennumber] = 0;
                number = atoi(num);

                sum = sum - number;

                start = start + lennumber + 1;
            }
            action = '-';
        }

        // עושה חיבור בין המספרים שנמצאים בתוך הסוגריים,
        //כאשר הסוגריים הצד הימני למכפיל או למחלק
        else if ((*ptr == '/' || *ptr == '*') && actionBrack == ')')
        {
            lennumber = ptr - start;
            strncpy(num, start, lennumber - 1);
            num[lennumber] = 0;
            number = atoi(num);

            if (action == '+')
            {
                sumBrack = sumBrack + number;
                sumMD = 1;
            }
            else if (actionMD == '-')
            {
                sumBrack = sumBrack - number;
                sumMD = -1;
            }

            if (*ptr == '*')
            {
                actionMD = '*';
            }
            else if (*ptr == '/')
            {
                actionMD = '/';
            }

            MorD = 1;
            start = start + lennumber + 1;
        }

        // בודק עם המספר שלפני הכפל חיובי או שלילי, ומכניס אותו לזיכרון 
        else if (*ptr == '*')
        {
            actionMD = '*';
            lennumber = ptr - start;
            lennumberMD = 0;
            lennumberMD = lennumberMD + lennumber;
            strncpy(numMD, start, lennumber);
            numMD[lennumber] = 0;
            if (action == '+')
            {
                sumMD = atoi(numMD);
            }
            else if (action == '-')
            {
                sumMD = atoi(numMD) * -1;
            }

            start = start + lennumber + 1;
        }

        // בודק עם המספר שלפני החילוק חיובי או שלילי, ומכניס אותו לזיכרון 
        else if (*ptr == '/')
        {
            actionMD = '/';
            lennumber = ptr - start;
            lennumberMD = 0;
            lennumberMD = lennumberMD + lennumber;
            strncpy(numMD, start, lennumber);
            numMD[lennumber] = 0;
            if (action == '+')
            {
                sumMD = atoi(numMD);
            }
            else if (action == '-')
            {
                sumMD = atoi(numMD) * -1;
            }

            start = start + lennumber + 1;
        }

        // מכניס לזיכרון למתחיל סוגריים
        // בודק את הפעולה לפני הסוגריים האם הייתה חיובית ומכניס אותה לזיכרון
        else if (*ptr == '(')
        {
            actionBrack = '(';
            action = '+';

            start = start + 1;
        }

        // מכניס לזיכרון שסוגריים נגמרים
        else if (*ptr == ')')
        {
            actionBrack = ')';
        }

        // במידה והוא מצביע על מספר, הוא מקדם את ההצבעה ב1 
        //סוגר (ליתר הביטחון, במידה והמספר הוא בעל יותר מתו אחד) את במערך של המספרים  
        num[1] = 0;
        ptr++;
    }

    // מבצע פעולה אחרונה לאחר שיוצא מהלולאה

    lennumber = ptr - start;
    strncpy(num, start, lennumber);
    num[lennumber] = 0;
    number = atoi(num);

    if (actionMD == '*')
    {
        sum = sumMD * number;
    }
    else if (actionMD == '/')
    {
        sum = sumMD / number;
    }
    else if (action == '+')
    {
        sum = sum + number;
    }
    else if (action == '-')
    {
        sum = sum - number;
    }


    printf("=%d", sum);
    //printf("%s=%d", str, sum);
    return 0;

}
