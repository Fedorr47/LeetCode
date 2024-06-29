#include <iostream>

#include <vector>


int maxProfit(std::vector<int>& prices) {
    int minprice = INT_MAX;
    int maxprofit = 0;
    for (int i = 0; i < prices.size(); i++) {
        if (prices[i] < minprice)
            minprice = prices[i];
        else if (prices[i] - minprice > maxprofit)
            maxprofit = prices[i] - minprice;
    }
    return maxprofit;
}

int main() {
    std::vector<int> arr{ 7, 1, 5, 3, 6, 4 };
    maxProfit(arr);

    return 0;
}
