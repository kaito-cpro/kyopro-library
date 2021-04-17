from collections import defaultdict

first_index = defaultdict(int)  # first_index[v] := 値 v が出現する最小の index (1-indexed)
vals = []  # 数列を順次構成していく

now = 2  # 初期値
first_index[now] = 1
vals.append(now)

i = 1
while True:
    i += 1
    now = now * now % 10  # 値の更新
    vals.append(now)
    if first_index[now]:
        break
    first_index[now] = i
    
cycle_start = first_index[now] - 1
cycle_end = i - 1
cycle = cycle_end - cycle_start
# たとえば 2 -> 3 -> 4 -> 5 -> 3 というサイクルの場合
#    cycle_start = 1, cycle_end = 4, cycle = 3,
#    vals = [2, 3, 4, 5, 3].
# vals[cycle_start] と vals[cycle_end] は同じ値
    
# K 番目(0-indexed)の値
K = 3141592
if K < cycle_start:
    ans = vals[K]
else:
    ans = vals[cycle_start + (K - cycle_start) % cycle]

