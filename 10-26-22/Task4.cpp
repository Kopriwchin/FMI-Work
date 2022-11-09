//#include <iostream>
//
//int main() {
//
//    int low, high, i;
//    bool is_prime = true;
//
//    std::cin >> low >> high;
//
//    while (low < high) {
//        is_prime = true;
//
//        if (low == 0 || low == 1) {
//            is_prime = false;
//        }
//
//        for (i = 2; i <= low / 2; ++i) {
//            if (low % i == 0) {
//                is_prime = false;
//                break;
//            }
//        }
//
//        if (is_prime)
//            std::cout << low << ", ";
//
//        ++low;
//    }
//
//    return 0;
//}