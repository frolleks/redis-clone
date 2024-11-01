#include "gen_info_string.h"

#include <chrono>
#include <sstream>
#include <thread>

// Platform-dependent includes for some values
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

std::string gen_info_string() {
    std::ostringstream info;

    // Static values
    info << "# Server\n";
    info << "redis_version: 1.0.0\n";     // Custom version for this application
    info << "redis_git_sha1: 00000000\n"; // Placeholder Git SHA1
    info << "redis_git_dirty: 0\n";       // No Git changes
    info << "redis_build_id: 12345\n";    // Placeholder build ID
    info << "redis_mode: standalone\n";   // Mode of operation (standalone)

    // OS-specific information
#ifdef _WIN32
    info << "os: Windows\n";
#else
    info << "os: Linux\n"; // Assuming Linux, adjust as needed
#endif

    info << "arch_bits: " << (sizeof(void *) * 8)
         << "\n";                        // 32 or 64 bits based on architecture
    info << "multiplexing_api: epoll\n"; // Assuming epoll for Linux, adjust as
                                         // needed
    info << "atomicvar_api: atomic-builtin\n"; // Placeholder for atomic API
    info << "gcc_version: 9.3.0\n";            // Placeholder GCC version

    // Process information
    info << "process_id: " << getpid() << "\n"; // Current process ID
    info << "process_supervised: no\n";   // No supervision system in place
    info << "run_id: 1234567890abcdef\n"; // Placeholder random ID
    info << "tcp_port: 6379\n"; // Placeholder port, typical Redis default

    // Server time and uptime
    auto now = std::chrono::system_clock::now();
    auto uptime_seconds =
        std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch())
            .count();

    info << "server_time_usec: " << uptime_seconds * 1000000
         << "\n"; // Convert seconds to microseconds
    info << "uptime_in_seconds: " << 3600 << "\n"; // Assuming 1 hour uptime
    info << "uptime_in_days: " << 3600 / 86400
         << "\n"; // Calculating days based on seconds

    // Server configuration
    info << "hz: 10\n";            // Placeholder for server frequency
    info << "configured_hz: 10\n"; // Placeholder configured frequency
    info << "lru_clock: " << (uptime_seconds / 60) % (1 << 31)
         << "\n"; // Increment every minute for LRU

    // Paths (Placeholders)
    info << "executable: /usr/local/bin/redis\n"; // Placeholder executable path
    info << "config_file: /etc/redis/redis.conf\n"; // Placeholder config file
                                                    // path

    // Threading and shutdown
    info << "io_threads_active: 0\n";        // I/O threads not active
    info << "shutdown_in_milliseconds: 0\n"; // Default for no shutdown

    return info.str();
}