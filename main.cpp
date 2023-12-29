//
// Created by wen on 2023-12-29.
//
#include <iostream>
#include <vector>
#include <memory>

template<typename T>
class Tensor {
public:
    Tensor() = default;
    Tensor(std::vector<size_t> shape) : shape_(shape) {
        size_t total_size = 1;
        for (auto &dim : shape) total_size *= dim;
        data_ = std::make_shared<std::vector<T>>(total_size);
    }

    T& operator[](const std::vector<size_t>& index) {
        return (*data_)[get_flat_index(index)];
    }

    const T& operator[](const std::vector<size_t>& index) const {
        return (*data_)[get_flat_index(index)];
    }
    void print() {
        for (size_t i = 0; i < shape_[0]; i++) {
            for (size_t j = 0; j < shape_[1];j++) {
                std::cout << (*data_)[i * shape_[1] + j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // ... 这里可以添加更多的功能，比如基本的数学运算等 ...

private:
    std::shared_ptr<std::vector<T>> data_;
    std::vector<size_t> shape_;

    size_t get_flat_index(const std::vector<size_t>& index) const {
        size_t flat_index = 0;
        size_t multiplier = 1;
        for (int i = shape_.size() - 1; i >= 0; --i) {
            flat_index += index[i] * multiplier;
            multiplier *= shape_[i];
        }
        return flat_index;
    }
};

// 示例用法
int main() {
    Tensor<float> tensor({2, 3}); // 创建一个2x3的tensor
//    tensor[{0, 1}] = 3.14;
//    std::cout << tensor[{0, 1}] << std::endl; // 输出3.14
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 3;j++) {
            tensor[{i, j}] = i * 3 + j;
//            std::cout << tensor[{i, j}] << std::endl;
        }
    }
    tensor.print();
    return 0;
}
