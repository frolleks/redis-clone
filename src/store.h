#ifndef STORE_H
#define STORE_H

#include <mutex>
#include <string>
#include <unordered_map>

class Store {
  public:
    void set(const std::string &key, const std::string &value);
    std::string get(const std::string &key);
    void del(const std::string &key);

  private:
    std::unordered_map<std::string, std::string> store_;
    std::mutex mu_;
};

#endif // STORE_H
