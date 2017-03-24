/*############################################################################*/
/*HW_08_SULEYMAN_BALABAN_121044014_part1.c                                    */
/*____________________________________________________________________________*/
/*Written by SULEYMAN BALABAN APRIL 21,2015                                   */
/*                                                                            */
/*DESCRIPTION                                                                 */
/*____________________________________________________________________________*/
/*Write a complete C program to find max rectangular sum                      */
/*                                                                            */
/*                                                                            */
/*############################################################################*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                  INCLUDES                                  */
/*----------------------------------------------------------------------------*/

#include<stdio.h>

#define COL_COUNT 8
#define ROW_CAP 10

#define FILE1 "Table1.txt" /*file define*/

typedef struct {
    int x;
    int y;
} Point_t;

typedef struct {
    Point_t left_up;
    Point_t right_down;
    double sum;
} Rectangle_t;

/*Point_t tipinde structlara donusturur*/
Point_t construct_point(int x, int y);

/*Rectangle_t tipinde structlara donusturur*/
Rectangle_t construct_rectangle(Point_t left_up, Point_t right_down);

/*genel sonuclari bastirir*/
void print_rectangle(const Rectangle_t*rectangle);

/*toplama islemi yapar adim adim*/
void getSum(double table [][COL_COUNT], Rectangle_t*rectangle);
/*orjinden baslayarak maxSum i bulur*/

Rectangle_t maxSumConstPoint(double table[][COL_COUNT], int nRow,
        Point_t left_up);

/*tum sayilar icin maxSum bulur*/
Rectangle_t maxSumRec(double table[][COL_COUNT], int nRow);

/*start of main*/
int main(void) {
    int x, y;
    Point_t result;
    Rectangle_t result1;
    Point_t left_up, right_down;
    double table [ROW_CAP][COL_COUNT];
    int row = 0;
    int col;
    int status = EOF + 1;

    /*dosyayi acip kontrol eder*/
    FILE*iptr;
    iptr = fopen(FILE1, "r");
    if (iptr == NULL)
        printf("file couldn't opened!");

    /*dosyadan arry e okuma yapilir*/
    while (status != EOF) {
        for (col = 0; col < COL_COUNT; col++)
            status = fscanf(iptr, "%1F", &table[row][col]);
        ++row;
    }
    row--; /*fazladan bir deger cikarilir*/

    result = construct_point(x, y); /*Point_t tipine donusturur*/

    /*Rectangle_t tipinde donusturur*/
    result1 = construct_rectangle(left_up, right_down);

    result.y = 0; /*orjine gore yapmak icin bu degerler sifirlanir*/
    result.x = 0;

    /*fonksiyon cagirilir Rectangle_t tipinde degisene assign edilir*/
    result1 = maxSumConstPoint(table, row, result);

    printf("################################################################\n");
    print_rectangle(&result1); /*sonuclari bastirma fonksiyonu*/
    printf("----------------------------------------------------------------\n");
    result1 = maxSumRec(table, row); /*sonuclari bastirma fonksiyonu*/
    printf("################################################################\n");
    return (0);
} /*end of main*/

Point_t construct_point(int x, int y) {
    Point_t temp; /*degisken tanimlanir*/

    temp.x = x; /*assign edilir*/
    temp.y = y;

    return temp; /*return value*/
}

Rectangle_t construct_rectangle(Point_t left_up, Point_t right_down) {

    Rectangle_t temp; /*degisken tanimlanir*/

    temp.left_up = left_up; /*assign edilir*/
    temp.right_down = right_down;

    return temp; /*return value*/
}

void print_rectangle(const Rectangle_t*rectangle) {
    /*sonuclar bastirilir*/
    printf("MaxSum Rectangular is %.2f.", rectangle->sum);
    printf("Its left upper coordinate (y,x) is %d, %d,",
            rectangle->left_up.y, rectangle->right_down.x);
}

void getSum(double table[][COL_COUNT], Rectangle_t*rectangle) {
    int row, col;
    rectangle->sum = 0; /*her basamakta sifirlansin diye*/

    for (row = rectangle->left_up.y; row <= rectangle->right_down.y; ++row)
        for (col = rectangle->left_up.x; col <= rectangle->right_down.x; ++col)
            rectangle->sum += table[row][col]; /*toplanir her indis*/
}

Rectangle_t maxSumConstPoint(double table[][COL_COUNT], int nRow,
        Point_t left_up) {
    int rDX;
    int rDY;
    Rectangle_t temp, rectangle;

    temp.sum = table[left_up.x][left_up.y]; /*baslangic orjin degeri*/
    temp.right_down.y = left_up.y; /*indis degerleri*/
    temp.right_down.x = left_up.x;

    rectangle.left_up.y = left_up.y; /*indis degerleri karsilastirmak icin*/
    rectangle.left_up.x = left_up.x;

    for (rDY = left_up.y; rDY < nRow; ++rDY) {
        rectangle.right_down.y = rDY; /*struct doldurulur*/
        rectangle.right_down.x = rDX;
        getSum(table, &rectangle); /*toplama fonk. cagrilir*/
        {
            temp.sum = rectangle.sum;
            temp.right_down.y = rDY;
            temp.right_down.x = rDX;
            temp.left_up.y = left_up.y;
            temp.left_up.x = left_up.x;
        }
    }
    return temp; /*degerler return edilir*/
}

Rectangle_t maxSumRec(double table [][COL_COUNT], int nRow) {
    int i, j; /*variables*/
    Rectangle_t temp, rectangle;
    Point_t val, left_up;

    left_up.y = 0; /*(0,0) noktasi baz alinarak sort yapilacak o yuzden*/
    left_up.x = 0;

    /*Rectangle_t tipinde struct a atilir*/
    temp = maxSumConstPoint(table, nRow, left_up);

    for (i = 0; i < nRow; ++i) {
        for (j = 0; j < nRow; ++j) {
            val.y = i;
            val.x = j; /*dongu ilerledikce indisler ve fonk. degeri degiscek*/
            rectangle = maxSumConstPoint(table, nRow, val);

            if (rectangle.sum < temp.sum)/*sort islemi*/ {
                temp.sum = rectangle.sum;
                temp.right_down.y = rectangle.right_down.y;
                temp.right_down.x = rectangle.right_down.x;
                temp.left_up.y = i;
                temp.left_up.x = j;
            }
        }
    }
    return temp; /*degerler return edilir*/
}

/*############################################################################*/
/*                  End of HW08_SULEYMAN_BALABAN_121044014_part1.c            */
/*############################################################################*/