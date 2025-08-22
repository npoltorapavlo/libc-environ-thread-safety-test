#include <string>
#include <thread>
#include <vector>

extern char** environ;

auto saveEnvironment(std::vector<std::string>& environment)
{
    char** env = environ;

    environment.clear();

    while (*env) {
        environment.push_back(*env);
        env++;
    }
}

auto clearEnvironment()
{
    std::vector<std::string> environment;
    saveEnvironment(environment);

    for (auto it = environment.begin(); it != environment.end(); ++it) {
        auto pos = it->find("=");
        if (pos != std::string::npos) {
            auto name = it->substr(0, pos);
            unsetenv(name.c_str());
        }
    }
}

auto setEnvironment(const std::vector<std::string>& environment)
{
    for (auto it = environment.begin(); it != environment.end(); ++it) {
        auto pos = it->find("=");
        if (pos != std::string::npos) {
            auto name = it->substr(0, pos);
            auto val = it->substr(pos + 1);

            setenv(name.c_str(), val.c_str(), 1);
        }
    }
}

auto main() -> int
{
    std::thread t1([&]() {
        while (1) {
            std::vector<std::string> env;
            saveEnvironment(env);
            clearEnvironment();
            setEnvironment(env);
        }
    });

    std::thread t2([&]() {
        while (1) {
            printf("%s, %s, %s\n",
                getenv("key1"), getenv("key2"), getenv("key3"));
        }
    });

    t1.join();
    t2.join();

    return (0);
}
