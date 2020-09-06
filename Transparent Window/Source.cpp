#include "TransparentWindowApi.h"

int main() {
    TransparentWindowApi tApi;
    tApi.Transparency() = 0xFF * 0.8;
    tApi.Execute(L"processName");
    std::cin.get();
    return 0;
}