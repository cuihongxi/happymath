#include "stdio.h"
#include "math.h"

// ����һ������ָ������
typedef double (*fun_t)(double x);
typedef double fun_drv(fun_t fun, double x, unsigned char n); // n�׺�����


// �����Ǻ����ĵ���
char sanjiao_derivative(char index, char* fuhao)
{
   if(index == 0)// sin��
       return 1;    // �������Һ������
   else
   {
        *fuhao = -(*fuhao); // �ı����
        return 0;   // �������Һ������
   }
}

// ���Ǻ���n����
double fun_derivative(fun_t fun, double x, unsigned char n)
{
    if(n == 0)
        return fun(x); // ���غ���ֵ
    char index = 0;
    char fuhao = 1; // ���ţ�1��ʾ����-1��ʾ��
    if(fun == cos)index = 1;
    
    for(int i=0; i < n; i++)
    {
        index = sanjiao_derivative(index, &fuhao); // ��
    }
    if(index == 0)
        return fuhao * sin(x); // �������Һ���ֵ
    else
        return fuhao * cos(x); // �������Һ���ֵ
}




// ����̩��չ����һ��
// n : չ���Ĵ���
double taile_n(fun_t fun, fun_drv f_drv, double x, double x0, double n)
{
    if(n == 0)
        return fun(x0);

    // ����x-x0��n�η�
    double ncifang = 1;  // (x-x0)��n�η�
    for(unsigned char i = 0; i < n; i++)
        ncifang *= (x - x0);

    // ����n�Ľ׳�
    double n_val = 1;    // n�Ľ׳�
    for(unsigned char i = 1; i <= n; i++)
        n_val *= i;

    // ������n�׵���
    double derivative = f_drv(fun, x0, n);

    double value = derivative/n_val * ncifang;
    
    return value;
}



// ����̩��չ��
// times : ����ǰ����
double taile(fun_t fun, fun_drv f_drv, unsigned char times, double x, double x0)
{
    double value = 0; // ̩��չ����ֵ
    for(unsigned char i = 0; i < times; i++)
    {
        value += taile_n(fun, fun_derivative, x, x0, i);
    }
    return value;

}



// ���Ժ���
void main()
{
    double x = 181 * 3.1415926 /180;  // Ҫ����ĵ�
    double x0 = 30 * 3.1415926 /180; // չ���� 30��

    double result = taile(sin, fun_derivative, 25, x, x0);
    printf("̩��չ�����: %lf\n", result);
}

