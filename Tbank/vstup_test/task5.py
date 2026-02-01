def count_points(R):
    count = 0
    for x in range(-R, R + 1):
        for y in range(-R, R + 1):
            if x**2 + y**2 <= R**2 :
                count += 1
    return count

n = int(input())
radius = list(map(int, input().split()))
points = [count_points(r) for r in radius]
S = sum(points)
if S % 8 == 0:
    print(0)
else:
    x = 0
    while ((S // 8) - x) != 0:
        S8 = ((S // 8) - x) * 8
        delta = S - S8
        for i in range(delta, 0, -1):
            if i in points and i == delta:
                print(1)
            elif i in points and delta % i == 0 and points.count(i) == (delta // i):
                print(delta // i)
        x += 1