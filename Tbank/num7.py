def f(num, massiv, index0):
    kopiia = massiv
    kopiia[num-1] = index0
    kol_proideno = 0
    i = 1
    while True:
        if kol_proideno > len(kopiia):
            return False
        if i == 1 and kol_proideno == len(kopiia):
            return True
        elif i == 1 and kol_proideno != len(kopiia) and kol_proideno != 0:
            print(len(kopiia), kol_proideno)
            return False
        else:
            i = kopiia[i-1]
            kol_proideno += 1

n = int(input())
massiv = list(map(int, input().split()))

massiv012 = [0]*n
for i in range(n):
    massiv012[massiv[i]-1] += 1

if massiv012.count(2) != 1 or massiv012.count(0) != 1:
    print(-1, -1)
else:
    for i in range(n):
        if massiv012[i] > 2:
            print(-1, -1)

    index0 = massiv012.index(0)+1
    index2 = massiv012.index(2)+1
    kto_darit_2 = []
    flag = False
    for i in range(n):
        if massiv[i] == index2:
            kto_darit_2.append(i+1)
        if massiv[i] == index2 and i+1 == index2:
            flag = True

    if flag:
        if f(index2, massiv, index0) == True:
            print(index2, index0)
        else:
            print(-1, -1)
    else:
        if f(kto_darit_2[0]-1, massiv, index0) == True:
            print(kto_darit_2[0], index0)
        elif f(kto_darit_2[1]-1, massiv, index0) == True:
            print(kto_darit_2[1], index0)
        else:
            print(-1, -1)