assert("Process.clock_gettime") do
  Process.clock_gettime(Process::CLOCK_MONOTONIC)
end
