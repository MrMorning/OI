#include <cstdio>

const int PRODUCT_NUM = 10;
const int SIZE_NUM = 3;
const int PROVINCE_NUM = 10;
const int CITY_NUM = 20;
const int REGION_NUM = 5;
const int MALE_NUM = 2;
const int AGE_NUM = 91;

int rec[PRODUCT_NUM][SIZE_NUM + 1][PROVINCE_NUM][CITY_NUM + 1][REGION_NUM + 1][MALE_NUM][AGE_NUM];
char ch, cmd[10];
int productId, sizeId, provinceId, cityId, regionId;
int unitsSold;
int startProduct, endProduct, startSize, endSize;
int startProvince, endProvince, startCity, endCity;
int startRegion, endRegion, startAge, endAge;
int age, sex;

int main()
{
	freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	while(_ --)
	{
		scanf("%s", cmd);
		if(cmd[0] == 'I')
		{
			scanf("%d", &productId);
			scanf("%c", &ch);
			if(ch == '.')
				scanf("%d", &sizeId);
			else
				sizeId = SIZE_NUM;
			scanf("%d", &provinceId);
			scanf("%c", &ch);
			if(ch == '.')
			{
				scanf("%d", &cityId);
				scanf("%c", &ch);
				if(ch == '.')
					scanf("%d", &regionId);
				else
					regionId = REGION_NUM;
			}
			else
				cityId = CITY_NUM, regionId = REGION_NUM;
			scanf("%s", cmd);
			if(cmd[0] == 'M')
				sex = 0;
			else
				sex = 1;
			scanf("%d%d", &age, &unitsSold);
			rec[productId][sizeId][provinceId][cityId][regionId][sex][age] += unitsSold;
		}
		else
		{
			scanf("%d", &productId);
			scanf("%c", &ch);
			if(ch == '.')
			{
				scanf("%d", &sizeId);
				startSize = endSize = sizeId;
			}
			else
				startSize = 0, endSize = SIZE_NUM;

			if(productId == -1)
				startProduct = 0, endProduct = PRODUCT_NUM - 1, startSize = 0, endSize = SIZE_NUM;
			else
				startProduct = endProduct = productId;

			scanf("%d", &provinceId);
			scanf("%c", &ch);
			if(ch == '.')
			{
				scanf("%d", &cityId);
				scanf("%c", &ch);
				if(ch == '.')
				{
					scanf("%d", &regionId);
					startRegion = endRegion = regionId;
				}
				else
					startRegion = 0, endRegion = REGION_NUM;
				startCity = endCity = cityId;
			}
			else
			{
				startCity = 0, endCity = CITY_NUM;
				startRegion = 0, endRegion = REGION_NUM;
			}

			if(provinceId == -1)
			{
				startProvince = 0, endProvince = PROVINCE_NUM - 1;
				startCity = 0, endCity = CITY_NUM;
				startRegion = 0, endRegion = REGION_NUM;
			}
			else
				startProvince = endProvince = provinceId;

			scanf("%s", cmd);
			if(cmd[0] == 'M')
				sex = 0;
			else
				sex = 1;
			scanf("%d%c", &startAge, &ch);
			if(ch == '-')
				scanf("%d", &endAge);
			else
				endAge = startAge;

			int res = 0;
			for(int i = startProduct; i <= endProduct; i ++)
				for(int j = startSize; j <= endSize; j ++)
					for(int k = startProvince; k <= endProvince; k ++)
						for(int l = startCity; l <= endCity; l ++)
							for(int m = startRegion; m <= endRegion; m ++)
								for(int n = startAge; n <= endAge; n ++)
									res += rec[i][j][k][l][m][sex][n];
			printf("%d\n", res);
		}
	}
}
