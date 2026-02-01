N, K = map(int, input().split())
cards = list(map(int, input().split()))
Summa = 0
Max_Summa = 0
for i in range(K):
    event = []
    j = 2
    while j < len(cards) + 1:
        summa_event = sum(cards[:j])
        event.append(summa_event)
        j += 1
    S = max(event)
    index_max_S = event.index(S)

    Summa += S
    cards = [S] + cards[index_max_S+2:]
    if Max_Summa < Summa:
        Max_Summa = Summa
print(Max_Summa)