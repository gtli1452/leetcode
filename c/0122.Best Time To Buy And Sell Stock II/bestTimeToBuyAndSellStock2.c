/*
 * These two approaches are available because we can buy the stock then
 * immediately sell it on the same day
 */

/* Peak valley approach */
int maxProfit(int *prices, int pricesSize)
{
    if (pricesSize <= 1)
        return 0;

    int valley = prices[0];
    int peak = 0;
    int max_profit = 0;

    for (int i = 0; i < pricesSize; i++) {
        if (prices[i] < valley)
            valley = prices[i];
        else if (prices[i] > valley) {
            peak = prices[i];
            max_profit += peak - valley;
            valley = prices[i];
        }
    }
    return max_profit;
}

/* Simple one pass */
int maxProfit_v2(int *prices, int pricesSize)
{
    if (pricesSize <= 1)
        return 0;

    int max_profit = 0;

    for (int i = 0; i < pricesSize - 1; i++) {
        if (prices[i] < prices[i + 1])
            max_profit += prices[i + 1] - prices[i];
    }
    return max_profit;
}