#include "store.hpp"

void Store::set(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mu_);
    store_[key] = value;
}

std::string Store::get(const std::string& key) {
    std::lock_guard<std::mutex> lock(mu_);
    if (store_.count(key) == 0) return "(nil)";
    return store_[key];
}

void Store::del(const std::string& key) {
    std::lock_guard<std::mutex> lock(mu_);
    store_.erase(key);
}
