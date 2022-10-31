#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

/*******   �������� �������� ���� �� ������� ��������� ���� ������ �� ������ ������   ********/
/*
     1+1=2
     10+20=30
     10-8=2
     10-7-1=2
     10-5+4+4-7-1=5

     ����� 1
     1+34-6+456-22+876-12+100-2+4=1429

     7*5=35
     10*5=50
     90/9=10

     ����� 2
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

    // ����� 3
    // 1+34*(6+56)-5+6*(3+9456)+876-12/100-2+4  //59,736
*/

int main()
{
    char str[1000];
    char num[100];
    char numMD[100]; // Mult_div


    printf("please enter a str: \n");
    gets(str);

    int sum = 0; // ������ ���� ���� 
    int sumMD = 0;  // ������ ������ �� ��� ������ ���� ��� ���� ������� 
    int sumBrack = 0; // ������ ������ ����� �������� ���� ��� ���� �������
    int action = '+';  //  ���� �� ������ ������� - ����� ����� �� ����� ��� ������ ������ ���� ���� ����� 
    int actionMD = 0;  // ���� ����� �������, ��� ����� ���� �� ����� ������ ���� ���� - �� ����� ������ �� �����
    int actionBrack = 0; // ���� ����� �������, ��� ����� ���� �� ����� ������ ���� �������� - �� ����� ������ �� �����
    char* ptr = str;  // ����� �� ������ �������
    char* start = str;  // ����� �� ������ �������

    int len = strlen(str);

    int lennumber;    // ��� ����� �� �����
    int lennumberMD;  // ���� �� ��� ���� ��� ����� ����� (1*2) ��� ������ ���� �����
    int number;       // ���� ��� ������ ��� ��� ����� �������� �� ���� ���� 
    int MorD = 0;         // ���� ��� �� ����� ����� ���� ����� ����

    for (int i = 0; i < len; i++)
    {
        // ���� ��� ����� ������ ����� ���� ������ ������
        if (*ptr == '+')
        {
            // ���� �� �� ����� ��� �������� ���� �� ���� �� ������ 
            // ���� ���� ������� ������ ��� ����� �� ��������
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

            // ���� �� �� ����� ��� �������� ���� �� ���� �� ������ �����
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
                // ����� ������ ����
                actionBrack = 0;
                actionMD = 0;
                sumBrack = 0;
            }

            // ����� ��� ����, ����� ���� ��� �� ���� �������
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

            // ����� ����� ����, ����� ���� ��� �� ���� �������
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

            // ����� ����� ���� ����� ���� �������
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

            // ����� ����� ����
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

        // ���� ��� ����� ������ ����� ���� ������ ������
        else if (*ptr == '-')
        {
            // ���� �� �� ����� ��� �������� ���� �� ���� �� ������ 
            // ���� ���� ������� ������ ��� ����� �� ��������
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

            // ���� �� �� ����� ��� �������� ���� �� ���� �����
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
                // ����� ������ ����
                actionBrack = 0;
                actionMD = 0;
                sumBrack = 0;
            }

            // ����� ��� ����, ����� ���� ��� �� ���� �������
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

            // ����� ����� ����, ����� ���� ��� �� ���� �������
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

            // ����� ����� ����� ���� ������� ���� ������ ������� ����� ������ ����� ���� ������
            //������: (3-2) �� ��� ���� ������ �� ����� 3
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

            // ����� ����� ���� ���� ������ ������� ����� ������ ����� ���� ������
            // ������ ��� ����� ������ ������ ����� ����� - ��� ���� ������ �� ����� ������
            else if (action == '+')
            {
                lennumber = ptr - start;
                strncpy(num, start, lennumber);
                num[lennumber] = 0;
                number = atoi(num);

                sum = sum + number;
                start = start + lennumber + 1;
            }

            // ����� ����� ���� ��������
            else if (*ptr == '-' && actionBrack == '(')
            {
                lennumber = ptr - start;
                strncpy(num, start, lennumber);
                num[lennumber] = 0;
                number = atoi(num);

                sumBrack = sumBrack - number;

                start = start + lennumber + 1;
            }

            // ����� ����� ����
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

        // ���� ����� ��� ������� ������� ���� ��������,
        //���� �������� ��� ����� ������ �� �����
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

        // ���� �� ����� ����� ���� ����� �� �����, ������ ���� ������� 
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

        // ���� �� ����� ����� ������ ����� �� �����, ������ ���� ������� 
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

        // ����� ������� ������ �������
        // ���� �� ������ ���� �������� ��� ����� ������ ������ ���� �������
        else if (*ptr == '(')
        {
            actionBrack = '(';
            action = '+';

            start = start + 1;
        }

        // ����� ������� �������� ������
        else if (*ptr == ')')
        {
            actionBrack = ')';
        }

        // ����� ���� ����� �� ����, ��� ���� �� ������ �1 
        //���� (���� �������, ����� ������ ��� ��� ���� ��� ���) �� ����� �� �������  
        num[1] = 0;
        ptr++;
    }

    // ���� ����� ������ ���� ����� �������

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
