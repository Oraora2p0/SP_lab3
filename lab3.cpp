#include <iostream>
#include <ctime>

int main()
{
    //генерация матрицы m на n
    srand(time(0));
    int n ,m;
    n   =rand()%5+3; //размеры матрицы от 3 до 7
    m   =rand()%5+3;
     long long arrayA[m][n];
    for (size_t i = 0; i < m ;i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            arrayA[i][j]=rand()%9+3; //числа в матрице от 3 до 11
        }
    }
    //вывод матрицы
    std::cout<<"___________________________"<<std::endl;
    for (size_t i = 0; i < m ;i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            std::cout<<arrayA[i][j]<<"\t";
        }
        std::cout<<'\n';
    }
    int a=0; //сумма
    printf("___________________________\n");
    long long *A_array_start=&arrayA[0][0]; //указатель на начало массива
    long long *A_array_end=&arrayA[m-1][n-1]; //указатель на конец массива
        //код ассемблера через ассемблерные вставки
        asm (  
        "movq $0,%%rax\n\t" //на всякий случай зануляем регистры
        "movq %[A_array_start],%%rbx\n\t" //перемещаем в регистр rbx указатель на начало массива
        "subq $8, %%rbx \n\t" // предварительное вычитание чтобы пройтись по ВСЕМ элементам
        "movq $0,%%r10\n\t" //на всякий случай зануляем регистры
        "start1: \n\t"
        "addq $8, %%rbx \n\t" // переход по массиву
        "movq (%%rbx), %%rax\n\t" //перебрасываем значение ячейки массива, в rax по указателю на область памяти (rbx)
        "mulq %%rax\n\t" //умножаем rax на rax (квадрат числа) 
        "addq %%rax, %%r10\n\t" //добавляем значение к сумме элементов
        "cmpq %%rbx, %[A_array_end]\n\t" //конец массива?
        "jne start1\n\t" //если нет, то переходим на start1 и начинаем заново
        "movq %%r10, %%rax\n\t" //перебрасываем результат в rax, который пойдёт в а
            :"=a"(a) //выходные операнды
            :[A_array_end]"m"(A_array_end),   // входные операнды  
            [A_array_start]"m"(A_array_start) //
            :"%rbx" //разрушаемые регистры
        );
    std::cout<<"____________sum____________"<<std::endl;
    std::cout<<a<<std::endl;
    std::cout<<"____________c++____________"<<std::endl;
    int sum=0;
        //проверка резульатата на c++
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            sum+=arrayA[i][j]*arrayA[i][j];
        }
    }
    std::cout<<sum<<std::endl;
    return 0;
}