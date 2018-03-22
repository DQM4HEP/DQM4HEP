/*
 *
 * Internal.cc source template automatically generated by a class generator
 * Creation date : lun. ao�t 17 2015
 *
 * This file is part of DQM4HEP libraries.
 *
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */

// -- dqm4hep headers
#include <dqm4hep/Internal.h>

#include <cstring>

namespace dqm4hep {

  namespace core {

#ifdef DQM4HEP_WITH_PROC_FS
    // only for unix systems
    int getProcValue(const std::string fname, const std::string &entry) {
      FILE* file = fopen(fname.c_str(), "r");
      int result = -1;
      char line[128];

      while (fgets(line, 128, file) != nullptr) {
        if (strncmp(line, entry.c_str(), entry.size()) == 0) {
          int i = strlen(line);
          const char* p = line;
          while (*p <'0' || *p > '9') {
            p++;
          }
          line[i-3] = '\0';
          result = atoi(p);
          break;
        }
      }
      fclose(file);
      return result;
    }
#endif

#ifdef _WIN32
    void memStats(MemoryStats &) {
      /* WINDOWS implementation: TBD */
    }
#elif __APPLE__
    void memStats(MemoryStats &stats) {
      double unit = 1024. * 1024.; // Store everything in mb

      // Swap info
      // Swap is dynamically alotted on OSX, It will expand as the system needs it until the boot drive is filled.
      struct xsw_usage swapStats;
      size_t lengthSwap = sizeof(swapStats);
      if (KERN_SUCCESS != sysctlbyname("vm.swapusage", &swapStats, &lengthSwap, NULL, 0))
        std::cerr << "[OSX] - Failed to get swap statistics" << std::endl;

      // Total physical memory
      int64_t physicalMem;
      size_t lengthPM = sizeof(physicalMem);
      if (KERN_SUCCESS != sysctlbyname("hw.memsize", &physicalMem, &lengthPM, NULL, 0))
        std::cerr << "[OSX] - Failed to get physical memory statistics" << std::endl;
      stats.rsstot = physicalMem;
      stats.rsstot /= unit;

      // Total virtual memory
      int pageSize;
      size_t lengthPage = sizeof(pageSize);
      if (KERN_SUCCESS != sysctlbyname("hw.pagesize", &pageSize, &lengthPage, NULL, 0))
        std::cerr << "[OSX] - Failed to get page size" << std::endl;

      vm_statistics_data_t vmStat;
      mach_msg_type_number_t vmInfoCount = HOST_VM_INFO_COUNT;
      if (KERN_SUCCESS != host_statistics (mach_host_self (), HOST_VM_INFO, (host_info_t) &vmStat, &vmInfoCount))
        std::cerr << "[OSX] - Failed to get VM statistics." << std::endl;

      double wired = vmStat.wire_count; // in use, cannot go inactive
      double active = vmStat.active_count; // currently in use, can go inactive if not accessed for some time
      double inactive = vmStat.inactive_count; // was in use not long ago, still retrievable -> Not Sure wheter to include in used ram
      double free = vmStat.free_count; // real free ram usable instantly -> Always around 0-50mb max on my mac
      double total = wired + active + inactive;
      stats.vmtot = physicalMem + swapStats.xsu_total;
      stats.vmtot /= unit;

      // Physical/Virtual memory used
      stats.rssused = (total - free) * pageSize;
      stats.vmused = stats.rssused + swapStats.xsu_used;
      stats.rssused /= unit;
      stats.vmused /= unit;

      // Process virtual and physical memory size
      // Physical memory in this case is the actual memory taken by the process
      // Virtual memory: Most processes are assigned ~4Go of virtual mem whether they use it or not. No idea what is governing this, or the real meaning of it.
      struct task_basic_info_64 taskInfo;
      mach_msg_type_number_t taskInfoCount = TASK_BASIC_INFO_64_COUNT;
      if (KERN_SUCCESS != task_info(mach_task_self(), TASK_BASIC_INFO_64, (task_info_t) &taskInfo, &taskInfoCount))
        std::cerr << "[OSX] - There was a big ass error " << std::endl;
      stats.rssproc = taskInfo.resident_size; // Corresponds to the `Real Mem` column from the Activity Monitor
      stats.rssproc /= unit;
      stats.vmproc = taskInfo.virtual_size; // I was hoping to get the `Memory` column from the Activity Monitor. Haven't figure out a way to do it
      stats.vmproc /= unit;
    }

#elif __linux__ || defined(_POSIX_VERSION)
    void memStats(MemoryStats &stats) {
      struct sysinfo memInfo;
      sysinfo (&memInfo);
      
      // total virtual memory
      stats.vmtot = memInfo.totalram;
      stats.vmtot += memInfo.totalswap;
      stats.vmtot *= memInfo.mem_unit;
      stats.vmtot /= (1024.*1024.);

      // total virtual memory in use
      stats.vmused = memInfo.totalram - memInfo.freeram;
      stats.vmused += memInfo.totalswap - memInfo.freeswap;
      stats.vmused *= memInfo.mem_unit;
      stats.vmused /= (1024.*1024.);
            
      // Total physical memory
      stats.rsstot = memInfo.totalram;
      stats.rsstot *= memInfo.mem_unit;
      stats.rsstot /= (1024.*1024.);
      
      // Total physical memory in use
      stats.rssused = memInfo.totalram - memInfo.freeram;
      stats.rssused *= memInfo.mem_unit;
      stats.rssused /= (1024.*1024.);
      
      // Process virtual memory size and physical memory size
      std::stringstream procstat; procstat << "/proc/" << core::pid() << "/status";
      stats.vmproc = getProcValue(procstat.str().c_str(), "VmSize:")/(1024.);
      stats.rssproc = getProcValue(procstat.str().c_str(), "VmRSS:")/(1024.);
    }
#elif __unix__
    void memStats(MemoryStats &) {
      /* nop */
    }
#else
    void memStats(MemoryStats &) {
      /* nop */
    }
#endif
  }
}
