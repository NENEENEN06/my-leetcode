class ProductOfNumbers {
public:
    vector<int> products = {1};

    ProductOfNumbers() {
    }

    void add(int num) {
        if (num) {
            products.push_back(products.back() * num);
        } else {
            // 乘积跨过这个 0 时一定为 0，不必再保存此前的前缀。
            products = {1};
        }
    }

    int getProduct(int k) {
        if (k < products.size()) {
            return products.back() / products[products.size() - k - 1];
        } else {
            return 0;
        }
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
