#include<stdio.h>
#include<conio.h>
#include<cmath>

/********************************************************
*   Luat 1: Neu VX day thi do VX di                    *
*   Luat 2: Neu VY rong thi do day nuoc cho binh 2     *
*   Luat 3: Neu VX khong day va VY khong rong thi      *
*   trut nuoc tu VY sang VX cho den khi VX day         *
*                                                      *
*********************************************************/
int Vx, Vy, z;
void nhap()
{
	printf("\n----------------------------------\n");
	printf("\nNhap Vx: ");
	scanf_s("%d", &Vx);
	printf("\nNhap Vy: ");
	scanf_s("%d", &Vy);
	printf("\nNhap z: ");
	scanf_s("%d", &z);
}

void dongnuoc()
{
	if (Vx > Vy)
	{
		int temp = Vx;
		Vx = Vy;
		Vy = temp;
	}

	int x, y, k;
	printf("\n----------------------------------\n");
	printf("\n\nBai Lam:");
	x = 0; y = 0;
	
	while ((x != z) && (y != z))
	{
		if (x == Vx)
		{
			x = 0;
			printf("\nLuat 1: x=%d ", x);
			printf(" y=%d ", y);
		}
		if (y == 0)
		{
			y = Vy;
			printf("\n\nLuat 2: x=%d", x);
			printf(" y=%d", y);
		}
		if (y > 0)
		{
			k = __min(Vx - x, y);
			x = x + k;
			y = y - k;
			printf("\nLuat 3: x=%d", x);
			printf(" y=%d", y);
		}
	}
}
int main()
{
	nhap();
	
	dongnuoc();

	_getch();
	return 0;
}