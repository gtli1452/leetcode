int maxProfit(int *prices, int pricesSize)
{
    if (pricesSize <= 1)
        return 0;

    int max_profit = 0;
    int min_price = prices[0];

    for (int i = 0; i < pricesSize; i++) {
        if (prices[i] < min_price)
            min_price = prices[i];
        else if (prices[i] - min_price > max_profit)
            max_profit = prices[i] - min_price;
    }
    return max_profit;
}

/* Use macro to simplify */
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

int maxProfit_v2(int *prices, int pricesSize)
{
    if (pricesSize <= 1)
        return 0;

    int max_profit = 0;
    int min_price = prices[0];

    for (int i = 0; i < pricesSize; i++) {
        min_price = min(prices[i], min_price);
        max_profit = max(prices[i] - min_price, max_profit);
    }
    return max_profit;
}

/* Brute force */
int maxProfit_v3(int *prices, int pricesSize)
{
    if (pricesSize <= 1)
        return 0;

    int max_profit = 0;

    for (int i = 0; i < pricesSize - 1; i++) {
        for (int j = i + 1; j < pricesSize; j++) {
            if (prices[j] - prices[i] > max_profit)
                max_profit = prices[j] - prices[i];
        }
    }
    return max_profit;
}