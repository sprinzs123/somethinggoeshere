from re import L


arr = [0,3,10,2,2,1]

increase = True
decrease = False
prev = arr[0]
l = 0
r = len(arr) - 1

while arr[l] < arr[l+1] and l< len(arr):
    l+=1

while arr[r] < arr[r-1] and r > l:
    r -= 1

print(r)
print(l==r)

print(l)