#include "stdio.h"
#include "math.h"

// 定义一个函数指针类型
typedef double (*fun_t)(double x);
typedef double fun_drv(fun_t fun, double x, unsigned char n); // n阶函数求导


// 求三角函数的导数
char sanjiao_derivative(char index, char* fuhao)
{
   if(index == 0)// sin求导
       return 1;    // 返回余弦函数序号
   else
   {
        *fuhao = -(*fuhao); // 改变符号
        return 0;   // 返回正弦函数序号
   }
}

// 三角函数n阶求导
double fun_derivative(fun_t fun, double x, unsigned char n)
{
    if(n == 0)
        return fun(x); // 返回函数值
    char index = 0;
    char fuhao = 1; // 符号，1表示正，-1表示负
    if(fun == cos)index = 1;
    
    for(int i=0; i < n; i++)
    {
        index = sanjiao_derivative(index, &fuhao); // 求导
    }
    if(index == 0)
        return fuhao * sin(x); // 返回正弦函数值
    else
        return fuhao * cos(x); // 返回余弦函数值
}




// 计算泰勒展开的一项
// n : 展开的次数
double taile_n(fun_t fun, fun_drv f_drv, double x, double x0, double n)
{
    if(n == 0)
        return fun(x0);

    // 计算x-x0的n次方
    double ncifang = 1;  // (x-x0)的n次方
    for(unsigned char i = 0; i < n; i++)
        ncifang *= (x - x0);

    // 计算n的阶乘
    double n_val = 1;    // n的阶乘
    for(unsigned char i = 1; i <= n; i++)
        n_val *= i;

    // 求函数的n阶导数
    double derivative = f_drv(fun, x0, n);

    double value = derivative/n_val * ncifang;
    
    return value;
}



// 计算泰勒展开
// times : 计算前几项
double taile(fun_t fun, fun_drv f_drv, unsigned char times, double x, double x0)
{
    double value = 0; // 泰勒展开的值
    for(unsigned char i = 0; i < times; i++)
    {
        value += taile_n(fun, fun_derivative, x, x0, i);
    }
    return value;

}



// 测试函数
void main()
{
    double x = 181 * 3.1415926 /180;  // 要计算的点
    double x0 = 30 * 3.1415926 /180; // 展开点 30°

    double result = taile(sin, fun_derivative, 25, x, x0);
    printf("泰勒展开结果: %lf\n", result);
}

