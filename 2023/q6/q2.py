#!/usr/bin/env python3
import sys
maxt = int(sys.stdin.readline().replace(' ', '').split(':')[1])
maxd = int(sys.stdin.readline().replace(' ', '').split(':')[1])
peak_time_1 = maxt>>1
peak_time_2 = (maxt+1)>>1
peak_dist = peak_time_1*(maxt - peak_time_1)
assert(peak_dist > maxd)
lo = 1
hi = peak_time_1
while lo < hi:
    mid = lo + ((hi - lo)>>1);
    dist = mid*(maxt - mid)
    if dist <= maxd:
        lo = mid + 1
    else:
        hi = mid
start_time = lo
lo = peak_time_1
hi = maxt
while lo < hi:
    mid = lo + ((hi - lo)>>1)
    dist = mid*(maxt - mid)
    if dist > maxd:
        lo = mid + 1
    else:
        hi = mid;
end_time = lo
print(end_time - start_time)
r = 0
for t0 in range(1,maxt):
    d = t0*(maxt - t0)
    if d > maxd:
        r += 1
print(r)
